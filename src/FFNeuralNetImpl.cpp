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
                                 long hiddenUnitCount,
                                 long outputUnitCount,
                                 const std::string& activationFunction)
    : m_inputUnitCount(inputUnitCount),
    // m is number of neurons in layer, n is input weights from prev layer + 1 bias weight (threshold simplification)
    m_HiddenLayer(hiddenUnitCount, inputUnitCount + 1),
    m_OutputLayer(outputUnitCount, hiddenUnitCount + 1),
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
    VectorXd inputActivations(m_inputUnitCount + 1);
    
    // validate function input
    size_t inputCount = inputs.size();
    if (inputCount == m_inputUnitCount + 1)
    {
        // abnormal case - check if client has pre-added bias value
        if (inputs.back() == -1)
        {
            // caller has pre-added bias value. we can handle the input below
            inputCount--;
        }
        else
        {
            throw NeuralNetTopologyMismatch("activation input must match number of activation units");
        }
    }
    if (inputCount == m_inputUnitCount)
    {
        // usual case - one activation value per input unit
        // we need to add -1 bias value
        for (double d : inputs)
        {
            inputActivations << d;
        }
        inputActivations << -1.0;
    }
    else
    {
        // input is invalid for this neural net topology
        throw NeuralNetTopologyMismatch("activation input must match number of activation units");
    }
    
    // calculate hidden layer net inputs
    VectorXd hiddenNetInputs = inputActivations * m_HiddenLayer;
    
    // calculate hidden layer activations
    VectorXd hiddenActivations = hiddenNetInputs.unaryExpr(
       [&] (double x) -> double
       {
           return m_activationFunction.f(x);
       });
    
    // calculate output layer net inputs
    VectorXd outputNetInputs = hiddenActivations * m_OutputLayer;
    
    // calculate output layer activations
    VectorXd outputActivations = outputNetInputs.unaryExpr(
       [&] (double x) -> double
       {
           return m_activationFunction.f(x);
       });
    
    // convert math vector back to stl vector
    std::vector<double> outputs;
    for (int k = 0; k < outputActivations.size(); k++)
    {
        outputs.push_back(outputActivations[k]);
    }
    
    return outputs;
}
        
        
void FFNeuralNetImpl::Train(const ILearningAlgorithm& learningAlgorithm)
{
    for (const auto& p = learningAlgorithm.GetNextTrainingPattern();
         p != ILearningAlgorithm::no_more_patterns;
         p = learningAlgorithm.GetNextTrainingPattern())
    {
        // what to do here?
    }
    bool bContinueLearning = true;
    while (bContinueLearning)
    {
        
    }learningAlgorithm.GetNextTrainingPattern()
}