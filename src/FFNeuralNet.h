//
//  FFNeuralNet.h
//  SimpleFFNet
//
//  Created by Phil McCarthy on 04/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#ifndef SimpleFFNet_FFNeuralNet_h
#define SimpleFFNet_FFNeuralNet_h

#include <memory>
#include <vector>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

class FFNeuralNetImpl; // Not defined here

// class to represent a 3 layer (input-hidden-output) feed forward neural net.
class FFNeuralNet
{
public:
    FFNeuralNet(); // for deserialisation use only
    FFNeuralNet(long inputUnitCount,
                long hiddenUnitCount,
                long outputUnitCount,
                const std::string& activationFunction = "1/(1+exp(-x))"); // unipolar sigmoid as default
    
    std::vector<double> Evaluate(const std::vector<double>& inputs) const;
    
private:
    //////// boost serialization ///////////////////////////
    friend class boost::serialization::access;
    
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & m_impl;
    }
    ////////////////////////////////////////////////////////
    
    // private implementation
    std::unique_ptr<FFNeuralNetImpl> m_impl;
};

#endif
