/*
Назовем x-отрезком группу подряд идущих элементов массива, каждый из которых равен x.
Для заданного числа x заменить элементы каждого x-отрезка на полусумму элементов, прилегающих к этому отрезку справа и слева.
Если x-отрезок расположен в начале или конце массива, считать недостающий крайний элемент равным нулю
тестич
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int FillMall(float** arr, int len) {

    FILE* input;
    input = fopen("input.txt", "r");
    if (!input)
    {
        return -1;
    }

    **arr = 0;
    int i = 1;
    while (!feof(input)) {
        fscanf(input, "%f", (*arr + i));
        ++i;

        if (i == len - 2) {
            len *= 2;
            *arr = (float*)realloc(*arr, sizeof(float) * len);
        }
    }
    fclose(input);

    len = i - 1;
    *arr = (float*)realloc(*arr, sizeof(float) * (i + 1));
    *(*arr + i) = 0;

    return len;
}

void change_x(float** arr, int len) {

    for (int i = 1; i < len; ++i) {
        int right = -1, left = i;
        float sum = 0;

        if (*(*arr + i) == *(*arr + i + 1)) {

            while (*(*arr + i) == *(*arr + i + 1)) {
                ++i;
            }
            right = i;

            for (int r = right + 1; r < len + 1; ++r) {
                sum += *(*arr + r);
            }
            for (int l = left - 1; l > 0; --l) {
                sum += *(*arr + l);
            }
            sum /= 2;

            for (int j = left; j < right + 1; ++j) {
                *(*arr + j) = sum;
            }
        }
    }
}

int MallOut(float** arr, int len) {

    FILE* output;
    output = fopen("output.txt", "w");
    if (!output)
    {
        fclose(output);
        return -1;
    }

    for (int i = 1; i < len + 1; i++)
    {
        fprintf(output, "%f ", *(*arr + i));
    }
    fclose(output);
}

int main() {

    int len = 100;
    float* arr;
    arr = (float*)malloc(sizeof(float) * len);
        
    len = FillMall(&arr, len);

    change_x(&arr, len);

    MallOut(&arr, len);
}