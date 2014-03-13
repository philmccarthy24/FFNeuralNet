//
//  LearningAlgorithm.h
//  SimpleFFNet
//
//  Created by Phil McCarthy on 04/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#ifndef SimpleFFNet_LearningAlgorithm_h
#define SimpleFFNet_LearningAlgorithm_h

#include "TrainingSetIterator.h"

class ILearningAlgorithm
{
    friend class training_set_iterator;
public:
    virtual ~ILearningAlgorithm()
    {
    };
    
    // begin and end to allow iteration over a training set.
    training_set_iterator begin()
    {
        return training_set_iterator(*this, GetNextExemplar());
    }
    training_set_iterator end()
    {
        return training_set_iterator(*this, nullptr);
    }
    
    virtual void AdjustWeights(const VectorXd& hiddenActivations, const VectorXd& outputPattern, MatrixXd& hiddenWeights, MatrixXd& outputWeights) const = 0;
    
protected:
    // up to implementors to determine the order of exemplars and end condition.
    // to signal no more exemplars, return nullptr.
    // note exemplar input vector size must match number of input units.
    virtual const exemplar* GetNextExemplar() = 0;
};

#endif
