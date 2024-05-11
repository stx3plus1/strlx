#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "randomstring.h"

int returnrandomnumber(int lower,int upper){
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
