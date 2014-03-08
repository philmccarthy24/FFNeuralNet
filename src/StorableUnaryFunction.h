//
//  StorableUnaryFunction.h
//  SimpleFFNet
//
//  Created by Phil McCarthy on 07/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#ifndef SimpleFFNet_StorableUnaryFunction_h
#define SimpleFFNet_StorableUnaryFunction_h

#include "Serializable.h"
#include <stdexcept>
#include <sstream>

// exception thrown if expression is not a valid unary maths function
class InvalidExpressionException : public std::invalid_argument
{
public:
    InvalidExpressionException(const std::string& expression, const std::string& error) :
        std::invalid_argument(expression),
        m_invalidExpression(expression),
        m_specificError(error)
    {
    }
    virtual ~InvalidExpressionException()
    {
    }
    
    virtual const char* what() const noexcept
    {
        std::stringstream sstr;
        sstr << "Unary expression [" << m_invalidExpression << "] invalid : " << m_specificError << std::endl;
        return sstr.str().c_str();
    }
private:
    std::string m_invalidExpression;
    std::string m_specificError;
};



class IStorableUnaryFunction : public ISerializable
{
public:
    virtual double f(double x) = 0;
};

#endif
