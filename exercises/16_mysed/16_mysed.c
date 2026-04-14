#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    if (cmd[0] != 's' || cmd[1] != '/') {
        return -1;
    }

    
    char *begin_old;
    char *end_old;
    char *begin_new;
    char *end_new;

    // TODO: 在这里添加你的代码
    while(*cmd && *cmd != '/'){
        cmd++;
    }
    cmd++;
    begin_old = cmd;
    while(*cmd && *cmd != '/'){
        cmd++;
    }
    end_old = cmd;

    cmd++;
    begin_new = cmd;
    while(*cmd && *cmd != '/'){
        cmd++;
    }
    end_new = cmd;

    int old_len = end_old - begin_old;
    int new_len = end_new - begin_new;

    char *old_str_buf = malloc(old_len+1);
    memcpy(old_str_buf, begin_old, old_len);
    old_str_buf[old_len] = 0;

    char *new_str_buf = malloc(new_len+1);
    memcpy(new_str_buf, begin_new, new_len);
    new_str_buf[new_len] = 0;

    *old_str = old_str_buf;
    *new_str = new_str_buf;

    return 0;
}

void replace_first_occurrence(char* str, const char* old, const char* new) {
    // TODO: 在这里添加你的代码
    char *fist_old = strstr(str, old);

    int len = strlen(str);
    int old_len = strlen(old);
    int new_len = strlen(new);
    //printf("%d %d \n", old_len, new_len);
    memmove(fist_old+new_len, fist_old+old_len, len-old_len);
    //printf("%s \n", str);
    memcpy(fist_old, new, new_len);
    str[len+new_len-old_len] = '\0';
}

int main(int argc, char* argv[]) {
    const char* replcae_rules = "s/unix/linux/";

    char line[MAX_LINE_LENGTH] = {"unix is opensource. unix is free os."};

    char* old_str = NULL;
    char* new_str = NULL;
    
    if (parse_replace_command(replcae_rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    
    replace_first_occurrence(line, old_str, new_str);
    fputs(line, stdout);

    free(old_str);
    free(new_str);
    return 0;
}
