#pragma once 
#include "structs.h"

void Print(struct network net);

double Sigmoid(double value);

double SigmoidPrime(double value);

void PrintAccuracy(struct network net, double** inputs, char** expectedOutputs, int lenOutput, int numberOfTests, int max);

double GetAccuracy(struct network net, double** inputs, char** expectedOutputs, int lenOutput, int numberOfTests, int max);