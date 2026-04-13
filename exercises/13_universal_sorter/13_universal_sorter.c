#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*CompareFunc)(const void *, const void *);

int compareInt(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int compareFloat(const void *a, const void *b) {
    float diff = (*(float*)a - *(float*)b);
    return (diff > 0) ? 1 : ((diff < 0) ? -1 : 0);
}

int compareString(const void *a, const void *b) {
    return strcmp(*(char**)a, *(char**)b);
}

void sort(void *array, size_t n, size_t size, CompareFunc compare) {
    qsort(array, n, size, compare);
}

void processFile(const char *filename) {
    FILE *fin = fopen(filename, "r");
    if (!fin) {
        printf("错误: 无法打开文件 %s\n", filename);
        return;
    }

    int choice, n;
    if (fscanf(fin, "%d", &choice) != 1 || fscanf(fin, "%d", &n) != 1) {
        printf("错误: 文件 %s 格式不正确\n", filename);
        fclose(fin);
        return;
    }

    if (n > 20) n = 20;  // 最多支持20个元素

    printf("=== 处理数据来自: %s ===\n", filename);

    int size = 0;
    CompareFunc func;
    char *formater = NULL;
    switch (choice) {
        // TODO: 在这里添加你的代码
        case(1):
            size = sizeof(int);
            func = compareInt;
            formater = "%d";
            break;
        case(2):
            size = sizeof(float);
            func = compareFloat;
            formater = "%f";
            break;
    }
    void *array = malloc(n*size);
    for(int i=0; i<n; i++){
        fscanf(fin, formater, array+i*size);
    }
    sort(array, n ,size, func);

    for(int i=0; i<n; i++){
        if(choice == 1)
            printf("%d ", *(int*)(array+i*size));
        else
            printf("%f ", *(float*)(array+i*size));
    }
    fclose(fin);
}

int main() {
    processFile("int_sort.txt");
    processFile("float_sort.txt");

    return 0;
}