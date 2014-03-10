//
//  EigenUtil.c
//  FFNeuralNet
//
//  Created by Phil McCarthy on 10/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#include <stdio.h>

#include "EigenUtil.h"

namespace EigenUtil
{
    void FillNoise(MatrixXd& matrixToFill, double min, double max)
    {
        srand((unsigned int)time(nullptr));
        
        for (int i = 0; i < matrixToFill.size(); i++)
        {
            double randomNumber = min + ((double)rand() / RAND_MAX) * (max - min);
            matrixToFill(i) = randomNumber;
        }
    }
}