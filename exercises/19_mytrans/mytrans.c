// mytrans.c
#include "myhash.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim(char *str) {
    // TODO: 在这里添加你的代码
    while(*str){
      if(*str == '\n'){
        *str='\0';
        return;
      }
      str++;
    }
}

int load_dictionary(const char *filename, HashTable *table,
                    uint64_t *dict_count) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("无法打开词典文件");
    return -1;
  }

  char line[1024];
  char current_word[100] = {0};
  char current_translation[1024] = {0};
  int in_entry = 0;
  char *res = NULL;
    // TODO: 在这里添加你的代码
  while(1){
    res = fgets(line, sizeof(line), file);
    if(!res){
      break;
    }
    strcpy(current_word, line+1);
    trim(current_word);
    res = fgets(line, sizeof(line), file);
    if(!res){
      break;
    }

    strcpy(current_translation, line+6);
    trim(current_translation);

    if(hash_table_insert(table, current_word, current_translation)){
      in_entry ++;
    }
  }
  *dict_count = in_entry;
  fclose(file);
  return 0;
}
