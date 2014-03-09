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

// note - expression string must contain 'x' as its unary operand / variable
class ActivationFunction
{
public:
    ActivationFunction();
    ActivationFunction(const std::string& expressionString);
    virtual ~ActivationFunction();
    
    virtual double f(double x);
    
private:
    friend class boost::serialization::access;
    
    // When the class Archive corresponds to an output archive, the
    // & operator is defined similar to <<.  Likewise, when the class Archive
    // is a type of input archive the & operator is defined similar to >>.
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
        // compile the expression ready for use
        Init();
    }
    
    void Init();
    
    std::string m_expressionString;
    
    class ExprTkWrapper;
    std::unique_ptr<ExprTkWrapper> m_impl;
};

#endif /* defined(__SimpleFFNet__ExprTkFunction__) */
