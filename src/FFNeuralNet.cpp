//
//  FFNeuralNet.cpp
//  SimpleFFNet
//
//  Created by Phil McCarthy on 04/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#include "FFNeuralNetImpl.h"
#include "FFNeuralNet.h"

using namespace Eigen;

FFNeuralNet::FFNeuralNet()
    : m_impl(nullptr)
{
}

FFNeuralNet::FFNeuralNet(long inputUnitCount,
                         long hiddenUnitCount,
                         long outputUnitCount,
                         const std::string& activationFunction)
    : m_impl(std::unique_ptr<FFNeuralNetImpl>(new FFNeuralNetImpl(inputUnitCount,
                                                                  hiddenUnitCount,
                                                                  outputUnitCount,
                                                                  activationFunction)))
{
}

std::vector<double> FFNeuralNet::Evaluate(const std::vector<double>& inputs) const
{
    return m_impl->Evaluate(inputs);
}