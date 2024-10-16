#include <iostream>
using namespace std;


int Largest(int a, int b, int c) {     
  int d = a;      // checking b is largest     
  if(d < b) {         
    d = b;     
  }      // checking c is largest     
  if(d < c) {         
    d = c;     
  }      
  return d; 
}
 
bool SumIsEven(int a, int b) {
  if((a+b) % 2) {
    return false;
  }
  else {
    return true;
  }
}

int BoxesNeeded(int apples) {
  if(apples <= 0) {
    return 0;
  }
  else if((apples % 20) == 0) {
    return (apples / 20);
  }
  else {
    return (apples / 20) + 1;
  }

}

bool SmarterSection(int A_correct, int A_total, int B_correct, int B_total) {
  if((A_correct > A_total) || B_correct > B_total) {
    throw std::invalid_argument("invalid_argument!");
  }
  if (A_correct < 0 || A_total < 0 || B_correct < 0 || B_total < 0) {
    throw std::invalid_argument("invalid_argument!");
  }
  if (((float)A_correct/A_total) > ((float)B_correct/B_total)) {
    return true;
  }
  else {
    return false; //returns false otherwise
  }
}


bool GoodDinner(int pizzas, bool is_weekend) {
if (10 <= pizzas && pizzas <= 20) {         
  return true;     
  } 
else if (is_weekend) {         
  return 10 <= pizzas;     
} 
else {         
  return false;     
} 
} 
 

int SumBetween(int low, int high) {
  int highholder;
  int lowholder;

  cout << low << " " << high << endl;
  if (low > high) {
    throw std::invalid_argument("invalid argument!");
  }

  if (abs(low + 1) == high) {
    return low;
  }

  if (low == high) {
    return low;
  }
  
  if (low * -1 == high) {
    return 0;
  } 
  
  if (abs(low) == (high - 1)) {
    return high;
  }

  if (low < 0 && high > 0) {
    if ((high * -1) > low) {
      lowholder = low;
      highholder = (high * -1) -1;
    }
    else if ((high * -1) < low) {
      lowholder = abs(low) + 1;
      highholder = high; 
    }
  }
  else {
    lowholder = low;
    highholder = high;
  }
  

  int sum = 0;

  for (int i = lowholder; i <= highholder; ++i) {
    if (i > 0) {
      if (INT32_MAX - i < sum) {
          throw std::overflow_error("overflow error!");   
      }     
    }
    else if (i < 0) {
      if ((INT32_MIN - i) * -1 < sum) {
        throw std::overflow_error("overflow error!");   
      }
    }
    sum += i;
    continue;
  }

  return sum;
}

int Product(int a, int b) {
  /*if((((a*b)/INT32_MAX > 1)) || (((a*b)/INT32_MIN < -1))) {         
    throw std::overflow_error("overflow error!");
  } 
  else {         
    return (a*b);
  }  */

  cout << a << " " << b;
  if (a == 0 || b == 0) {
    return 0;
  }
  if (a > 0 && b > 0) {
    if (INT32_MAX/a < b) {
      throw std::overflow_error("overflow error!");
    }
    return a*b;
  }
  else if (a < 0 && b < 0) {
    if ((INT32_MIN/(a * -1)) * -1 <= (b * -1)) {
      throw std::overflow_error("overflow error!");
    }
    return a*b;
  }
  else if (a < 0) {
    if ((INT32_MIN / b) > a) {
      throw std::overflow_error("overflow error!");
    }
    return a*b;
  }
  else if (b < 0) {
    if ((INT32_MIN / a) > b) {
      throw std::overflow_error("overflow error!");
    }
  }
  return a*b;
}
