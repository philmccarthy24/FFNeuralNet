//
//  FFNetCommon.cpp
//  FFNeuralNet
//
//  Created by Phil McCarthy on 11/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#include <stdio.h>
#include "FFNetCommon.h"

namespace FFNetUtil
{
    void FillNoise(MatrixXd& matrixToFill, double min, double max)
    {
        for (int i = 0; i < matrixToFill.size(); i++)
        {
            matrixToFill(i) = FFNetUtil::GenerateRandomDouble(min, max);
        }
    }
    
    double GenerateRandomDouble(double min, double max)
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        double frac = (double)rand() / RAND_MAX;
        return min + (frac * (max - min));
    }
    
    int GenerateRandomInteger(int min, int max)
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        return min + (rand() % (max - min) + 1);
    }
}