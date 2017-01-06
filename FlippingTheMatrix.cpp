#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;



int MaxSumOfUpperleftQuadrant(std::vector< std::vector<int> > & matrix,int n) {
  if (matrix.empty()) return 0;
  int reval(0);
  const int size(matrix.size());

  for (long long i=0;i<n;++i) {
    for (long long j=0;j<n;++j) {
      reval += std::max(matrix[i][j],
                        std::max(matrix[size-i-1][j],
                                 std::max(matrix[i][size-j-1],matrix[size-i-1][size-j-1])));
    }
  }
  return reval;
}

int main() {
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */

  int num_of_query(0);
  int n(0);
  std::cin>>num_of_query;
  for (int i=0;i<num_of_query;++i) {
    std::cin >> n;
    std::vector< std::vector<int> > matrix;

    int temp(0);
    for (int i=0;i<2*n;++i) {
      std::vector<int> cur_row;
      for (int j=0;j<2*n;++j) {
        std::cin >> temp;
        cur_row.push_back(temp);
      }
      matrix.push_back(cur_row);
    }

    std::cout << MaxSumOfUpperleftQuadrant(matrix,n) << std::endl;

  }
  return 0;
}
