#include <stdio.h>
#include "structs.h"
#include <math.h>
#include <stdlib.h>
#include <time.h> 
#include "networking.h"


void Print(struct network net)
{
    for (int i=0; i <net.NumberOfLayers; i++)
    {
        for(int k = 0; k < net.Layers[i].Length; k++)
        {
            printf("[%10lf]  ",net.Layers[i].Neurons[k].Value);
        }
        printf("\n");
        printf("---------------------------------------------------------------------------------\n");
    }
}

double Sigmoid(double value)
{
    return (double)1 / ((double)1 + (double)exp(-value));//probleme de compile, faudra ajouter -lm pour compiler dans les flags: https://koor.fr/C/cmath/exp.wp
}

double SigmoidPrime(double value)
{
    double sx = Sigmoid(value);
    return sx * ((double)1 - sx);
}


int GetExpectedOutput(char* outputs, int length)//use only on Test/trainLABELS
{
for (int i = 0; i < length; i++)
{
    if (outputs[i] == 1)
        return i;
}

return -1;
}


void PrintAccuracy(struct network net, double** inputs, char** expectedOutputs, int lenOutput, int numberOfTests, int max)
{
    int goods = 0;
    srand((unsigned int)clock());
    int index; 
    for (int i = 0; i < numberOfTests; i++)
    {
        //printf("%d\n",i);
        index = rand() % (max+1);
        //printf("%d\n",index);
        //printf("%d\n", inputs[index][0]);
        int expected = GetExpectedValue(net, inputs[index]);
        //printf("%d\n",GetExpectedValue(net, inputs[index]));

        if (expectedOutputs[index][expected] == 1)
            goods++;
        int trueVal = GetExpectedOutput(expectedOutputs[index], lenOutput);
        /*
        for (int i = 0; i < 28; i++)
        {
            for(int k =0; k<28; k++)
            {
                //printf("%d",&TrainImages[0][28*i +k]);
                //printf("%d  %d\n",i,k);
                if (inputs[index][28*i +k]!=0)
                    printf("&");
                else
                    printf("_");
            }
            printf("\n");
        } 
        */
        printf("\n"); 
        //Print(net);
        /*
        for(int j = 0; j<10; j++)
            printf("%d,  ", expectedOutputs[index][j]);
        */
        printf("guessed %d good result was %d\n", expected, trueVal);
    }
    printf("\n"); 
    
    printf("----------------------------------------\n"); 
    printf("\n"); 
    printf("The accuracy was of %d/%d: %f%c\n",goods, numberOfTests,100*(float)goods/(float)numberOfTests,'%');
    printf("\n"); 
    
    printf("----------------------------------------\n"); 

}


double GetAccuracy(struct network net, double** inputs, char** expectedOutputs, int lenOutput, int numberOfTests, int max)
{
    int goods = 0;
    srand((unsigned int)clock());
    int index; 
    for (int i = 0; i < numberOfTests; i++)
    {
        //printf("%d\n",i);
        index = rand() % (max+1);
        //printf("%d\n",index);
        //printf("%d\n", inputs[index][0]);
        int expected = GetExpectedValue(net, inputs[index]);
        //printf("%d\n",GetExpectedValue(net, inputs[index]));

        if (expectedOutputs[index][expected] == 1)
            goods++;
        int trueVal = GetExpectedOutput(expectedOutputs[index], lenOutput);
        /*
        for (int i = 0; i < 28; i++)
        {
            for(int k =0; k<28; k++)
            {
                //printf("%d",&TrainImages[0][28*i +k]);
                //printf("%d  %d\n",i,k);
                if (inputs[index][28*i +k]!=0)
                    printf("&");
                else
                    printf("_");
            }
            printf("\n");
        } 
        */
        //Print(net);
        /*
        for(int j = 0; j<10; j++)
            printf("%d,  ", expectedOutputs[index][j]);
        */
        
    }

    return (float)goods/(float)numberOfTests;

}

