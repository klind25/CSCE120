#include "functions.h"
using std::cin, std::cout, std::endl, std::ostream, std::string;

#define INFO(X)  cout << "[INFO] ("<<__FUNCTION__<<":"<<__LINE__<<") " << #X << " = " << X << endl;
#define INFO_STRUCT(X) cout << "[INFO] ("<<__FUNCTION__<<":"<<__LINE__<<") " << #X << " count = " << X.count << endl;

/**
 * ----- REQUIRED -----
 * Pushes number to top of stack. If stack is full, then resize stack's array.
 * @param   stack   Target stack.
 * @param   number  Number to push to stack.
 */
void push(Stack& stack, int number) {
  // TODO: implement push function for stack

  if (stack.capacity == stack.count) { // Checks if array needs to be doubled 
    stack.capacity *= 2; // Update capacity
    int* array = new int [stack.capacity];

    for (int i = 0; i < stack.count; ++i) { // Copy the array
      array[i] = stack.numbers[i];
    }
    delete[] stack.numbers; // Delete the old array

    stack.numbers = array; // Get the original array back

  }

  stack.numbers[stack.count] = number; // Append the array
  stack.count += 1; // Update count

  INFO_STRUCT(stack);
  INFO(number);
}

/**
 * ----- REQUIRED -----
 * Pops number from top of stack. If stack is empty, return INT32_MAX.
 * @param   stack   Target stack.
 * @return          Value of popped number.
 */
int pop(Stack& stack) {
  int popped;

  if (stack.count != 0) {
    popped = stack.numbers[stack.count - 1]; // Get value to return
    stack.numbers[stack.count] = 0;

    stack.count -= 1; // Update count
  }
  else{popped = INT32_MAX;}


  INFO_STRUCT(stack);
  return popped;
}

/**
 * ----- REQUIRED -----
 * Returns the number at top of stack without popping it. If stack is empty, return INT32_MAX.
 * @param   stack   Target statck.
 * @return          Number at top of stack.
 */
int peek(const Stack& stack) {
  int top;
  if (stack.count != 0) {
    top = stack.numbers[stack.count - 1];
  }
  else {top = INT32_MAX;}

  INFO_STRUCT(stack);
  return top;
}
