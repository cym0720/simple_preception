#include "train.h"
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define DATA_NUM 20

// ����
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

    // ѵ������
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

    // ѵ����ǩ��1��������������0����������
    int labels[DATA_NUM];
    init_label(labels, datas, DATA_NUM);

    // ѵ����֪��
    trainPerceptron(&p, trainingData, labels, DATA_NUM);

    // ����׼ȷ��
    float accur=accuracy(&p,labels,trainingData,datas,DATA_NUM);
    printf("��ģ��׼ȷ��Ϊ%.2f\n",accur);

    // ������
    char save[4];
    printf("�Ƿ񱣴汾�����ݣ�\n") ;
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
    // ��������
    int output = calculateOutput(&p, answers);
    // ����������
    if (output == 1) 
    {
        printf("�������������ģ�\n");
    } 
    else 
    {
        printf("��������Ǹ���ģ�\n");
    }
    return 0;
}
