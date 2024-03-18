#include <stdio.h>
#include "utils.h"
#include "networking.h"
#include "structs.h"


void SetNeuronValues(struct network net, char* expectedValues) //sets the NVs for the given expectedValues[]
{
    int L = net.NumberOfLayers - 1;
    for (int k = 0; k < net.Layers[L].Length; k++)//loop on the last layer
    {
        net.Layers[L].Neurons[k].NeuronValue = 2 * (net.Layers[L].Neurons[k].Value - expectedValues[k]);
    }

    L--;

    double sum;
    while (L > 0) // we don't want to loop on the first layer bc values are useless
    {
        for (int k = 0; k < net.Layers[L].Length; k++)
        {
            sum = 0;
            for (int j = 0; j<net.Layers[L+1].Length; j++)
            {
                sum += net.Layers[L+1].Neurons[j].Weights[k] * SigmoidPrime(net.Layers[L+1].Neurons[j].Z) * net.Layers[L+1].Neurons[j].NeuronValue;
            }

            net.Layers[L].Neurons[k].NeuronValue = sum;
        }
        L--;
    }
}

void SetGradients(struct network net)//adds the gradients for a given value
{
    for (int layerIndex = 1; layerIndex < net.NumberOfLayers; layerIndex++)
    {
        for(int j = 0; j < net.Layers[layerIndex].Length; j++)
        {
            double sigPrimeTimesNV = SigmoidPrime(net.Layers[layerIndex].Neurons[j].Z) * net.Layers[layerIndex].Neurons[j].NeuronValue;
            for (int k = 0; k < net.Layers[layerIndex-1].Length; k++)
            {
                net.Layers[layerIndex].Neurons[j].WeightsGradientsSum[k] -= net.Layers[layerIndex - 1].Neurons[k].Value * sigPrimeTimesNV;
            }
            net.Layers[layerIndex].Neurons[j].BiaisGradientSum -= sigPrimeTimesNV;
        }
    }
}

void CleanGradients(struct network net)
{
    for(int i = 1; i<net.NumberOfLayers; i++)
    {
        for(int k = 0; k < net.Layers[i].Length;k++)
        {
            net.Layers[i].Neurons[k].BiaisGradientSum = 0;
            for (int j = 0; j < net.Layers[i-1].Length; j++)
            {
                net.Layers[i].Neurons[k].WeightsGradientsSum[j] = 0;
            }
        }
    }
}

void TrainOnOneSet(struct network net, double** inputs, char** expectedOutputs, double trainRatio, int batchSize) //inputs.length should be equal to expectedOutputs.length
{

    CleanGradients(net);
    
    for (int i = 0; i < batchSize; i++)
    {
        
        FrontPropagation(net, inputs[i]);
        SetNeuronValues(net, expectedOutputs[i]);
        SetGradients(net);
    }


    for(int i = 1; i<net.NumberOfLayers; i++)
    {
        for(int k = 0; k < net.Layers[i].Length;k++)
        {
            
            net.Layers[i].Neurons[k].Biais += (net.Layers[i].Neurons[k].BiaisGradientSum / (double)batchSize) * trainRatio;
            
            for (int j = 0; j < net.Layers[i-1].Length; j++)
            {
                //printf("%f\n",(net.Layers[i].Neurons[k].WeightsGradientsSum[j]/batchSize)*trainRatio);
                //printf("%f\n",net.Layers[i].Neurons[k].Weights[j]);
                net.Layers[i].Neurons[k].Weights[j] += (net.Layers[i].Neurons[k].WeightsGradientsSum[j]/(double)batchSize)*trainRatio;
                //printf("here\n");
            }
        }
    }
}

void Train(struct network net, double** allInputs, char** aLLExpectedOutputs, int totsize, double trainRatio, int batchSize, int numberOfBatchs, char print)
{
    double** nextInputs = allInputs;
    char** nextOutputs = aLLExpectedOutputs;
    for (int i = 0; i < numberOfBatchs; i++)
    {

        TrainOnOneSet(net,nextInputs,nextOutputs,trainRatio, batchSize);

        if (print)
        {
            PrintAccuracy(net, nextInputs, nextOutputs,10,100,50000);
        }
        nextInputs += batchSize;
        nextOutputs += batchSize;
        if(nextInputs > allInputs + totsize)
        {
            nextInputs = allInputs;
            nextOutputs = aLLExpectedOutputs;
        }
    }
}