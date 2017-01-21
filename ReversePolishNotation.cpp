/*
https://www.hackerrank.com/contests/hacksouthcarolinaint/challenges/reverse-polish-notation
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <stdexcept>
using namespace std;

int Calculate(const std::vector<std::string> & tokens) {
  std::vector<int> operands;
  for (const std::string token : tokens) {
    if (!token.empty() && !std::isdigit(token[0])) {
      if (token[0]=='+') {
        int right = operands.back();
        operands.pop_back();
        operands.back() += right;
      } else if (token[0]=='-') {
        int right = operands.back();
        operands.pop_back();
        operands.back() -= right;
      } else if (token[0]=='*') {
        int right = operands.back();
        operands.pop_back();
        operands.back() *= right;
      } else if (token[0]=='/') {
        int right = operands.back();
        operands.pop_back();
        operands.back() /= right;
      } else if (token[0]=='x') {
        int n2 = operands.back();
        operands.pop_back();
        int n1 = operands.back();
        operands.pop_back();
        operands.push_back(n1 * n1 + n2);
      } else if (token[0]=='y') {
        int n = operands.back();
        operands.pop_back();
        operands.push_back( 2 * n + 1);
      } else if (token[0]=='z') {
        int n3 = operands.back();
        operands.pop_back();
        int n2 = operands.back();
        operands.pop_back();
        int n1 = operands.back();
        operands.pop_back();
        operands.push_back(n1 + 2 * n2 + 3 * n3);
      } else {
        //do nothing
      }
    }  else  {
      operands.push_back(std::stoi(token));
    }
  }
  return operands.back();
}

void UnitTest() {
  std::vector<std::string> tokens = {"1","+","2"};
}

int main() {
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  std::string temp("");
  std::getline(std::cin,temp);
  int num_of_test = std::stoi(temp);
  std::istringstream iss;
  std::vector<std::string> tokens;
  for (int i=0;i<num_of_test;++i) {
    iss.clear();
    tokens.clear();

    std::getline(std::cin,temp);
    iss.str(temp);

    while (iss>>temp) {
      tokens.push_back(temp);
    }

    try {
      std::cout<< Calculate(tokens) << std::endl;
    } catch(const std::exception & err) {
      std::cout << "NO" << std::endl;
    }

  }
  return 0;
}
