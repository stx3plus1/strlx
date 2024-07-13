#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
// #include "randomstring.h"
// 1.8 will have a toggle, im probably gonna add it tonight

int returnrandomnumber(int lower,int upper){
  srand(time((0)));
  int number = (rand() % (upper - lower + 1)) + lower ;
  return number;
}
// conflicts would arise if uncommenting this, but it will stay
// int main(){
//   srand(time(0)); 
//   int low = 5;
//   int high = 40;
//   int random = returnrandomnumber(low,high);
//   printf("%s\n",randomstring[random]);
// }
