//
//  EigenUtilTests.cpp
//  TestRunner
//
//  Created by Phil McCarthy on 09/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#include <stdio.h>
#include "catch/catch.hpp"
#include "FFNeuralNetImpl.h"

TEST_CASE( "Test neural net correct evaluation", "[FFNeuralNetImpl]" )
{
    MatrixXd hiddenLayer(2, 3);
    MatrixXd outputLayer(1, 3);
    
    hiddenLayer << -40.0, 20.0, 10.0,       // 01 feature detector
                    20.0, -40.0, 10.0;      // 10 feature detector
    outputLayer << 20.0, 20.0, 10.0;        // OR gate
    
    FFNeuralNetImpl xornet(2, hiddenLayer, outputLayer, "1/(1+exp(-x))");
    
    std::vector<double> inputs;
    inputs.resize(2);
    
    // demonstrate correct inputs and outputs - go through truth table
    typedef unsigned char byte;
    for (byte b = 0; b < 4; b++)
    {
        // set the input activations
        inputs[0] = (b & 0x01) ? 1.0 : 0.0;
        inputs[1] = (b & 0x02) ? 1.0 : 0.0;
        
        std::vector<double> output = xornet.Evaluate(inputs);
        REQUIRE(output.size() == 1);
        
        double outputActivation = output.back();
        double expectedActivation = (inputs[0] != inputs[1]) ? 1.0 : 0.0; // xor test case
        
        REQUIRE(outputActivation == Approx(expectedActivation).epsilon(0.01));
    }
}


// Next up: test that we can fill matrices with noise correctly!

