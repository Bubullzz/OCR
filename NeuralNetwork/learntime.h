#pragma once

void Train(struct network net, double** allInputs, char** aLLExpectedOutputs, int totsize, double trainRatio, int batchSize, int numberOfBatchs, char print);