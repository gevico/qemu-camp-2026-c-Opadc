#include "mywc.h"

// 创建哈希表
WordCount **create_hash_table() {
  WordCount **hash_table = calloc(HASH_SIZE, sizeof(WordCount *));
  return hash_table;
}

// 简单的哈希函数
unsigned int hash(const char *word) {
  unsigned long hash = 5381;
  int c;
  while ((c = *word++))
    hash = ((hash << 5) + hash) + c; // hash * 33 + c
  return hash % HASH_SIZE;
}

// 检查字符是否构成单词的一部分
bool is_valid_word_char(char c) { return isalpha(c) || c == '\''; }

// 转换为小写
char to_lower(char c) { return tolower(c); }

// 添加单词到哈希表
void add_word(WordCount **hash_table, const char *word) {
    // TODO: 在这里添加你的代码
    int idx = hash(word);
    WordCount *bucket = hash_table[idx];

    while(bucket){
      if(strcmp(bucket->word, word) == 0){
        bucket->count += 1;
        return;
      }
      bucket = bucket->next;
    }

    // not found
    WordCount *new_word = malloc(sizeof(WordCount));
    new_word->count = 1;
    new_word->next =  hash_table[idx];
    strcpy(new_word->word, word);
    hash_table[idx] = new_word;
}

// 打印单词统计结果
void print_word_counts(WordCount **hash_table) {
  printf("Word Count Statistics:\n");
  printf("======================\n");

    // TODO: 在这里添加你的代码
  WordCount *word_count;
  for(int i=0; i<HASH_SIZE; i++){
    word_count = hash_table[i];
    if(word_count){
      while(word_count){
        printf("%-21s%d\n", word_count->word, word_count->count);
        word_count = word_count->next;
      }
    }
  }
}
             
// 释放哈希表内存
void free_hash_table(WordCount **hash_table) {
    // TODO: 在这里添加你的代码
    WordCount *word_count;
    WordCount *next_word_count;
    for(int i=0; i<HASH_SIZE; i++){
      if(word_count = hash_table[i]){
        while(word_count){
          next_word_count = word_count->next;
          free(word_count);
          word_count = next_word_count;
        }
      }
    }
}

// 处理文件并统计单词
void process_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  WordCount **hash_table = create_hash_table();
  char word[MAX_WORD_LEN];
  int word_pos = 0;
  int c;

  while ((c = fgetc(file)) != EOF) {
    if (is_valid_word_char(c)) {
      if (word_pos < MAX_WORD_LEN - 1) {
        word[word_pos++] = to_lower(c);
      }
    } else {
      if (word_pos > 0) {
        word[word_pos] = '\0';
        add_word(hash_table, word);
        word_pos = 0;
      }
    }
  }

  // 处理文件末尾的最后一个单词
  if (word_pos > 0) {
    word[word_pos] = '\0';
    add_word(hash_table, word);
  }

  fclose(file);
  print_word_counts(hash_table);
  free_hash_table(hash_table);
}
