#include <stdio.h>
#include "structs.h"
#include "utils.h"

double GetNeuronValue(struct network net, struct neuron n, int layer)
{
    double sum = n.Biais; //initialize sum with the biais
    for (int i = 0; i < net.Layers[layer - 1].Length; i++)
    {
        sum += net.Layers[layer - 1].Neurons[i].Value * n.Weights[i];
    }
    n.Z = sum;
    //printf("%f\n",sum);
    return Sigmoid(sum);
}

double Cost(char* expectedResults, int length, struct network net)
{
    double sum = 0;
    double tempVal;
    for (int i = 0; i < length; i++)
    {
        tempVal = expectedResults[i] - net.Layers[net.NumberOfLayers - 1].Neurons[i].Value;
        sum += tempVal * tempVal;
    }
    
    return sum;
}


void FrontPropagation(struct network net, double* input)// input is the values of the first layer of neurons (I guess ?)
{
    for (int i = 0; i < net.Layers[0].Length; i++)
    {
        net.Layers[0].Neurons[i].Value = input[i];
    }

    for (int j = 1; j < net.NumberOfLayers; j++)
    {
        for(int k = 0; k < net.Layers[j].Length;k++)
            net.Layers[j].Neurons[k].Value = GetNeuronValue(net, net.Layers[j].Neurons[k], j);
    }
}

int GetExpectedValue(struct network net, double* input)//function to call to get the rnumebr guessed by me (the machine)
{
    FrontPropagation(net, input);
    //Print(net);
    double max = 0;
    int maxIndex = 0;
    for (int i = 0; i < net.Layers[net.NumberOfLayers - 1].Length; i++)
    {
        if (net.Layers[net.NumberOfLayers - 1].Neurons[i].Value > max)
        {
            max = net.Layers[net.NumberOfLayers - 1].Neurons[i].Value;
            maxIndex = i;
        }
    }
    //printf("%d\n",maxIndex);
    //Print(net);
    return maxIndex;
}