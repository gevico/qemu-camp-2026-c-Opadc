#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

enum {
    WAIT_KEY,
    READ_KEY,
    WAIT_VALUE,
    READ_VALUE,
};
/**
 * URL参数解析器
 * 输入：包含http/https超链接的字符串
 * 输出：解析出所有的key-value键值对，每行显示一个
 */


int parse_url(const char* url) {
    int err = 0;

    // TODO: 在这里添加你的代码
    int state = WAIT_KEY;
    char *p = (char *)url;

    char *key = NULL;
    char *value = NULL;

    char buf[50];

    while(*p){
        switch(state){
            case(WAIT_KEY):
                if(*p == '?'){
                    state = READ_KEY;
                }
                break;
            case(READ_KEY):
                if(!key){
                    key = p;
                }
                if(*p == '='){
                    state = READ_VALUE;
                    // print key
                    int key_len = p-key;
                    memcpy(buf, key, key_len);
                    buf[key_len] = '\0';
                    printf("key = %s, ", buf);
                    key = NULL;
                }
                break;
            case(READ_VALUE):
                if(!value){
                    value = p;
                }
                if(*p == '&'){
                    state = READ_KEY;
                    // print value
                    int value_len = p-value;
                    memcpy(buf, value, value_len);
                    buf[value_len] = '\0';
                    printf("value = %s\n", buf);

                    value = NULL;
                }
                break;
            
        }
        p++;
    }
    if(state == READ_VALUE){
        int value_len = p-value;
        memcpy(buf, value, value_len);
        buf[value_len] = '\0';
        printf("value = %s\n", buf);        
    }


    return err;
}

int main() {
    const char* test_url = "https://cn.bing.com/search?name=John&age=30&city=New+York";

    printf("Parsing URL: %s\n", test_url);
    printf("Parameters:\n");

    parse_url(test_url);

    return 0;
}