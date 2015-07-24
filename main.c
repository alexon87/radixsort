//
// Radix sort algorithm for unsigned numbers implemented in C
// Bartlomiej Nowak 22.07.2015

#include <stdio.h>
#include <stdlib.h>             // atoi

#define DEBUG                   // Debugging messages, comment out to not use them

#ifdef DEBUG
#define debug_print(A, ...) printf("[%s:%d]: " A "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define debug_print(A, ...)
#endif

//
// findMax: Finds the max value in given array of numbers

int findMax(int *argint, int argc) {
  int max=0;
  for (int i=0; i<argc; i++) if (argint[i]>max) max=argint[i];
  return max;
}

//
// sortForDigit:
// Takes a pointer to an array of integers and their count as arguments
// Sorts the array of integers only on a certain digit

void sortForDigit(int *argint, int argc, int div) {
  for (int i=0; i<10; i++) counter[i]=0;

  debug_print("div==%d Counting occurences", div);
  for (int i=0; i<argc; i++) {                           // Count the occurences of digits 0-9
    counter[ (argint[i]/div)%10 ]++;
    debug_print("counter[%d]++", (argint[i]/div)%10);
  }

  #ifdef DEBUG
  for (int i=0; i<10; i++) { debug_print("counter[%d]=%d", i, counter[i]); }
  #endif

  debug_print("Calculating positions");
  debug_print("counter[0]=%d", counter[0]);
  for (int i=1; i<10; i++) {                             // Make counters point to the actual digit positions in resulting array
    counter[i]+=counter[i-1];                            // by treating each counter value as an offset from previous counter position
    debug_print("counter[%d]=%d", i, counter[i]);
  }

  debug_print("Inserting values into resulting array");
  for (int i=argc-1;i>=0;i--) {
    sortedlist[ counter[ ((argint[i]/div)%10)-1 ] ]=argint[i];  // Insert the value into position
    counter[ (argint[i]/div)%10 ]--;                            // Decrement the digit counter
    debug_print("sortedlist[%d]=%d", i, sortedlist[i])
  }
}

//
// radixSort:
// Takes a pointer to an array of integers and their count as arguments
// Sorts the array with increasing numbers

int *radixSort(int *argint, int argc) {

  int max = findMax(argint, argc);                         // Find the highest value in the sorted array
  int div = 1;                                             // Used to iterate the main loop through each digit in the number
  int counter[10] = {0};                                   // Counter array for each occurence of digit 0-9

  debug_print("radixSort: max=%d", max);


  while ( (max/div)%10>0 ) {                               // For each digit in the array
    sortForDigit();
    div*=10;
  }
  return sortedlist;
}

//
// Program start:

int main(int argc, char *argv[]) {

  // Convert string arguments to integers
  int *argint = malloc(sizeof(int)*argc);
  if (!argint) return -1;
  for (int i=1; i<argc; i++) argint[i-1]=atoi(argv[i]);

  int *sortedlist = radixSort(argint, argc-1);

  printf("Sorted list: ");
  for (int i=0; i<argc; i++) printf("%d, ", sortedlist[i]);
  printf("\n");

  free(argint);
  free(sortedlist);
  return 0;
}
