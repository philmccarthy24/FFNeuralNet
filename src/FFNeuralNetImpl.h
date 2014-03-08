//
//  FFNeuralNet.h
//  SimpleFFNet
//
//  Created by Phil McCarthy on 01/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#ifndef __SimpleFFNet__FFNeuralNet__
#define __SimpleFFNet__FFNeuralNet__

#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include "LearningAlgorithm.h"

using namespace Eigen;

// class to represent a 3 layer (input-hidden-output) feed forward neural net.
class FFNeuralNetImpl
{
public:
    FFNeuralNetImpl(long inputUnitCount, long hiddenUnitCount, long outputUnitCount);
    void Train(std::unique_ptr<ILearningAlgorithm> pTrainer);
    
    VectorXd Evaluate(VectorXd inputActivations) const;
    
private:
    long m_inputUnitCount;
    
    MatrixXd m_HiddenLayer;
    MatrixXd m_OutputLayer;
    
    static double Sigmoid(double netInput);
};

#endif /* defined(__SimpleFFNet__FFNeuralNet__) */
