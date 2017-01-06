//Find all distinct palindromic sub-strings of a given string.

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;


bool CanBeAbbreviated(const std::string & a, const std::string & b){
  const std::size_t a_size(a.size()), b_size(b.size());
  std::vector< std::vector<bool> > can_abbre(a_size+1,std::vector<bool>(b_size+1,false));
  can_abbre[0][0] = true;
  for (std::size_t i=1;i<=a_size && std::islower(a[i-1]);++i) can_abbre[i][0] = true ;
  for (std::size_t i=1;i<=a_size;++i) {
    for (std::size_t j=1;j<=b_size;++j) {
      can_abbre[i][j] = ( can_abbre[i-1][j-1] && ( (std::toupper(a[i-1])==b[j-1]) || a[i-1]==b[j-1]) )
        || (std::islower(a[i-1]) && can_abbre[i-1][j] );
    }
  }

  for (std::size_t i=0;i<=a_size;++i) {
    for (std::size_t j=0;j<=b_size;++j) {
      std::cout << (can_abbre[i][j] ? 'Y' : 'N') << ',';
    }
    std::cout << std::endl;
  }
  return can_abbre[a_size][b_size];
}

int main(int argc, char* argv[])
{
 
  std::string temp;
  std::getline(std::cin,temp);
  int num_of_queries = std::stoi(temp);
  for (int i=0;i<num_of_queries;++i) {
    std::string a(""),b("");
    std::getline(std::cin,a);
    std::getline(std::cin,b);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << ( CanBeAbbreviated(a,b)? "YES" : "NO" ) << std::endl;
  }
  return 0;
}
