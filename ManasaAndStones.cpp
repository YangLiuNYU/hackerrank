/*
Manasa is out on a hike with friends. She finds a trail of stones with numbers on them. She starts following the trail and notices that two consecutive stones have a difference of either  or . Legend has it that there is a treasure trove at the end of the trail and if Manasa can guess the value of the last stone, the treasure would be hers. Given that the number on the first stone was , find all the possible values for the number on the last stone.

Note: The numbers on the stones are in increasing order.

Input Format

The first line contains an integer , i.e. the number of test cases.  test cases follow; each has 3 lines. The first line contains  (the number of stones). The second line contains , and the third line contains .

Constraints

Output Format

Space-separated list of numbers which are the possible values of the last stone in increasing order.

Sample Input

2
3 
1
2
4
10
100
Sample Output

2 3 4 
30 120 210 300 
Explanation

All possible series for the first test case are given below:

0,1,2
0,1,3
0,2,3
0,2,4
Hence the answer 2 3 4.

Series with different number of final steps for second test case are the following:

0, 10, 20, 30
0, 10, 20, 120
0, 10, 110, 120
0, 10, 110, 210
0, 100, 110, 120
0, 100, 110, 210
0, 100, 200, 210
0, 100, 200, 300
Hence the answer 30 120 210 300.
*/

std::vector<int> PossibleLastStoneNumber(int stones,int a,int b) {
  std::vector<int> res;
  int small = std::min(a,b),big = std::max(a,b), diff = big - small;
  int smallest = small * (stones-1), bigest = big * (stones-1);

  if (diff==0) {
    return std::vector<int> (1,smallest);
  } else {
    for (int i=smallest;i<=bigest;i+=diff) {
      res.push_back(i);
    }

    return res;
  }
}



int main() {
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  int num_of_test(0);
  std::cin >> num_of_test;
  for (int i=0;i<num_of_test;++i) {
    int total_stones(0),a(0),b(0);
    std::cin >> total_stones;
    std::cin >> a;
    std::cin >> b;
    const std::vector<int> & res = PossibleLastStoneNumber(total_stones,a,b);
    for (int i=0;i<res.size();++i) {
      std::cout << res[i] << ' ' ;
    }
    std::cout << std::endl;
  }
  return 0;
}
