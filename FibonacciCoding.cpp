/*
http://www.geeksforgeeks.org/fibonacci-coding/
In mathematics and computing, Fibonacci coding is a universal code which encodes positive integers into binary code words. 
It is one example of representations of integers based on Fibonacci numbers. 
Each code word ends with "11" and contains no other instances of "11" before the end.
The Fibonacci code is closely related to the Zeckendorf
representation, a positional numeral system that uses Zeckendorf's
theorem and has the property that no number has a representation with
consecutive 1s. 
The Fibonacci code word for a particular integer is exactly the
integer's Zeckendorf representation 
with the order of its digits reversed and an additional "1" appended to the end.
*/

#include <string>
#include <vector>
#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

std::string FibonacciEncoding(int n) {
  if (n<1) return "";
  // Fibonacci sequence
  vector<int> fib_sequence = {1,2};
  // we need have the greatest Fibonacci number smaller than n,
  // or if could the one equals to n.
  while (fib_sequence.back()<n) {
    fib_sequence.push_back(fib_sequence[fib_sequence.size()-2]+fib_sequence.back());
  }
  int index = std::lower_bound(fib_sequence.begin(),fib_sequence.end(),n) - fib_sequence.begin();
  if (fib_sequence[index]>n) --index;
  std::string res("");
  while (index>=0) {
    if (fib_sequence[index]<=n) {
      res.push_back('1');
      n -= fib_sequence[index];
    } else {
      res.push_back('0');
    }
    -- index;
  }
  std::reverse(res.begin(),res.end());
  res.push_back('1');// extra 1
  return res;
}


void UnitTestFibonacciEncoding() {
  assert(FibonacciEncoding(1)=="11");
  assert(FibonacciEncoding(2)=="011");
  assert(FibonacciEncoding(3)=="0011");
  assert(FibonacciEncoding(4)=="1011");
  assert(FibonacciEncoding(5)=="00011");
  assert(FibonacciEncoding(6)=="10011");
  assert(FibonacciEncoding(8)=="000011");
  assert(FibonacciEncoding(16)=="0010011");
  assert(FibonacciEncoding(11)=="001011");
  assert(FibonacciEncoding(143)=="01010101011");
}
int main(int argc, char* argv[]) {
  UnitTestFibonacciEncoding();
  return 0;
}
