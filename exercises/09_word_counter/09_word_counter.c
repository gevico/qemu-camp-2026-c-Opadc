#include <stdio.h>
#include <ctype.h>
#include <string.h>
int main() {
    char str[]="Don't ask what your country can do for you, but ask what you can do for your country.";
    int wordCount = 0;
    
    char *p = str;
    int in_word = 0;
    while(*p){
        // bypass all space.
        while(*p && isspace(*p)){
            if(in_word){
                in_word = 0;
                wordCount++;
            }
            p++;
        }
        while(*p && !isspace(*p)){
            in_word = 1;
            p++;
        }
    }

    if(in_word){
        wordCount++;
    }
    
    printf("单词数量: %d\n", wordCount);
    
    return 0;
}