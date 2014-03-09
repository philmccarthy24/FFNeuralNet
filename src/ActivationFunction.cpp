//
//  ExprTkFunction.cpp
//  SimpleFFNet
//
//  Created by Phil McCarthy on 07/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#include "ActivationFunction.h"
#include "exprtk.hpp"
#include <sstream>
#include "FFNetExceptions.h"

// private data we want hidden from client code (to reduce library dependencies
// and not require client knowledge of ExprTk). this is the pimpl / d pointer pattern.
class ActivationFunction::ExprTkWrapper
{
public:
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;
    typedef exprtk::parser_error::type error_t;
    
    ExprTkWrapper() :
        boundVariable(0.0),
        isInitialised(false)
    {
    }

    void CompileExpression(const std::string& expressionString)
    {
        symbolTable.add_variable("x", boundVariable);
        symbolTable.add_constants();
        
        expression.register_symbol_table(symbolTable);
        
        if (!parser.compile(expressionString, expression))
        {
            std::stringstream sstr;
            sstr << parser.error() << std::endl;
            
            for (std::size_t i = 0; i < parser.error_count(); ++i)
            {
                error_t error = parser.get_error(i);
                sstr << "Error: " << static_cast<int>(i) << " Position: " << static_cast<int>(error.token.position);
                sstr << " Type: [" << exprtk::parser_error::to_str(error.mode) << "] Msg: " << error.diagnostic;
            }
            
            throw InvalidExpressionException(expressionString, sstr.str());
        }
        isInitialised = true;
    }
    
    double Evaluate(double x)
    {
        if (!isInitialised)
        {
            // can't evaluate expression that hasn't been set
            throw InvalidExpressionException("", "no expression specified - was Init() called?");
        }
        boundVariable = x;
        return expression.value();
    }
    
private:
    symbol_table_t symbolTable;
    expression_t expression;
    parser_t parser;
    double boundVariable;
    bool isInitialised;
};

ActivationFunction::ActivationFunction()
    : m_impl(std::unique_ptr<ExprTkWrapper>(new ActivationFunction::ExprTkWrapper))
{
}

ActivationFunction::ActivationFunction(const std::string& expressionString)
    : m_impl(std::unique_ptr<ExprTkWrapper>(new ActivationFunction::ExprTkWrapper)),
    m_expressionString(expressionString)
{
    Init();
}

ActivationFunction::~ActivationFunction()
{
}

double ActivationFunction::f(double x)
{
    return m_impl->Evaluate(x);
}

void ActivationFunction::Init()
{
    // compile ExprTk expression from string
    m_impl->CompileExpression(m_expressionString);
}

