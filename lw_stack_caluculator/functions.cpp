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
  INFO_STRUCT(stack);
  INFO(number);

  if (stack.capacity == stack.count) {
    stack.capacity *=2;
    int * temp = new int[stack.capacity];
    for (int i =0; i < stack.capacity; i++) {
      temp[i] = stack.numbers[i];
    }
    temp[stack.count] = number;
    delete stack.numbers;
    stack.numbers = temp;
    stack.count++;
  } 
  else {
    stack.numbers[stack.count] = number;
    stack.count++;
  }

  //stack.numbers = temp;
  //temp = nullptr;
}

/**
 * ----- REQUIRED -----
 * Pops number from top of stack. If stack is empty, return INT32_MAX.
 * @param   stack   Target stack.
 * @return          Value of popped number.
 */
int pop(Stack& stack) {
  // TODO: implement pop function for stack
  INFO_STRUCT(stack);
  if (stack.count == 0) {
    return INT32_MAX;
  }
  int * temp = new int[stack.capacity];
  int tot = 0;

  for (int i = 0; i < stack.count-2; i++) {
    temp[i] = stack.numbers[i];
    tot += temp[i];
  }

  stack.count--;
  return stack.count;
}

/**
 * ----- REQUIRED -----
 * Returns the number at top of stack without popping it. If stack is empty, return INT32_MAX.
 * @param   stack   Target statck.
 * @return          Number at top of stack.
 */
int peek(const Stack& stack) {
  // TODO: implement peek function for stack
  INFO_STRUCT(stack);
  if (stack.count == 0) {
    return INT32_MAX;
  }

  int * temp = new int[stack.capacity];
  int tot = 0;

  for (int i = 0; i < stack.count-2; i++) {
    temp[i] = stack.numbers[i];
    tot += temp[i];
  }

  int x = stack.count - 1;
  return x;

}
