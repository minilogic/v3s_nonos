#include <stdio.h>

int coremark_main(void);

int main (void)
{
  puts("\e[36mAllwinner V3S Coremark\e[0m");
  while(1)
  {
    printf("Benchmark started\r");
    coremark_main();
    printf("Press any key\r");
    getchar();
  }
}
