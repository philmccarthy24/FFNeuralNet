//
//  BackPropagation.h
//  SimpleFFNet
//
//  Created by Phil McCarthy on 04/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#ifndef __SimpleFFNet__BackPropagation__
#define __SimpleFFNet__BackPropagation__

#include "SupervisedLearningAlgorithm.h"
#include <vector>

class BackPropagation : public ISupervisedLearningAlgorithm
{
public:
    BackPropagation(double learningRate, double targetNetworkError, long iterationLimit);
    virtual ~BackPropagation();
    
    virtual void TrainNeuralNetwork(LayeredFeedForwardNeuralNet& networkToTrain, const TrainingSet& trainingSet) const override;
    
    virtual double CalculateNetworkError(LayeredFeedForwardNeuralNet& networkToTrain, const TrainingSet& trainingSet) const override;
    
private:
    double m_learningRate;   // eta
    double m_targetNetworkError;
    long m_iterationLimit;
};

#endif /* defined(__SimpleFFNet__BackPropagation__) */
