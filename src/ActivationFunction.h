//
//  ExprTkFunction.h
//  SimpleFFNet
//
//  Created by Phil McCarthy on 07/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#ifndef __SimpleFFNet__ExprTkFunction__
#define __SimpleFFNet__ExprTkFunction__

#include <iostream>
#include "StorableUnaryFunction.h"

class ActivationFunction : public IStorableUnaryFunction
{
public:
    ActivationFunction(std::istream& inStream);
    ActivationFunction(const std::string& expression, const std::string& unaryOperandVarName);
    virtual ~ActivationFunction();
    
    virtual double f(double x) override;
    virtual void Load(std::istream& inStream) override;
    virtual void Store(std::ostream& outStream) override;
    
private:
    std::string m_expressionString;
    std::string m_unaryOperand;
    
    class ExprTkWrapper;
    std::unique_ptr<ExprTkWrapper> m_impl;
};

#endif /* defined(__SimpleFFNet__ExprTkFunction__) */
