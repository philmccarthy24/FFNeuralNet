//
//  TestRunner.cpp
//  TestRunner
//
//  Created by Phil McCarthy on 07/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#define CATCH_CONFIG_MAIN

#include "ActivationFunction.h"
#include "FFNetExceptions.h"
#include <cmath>
#include <functional>
#include <map>

#include "catch/catch.hpp"

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/stream.hpp>
#include <vector>
#include <iostream>

using namespace boost;

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
    ActivationFunction sigmoid("1/(1+exp(-x))");
    
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
    ActivationFunction square("x^2");
    
    // generate some test data
    auto testData = GenerateTestData(1.0, 3.0, 5,
     [&] (double x) -> double
     {
         return pow(x, 2);
     });
    
    // show the normal function works
    for (auto i : testData)
    {
        REQUIRE( square.f(i.first) == i.second );
    }
    
    // temporary buffer to serialize to/from
    char buffer[256] = {0};
    
    {
        // create oarchive on this buffer
        iostreams::array_sink sink(buffer);
        iostreams::stream<iostreams::array_sink> stream(sink);
        archive::binary_oarchive out_archive(stream);
        
        // serialize object
        out_archive << square;
    }
    
    // load the object back in
    ActivationFunction loaded;
    
    {
        // create iarchive on this buffer
        iostreams::array_source source(buffer);
        iostreams::stream<iostreams::array_source> stream(source);
        archive::binary_iarchive in_archive(stream);
        
        // deserialize object
        in_archive >> loaded;
    }
    
    // test actuals against expectations
    for (auto i : testData)
    {
        REQUIRE( loaded.f(i.first) == i.second );
    }
}

TEST_CASE( "Test uninitialised ActivationFunction throws appropriate exception when used", "[ActivationFunction]" )
{
    ActivationFunction exprNotSet;
    REQUIRE_THROWS_AS(exprNotSet.f(4.32), InvalidExpressionException);
}

TEST_CASE( "Test bad ActivationFunction expression", "[ActivationFunction]" )
{
    REQUIRE_THROWS_AS(ActivationFunction exprNotSet("sqrt(theta^8) * 2 / 12"), InvalidExpressionException);
}
