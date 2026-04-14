#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


const char *required_strings[] = {
    [0] = "Unknown",
    [1] = "Relocatable",
    [2] = "Executable",
    [3] = "Shared Object/PIE"
};
    
void print_elf_type(uint16_t e_type) {
  const char *type_str = required_strings[e_type];
  printf("ELF Type: %s (0x%x)\n", type_str, e_type);
}

int main(int argc, char *argv[]) {
  char filepath[2][256] = {
    "./17_myfile.o",
    "./17_myfile",
  };

  int fd;
  Elf64_Ehdr ehdr;

  // TODO: 在这里添加你的代码
  for(int i=0; i<2; i++){
    FILE *f = fopen(filepath[i], "r");
    if(f == NULL){
      printf("read fail %s\n", filepath[i]);
      continue;
    }
    fread(&ehdr, sizeof(ehdr), 1, f);
    print_elf_type(ehdr.e_type);
  }
  
  return 0;
}
