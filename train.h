#ifndef TRAIN_H
#define TRAIN_H

#define NUM_QUESTIONS 6

typedef struct {
    int x[NUM_QUESTIONS];
    int y;
} Datas;

typedef struct {
    double weights[NUM_QUESTIONS]; // 权重
    double threshold; // 阈值
} Perceptron;

// 初始化
void init_trainingData(int trainingData[][NUM_QUESTIONS], Datas* datas, int DATA_NUM);

// 初始化
void init_label(int label[], Datas* datas, int DATA_NUM);

// 初始化感知机
void initializePerceptron(Perceptron *p);

// 计算感知机的输出
int calculateOutput(Perceptron *p, int inputs[]);

// 训练感知机
void trainPerceptron(Perceptron *p, int trainingData[][NUM_QUESTIONS], int labels[], int numSamples);

//测试感知机准确度
float accuracy(Perceptron *p, int label[],int trainingData[][NUM_QUESTIONS], Datas* datas, int DATA_NUM); 

//图形化界面
char** gui();

//输入答案
void input(int arr,char* answer);

//保存权重和阈值的函数 
void savePerceptron(const Perceptron *p, const char *filename); 

#endif // TRAIN_H