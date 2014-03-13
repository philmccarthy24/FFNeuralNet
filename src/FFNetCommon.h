//
//  FFNetCommon.h
//  FFNeuralNet
//
//  Created by Phil McCarthy on 11/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#ifndef FFNeuralNet_FFNetCommon_h
#define FFNeuralNet_FFNetCommon_h

#include <Eigen/Dense>

using namespace Eigen;

// define exemplar type
typedef std::pair<VectorXd, VectorXd> exemplar;

// general global function to allow matrices to be serialised via boost.
namespace boost
{
    template<class Archive, typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
    inline void serialize(Archive & ar,
                          Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> & t,
                          const unsigned int file_version)
    {
        for (size_t i = 0; i < t.size(); i++)
        {
            ar & t.data()[i];
        }
    }
}

namespace FFNetUtil
{
    void FillNoise(MatrixXd& matrixToFill, double min, double max);
    
    double GenerateRandomDouble(double min, double max);
    int GenerateRandomInteger(int min, int max);
}

#endif
