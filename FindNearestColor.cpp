/***
I have a sequence of 24 bits that represent a pixel. The leftmost 8 bits give the red component of the pixel, the middle 8 bits give the green component and the rightmost 8 bits give the blue component. The red, green and blue components of the pixel can take values between 0 (binary 00000000) to 255 (binary 11111111) each.

I need to identify whether the color of this pixel is geometrically closest to pure red, green, white or black. The geometric distance between two colors with RGB component (r1, g1, b1) and (r2,g2,b2) is given by

d = ( (r1-r2)^2 + (g1-g2)^2 + (b1-b2)^2 ) ^ 1/2
The RGB value of pure black is (0, 0, 0), pure white is (255, 255, 255), pure red is (255, 0, 0) and pure blue is (0, 0, 255)

My task is to identify which of these five colors is closest to the color of pixel P.

For example if pixel is represented by 000000001111111100000110, then

The red component = 00000000 (in binary) = 0 (in base 10)
The green component = 11111111 (in binary) = 255 (in base 10)
The blue component = 00000110 (in binary) = 6 (in base 10)
So, the RGB Value of P is (0, 255, 6)

Euclidean Distance of P from pure black (RGB = (0,0,0)):  
d = ( (0 - 0)^2 + (255 - 0)^2 + (6 - 0)2))^1/2  = 65061^1/2

Euclidean Distance of P from pure white (RGB = (255, 255, 255)): 
d =  ( (0 - 255)^2 + (255 - 255)^2 + (6 - 255)2))^1/2  = 127026^1/2

Euclidean Distance of P from pure red (RGB = (255, 0, 0)): 
d =  ( (0 - 255)^2 + (255 - 0)^2 + (6 - 0)^2))^1/2  = 130086^1/2

Euclidean Distance of P from pure green (RGB = (0, 255, 0)): 
d =  ( (0 - 0)^2 + (255 - 255)^2 + (6 - 0)^2))^1/2  = 36^1/2

Euclidean Distance of P from pure blue (RGB = (0, 0, 255)): 
d = ( (0 - 0)^2 + (255 - 0)^2 + (6 - 255)^2))^1/2  = 127026^1/2
From the above, we see, that P is closest to pure green. If P is equidistant from two or more colors, you should output "Ambiguous"

Sample Input:

5 // The first line contains an integer N(1<=N<=100), which is the number of input pixels to follow.
101111010110011011100100
110000010101011111101111
100110101100111111101101
010111011010010110000011
000000001111111111111111
Sample Output:

White
White
White
Green
Ambiguous
 ***/
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// We are going to calculate EuclideanDistanceSquare
// instead of Euclidean Distance since squre root is generally
// more expensive.

struct Pixel {
  Pixel(const string & tag, int r, int g, int b)
    : label(tag),red(r),green(g),blue(b) {}
  string label;
  int red,green,blue;
};

// return value could be very large. 
std::size_t EuclideanDistanceSquare(const Pixel & left,const Pixel & right) {
  return std::pow(right.red-left.red , 2)
    + std::pow(right.green-left.green , 2)
    + std::pow(right.blue-left.blue , 2) ;
}

std::string FindNearestColor(const std::string & str) {
  static Pixel BLACK("Black",0,0,0);
  static Pixel WHITE("White",255,255,255);
  static Pixel RED("Red",255,0,0);
  static Pixel GREEN("Green",0,255,0);
  static Pixel BLUE("Blue",0,0,255);
  static const std::vector<Pixel> colors = { BLACK,WHITE, RED, GREEN, BLUE };

  
  int red(0),green(0),blue(0);
  for (int i=0;i<8;++i) red = (red<<1) + (str[i]-'0');
  for (int i=8;i<16;++i) green = (green<<1) + (str[i]-'0');
  for (int i=16;i<24;++i) blue = (blue<<1) + (str[i]-'0');
  Pixel cur_pixel("",red,green,blue);
  std::string reval("");
  std::size_t min_distance(INT_MAX),count(0);
  for (const Pixel& color : colors) {
    std::size_t distance = EuclideanDistanceSquare(color,cur_pixel);
    if (distance<=min_distance) {
      if (distance<min_distance) {count = 1;min_distance = distance; reval=color.label; }
      else ++count;
    }
  }
  return count==1? reval : "Ambiguous";
}

void UnitTest() {
  std::vector<std::string> input;
  input.push_back("101111010110011011100100");
  input.push_back("110000010101011111101111");
  input.push_back("100110101100111111101101");
  input.push_back("010111011010010110000011");
  input.push_back("000000001111111111111111");
  for (const std::string & item : input) {
    std::cout << FindNearestColor(item) << std::endl;
  }
}

int main() {
  UnitTest();

  return 0;
}
