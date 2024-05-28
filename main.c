#include "train.h"
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define DATA_NUM 20

// 数据
Datas datas[] = {
    {{0, 1, 1, 0, 0, 1}, 1},
    {{1, 1, 0, 0, 0, 1}, 1},
    {{0, 0, 0, 1, 0, 0}, 0},
    {{1, 1, 1, 1, 0, 1}, 1},
    {{0, 0, 0, 0, 1, 0}, 0},
    {{0, 1, 1, 1, 1, 0}, 1},
    {{1, 0, 0, 0, 1, 1}, 0},
    {{0, 1, 1, 1, 0, 1}, 1},
    {{0, 1, 0, 1, 1, 1}, 1},
    {{1, 1, 1, 1, 0, 1}, 1},
    {{1, 1, 0, 0, 0, 1}, 1},
    {{0, 0, 0, 1, 1, 1}, 0},
    {{1, 1, 1, 1, 1, 1}, 1},
    {{1, 0, 0, 0, 1, 0}, 0},
    {{1, 0, 1, 0, 0, 0}, 1},
    {{1, 0, 0, 0, 1, 1}, 0},
    {{1, 1, 0, 1, 1, 1}, 0},
    {{1, 0, 0, 1, 1, 1}, 1},
    {{1, 0, 1, 0, 1, 0}, 0},
    {{0, 1, 0, 1, 0, 1}, 1},
};

int main() {
    Perceptron p;
    initializePerceptron(&p);

    // 训练数据
    int trainingData[DATA_NUM][NUM_QUESTIONS];
    init_trainingData(trainingData, datas, DATA_NUM);
    for(int i=0;i<DATA_NUM;i++)
    {
        for(int j=0;j<6;j++)
        {
            printf("%d ",trainingData[i][j]);
        }
        printf("\n");
    }

    // 训练标签，1代表正向情绪，0代表负面情绪
    int labels[DATA_NUM];
    init_label(labels, datas, DATA_NUM);

    // 训练感知机
    trainPerceptron(&p, trainingData, labels, DATA_NUM);

    // 评价准确度
    float accur=accuracy(&p,labels,trainingData,datas,DATA_NUM);
    printf("该模型准确度为%.2f\n",accur);

    // 保存结果
    char save[4];
    printf("是否保存本次数据？\n") ;
    scanf("%s",save);
    if(strcmp(save,"yes")==0)
    {
        const char *filename = "params.txt";
        savePerceptron(&p,"params.txt");
    }

    int answers[NUM_QUESTIONS];
    char** ans= gui();
    for(int i=0;i<NUM_QUESTIONS;i++)
    {
        input(answers[i],ans[i]);
    }
    // 计算情绪
    int output = calculateOutput(&p, answers);
    // 输出情绪结果
    if (output == 1) 
    {
        printf("你的情绪是正向的！\n");
    } 
    else 
    {
        printf("你的情绪是负面的！\n");
    }
    return 0;
}
