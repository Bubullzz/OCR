Créer un réseau:
- déja existant :
                #include "importExport.h"
                #include "structs.h"
                struct network net = Import("path");// "NeuralNetwork/Network" est pas mal

- from scratch :
                #include "importValues.h"
                #include "structs.h"
                #include "utils.h"
                #include "networking.h"
                #include "learntime.h"
                #include "importExport.h"

                double** TrainImages;
                char** TrainLabels;
                double** TestImages;
                char** TestLabels;
    
                ImportInLists(&TrainImages, &TrainLabels, &TestImages, &TestLabels, 1);

                int layers[] = {a,b,...,k}; //a = numbers of neurons in first layer, b = numbers of neurons in second layer, etc...

                struct network net = CreateNetwork(layers,totNumberOfLayers);
                while(accuracy insuffisante, nombre de boulces, jsp tu train autant que tu veux comme tu veux)
                    Train(net, TrainImages, TrainLabels, 40000, ratio, batchSize , NumberOfBatchs, 0); // BATCHSIZE*NUMBEROFBATCHS < 40000 !!!!!!!!!!!

                    //batchSize: Nombre d'elements sur lesquels on entraine avant d'appliquer les changements
                    //NumberOfBatchs: Nombre de Batchs sur lesquels on va entrainer le réseau.
                    //ratio: plus il est grand plus ça va faire des changements importants entre chaque batch
                    //pas besoin de toucher aux autres paramètres
                
                //Une fois sorti du while, le réseau est considéré bien entraîné et c'est du coup fini 
                //on peut l'exporter si besoin avec Export(net, path);


Obtenir une valeur: 
    #include "networking.h"
    GetExpectedValue(net, double* input) // input is levels of grey from 0 to 1 in row order first(iguess)

tester l'accuracy: 
    #include "utils.h"
    GetAccuracy(net,TestImages,TestLabels,10,NumberOfTests,8900)
    //NumberOfTests: nombre de tests pour avoir le ratio de réussite, 100 c'est ok,10000 c'est bien.


