#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int MaximumContinousSubarray(const std::vector<int> & numbers) {
  int reval(numbers[0]),max_include_curr(numbers[0]);
  const std::size_t numbers_size(numbers.size());
  for (std::size_t i=1;i<numbers_size;++i) {
    max_include_curr = std::max(numbers[i],numbers[i]+max_include_curr);
    reval = std::max(reval,max_include_curr);
  }
  return reval;
}

int MaximumNonContinousSubarray(const std::vector<int> & numbers) {
  
  int reval(0);
  for (int num : numbers) {
    reval += std::max(0,num);
  }
  // Maybe numbers are all negative, in this case return the maximum number
  int max_val = * std::max_element(numbers.begin(),numbers.end());
  if (reval==0 && max_val<0) reval = max_val;
  return reval;
}

int main() {
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  int case_num(0),n(0),temp(0);
  std::cin >> case_num;
  for (int i=0;i<case_num;++i) {
    std::cin>> n;
    std::vector<int> numbers;
    for (int i=0;i<n;++i) {
      std::cin >> temp;
      numbers.push_back(temp);
    }
    std::cout << MaximumContinousSubarray(numbers) << ' ' << MaximumNonContinousSubarray(numbers)<< std::endl;
  }
  return 0;
}
