//
//  EigenUtilTests.cpp
//  TestRunner
//
//  Created by Phil McCarthy on 09/03/2014.
//  Copyright (c) Phil McCarthy all rights reserved.
//

#include <stdio.h>
#include "LayeredFeedForwardNeuralNet.h"
#include "BackPropagation.h"

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

static const TrainingSet BuildXorTrainingSet()
{
    TrainingSet trainingSet;
    trainingSet.push_back(std::make_pair((VectorXd(2) << 0.0, 0.0).finished(), VectorXd::Constant(1, 0.0)));
    trainingSet.push_back(std::make_pair((VectorXd(2) << 0.0, 1.0).finished(), VectorXd::Constant(1, 1.0)));
    trainingSet.push_back(std::make_pair((VectorXd(2) << 1.0, 0.0).finished(), VectorXd::Constant(1, 1.0)));
    trainingSet.push_back(std::make_pair((VectorXd(2) << 1.0, 1.0).finished(), VectorXd::Constant(1, 0.0)));
    return trainingSet;
}

// create the XOR training set
static const TrainingSet trainingSet = BuildXorTrainingSet();


// test that the basic evaluation works as expected.
TEST_CASE( "Test neural net correct evaluation", "LayeredFeedForwardNeuralNet" )
{
    MatrixXd hiddenLayer(2, 3);
    MatrixXd outputLayer(1, 3);
    
    hiddenLayer << -40.0, 20.0, 10.0,       // 01 feature detector
                    20.0, -40.0, 10.0;      // 10 feature detector
    outputLayer << 20.0, 20.0, 10.0;        // OR gate
    
    LayeredFeedForwardNeuralNet xornet({2, 2, 1}, "1/(1+exp(-x))");
    xornet.SetLayerInputWeights(hiddenLayer, 1);
    xornet.SetLayerInputWeights(outputLayer, 2);
    
    VectorXd inputs(2);
    
    // demonstrate correct inputs and outputs - go through truth table
    for (const Exemplar& exemplar : trainingSet)
    {
        VectorXd output = xornet.Evaluate(exemplar.first);
        REQUIRE(output.size() == 1);
        REQUIRE(output(0) == Approx(exemplar.second(0)).epsilon(0.01));
    }
}


// test that we can fill matrices with noise correctly.
TEST_CASE( "Test neural net weight matrix initialisation", "FFNetUtil" )
{
    MatrixXd testMatrix(3, 3);
    
    // initialise the weights of the matrix with random values
    FFNetUtil::FillNoise(testMatrix, -2.0, 2.0);
    
    // set the last column in the weight matrix to the 1 weight bias value
    testMatrix.col(2).fill(1.0);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (j < 2)
            {
                REQUIRE(testMatrix(i, j) != 0.0); // ! incredibly rarely it might be 0.0 - so not a fantastic unit test.
            } else {
                REQUIRE(testMatrix(i, j) == 1.0);
            }
        }
    }
}

// test backprop learning using the simple xor test case
TEST_CASE( "Test neural net backprop for xor test case", "LayeredFeedForwardNeuralNet" )
{
    // create the neural net
    LayeredFeedForwardNeuralNet xornet({2, 2, 1}, "1/(1+exp(-x))");
    
    // train the net
    const double ETA = 20.0; // this is quite a big learning rate, but seems to converge to a result after ~1000 or so training set iterations.
    const double TARGET_ERROR = 0.0001;
    const long SOME_LARGE_LIMIT = 10000;
    BackPropagation backProp(ETA, TARGET_ERROR, SOME_LARGE_LIMIT);
    backProp.TrainNeuralNetwork(xornet, trainingSet);
    
    for (const Exemplar& exemplar : trainingSet)
    {
        VectorXd output = xornet.Evaluate(exemplar.first);
        REQUIRE(output.size() == 1);
        REQUIRE(output(0) == Approx(exemplar.second(0)).epsilon(0.01));
    }
}