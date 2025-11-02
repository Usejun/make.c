#include <string.h>
#include <stdio.h>
#include "string/string.h"

int main(void) {
   String s = str_from("1 2 3 4 5 6 7 8 9");
   StringViewMut svm = str_slicevm(&s, 2, 5);
   String s1 = svm_upper(&svm);
   str_set(&s1, 0, 'X');

   printf("%s", s.data);
   return 0;
}