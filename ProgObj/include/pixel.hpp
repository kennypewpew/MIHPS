#ifndef PIXEL_HPP
#define PIXEL_HPP

#include "N2.hpp"
#include <iostream>
#include <cstdlib>


/* Summary
     protected: color
     public:
       Pixel()
       Pixel(const N2&, const int&)
       Pixel(const int&, const int&, const int&)
       void setColor(const int&)
       Pixel operator+(const Pixel&)
       Pixel operator-(const Pixel&)
       Pixel operator+=(const Pixel&)
       Pixel operator-=(const Pixel&)
       Pixel operator/(const Pixel&)
       Pixel operator=(const Pixel&)
       int getColor() const
 */
class Pixel
  :public N2
{
private:
  int color;

public:
/* Constructors */
  Pixel() {
    setx(0);
    sety(0);
    color = 0;
}

  Pixel(const N2& init, const int& col) {
    setx(init.x());
    sety(init.y());
    color = col;
  }

  Pixel(const int& xx, const int& yy, const int& col) {
    setx(xx);
    sety(yy);
    color = col;
  }

  ~Pixel() {}

/* Methods */
  void setColor(const int& col) {
    color = col;
  }


/* Operators */
// Might want to add assert( val < 256 && val >= 0 )
  Pixel operator+(const Pixel& plus) {
    int xout, yout, cout;
    xout = x() + plus.x();
    yout = y() + plus.y();
    cout = color + plus.getColor();
    Pixel out(xout, yout, cout);
    return out;
  }

  Pixel operator-(const Pixel& minus) {
    int xout, yout, cout;
    xout = x() - minus.x();
    yout = y() - minus.y();
    cout = getColor() + minus.getColor();
    Pixel out(xout, yout, cout);
    return out;
  }

  Pixel operator+=(const Pixel& plus) {
    setx( x() + plus.x() );
    sety( y() + plus.y() );
    color += plus.getColor();
  }

  Pixel operator-=(const Pixel& minus) {
    setx( x() - minus.x() );
    sety( y() - minus.y() );
    color -= minus.getColor();
  }

  Pixel operator/(const int& div) {
    int xout, yout, cout;
    xout = x()/div;
    yout = y()/div;
    cout = color/div;
    Pixel out(xout, yout, cout);
    return out;
  }

  Pixel operator=(const Pixel& equal) {
    setx(equal.x());
    sety(equal.y());
    color = equal.getColor();
  }

/* Methods */
  int getColor() const {
    return color;
  }

};

/* Overload cout << */
std::ostream & operator<<(std::ostream& stream, const Pixel& print) {
  std::cout << print.x() << ", " << print.y() << ", " << print.getColor();
}

#endif
