#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50

typedef struct {
    char name[NAME_LEN];
    int score;
} Student;

Student students[MAX_STUDENTS];
Student temp[MAX_STUDENTS];

void merge_sort(int left, int right) {
    // [left, right]
    if(left >= right){
        return;
    }else if(left < right){
        int mid = (left + right) / 2;

        // [left, mid]
        merge_sort(left, mid);
        // [mid+1, right]
        merge_sort(mid+1, right);
        
        int merge_index = left;
        int merge_left = left;
        int merge_right = mid+1;
        while(merge_index <= right){
            if(merge_left <= mid && merge_right <= right){
                if(students[merge_left].score < students[merge_right].score){
                    temp[merge_index] = students[merge_right];
                    merge_index++;
                    merge_right++;
                }else{
                    temp[merge_index] = students[merge_left];
                    merge_index++;
                    merge_left++;
                }
            }else if(merge_left <= mid){
                temp[merge_index] = students[merge_left];
                merge_index++;
                merge_left++;
            }else if(merge_right <= right){
                temp[merge_index] = students[merge_right];
                merge_index++;
                merge_right++;
            }else{
                // should not happen;

            }
        }
        printf("[%d, %d] \n", left, right);
        for(int i=left; i<=right; i++){
            students[i] = temp[i];
            printf("%d ", students[i].score);
        }
        printf("\n");

    }
}

int main(void) {
    FILE *file = fopen("02_students.txt", "r");
    if (!file) {
        printf("错误：无法打开文件 02_students.txt\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);

    if (n <= 0 || n > MAX_STUDENTS) {
        printf("学生人数无效：%d\n", n);
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%s %d", students[i].name, &students[i].score);
    }
    fclose(file);

    merge_sort(0, n - 1);

    printf("\n归并排序后按成绩从高到低排序的学生名单：\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", students[i].name, students[i].score);
    }

    return 0;
}