#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "pixel.hpp"

#include <iostream>
#include <cmath>

/*  Summary of contents

    protected: one, two, three (Pixels)
    public:
       Triangle(const Pixel&(x3))
       ~Triangle
       const Pixel& operator(const int& i) const
       Pixel barycenter() const
       bool CircleContains(const N2&) const
 */
class Triangle
{
private:
  Pixel one, two, three;

public:
  Triangle(const Pixel& first, const Pixel& second, const Pixel& third) {
    one = first;
    two = second;
    three = third;
  }

  Triangle() {}

  ~Triangle() { }


  Pixel barycenter() const {
    Pixel bar;
    //bar = (one + two + three) / 3;
    bar = one;// std::cout << bar << "\n";
    bar += two;// std::cout << bar << "\n";
    bar += three;// std::cout << bar << "\n";
    bar = bar/3;// std::cout << bar << "\n";
    return bar;
  }

  
  const Pixel& operator()(const int& i) const {
    switch ( i )
      {
      case 0: return one;
	break;
      case 1: return two;
	break;
      case 2: return three;
	break;
      default: std::cout << "Error: Invalid vertex of triangle." << "\n";
	return one;
      }
    }

  /*
    | Ax Ay (Ax^2+Ay^2) 1 |
 if | Bx By (Bx^2+By^2) 1 | > 0 then D is contained within the circle
    | Cx Cy (Cx^2+Cy^2) 1 |
    | Dx Dy (Dx^2+Dy^2) 1 |

    eventually can be written as
    | a b c |
    | d e f |
    | g h i |
   */
  bool CircleContains(const N2& ref) const {
    bool result;
    long long int det;
    long long int a, b, c, d, e, f, g, h, i; // 

    a = one.x() - ref.x();
    b = one.y() - ref.y();
    c = pow(one.x(),2) + pow(one.y(),2) - pow(ref.x(),2) - pow(ref.y(),2);
    d = two.x() - ref.x(); 
    e = two.y() - ref.y(); 
    f = pow(two.x(),2) + pow(two.y(),2) - pow(ref.x(),2) - pow(ref.y(),2);
    g = three.x() - ref.x(); 
    h = three.y() - ref.y(); 
    i = pow(three.x(),2) + pow(three.y(),2) - pow(ref.x(),2) - pow(ref.y(),2);

    det = a*(e*i - h*f) + b*(f*g - d*i) + c*(d*h - e*g);

    result = ( det >= 0 );
    // returns true if det >= 0, false otherwise

    return result;
  }

};


#endif
