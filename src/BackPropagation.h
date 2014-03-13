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
#include <vector>

class BackPropagation : public ILearningAlgorithm
{
public:
    BackPropagation(double learningRate, double targetNetworkError, int iterationLimit, const std::vector<exemplar>& trainingSet);
    virtual ~BackPropagation();
    
    virtual void AdjustWeights(const VectorXd& hiddenActivations, const VectorXd& outputPattern, MatrixXd& hiddenWeights, MatrixXd& outputWeights) const override;
    
protected:
    virtual const exemplar* GetNextExemplar() override;
    
private:
    double m_learningRate;   // eta
    double m_targetNetworkError;
    double m_cumulativeNetworkError;
    const std::vector<exemplar>& m_trainingSet;
    
    // vars for exemplar provisioning
    std::vector<exemplar*> m_ExemplarQueue;
    exemplar* m_pCurrentExemplar;
};

#endif /* defined(__SimpleFFNet__BackPropagation__) */
