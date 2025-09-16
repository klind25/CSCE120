#include <stdexcept>
#include <climits>

bool SumIsEven(int a, int b) {
  if((((a + b) % 2) == 1) || ((a + b) % 2) == -1){
    return false;
  }
  else{
    return true;
  }
}

int Largest(int a, int b, int c) {
  int d = a;

  if (b > d) {
    d = b;}
  if (c > d) {
    d = c;
  }
  return d;
}

unsigned int BoxesNeeded(int apples) {
  if (apples <= 0) { // Special case
    return 0;
  }
  else if (apples % 20 == 0) { // Evenly divisible
    return (apples/20);
  }
  else { // Not evenly divisible
    return (apples / 20 + 1);
  }
}


bool SmarterSection(int A_correct, int A_total, int B_correct, int B_total) {

  if (A_correct < 0 || A_total < 0 || B_correct < 0 || B_total < 0) { // Invalid inputs
    throw std::invalid_argument("Invalid argument");}
  else if (A_correct > A_total || B_correct > B_total) {
    throw std::invalid_argument("Invalid argument");
  }

  if ((A_correct*10000/A_total) > (B_correct*10000/B_total)) { // Perform operation
    return true;
  }
  return false;

  
}


bool GoodDinner(int pizzas, bool is_weekend) {
  if (pizzas >= 10 && pizzas <= 20) {
    return true;
  }
  else if (is_weekend) {
    if (pizzas >= 10) {
      return true;
    }
  }
  return false;
}

long long SumBetween(long long low, long long high) {
  long long value = 0;

  if (low > high) { // Invalid inputs
    throw std::invalid_argument("Invalid argument");
  } else if (low == high) { // Edge cases
    return low;
  } else if (low*-1 == high) {
    return 0;
  } else if (low + high == 1) {
    return high;
  } else if (low + high == -1) {
    return low;
  } else if (low <= LLONG_MIN || high >= LLONG_MAX) {
    throw std::overflow_error("Overflow");
  }

  // Check for overflow
  if (high > 0) { // High positive
    if (low > LLONG_MAX - high) {
      throw std::overflow_error("Overflow");
    }
  } 
  else if (high < 0) { // High negative
    if (low < LLONG_MIN - high) { 
      throw std::overflow_error("Overflow");
    } 
  }

  value = (high * high - low * low + high + low) / 2; // Series formula

  return value;
}

long long Product(long long a, long long b) {

  if (b > 0 && a > 0) {
    if (a < LLONG_MIN/b || a > LLONG_MAX/b) { // Both positive error
      throw std::overflow_error("Overflow");
    }
  } else if (b < 0 && a > 0) {
    if (a > LLONG_MIN/b || a < LLONG_MAX/b) { // B negative error
      throw std::overflow_error("Overflow");
    }
  } else if (b > 0 && a < 0) {
    if (a < LLONG_MIN/b || a > LLONG_MAX/b) { // A negative error
      throw std::overflow_error("Overflow");
    }
  } else if (b < 0 && a < 0) {
    if (a == LLONG_MIN || b == LLONG_MIN) {
      throw std::overflow_error("Overflow");
    }
    if ((a*-1 < LLONG_MIN/b*-1) || (-1*a > -1*LLONG_MAX/b)) { // Both negative error
      throw std::overflow_error("Overflow");
    }
  }
  if (a < LLONG_MIN || a > LLONG_MAX || b < LLONG_MIN || b > LLONG_MAX) { // Check values without multiplying
    throw std::overflow_error("Overflow");
  }
  if (abs(a) > LLONG_MAX || abs(b) > LLONG_MAX) {
    throw std::overflow_error("Overflow");
  }

  

  return a * b;
}