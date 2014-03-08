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

class FFNeuralNetImpl; // Not defined here

// class to represent a 3 layer (input-hidden-output) feed forward neural net.
class FFNeuralNet
{
public:
    FFNeuralNet(long inputUnitCount, long hiddenUnitCount, long outputUnitCount);
    
    std::vector<double> Evaluate(const std::vector<double>& inputs) const;
    
private:
    std::unique_ptr<FFNeuralNetImpl> impl_;
};

#endif
