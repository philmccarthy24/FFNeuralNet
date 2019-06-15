//
//  LayeredFeedForwardNeuralNet.cpp
//  FFNeuralNet
//
//  Created by Phil McCarthy on 22/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#include <iostream>
#include "LayeredFeedForwardNeuralNet.h"
#include "FFNetExceptions.h"
#include "UnaryExpressionParser.h"

LayeredFeedForwardNeuralNet::LayeredFeedForwardNeuralNet()
{
}

// topology is the number of neural units in each layer.
LayeredFeedForwardNeuralNet::LayeredFeedForwardNeuralNet(std::vector<long> topology, const std::string& activationFunction)
: m_activationFunction(activationFunction)
{
    for (size_t idx = 1; idx < topology.size(); idx++)
    {
        // create layer input weight matrix. each row represents
        // the weights of all the links going into a unit in the layer
        // from all the units below. +1 for bias weight (threshold simplification)
        MatrixXd layerInputWeights(topology[idx], topology[idx - 1] + 1);
        
        // initialise the weights of the matrix with random values
        FFNetUtil::FillNoise(layerInputWeights, -2.0, 2.0);
        
        // set the last column in the weight matrix to the 1 weight bias value
        layerInputWeights.col(topology[idx - 1]).fill(1.0);
        
        //std::cout << "initialised to: " << layerInputWeights << std::endl;
        
        
        // finally add the layer to the vector
        m_neuralNetLayerWeights.push_back(layerInputWeights);
    }
}

LayeredFeedForwardNeuralNet::~LayeredFeedForwardNeuralNet()
{
}

///////////////////////////////////////////////////////////////////////////
/// Perform the actual activation of the neural net: for a given set of
/// inputs, one for each unit in the input layer, calculate what the
/// activations would be in the output layer.
///
/// \param [in] VectorXd inputActivations - vector of input activations.
///
/// \return VectorXd - the list of output unit activations. the
///                     size of this vector == outputUnitCount
VectorXd LayeredFeedForwardNeuralNet::Evaluate(const VectorXd& inputActivations) const
{
    VectorXd layerInput = inputActivations;
    // iteratively activate the layers (not the dummy input layer as this is inputActivations).
    for (size_t idx = 1; idx < GetLayerCount(); idx++)
    {
        layerInput = FireSingleLayer(layerInput, idx);
    }
    // (last layer + 1) "input" are the output activations
    return layerInput;
}

VectorXd LayeredFeedForwardNeuralNet::FireSingleLayer(const VectorXd& inputActivations, long layerIndex) const
{
    // get layer input weights (also checks valid layerIndex)
    const MatrixXd& layerInputWeights = GetLayerInputWeights(layerIndex);
    
    if (layerInputWeights.cols() - 1 != inputActivations.size())
    {
        // input is invalid for this neural net topology
        throw NeuralNetTopologyMismatch("activation input must match number of units in neural network layer");
    }
    
    // get the activation function
    auto expressionParser = UnaryExpressionParserFactory::CreateParser();
    UnaryFunction activationFunction = expressionParser->GetFunctionForExpression(m_activationFunction);
    
    // bias activation
    VectorXd bias(1);
    bias << -1.0;
    
    // calculate layer net inputs
    VectorXd inputPlusBias(layerInputWeights.cols());
    inputPlusBias << inputActivations, bias;
    
    //std::cout << "layer " << layerIndex << " input activations +bias : " << std::endl << inputPlusBias << std::endl << std::endl;
    //std::cout << "layer " << layerIndex << " input weights : " << std::endl << layerInputWeights << std::endl << std::endl;
    
    VectorXd layerNetInputs = layerInputWeights * inputPlusBias;
    
    //std::cout << "layer " << layerIndex << " net inputs : " << std::endl << layerNetInputs << std::endl << std::endl;
    
    // calculate layer activations
    VectorXd layerActivations = layerNetInputs.unaryExpr(activationFunction);
    
    //std::cout << "layer " << layerIndex << " output activations : " << layerActivations << std::endl << std::endl;
    
    return layerActivations;
}

// note index is 0 based: 0 -> n-1 (where n = number of network layers). layerIndex=0 is invalid (as dummy layer)
const MatrixXd& LayeredFeedForwardNeuralNet::GetLayerInputWeights(long layerIndex) const
{
    if (layerIndex < 1)
    {
        throw NeuralNetTopologyMismatch("input weights for dummy input layer 0 do not exist.");
    }
    if (layerIndex >= GetLayerCount())
    {
        throw NeuralNetTopologyMismatch("neural unit layer specified does not exist in this neural network topology.");
    }
    
    // get layer input weights
    return m_neuralNetLayerWeights[layerIndex - 1];
}

void LayeredFeedForwardNeuralNet::SetLayerInputWeights(const MatrixXd& layerWeights, long layerIndex)
{
    if (layerIndex < 1)
    {
        throw NeuralNetTopologyMismatch("input weights for dummy input layer 0 do not exist.");
    }
    if (layerIndex >= GetLayerCount())
    {
        throw NeuralNetTopologyMismatch("neural unit layer specified does not exist in this neural network topology.");
    }
    m_neuralNetLayerWeights[layerIndex - 1] = layerWeights;
}

const std::string& LayeredFeedForwardNeuralNet::GetActivationFunction() const
{
    return m_activationFunction;
}

void LayeredFeedForwardNeuralNet::SetActivationFunction(const std::string& activationFunction)
{
    m_activationFunction = activationFunction;
}

long LayeredFeedForwardNeuralNet::GetLayerCount() const
{
    // +1 for dummy input layer (which isn't represented in the layer input weights)
    return m_neuralNetLayerWeights.size() + 1;
}