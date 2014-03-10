//
//  TrainingSetIterator.h
//  FFNeuralNet
//
//  Created by Phil McCarthy on 10/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#ifndef __FFNeuralNet__TrainingSetIterator__
#define __FFNeuralNet__TrainingSetIterator__

#include <Eigen/Dense>

using namespace Eigen;

class ILearningAlgorithm;

typedef std::pair<VectorXd, VectorXd> exemplar;

// syntactic sugar class for range-based for.
// allows iteration over a training set until
// a particular training condition is met (the condition
// being internal to and managed by an ILearningAlgorithm
// implementation)
class training_set_iterator
{
    friend class ILearningAlgorithm;
public:
    const exemplar& operator *() const;
    training_set_iterator& operator ++();
    bool operator ==(const training_set_iterator &other) const;
    bool operator !=(const training_set_iterator &other) const;
    
protected:
    training_set_iterator(ILearningAlgorithm& learningAlgorithm,
                          const exemplar* pExemplar);
    
private:
    const exemplar* m_pCurrentExemplar;
    ILearningAlgorithm& m_parent;
    const exemplar m_empty; // dummy empty exemplar
};

#endif /* defined(__FFNeuralNet__TrainingSetIterator__) */
