//
//  FFNetExceptions.h
//  FFNeuralNet
//
//  Created by Phil McCarthy on 08/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#ifndef FFNeuralNet_FFNetExceptions_h
#define FFNeuralNet_FFNetExceptions_h

#include <stdexcept>
#include <sstream>

// exception thrown if expression is not a valid unary maths function
class InvalidExpressionException : public std::invalid_argument
{
public:
    explicit InvalidExpressionException(const std::string& expression, const std::string& error) :
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
        
class NeuralNetTopologyMismatch : public std::invalid_argument
{
public:
    explicit NeuralNetTopologyMismatch(const std::string& message) :
    std::invalid_argument(message)
    {
    }
    virtual ~NeuralNetTopologyMismatch()
    {
    }
};
        
class InvalidLearningAlgorithmState : public std::runtime_error
{
public:
    explicit InvalidLearningAlgorithmState(const std::string& what_arg) :
    std::runtime_error(what_arg)
    {
    }
};

#endif
