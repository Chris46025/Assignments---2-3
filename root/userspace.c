#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <linux/unistd.h>
#define __NR_sys_hello 326

int main(){

  long a = syscall(__NR_sys_hello);
  printf("System call sys_hello returned %ld\n", a);
  return 0;
}
