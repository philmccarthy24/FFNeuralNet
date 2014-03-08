//
//  BackPropagation.h
//  SimpleFFNet
//
//  Created by Phil McCarthy on 04/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#ifndef __SimpleFFNet__BackPropagation__
#define __SimpleFFNet__BackPropagation__

#include "LearningAlgorithm.h"
#include <iostream>

class BackPropagation : public ILearningAlgorithm
{
public:
    BackPropagation(double learningRate);
    virtual ~BackPropagation();
    
    virtual const std::pair<VectorXd, VectorXd>& NextTrainingPattern() override;
    virtual void AdjustWeights(const VectorXd& outputPattern, MatrixXd& hiddenWeights, MatrixXd& outputWeights) override;
    
private:
    double m_learningRate;

};

#endif /* defined(__SimpleFFNet__BackPropagation__) */
