//
//  TrainingSetIterator.cpp
//  FFNeuralNet
//
//  Created by Phil McCarthy on 10/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#include "TrainingSetIterator.h"
#include "LearningAlgorithm.h"

training_set_iterator::training_set_iterator(ILearningAlgorithm& learningAlgorithm,
                                             const exemplar* pExemplar)
: m_parent(learningAlgorithm),
m_pCurrentExemplar(pExemplar),
m_empty(VectorXd::Zero(1), VectorXd::Zero(1))
{
}

const exemplar& training_set_iterator::operator *() const
{
    if (m_pCurrentExemplar == nullptr)
    {
        // not pointing to any exemplar - so return
        // pair of vectors with single 0 element.
        return m_empty;
    }
    return *m_pCurrentExemplar;
}

training_set_iterator& training_set_iterator::operator ++()
{
    if (m_pCurrentExemplar != nullptr)
    {
        // only iterate if there are exemplars left in training set
        m_pCurrentExemplar = m_parent.GetNextExemplar();
    }
    return *this;
}

bool training_set_iterator::operator ==(const training_set_iterator &other) const
{
    return m_pCurrentExemplar == other.m_pCurrentExemplar;
}

bool training_set_iterator::operator !=(const training_set_iterator &other) const
{
    return !operator==(other);
}