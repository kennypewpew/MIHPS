#ifndef N2_HPP
#define N2_HPP

#include <iostream>
#include <cstdlib>


/* Summary 
     private: xval, yval (int)
     public:
       N2()
       N2(const int&, const int&)
       N2(const N2&)
       void setx(const int&)
       void sety(const int&)
       N2 operator+(const N2&)
       N2 operator-(const N2&)
       N2 operator+=(const N2&)
       N2 operator-=(const N2&)
       N2 operator/(const int&)
       N2 operator=(const N2&)
       bool operator==(const N2&)
       bool operator!=(const N2&)
       int x()
       int y()
*/
class N2
{
private:
  int xval, yval;

public:
  //===============
 //  Constructors
//=================

  /* No args: set everything to 0 */
  N2() {
    xval = yval = 0;
  }

  /* Define with preset coordinates */
  N2(const int& xx, const int& yy) {
    xval = xx;
    yval = yy;
  }

  N2(const N2& clone) {
    xval = clone.xval;
    yval = clone.yval;
  }

  //==========
 //  Methods
//============
  void setx(const int& xx) {
    xval = xx;
  }

  void sety(const int& yy) {
    yval = yy;
  }


  //============
 //  Operators
//==============
  N2 operator+(const N2& plus) {
    N2 out;
    out.xval = xval + plus.xval;
    out.yval = yval + plus.yval;
    return out;
  }

  N2 operator-(const N2& minus) {
    N2 out;
    out.xval = xval - minus.xval;
    out.yval = yval - minus.yval;
    return out;
  }

  N2 operator+=(const N2& plus) {
    xval += plus.xval;
    yval += plus.yval;
  }

  N2 operator-=(const N2& minus) {
    xval -= minus.xval;
    yval -= minus.yval;
  }

  N2 operator/(const int& div) {
    xval = xval/div;
    yval = yval/div;
  }

  N2 operator=(const N2& equal) {
    xval = equal.xval;
    yval = equal.yval;
  }


  bool operator==(const N2& compare) {
    if ( x() == compare.x() && y() == compare.y() ) {
      return true;
    }
    else { return false; }
  }

  bool operator!=(const N2& compare) {
    if ( x() != compare.x() && y() != compare.y() ) {
      return true;
    }
    else { return false; }
  }

  //===========
 //  Methods
//=============

  int x() const {
    return xval;
  }

  int y() const {
    return yval;
  }

};

/* Overload cout << */
std::ostream & operator<<(std::ostream& stream, const N2& print) {
  std::cout << print.x() << "," << print.y();
}



#endif
