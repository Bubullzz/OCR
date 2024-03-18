
#include <stdio.h>
#include "importValues.h"
#include "structs.h"
#include "utils.h"
#include "networking.h"
#include "learntime.h"
#include "importExport.h"


int main()
{
    double** TrainImages;
    char** TrainLabels;
    double** TestImages;
    char** TestLabels;
    
    ImportInLists(&TrainImages, &TrainLabels, &TestImages, &TestLabels, 1);
    
    int layers[] = {784,30,10};
    struct network net = CreateNetwork(layers,3);
    
/*
    Train(net, TrainImages, TrainLabels, 40000, 1, 10 , 4500, 0);
    Train(net, TrainImages, TrainLabels, 40000, 1, 10 , 4500, 0);
    Train(net, TrainImages, TrainLabels, 40000, 0.5, 10 , 4500, 0);
    
    
    double ration = 1;

    Train(net, TrainImages, TrainLabels, 40000, ration, 50 , 700, 0);
    PrintAccuracy(net,TestImages,TestLabels,10,100,8900);
    Export(net,"Network");
    */
    printf("freshly imported network\n");
    struct network net2 = Import("Network");
    
    if(net2.NumberOfLayers < 0)
        printf("pas bon\n");
    printf("%f\n",GetAccuracy(net2,TestImages,TestLabels,10,100,8900)*100);

    /*
    while (0)
    {
    
    printf("Training with TrainRatio = 1\n");
    Train(net, TrainImages, TrainLabels, 40000, ration, 50 , 700, 0);
    PrintAccuracy(net,TestImages,TestLabels,10,1000,8900);
    i++;
    printf("starting %dth iteration\n",i);
    }
    //int layers[] = {784,20,10};
    //struct network net = CreateNetwork(layers,3);

    //printf("%d\n", net.Layers[0].Length);
    //Print(net);
    //printf("\n");
 

    //printf("%d\n", GetExpectedValue(net, input));*/

    

}
