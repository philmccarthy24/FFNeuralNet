//
//  LearningAlgorithm.h
//  SimpleFFNet
//
//  Created by Phil McCarthy on 04/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#ifndef SimpleFFNet_LearningAlgorithm_h
#define SimpleFFNet_LearningAlgorithm_h

#include <Eigen/Dense>

using namespace Eigen;

class ILearningAlgorithm
{
public:
    virtual ~ILearningAlgorithm() {};
    
    virtual const std::pair<VectorXd, VectorXd>& GetNextTrainingPattern() const = 0;
    virtual void AdjustWeights(const VectorXd& outputPattern, MatrixXd& hiddenWeights, MatrixXd& outputWeights) const = 0;
    
    static const std::pair<VectorXd, VectorXd> no_more_patterns;
};

#endif
