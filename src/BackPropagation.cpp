//
//  BackPropagation.cpp
//  SimpleFFNet
//
//  Created by Phil McCarthy on 04/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#include "BackPropagation.h"


BackPropagation::BackPropagation(double learningRate) :
m_learningRate(learningRate)
{
}

BackPropagation::~BackPropagation()
{
}

const std::pair<VectorXd, VectorXd>& BackPropagation::NextTrainingPattern()
{
    return ILearningAlgorithm::no_more_patterns;
}

void BackPropagation::AdjustWeights(const VectorXd& outputPattern, MatrixXd& hiddenWeights, MatrixXd& outputWeights)
{
}