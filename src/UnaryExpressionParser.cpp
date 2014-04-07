//
//  UnaryExpressionParser.cpp
//  FFNeuralNet
//
//  Created by Phil McCarthy on 22/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#include "UnaryExpressionParser.h"
#include <cmath>

// currently this is a dummy implementation that just gives the unipolar sigmoid.
// parsing math expressions and finding the derivative is a project in its own right
// (fun with RPN, Railyard Shunting Algorithm and abstract parse trees for another time!)
class DummyParser_UnipolarSigmoid : public IUnaryExpressionParser
{
public:
    virtual ~DummyParser_UnipolarSigmoid()
    {
    }
    
    // hardcoded to return the unipolar sigmoid
    virtual UnaryFunction GetFunctionForExpression(const std::string& unaryExpression) override
    {
        return [] (double x) -> double
        {
            return 1 / (1 + exp(-x));
        };
    }
};

// hard coded to return unipolar sigmoid derivative
class DummyParser_UnipolarSigmoidDerivative : public IUnaryExpressionParser
{
public:
    virtual ~DummyParser_UnipolarSigmoidDerivative()
    {
    }
    
    // hardcoded to return the derivative of the unipolar sigmoid
    virtual UnaryFunction GetFunctionForExpression(const std::string& unaryExpression) override
    {
        return [] (double y) -> double
        {
            return y * (1 - y);
        };
    }
};



std::shared_ptr<IUnaryExpressionParser> UnaryExpressionParserFactory::CreateParser()
{
    return std::make_shared<DummyParser_UnipolarSigmoid>();
}

std::shared_ptr<IUnaryExpressionParser> UnaryExpressionParserFactory::CreateDerivativeParser()
{
    return std::make_shared<DummyParser_UnipolarSigmoidDerivative>();
}