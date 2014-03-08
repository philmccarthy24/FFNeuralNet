//
//  FFNeuralNet.cpp
//  SimpleFFNet
//
//  Created by Phil McCarthy on 04/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#include "FFNeuralNetImpl.h"
#include "FFNeuralNet.h"
#include <Eigen/Dense>

using namespace Eigen;

FFNeuralNet::FFNeuralNet(long inputUnitCount, long hiddenUnitCount, long outputUnitCount) :
impl_(std::unique_ptr<FFNeuralNetImpl>(new FFNeuralNetImpl(inputUnitCount, hiddenUnitCount, outputUnitCount)))
{
}

std::vector<double> FFNeuralNet::Evaluate(const std::vector<double>& inputs) const
{
    // get input activations as an "Eigen" lib vector so we can do linear algebra on it
    VectorXd inputActivations(inputs.size() + 1);
    
    inputActivations.Map(inputs.data(), inputs.size());
    // and add the bias input!
    inputActivations << -1;
    
    VectorXd outputActivations = impl_->Evaluate(inputActivations);
    
    // convert math vector back to stl vector
    std::vector<double> outputs(outputActivations.data(), outputActivations.count());
    
    return outputs;
}