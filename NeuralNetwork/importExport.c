
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"

/*
<structure of nerula network file>
[6] char
[9] char
[Number of layers] int
[number of neurons in 0th layer] int
[number of neurons in 1th layer] int 
[number of neurons in 2th layer] int 
...
[number of neurons in last layer] int


skipping 0th layer because biais and wieghts irrelevant

[layer 1, neuron 0, weight 0]  double
[layer 1, neuron 0, weight 1]  ...
...
[layer 1, neuron 0, weight n]
[layer 1, neuron 0, biais]

[layer 1, neuron 1, weight 0]
...
[layer 1, neuron 1, weight n]
[layer 1, neuron 1, biais]
...
[layer 1, neuron n, wieght 0]
...
[layer 1, neuron n, weight n]
[layer 1, neuron n, biais]
[layer 2, neuron 0, weight 0]  double
...
[layer last, neuron last, biaias last]

*/
struct network Import(char* path)
{
    FILE* stream;
    stream = fopen(path,"rb");
    char garbage[2];
    struct network net;
    fread(&garbage,sizeof(char),2,stream);
    if (garbage[0] != '6' || garbage[1] != '9')
    {
        net.NumberOfLayers = -1;
        return net;
    }
    unsigned int numberOfLayers;
    fread(&numberOfLayers,sizeof(int),1,stream);

    int* numberOfNeuronsPerLayer = malloc(sizeof(int)*numberOfLayers);
    for(int l = 0; l < numberOfLayers; l++)
    {
        fread(&numberOfNeuronsPerLayer[l], sizeof(int),1,stream);
    }
    
    
    net.NumberOfLayers = numberOfLayers;
    net.Layers = (struct layer *)malloc(sizeof(struct layer)*numberOfLayers);
    
    net.Layers[0] = GetNewLayer(numberOfNeuronsPerLayer[0], 0); //initializing 0th layer


    for (int i = 1; i < numberOfLayers; i++)
    {
        struct layer tempLayer;
        tempLayer.Length = numberOfNeuronsPerLayer[i];
        tempLayer.Neurons = (struct neuron *)malloc(sizeof(struct neuron)*tempLayer.Length);
        for(int j = 0; j < tempLayer.Length; j++)
        {
            struct neuron tempNeuron;
            tempNeuron.Weights = (double *)malloc(sizeof(double)*numberOfNeuronsPerLayer[i-1]);
            for(int k = 0; k < numberOfNeuronsPerLayer[i-1]; k++)
            {
                fread(&tempNeuron.Weights[k],sizeof(double),1,stream);
            }
            fread(&tempNeuron.Biais,sizeof(double),1,stream);
            tempLayer.Neurons[j] = tempNeuron;
        }
        net.Layers[i] = tempLayer;
    }
    fclose(stream);
    return net;
}

void Export(struct network net, char* path)
{
    FILE* stream;
    stream = fopen(path,"wb");
    char six = '6';
    char nine = '9';
    fwrite(&six,sizeof(char),1,stream);
    fwrite(&nine,sizeof(char),1,stream);
    fwrite(&net.NumberOfLayers,sizeof(int),1,stream);

    for(int l = 0; l < net.NumberOfLayers; l++)
    {
        fwrite(&net.Layers[l].Length, sizeof(int),1,stream);
    }

    for (int i = 1; i < net.NumberOfLayers; i++)
    {
        for (int j = 0; j < net.Layers[i].Length; j++)
        {
            for(int k = 0; k < net.Layers[i-1].Length; k++)
            {
                fwrite(&net.Layers[i].Neurons[j].Weights[k], sizeof(double),1,stream);
            }
            fwrite(&net.Layers[i].Neurons[j].Biais, sizeof(double),1,stream);
        }
    }
    fclose(stream);
}