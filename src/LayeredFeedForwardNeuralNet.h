//
//  LayeredFeedForwardNeuralNet.h
//  FFNeuralNet
//
//  Created by Phil McCarthy on 22/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#ifndef __FFNeuralNet__LayeredFeedForwardNeuralNet__
#define __FFNeuralNet__LayeredFeedForwardNeuralNet__

#include <vector>
#include <Eigen/Dense>
#include "FFNetCommon.h"

using namespace Eigen;



// class to represent an N layer (typically input-hidden-output) feed forward neural net.
class LayeredFeedForwardNeuralNet
{
public:
    LayeredFeedForwardNeuralNet(); // for deserialisation use only
    LayeredFeedForwardNeuralNet(NeuralNetTopology topology, const std::string& activationFunction);
    virtual ~LayeredFeedForwardNeuralNet();
    
    virtual VectorXd Evaluate(const VectorXd& inputActivations) const;
    virtual VectorXd FireSingleLayer(const VectorXd& inputActivations, long layerIndex) const;
    
    // getters and setters
    const MatrixXd& GetLayerInputWeights(long layerIndex) const;
    void SetLayerInputWeights(const MatrixXd& layerWeights, long layerIndex);
    
    const std::string& GetActivationFunction() const;
    void SetActivationFunction(const std::string& activationFunction);
    
    long GetLayerCount() const;
    
private:
    // note layer weights maps to layerIndex-1
    std::vector<MatrixXd> m_neuralNetLayerWeights;
    std::string m_activationFunction;
};

#endif /* defined(__FFNeuralNet__LayeredFeedForwardNeuralNet__) */
