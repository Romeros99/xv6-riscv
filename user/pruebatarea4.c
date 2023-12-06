#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void){
  int file;
  file = open("archivo_prueba.txt", 0x200);
  close(file);

  chmod("archivo_prueba.txt", 1);
  file = open("archivo_prueba.txt", 0x001);
  close(file);

  chmod("archivo_prueba.txt", 2);
  file = open("archivo_prueba.txt", 0x001);
  close(file);

  chmod("archivo_prueba.txt", 1);
  file = open("archivo_prueba.txt", 0x002);
  close(file);
  printf("%d\n", file);
  return 0;
}
