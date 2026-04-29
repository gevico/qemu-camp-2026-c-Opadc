#include <stdint.h>
#include <stdio.h>

uint32_t swap_endian(uint32_t num) {
    // TODO: 在这里添加你的代码
    uint32_t byte0 = num & 0xff;
    uint32_t byte1 = (num & 0xff00) >> 8;
    uint32_t byte2 = (num & 0xff0000) >> 16;
    uint32_t byte3 = (num & 0xff000000) >> 24;

    printf("%x %x %x %x\n", byte0, byte1, byte2, byte3);
    return (byte0 << 24) | (byte1 << 16) | (byte2 << 8) | byte3;
}

int main(int argc, char* argv[]) {
    uint32_t num = 0x78563412;
    uint32_t swapped = swap_endian(num);
    printf("0x%08x -> 0x%08x\n", num, swapped);
    return 0;
}