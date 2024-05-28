#include "train.h"
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>

#define LEARNING_RATE 0.1
#define MAX_ITERATIONS 10000

// 初始化训练数据
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

// 初始化结果
void init_label(int label[], Datas* datas, int DATA_NUM) 
{
    for (int i = 0; i < DATA_NUM; i++) 
    {
        label[i] = datas[i].y;
    }
}

//初始化权重
void initializePerceptron(Perceptron *p) 
{
    for (int i = 0; i < NUM_QUESTIONS; i++) 
    {
        p->weights[i] = 0.0; //初始化权重
    }
    p->threshold = 0.0; // 初始化阈值
}

// 计算y值
int calculateOutput(Perceptron *p, int inputs[]) 
{
    double sum = 0;
    for (int i = 0; i < NUM_QUESTIONS; i++) 
    {
        sum += p->weights[i] * inputs[i];
    }
    return (sum > p->threshold) ? 1 : 0; // 转化为结果
}

// 训练感知机
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
        printf("训练成功\n");
    }
}

//测试感知机准确度
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

// 显示问题
void  PrintfQuestion(char question[],char anwser[])
{
    printf("%s",question);
    while(1)
    {
        scanf("%s",anwser);
        if(strcmp(anwser,"yes")!=0&&strcmp(anwser,"no")!=0)
        {
            printf("输入错误，请重新输入！\n");
        }
        else
        {
            return 0;
        }
    }
}
 
// 图形化界面并且回答问题
char** gui()
{
    char** anwsers=malloc(NUM_QUESTIONS*sizeof(char*));
    for(int i=0;i<NUM_QUESTIONS;i++) 
    {
        anwsers[i]=malloc(200*sizeof(char));
    }
    printf("情绪判断现在开始！请回答以下六个问题，按下任意键继续\n");
    getch();


    // window下实现清屏功能
	system("cls"); 
    PrintfQuestion("你觉得你的做的事情对你的未来有帮助吗？\n",anwsers[0]);

    PrintfQuestion("你最近是否愿意抽时间做些自己喜欢的事情，比如运动或者出去逛逛？\n",anwsers[1]);

    PrintfQuestion("面对困难，我相信我永远能找出解决方法\n",anwsers[2]);

    PrintfQuestion("我周围有很多好朋友\n",anwsers[3]);

    PrintfQuestion("生活中的不愉快我十分在意\n",anwsers[4]);

    PrintfQuestion("我觉得世上还是好人多\n",anwsers[5]);

    return anwsers;
}
 
//将答案转化为数据
void input(int arr,char* answer)
{
        arr = (strcmp(answer, "yes\n") == 0) ? 1 : 0; 
}

//保存权重和阈值的函数 
void savePerceptron(const Perceptron *p, const char *filename) 
{
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // 保存权重
    for (int i = 0; i < NUM_QUESTIONS; i++) 
    {
        fprintf(file, "Weight %d: %f\n", i, p->weights[i]);
    }

    // 保存阈值
    fprintf(file, "Threshold: %f\n", p->threshold);

    fclose(file);
}