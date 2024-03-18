#pragma once

struct neuron
{
    double Value; // a
    double Biais;// b
    double Z; // Z as in the videos, used to represent the element passed to the sigmoid function
    double NeuronValue; // NV -- the derivative of Cost towards Activation
    double BiaisGradientSum;
    double* Weights;// w
    double* WeightsGradientsSum;
};

struct neuron GetNewNeuron(int precedentNeurons);

struct layer
{
    struct neuron* Neurons;
    int Length;
};

struct network
{
    struct layer* Layers;
    int NumberOfLayers;
};

struct network CreateNetwork(int* numberOfNeuronsPerLayer,int length);

struct layer GetNewLayer(int length, int precedentNeurons);


