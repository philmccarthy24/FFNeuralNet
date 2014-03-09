//
//  ExprTkFunction.h
//  SimpleFFNet
//
//  Created by Phil McCarthy on 07/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#ifndef __SimpleFFNet__ExprTkFunction__
#define __SimpleFFNet__ExprTkFunction__

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

// note - expression string must contain 'x' as its unary operand / variable,
// and be of the syntax described at http://www.partow.net/programming/exprtk/index.html.
class ActivationFunction
{
public:
    ActivationFunction(); // for deserialisation use only
    ActivationFunction(const std::string& expressionString);
    virtual ~ActivationFunction();
    
    double f(double x) const; // the function clients call
    
private:
    //////// boost serialization stuff /////////////////////
    friend class boost::serialization::access;
    
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        boost::serialization::split_member(ar, *this, version);
    }
    
    template<class Archive>
    void save(Archive & ar, const unsigned int version) const
    {
        ar << m_expressionString;
    }
    
    template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
        ar >> m_expressionString;
        // initialise this expression obj ready for use
        // (which internally does an ExprTk::parser::compile)
        Init();
    }
    /////////////////////////////////////////////////////////
    
    void Init();
    
    std::string m_expressionString;
    
    class ExprTkWrapper;
    std::unique_ptr<ExprTkWrapper> m_impl;
};

#endif /* defined(__SimpleFFNet__ExprTkFunction__) */
