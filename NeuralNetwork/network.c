#include <stdio.h>
#include "structs.h"
#include <stdlib.h>

struct layer GetNewLayer(int length, int precedentNeurons)//length: number of neurons on this layer || precedentNeurons: number of neurons on the precedent layer
{
    struct layer l;
    l.Length = length;
    l.Neurons = (struct neuron *)malloc(sizeof(struct neuron)*length);
    for(int i = 0; i < length; i++)
    {
        l.Neurons[i] = GetNewNeuron(precedentNeurons);
    }
    return l;
}

struct network CreateNetwork(int* numberOfNeuronsPerLayer,int numberOfLayers)
{
    struct network net;
    net.NumberOfLayers = numberOfLayers;
    net.Layers = (struct layer *)malloc(sizeof(struct layer)*numberOfLayers);

    //for the starting neurons, because their wheigts and biaises are useless
    net.Layers[0] = GetNewLayer(numberOfNeuronsPerLayer[0],0);


    for (int i = 1; i < numberOfLayers; i++)
    {
        net.Layers[i] = GetNewLayer(numberOfNeuronsPerLayer[i], numberOfNeuronsPerLayer[i-1]);
    }
    return net;
}
