//
//  BackPropagation.cpp
//  SimpleFFNet
//
//  Created by Phil McCarthy on 04/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#include "BackPropagation.h"
#include <float.h>
#include "FFNetCommon.h"
#include "FFNetExceptions.h"

BackPropagation::BackPropagation(double learningRate, double targetNetworkError, const std::vector<exemplar>& trainingSet)
    : m_learningRate(learningRate),
    m_targetNetworkError(targetNetworkError),
    m_trainingSet(trainingSet),
    m_cumulativeNetworkError(DBL_MAX),
    m_pCurrentExemplar(nullptr)
{
}

BackPropagation::~BackPropagation()
{
    
}

// the backprop algorithm. think of a better way to update private members of neural net class - this feels really clunky
void BackPropagation::AdjustWeights(const VectorXd& hiddenActivations, const VectorXd& outputPattern, MatrixXd& hiddenWeights, MatrixXd& outputWeights) const
{
    if (m_pCurrentExemplar == nullptr)
    {
        throw InvalidLearningAlgorithmState("No current exemplar - is learning algorithm being iterated over?");
    }
    
    // first calculate Eo and Eh (output and hidden unit) activation errors
    const VectorXd& expectedOutputPattern = m_pCurrentExemplar->second;
    const VectorXd& inputPattern = m_pCurrentExemplar->first;
    // Eo = (Do - Yo)Yo([1_0..1_n] - Yo)
    VectorXd Eo = (expectedOutputPattern - outputPattern) * outputPattern * (VectorXd::Constant(outputPattern.size(), 1) - outputPattern);
    // Eh = Yh(1 - Yh)Wi^T.Eo
    VectorXd Eh = hiddenActivations * (VectorXd::Constant(hiddenActivations.size(), 1) - hiddenActivations) * (outputWeights.transpose() * Eo);
    
    // change in output weights ΔWo = η Yh^T . Eo (where . is outer product)
    MatrixXd DeltaWo = m_learningRate * hiddenActivations.transpose() * Eo;
    // update output weights
    outputWeights += DeltaWo;
    
    // change in hidden weights ΔWh = η X^T . Eh
    MatrixXd DeltaWh = m_learningRate * inputPattern.transpose() * Eh;
    // update hidden weights
    hiddenWeights += DeltaWh;
}

const exemplar* BackPropagation::GetNextExemplar()
{
    exemplar* pNext = nullptr;
    if (m_cumulativeNetworkError >= m_targetNetworkError)
    {
        // carry on providing training data
        if (m_ExemplarQueue.empty())
        {
            // fill the queue with exemplars
            for (auto e : m_trainingSet)
            {
                m_ExemplarQueue.push_back(&e);
            }
        } else if (m_ExemplarQueue.size() == 1) {
            m_pCurrentExemplar = m_ExemplarQueue.back();
            pNext = m_pCurrentExemplar;
            m_ExemplarQueue.clear();
        } else {
            // randomly pick an exemplar from the queue
            int randomIndex = FFNetUtil::GenerateRandomInteger(0, static_cast<int>(m_ExemplarQueue.size() - 1));
            m_pCurrentExemplar = m_ExemplarQueue[randomIndex];
            m_ExemplarQueue.erase(m_ExemplarQueue.begin() + randomIndex);
        }
    }
    return pNext;
}