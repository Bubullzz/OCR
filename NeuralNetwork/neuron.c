#include <stdio.h>
#include "structs.h"
#include <stdlib.h>
#include <time.h> 
//declaration of neuron in neuron.h



double drand (double low, double high )
    {
        srand((unsigned int)clock());
        return ( (double)rand() * ( high - low ) ) / (double)RAND_MAX + low;
    }
    /*
    for (int i =0; i<100;i++)
    printf("%f\n",drand(-1,1));
    */

struct neuron GetNewNeuron(int precedentNeurons)
{
    struct neuron n;
    //double clock;
    //Random r = new Random();
    if (precedentNeurons != 0)//if precedentNeurons = 0, its a starting neuron
    {

        n.Biais = 0; //doesn't cause an problem : https://www.analyticsvidhya.com/blog/2021/05/how-to-initialize-weights-in-neural-networks/
        n.Weights = (double *)malloc(sizeof(double)*precedentNeurons);//
        n.WeightsGradientsSum = (double *)malloc(sizeof(double)*precedentNeurons);//
        for (int i = 0; i < precedentNeurons; i++)
        {
            n.Weights[i] = drand(-1,1);
            //printf("%f\n", n.Weights[i]);
        }
    }
    /* we shouldn't enter here
    else
    {
        Biais = 0; //doesn't cause an problem : https://www.analyticsvidhya.com/blog/2021/05/how-to-initialize-weights-in-neural-networks/
        Weights = new double[0];
        WeightsGradientsSum = new double[0]; 
        for (int i = 0; i < Weights.Length; i++)
        {
            if (r.NextDouble() > 0.5)
                clock = 1;
            else
                clock = -1;
            Weights[i] = r.NextDouble() * clock; //r.NextDouble() > 0.5 ? (double)-1 : (double)1;// don't ask me why, mais ça marche pas
        }
    }
    */

    return n;

}

