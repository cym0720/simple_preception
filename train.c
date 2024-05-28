#include "train.h"
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>

#define LEARNING_RATE 0.1
#define MAX_ITERATIONS 10000

// ��ʼ��ѵ������
void init_trainingData(int trainingData[][NUM_QUESTIONS], Datas datas[20], int DATA_NUM) 
{
    for (int i = 0; i < DATA_NUM; i++) 
    {
        for (int j = 0; j < NUM_QUESTIONS; j++) 
        {
            trainingData[i][j] = datas[i].x[j];
        }
    }
}

// ��ʼ�����
void init_label(int label[], Datas* datas, int DATA_NUM) 
{
    for (int i = 0; i < DATA_NUM; i++) 
    {
        label[i] = datas[i].y;
    }
}

//��ʼ��Ȩ��
void initializePerceptron(Perceptron *p) 
{
    for (int i = 0; i < NUM_QUESTIONS; i++) 
    {
        p->weights[i] = 0.0; //��ʼ��Ȩ��
    }
    p->threshold = 0.0; // ��ʼ����ֵ
}

// ����yֵ
int calculateOutput(Perceptron *p, int inputs[]) 
{
    double sum = 0;
    for (int i = 0; i < NUM_QUESTIONS; i++) 
    {
        sum += p->weights[i] * inputs[i];
    }
    return (sum > p->threshold) ? 1 : 0; // ת��Ϊ���
}

// ѵ����֪��
void trainPerceptron(Perceptron *p, int trainingData[][NUM_QUESTIONS], int labels[], int numSamples) {
    int error;
    int iteration = 0;

    do {
        error = 0;
        for (int i = 0; i < numSamples; i++) 
        {
            int output = calculateOutput(p, trainingData[i]);
            int delta = labels[i] - output;
            if (delta != 0) 
            {
                error = 1; 
                for (int j = 0; j < NUM_QUESTIONS; j++) {
                    p->weights[j] += LEARNING_RATE * delta * trainingData[i][j];
                }
                p->threshold -= LEARNING_RATE * delta;
            }
        }
        iteration++;
    } while (error && iteration < MAX_ITERATIONS);

    if (iteration >= MAX_ITERATIONS) 
    {
        printf("ѵ���ɹ�\n");
    }
}

//���Ը�֪��׼ȷ��
float accuracy(Perceptron *p, int label[],int trainingData[][NUM_QUESTIONS], Datas* datas, int DATA_NUM) 
{
    
     int correct = 0;
    for (int i = 0; i < DATA_NUM; i++) {
        int output = calculateOutput(p, trainingData[i]);
        if(output==label[i]){
        	correct++;
        }
    }
    
    float accuracy =(float)correct/ DATA_NUM;
    return accuracy;
    
}

// ��ʾ����
void  PrintfQuestion(char question[],char anwser[])
{
    printf("%s",question);
    while(1)
    {
        scanf("%s",anwser);
        if(strcmp(anwser,"yes")!=0&&strcmp(anwser,"no")!=0)
        {
            printf("����������������룡\n");
        }
        else
        {
            return 0;
        }
    }
}
 
// ͼ�λ����沢�һش�����
char** gui()
{
    char** anwsers=malloc(NUM_QUESTIONS*sizeof(char*));
    for(int i=0;i<NUM_QUESTIONS;i++) 
    {
        anwsers[i]=malloc(200*sizeof(char));
    }
    printf("�����ж����ڿ�ʼ����ش������������⣬�������������\n");
    getch();


    // window��ʵ����������
	system("cls"); 
    PrintfQuestion("��������������������δ���а�����\n",anwsers[0]);

    PrintfQuestion("������Ƿ�Ը���ʱ����Щ�Լ�ϲ�������飬�����˶����߳�ȥ��䣿\n",anwsers[1]);

    PrintfQuestion("������ѣ�����������Զ���ҳ��������\n",anwsers[2]);

    PrintfQuestion("����Χ�кܶ������\n",anwsers[3]);

    PrintfQuestion("�����еĲ������ʮ������\n",anwsers[4]);

    PrintfQuestion("�Ҿ������ϻ��Ǻ��˶�\n",anwsers[5]);

    return anwsers;
}
 
//����ת��Ϊ����
void input(int arr,char* answer)
{
        arr = (strcmp(answer, "yes\n") == 0) ? 1 : 0; 
}

//����Ȩ�غ���ֵ�ĺ��� 
void savePerceptron(const Perceptron *p, const char *filename) 
{
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // ����Ȩ��
    for (int i = 0; i < NUM_QUESTIONS; i++) 
    {
        fprintf(file, "Weight %d: %f\n", i, p->weights[i]);
    }

    // ������ֵ
    fprintf(file, "Threshold: %f\n", p->threshold);

    fclose(file);
}