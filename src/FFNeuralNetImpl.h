//
//  FFNeuralNet.h
//  SimpleFFNet
//
//  Created by Phil McCarthy on 01/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#ifndef __SimpleFFNet__FFNeuralNet__
#define __SimpleFFNet__FFNeuralNet__

#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include "LearningAlgorithm.h"
#include "ActivationFunction.h"
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include "EigenUtil.h"

using namespace Eigen;

// internal implementation class to represent a 3 layer (input-hidden-output) feed forward neural net.
class FFNeuralNetImpl
{
public:
    FFNeuralNetImpl(); // for deserialisation use only
    FFNeuralNetImpl(long inputUnitCount,
                    long hiddenUnitCount,
                    long outputUnitCount,
                    const std::string& activationFunction);
    FFNeuralNetImpl(long inputUnitCount,
                    const MatrixXd& hiddenWeights,
                    const MatrixXd& outputWeights,
                    const std::string& activationFunction);
    virtual ~FFNeuralNetImpl();
    
    void Train(ILearningAlgorithm& learningAlgorithm);
    
    std::vector<double> Evaluate(const std::vector<double>& inputs) const;
    
private:
    //////// boost serialization stuff //////////////////////
    friend class boost::serialization::access;
    
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        boost::serialization::split_member(ar, *this, version);
    }
    
    template<class Archive>
    void save(Archive & ar, const unsigned int version) const
    {
        ar << m_inputUnitCount;
        ar << m_HiddenLayer;
        ar << m_OutputLayer;
        ar << m_activationFunction;
    }
    
    template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
        ar >> m_inputUnitCount;
        ar >> m_HiddenLayer;
        ar >> m_OutputLayer;
        ar >> m_activationFunction;
        m_isInitialised = true;
    }
    ////////////////////////////////////////////////////////
    
    void Evaluate_internal(const VectorXd& inputActivations, VectorXd& outputActivations) const;
    
    long m_inputUnitCount;
    
    MatrixXd m_HiddenLayer;
    MatrixXd m_OutputLayer;
    
    ActivationFunction m_activationFunction;
    
    bool m_isInitialised;
};


#endif /* defined(__SimpleFFNet__FFNeuralNet__) */
