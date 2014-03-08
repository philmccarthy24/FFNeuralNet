//
//  TestRunner.cpp
//  TestRunner
//
//  Created by Phil McCarthy on 07/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#define CATCH_CONFIG_MAIN

#include "ActivationFunction.h"
#include <cmath>
#include <functional>
#include <map>
#include <iostream>
#include "catch/catch.hpp"

// get a map of test data of [input, expected] pairs
static std::map<double, double>
GenerateTestData(double fromRange, double toRange, int numRequired, std::function<double (double)> unaryFunction)
{
    srand((unsigned int)time(nullptr));
    std::map<double, double> testData;
    for (int i = 0; i < numRequired; i++)
    {
        double randomNumber = fromRange + ((double)rand() / RAND_MAX) * (toRange - fromRange);
        testData[randomNumber] = unaryFunction(randomNumber);
    }
    return testData;
}

TEST_CASE( "Test correctness of ActivationFunction expression parsing", "[ActivationFunction]" )
{
    // our code under test
    ActivationFunction sigmoid("1/(1+exp(-netInput))", "netInput");
    
    // generate some test sigmoids
    auto testData = GenerateTestData(-3.0, 3.0, 10,
        [&] (double x) -> double
        {
            return 1 / (1 + exp(-x));
        });
    
    // test actuals against expectations
    for (auto i : testData)
    {
        REQUIRE( sigmoid.f(i.first) == i.second );
    }
}

TEST_CASE( "Test serialisation of ActivationFunction", "[ActivationFunction]" )
{
    // our code under test
    ActivationFunction square("pow(x,2)", "x");
    
    std::ostringstream oss;
    square.Store(oss);
    
    std::cout << oss.str() << std::endl;
    
    std::istringstream iss(oss.str());
    ActivationFunction loaded(iss);
    
    // generate some test data
    auto testData = GenerateTestData(1.0, 3.0, 3,
        [&] (double x) -> double
        {
            return pow(x, 2);
        });
    
    // test actuals against expectations
    for (auto i : testData)
    {
        REQUIRE( loaded.f(i.first) == i.second );
    }
}