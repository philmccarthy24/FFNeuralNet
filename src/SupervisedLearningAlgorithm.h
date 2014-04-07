//
//  TrainingStrategy.h
//  FFNeuralNet
//
//  Created by Phil McCarthy on 22/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#ifndef FFNeuralNet_SupervisedLearningAlgorithm_h
#define FFNeuralNet_SupervisedLearningAlgorithm_h

#include <vector>
#include "LayeredFeedForwardNeuralNet.h"

// type for examplars: an input pattern, and an expected output pattern
typedef std::pair<VectorXd, VectorXd> Exemplar;
typedef std::vector<Exemplar> TrainingSet;

class ISupervisedLearningAlgorithm
{
public:
    virtual ~ISupervisedLearningAlgorithm()
    {
    }
    
    virtual void TrainNeuralNetwork(LayeredFeedForwardNeuralNet& networkToTrain, const TrainingSet& trainingSet) const = 0;
    
    virtual double CalculateNetworkError(LayeredFeedForwardNeuralNet& networkToTrain, const TrainingSet& trainingSet) const = 0;
};


#endif
