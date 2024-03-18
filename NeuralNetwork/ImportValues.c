
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ImportInLists(double*** TrainImagesP, char*** TrainLabelsP,
            double*** TestImagesP, char*** TestLabelsP, char print)
            {

                if (print)
                    printf("Start Importing Values...\n\n");

                
                FILE* trainImagesStream;
                trainImagesStream = fopen("../MNSIT/train-images.idx3-ubyte", "rb");

                FILE* trainLabelsStream;
                trainLabelsStream = fopen("../MNSIT/train-labels.idx1-ubyte", "rb");

                FILE* testImagesStream;
                testImagesStream = fopen("../MNSIT/t10k-images.idx3-ubyte", "rb");

                FILE* testLabelsStream;
                testLabelsStream = fopen("../MNSIT/t10k-labels.idx1-ubyte", "rb");


                int poubelle[4];

                fread(poubelle, 4,4, trainImagesStream);//discard the first useless infos TrainImage
                fread(poubelle, 4,2, trainLabelsStream);//discard the first useless infos TrainLabels
                fread(poubelle, 4,4, testImagesStream);//discard the first useless infos TestImage
                fread(poubelle, 4,2, testLabelsStream);//discard the first useless infos TestLabels

                

                //--------------- Train Images ------------
                unsigned char temp = 0;
                if(print)
                    printf("Importing Train Images...\n");
                
                double** TrainImages = (double **)malloc(sizeof(double*)*50000);

                for (size_t i = 0; i < 50000; i++)
                {
                    
                    TrainImages[i] = (double *)malloc(sizeof(double)*784);
                    for(int k = 0; k<784;k++)
                    {
                        fread(&temp,1,1,trainImagesStream);
                        //printf("%f\n", ((double)abs(temp)));
                        TrainImages[i][k] = ((double)abs(temp))/255;
                    }
                }
                                
                if(print)
                    printf("Finished Importing Train Images\n\n");
                
            
                /*
                for (size_t z = 0; z < 50000; z++)
                {
                for (int i = 0; i < 28; i++)
                {
                    for(int k =0; k<28; k++)
                    {
                        //printf("%d",&TrainImages[0][28*i +k]);
                        //printf("%d  %d\n",i,k);
                        if (TrainImages[z][28*i +k]!=0)
                            printf("&");
                        else
                            printf("_");
                    }
                    printf("\n");
                } 
                printf("\n\n\n");                   
                }
                */

                //----------------------- Test Images --------------------------

                if(print)
                    printf("Importing Test Images...\n");
                
                double** TestImages = (double **)malloc(sizeof(double*)*10000);
                for (size_t i = 0; i < 10000; i++)
                {
                    TestImages[i] = (double *)malloc(sizeof(double)*784);
                    for(int k = 0; k<784;k++)
                    {
                        fread(&temp,1,1,testImagesStream);
                        //printf("%f\n", atof(&temp));
                        TestImages[i][k] = ((double)abs(temp))/255;
                    }
                }
                                
                if(print)
                    printf("Finished Importing Test Images\n\n");
                                    
                

                //------------------------- Train Labels ------------


                if(print)
                    printf("Importing Train Labels...\n");

                char** TrainLabels = (char **)malloc(sizeof(char*)*50000);

                for (size_t i = 0; i < 50000; i++)
                {
                    TrainLabels[i] = (char *)calloc(10,sizeof(char));
                    fread(&temp,1,1, trainLabelsStream);
                    //printf("%d\n",temp);
                    TrainLabels[i][temp] = 1;
                    /*for (size_t k = 0; k < 10; k++)
                    {
                        printf("%d, ", TrainLabels[i][k]);
                    }
                    printf("\n");
                    */
                }
                                
                if(print)
                    printf("Finished Importing Train Labels\n\n");
                
                //------------------------- Test Labels ------------

                if(print)
                    printf("Importing Test Labels...\n");
                
                char** TestLabels = (char **) malloc(sizeof(char *)*10000);
                for (size_t i = 0; i < 10000; i++)
                {
                    TestLabels[i] = (char *)calloc(10,sizeof(char));
                    //printf("here%ld\n",i);
                    fread(&temp,1,1, testLabelsStream);
                    TestLabels[i][temp] = 1;
                }
                                
                if(print)
                    printf("Finished Importing Test Labels\n\n");

                //---------------------------END---------------------------

                /* //#Test for the TrainBatch
                for (size_t z = 0; z < 50000; z++)
                {
                    for (size_t i = 0; i < 10; i++)
                    {
                        if (TrainLabels[z][i] == 1)
                            printf("number : %ld\n",i);
                    }
                    
                    for (int i = 0; i < 28; i++)
                    {
                        for(int k =0; k<28; k++)
                        {
                            //printf("%d",TrainImages[0][0]);
                            //printf("%d  %d\n",i,k);
                            if (TrainImages[z][28*i +k]!=0)
                                printf("&");
                            else
                                printf("_");
                        }
                        printf("\n");
                    } 
                    printf("\n\n\n");                   
                }
                */
                
               /*  #Test for the TestBatch
               for (size_t z = 0; z < 10000; z++)
                {
                for (size_t i = 0; i < 10; i++)
                {
                    if (TestLabels[z][i] == 1)
                        printf("number : %ld\n",i);
                }
                
                for (int i = 0; i < 28; i++)
                {
                    for(int k =0; k<28; k++)
                    {
                        //printf("%d",&TrainImages[0][28*i +k]);
                        //printf("%d  %d\n",i,k);
                        if (TestImages[z][28*i +k]!=0)
                            printf("&");
                        else
                            printf("_");
                    }
                    printf("\n");
                } 
                printf("\n\n\n");                   
                }*/


                
                *TrainImagesP = TrainImages;
                *TrainLabelsP = TrainLabels;
                *TestImagesP = TestImages;
                *TestLabelsP = TestLabels;
                fclose(trainImagesStream);
                fclose(trainLabelsStream);
                fclose(testImagesStream);
                fclose(testLabelsStream);
                if(print)
                    printf("finished importing values\n");
                
            }
