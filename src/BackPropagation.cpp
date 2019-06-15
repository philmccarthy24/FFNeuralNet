//
//  BackPropagation.cpp
//  SimpleFFNet
//
//  Created by Phil McCarthy on 04/03/2014.
//  Copyright (c) 2014 Cognitive Research Systems. All rights reserved.
//

#include "BackPropagation.h"
#include <float.h>
#include "FFNetCommon.h"
#include "FFNetExceptions.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "UnaryExpressionParser.h"
#include <deque>

BackPropagation::BackPropagation(double learningRate, double targetNetworkError, long iterationLimit)
    : m_learningRate(learningRate),
    m_targetNetworkError(targetNetworkError),
    m_iterationLimit(iterationLimit)
{
}

BackPropagation::~BackPropagation()
{
}

double BackPropagation::CalculateNetworkError(LayeredFeedForwardNeuralNet& networkToTrain, const TrainingSet& trainingSet) const
{
    // TODO : implement me
    return 0.0;
}

void BackPropagation::TrainNeuralNetwork(LayeredFeedForwardNeuralNet& networkToTrain, const TrainingSet& trainingSet) const
{
    long trainingIterations = 0;
    double cumulativeNetworkError = DBL_MAX;
    TrainingSet trainingSetCopy = trainingSet;
    
    // get activation derivative function for delta rule
    std::shared_ptr<IUnaryExpressionParser> pExpressionParser = UnaryExpressionParserFactory::CreateDerivativeParser();
    UnaryFunction activationDerivative = pExpressionParser->GetFunctionForExpression(networkToTrain.GetActivationFunction());
    
    while (cumulativeNetworkError > m_targetNetworkError && trainingIterations < m_iterationLimit)
    {
        std::cout << "Enet = " << cumulativeNetworkError << std::endl;
        
        // reset network error for new training set iteration.
        cumulativeNetworkError = 0.0;
        
        // begin a new training cycle: put exemplars in random order
        std::random_shuffle(trainingSetCopy.begin(), trainingSetCopy.end());
        
        for (const Exemplar& exemplar : trainingSetCopy)
        {
            // fire the neural network and record activations at each layer
            std::vector<VectorXd> layerActivations;
            layerActivations.push_back(exemplar.first);
            for (long layerIndex = 1; layerIndex < networkToTrain.GetLayerCount(); layerIndex++)
            {
                layerActivations.push_back(
                    networkToTrain.FireSingleLayer(layerActivations[layerIndex - 1], layerIndex)
                );
            }
            
            // deque of errors on each layer (so we can add in reverse order)
            std::deque<VectorXd> layerErrors;
            
            // iterate over the layers in reverse order (back propagating), calculating errors.
            // reverse order because error in below layers is dependent on error of above layers.
            for (long layerIndex = networkToTrain.GetLayerCount() - 1; layerIndex > 0; layerIndex--)
            {
                VectorXd currentLayerError; // what we're trying to calculate
                const VectorXd& currentLayerActivation = layerActivations[layerIndex];
                
                if (layerIndex == networkToTrain.GetLayerCount() - 1)
                {
                    // this is the output layer's error, which is calculated against the known exemplar expected output
                    // Eo = (Do - Yo)Yo([1_0..1_n] - Yo)    for sigmoid (we use generalised delta rule and derivative of activation fn)
                    const VectorXd& expectedOutputPattern = exemplar.second;
                    currentLayerError = (expectedOutputPattern - currentLayerActivation) * currentLayerActivation.unaryExpr(activationDerivative);
                } else {
                    // this is a hidden layer error vector, which is calculated against the above layer's error and input weights.
                    // Ehy = Yh(1 - Yh)Wi^T.Eo    for sigmoid (we use generalised delta rule and derivative of activation fn)
                    MatrixXd aboveLayerInputWeights = networkToTrain.GetLayerInputWeights(layerIndex + 1);
                    const VectorXd& aboveLayerError = layerErrors.front();
                    // when calculating hidden layer errors we don't care about bias weights for the input weights of the above layer.
                    // this is because the "error of the bias unit" in a hidden layer is not used to calculate changes in weights below. so get rid of these to simplify calculation.
                    MatrixXd aboveLayerInputWeightsMinusBias = aboveLayerInputWeights.leftCols(aboveLayerInputWeights.cols() - 1);
                    // note we use cwiseProduct because we want to multiply elements of weighted error vector against deriative of current layer activations.
                    currentLayerError = (aboveLayerInputWeightsMinusBias.transpose() * aboveLayerError).cwiseProduct(currentLayerActivation.unaryExpr(activationDerivative));
                }
                layerErrors.push_front(currentLayerError);
            }
            // push a dummy 0 error to error deque so error/activation stl vector elements line up.
            layerErrors.push_front(VectorXd::Zero(exemplar.first.size()));
            
            // next we need to iterate over errors for each layer (excluding dummy input layer), calculating change in input weights.
            for (long layerIndex = 1; layerIndex < networkToTrain.GetLayerCount(); layerIndex++)
            {
                // get weight matrix to adjust
                MatrixXd weightsToAdjust = networkToTrain.GetLayerInputWeights(layerIndex);
                
                // get previous layer's activations (plus bias value)
                VectorXd previousLayerActivationPlusBias(weightsToAdjust.cols());
                previousLayerActivationPlusBias << layerActivations[layerIndex - 1], VectorXd::Constant(1, -1.0);
                
                // calculate change in weights ΔW = η Yh^T . Eo (where . is outer product)
                MatrixXd layerInputWeightsDelta = (layerErrors[layerIndex] * previousLayerActivationPlusBias.transpose()) * m_learningRate;
                
                // update neural net weights
                weightsToAdjust += layerInputWeightsDelta;
                networkToTrain.SetLayerInputWeights(weightsToAdjust, layerIndex);
                
                //std::cout << "Weights for layer " << layerIndex << " are now:" << std::endl;
                //std::cout << weightsToAdjust << std::endl;
            }
            
            // ok now update the cumulative network error.
            // this is (expected - actual activations) normalised, squared and then halved.
            cumulativeNetworkError += (exemplar.second - layerActivations.back()).squaredNorm() / 2;
            
        } // end for training-set-iteration
        trainingIterations++;
    } // target reached (or iteration limit exceeded). end training.
    
    if (trainingIterations == m_iterationLimit)
    {
        std::cout << "Iteration limit reached - optimisation did not converge on a global minimum." << std::endl;
    } else {
        std::cout << "Target network error reached after " << trainingIterations << " training set iterations." << std::endl;
    }
}