//
//  UnaryExpressionParser.h
//  FFNeuralNet
//
//  Created by Phil McCarthy on 22/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#ifndef __FFNeuralNet__UnaryExpressionParser__
#define __FFNeuralNet__UnaryExpressionParser__

#include <iostream>
#include <functional>

typedef std::function<double (double)> UnaryFunction;

// interface to represent a unary expression parser, that is able to take a string
// representation of a unary math expression, and "generate" a callable function for it.
// this callable function will probably be a lambda that calls into a parse tree
// object instance structure or somesuch.
class IUnaryExpressionParser
{
public:
    virtual ~IUnaryExpressionParser()
    {
    }
    
    // Get an executable function for a unary expression string
    virtual UnaryFunction GetFunctionForExpression(const std::string& unaryExpression) = 0;
};

class UnaryExpressionParserFactory
{
public:
    // makes a parser that for a given unary expression string, gets the equivalent executable function
    static std::shared_ptr<IUnaryExpressionParser> CreateParser();
    
    // makes a parser that for a given unary expression string, gets an executable derivative function
    static std::shared_ptr<IUnaryExpressionParser> CreateDerivativeParser();
};

#endif /* defined(__FFNeuralNet__UnaryExpressionParser__) */
