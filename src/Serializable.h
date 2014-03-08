//
//  Serializable.h
//  SimpleFFNet
//
//  Created by Phil McCarthy on 07/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#ifndef SimpleFFNet_Serializable_h
#define SimpleFFNet_Serializable_h

#include <iostream>

class ISerializable
{
public:
    virtual void Load(std::istream& inStream) = 0;
    virtual void Store(std::ostream& outStream) = 0;
};

#endif
