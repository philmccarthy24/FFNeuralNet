//
//  FFNeuralNet.cpp
//  SimpleFFNet
//
//  Created by Phil McCarthy on 01/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#include "FFNeuralNetImpl.h"
#include "FFNetExceptions.h"
#include <math.h>

FFNeuralNetImpl::FFNeuralNetImpl()
    : m_inputUnitCount(0),
    m_isInitialised(false)
{
}

FFNeuralNetImpl::FFNeuralNetImpl(long inputUnitCount,
                                 const MatrixXd& hiddenWeights,
                                 const MatrixXd& outputWeights,
                                 const std::string& activationFunction)
    : m_inputUnitCount(inputUnitCount),
    m_HiddenLayer(hiddenWeights),
    m_OutputLayer(outputWeights),
    m_activationFunction(activationFunction),
    m_isInitialised(true)
{
}

FFNeuralNetImpl::FFNeuralNetImpl(long inputUnitCount,
                                 long hiddenUnitCount,
                                 long outputUnitCount,
                                 const std::string& activationFunction)
    : m_inputUnitCount(inputUnitCount),
    // m is number of neurons in layer, n is input weights from prev layer
    m_HiddenLayer(hiddenUnitCount, inputUnitCount + 1),  // + 1 bias weight (threshold simplification)
    m_OutputLayer(outputUnitCount, hiddenUnitCount + 1),  // + 1 bias weight (threshold simplification)
    m_activationFunction(activationFunction),
    m_isInitialised(true)
{
    // initialise the weight matrices with random values
    EigenUtil::FillNoise(m_HiddenLayer, -2.0, 2.0);
    EigenUtil::FillNoise(m_OutputLayer, -2.0, 2.0);
    
    // set the last column in each weight matrix to the 1 weight bias value
    m_HiddenLayer.col(inputUnitCount).fill(1.0);
    m_OutputLayer.col(hiddenUnitCount).fill(1.0);
    
    // debug output
    std::cout << "Initial weight matrices:" << std::endl;
    std::cout << "Hidden layer input weights:" << std::endl << m_HiddenLayer << std::endl;
    std::cout << "Output layer input weights:" << std::endl << m_OutputLayer << std::endl;
}

FFNeuralNetImpl::~FFNeuralNetImpl()
{
}

///////////////////////////////////////////////////////////////////////////
/// Perform the actual activation of the neural net: for a given set of
/// inputs, one for each unit in the input layer, calculate what the
/// activations would be in the output layer.
///
/// \param [in] VectorXd inputActivations - vector of input activations.
///
/// \return std::vector<double> - the list of output unit activations. the
///                     size of this vector == outputUnitCount
std::vector<double> FFNeuralNetImpl::Evaluate(const std::vector<double>& inputs) const
{
    // fill the math vector
    VectorXd inputActivations = Map<const VectorXd> (inputs.data(), inputs.size());
    
    VectorXd outputActivations;
    Evaluate_internal(inputActivations, outputActivations);
    
    std::vector<double> outputs(outputActivations.data(),
                                outputActivations.data() + outputActivations.size());
    return outputs;
}

void FFNeuralNetImpl::Evaluate_internal(const VectorXd& inputActivations, VectorXd& outputActivations) const
{
    if (inputActivations.size() != m_inputUnitCount)
    {
        // input is invalid for this neural net topology
        throw NeuralNetTopologyMismatch("activation input must match number of activation units");
    }
    
    // bias activation
    VectorXd bias(1);
    bias << -1.0;
    
    // calculate hidden layer net inputs
    VectorXd inputPlusBias(m_inputUnitCount + 1);
    inputPlusBias << inputActivations, bias;
    
    std::cout << "input +b : " << inputPlusBias << std::endl << std::endl;
    std::cout << "hidden weights : " << m_HiddenLayer << std::endl << std::endl;
    
    VectorXd hiddenNetInputs = m_HiddenLayer * inputPlusBias;
    
    std::cout << "hidden net inputs : " << hiddenNetInputs << std::endl << std::endl;
    
    // calculate hidden layer activations
    VectorXd hiddenActivations = hiddenNetInputs.unaryExpr(
       [&] (double x) -> double
       {
           return m_activationFunction.f(x);
       });
    
    // calculate output layer net inputs
    VectorXd hiddenPlusBias(m_HiddenLayer.rows() + 1);
    hiddenPlusBias << hiddenActivations, bias;
    
    std::cout << "hidden activations +b : " << hiddenPlusBias << std::endl << std::endl;
    std::cout << "output weights : " << m_OutputLayer << std::endl << std::endl;
    
    VectorXd outputNetInputs = m_OutputLayer * hiddenPlusBias;
    
    std::cout << "output net inputs : " << outputNetInputs << std::endl << std::endl;
    
    // calculate output layer activations
    outputActivations = outputNetInputs.unaryExpr(
       [&] (double x) -> double
       {
           return m_activationFunction.f(x);
       });
    
    std::cout << "output activations : " << outputActivations << std::endl << std::endl;
}

void FFNeuralNetImpl::Train(ILearningAlgorithm& learningAlgorithm)
{
    for (auto exemplar : learningAlgorithm)
    {
        VectorXd outputActivations;
        Evaluate_internal(exemplar.first, outputActivations);
        learningAlgorithm.AdjustWeights(outputActivations, m_HiddenLayer, m_OutputLayer);
    }
}