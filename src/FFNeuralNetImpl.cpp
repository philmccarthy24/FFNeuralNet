//
//  FFNeuralNet.cpp
//  SimpleFFNet
//
//  Created by Phil McCarthy on 01/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#include "FFNeuralNetImpl.h"
#include <math.h>


FFNeuralNetImpl::FFNeuralNetImpl(long inputUnitCount, long hiddenUnitCount, long outputUnitCount) :
m_inputUnitCount(inputUnitCount),
// m is number of neurons in layer, n is input weights from prev layer + 1 bias weight (threshold simplification)
m_HiddenLayer(hiddenUnitCount, inputUnitCount + 1),
m_OutputLayer(outputUnitCount, hiddenUnitCount + 1)
{
    //TODO: last n (col val) is 1 (bias)
}


///////////////////////////////////////////////////////////////////////////
/// Perform the actual activation of the neural net: for a given set of
/// inputs, one for each unit in the input layer, calculate what the
/// activations would be in the output layer.
///
/// \param [in] VectorXd inputActivations - vector of input activations.
///             inputActivations size must be equal to inputUnitCount + 1,
///             and last value must be -1 bias value.
/// \return std::vector<double> - the list of output unit activations. the
///                     size of this vector == outputUnitCount
VectorXd FFNeuralNetImpl::Evaluate(VectorXd inputActivations) const
{
    // get input activations as an "Eigen" lib vector so we can do linear algebra on it
    VectorXd inputActivations(inputs.size() + 1);
    for (double x : inputs)
    {
        inputActivations << x;
    }
    // add bias
    inputActivations << -1;
    
    // calculate hidden layer net inputs
    VectorXd hiddenNetInputs = inputActivations * m_HiddenLayer;
    
    // calculate hidden layer activations
    VectorXd hiddenActivations = hiddenNetInputs.unaryExpr(std::ptr_fun(Sigmoid));
    
    // calculate output layer net inputs
    VectorXd outputNetInputs = hiddenActivations * m_OutputLayer;
    
    // calculate output layer activations
    VectorXd outputActivations = outputNetInputs.unaryExpr(std::ptr_fun(Sigmoid));
    
    // convert math vector back to stl vector
    std::vector<double> outputs;
    for (int k = 0; k < outputActivations.count(); k++)
    {
        outputs.push_back(outputActivations(k));
    }
    
    return outputs;
}
        
        
void FFNeuralNetImpl::Train(std::unique_ptr<ILearningAlgorithm> pTrainer)
{
}


///////////////////////////////////////////////////////////////////////////
/// Sigmoid function to squash the netInput to a value y where 0<y<1.
/// Asymptotic S curve like a smoothed off step function.
///
/// \param [in] double netInput - the input to the function, sum of products
///                     of weights and previous layer activations.
/// \return double - a smooth activation y where 0<y<1.
double FFNeuralNetImpl::Sigmoid(double netInput)
{
	return 1 / (1 + exp(-netInput));
}