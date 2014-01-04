#ifndef CAVITE_HPP
#define CAVITE_HPP

#include "pixel.hpp"
#include <map>
#include <cmath>

class Cavite
{
private:
  array<int> m_numeros_anciens_triangles;
             // number in array of triangles in cavity
  array<Pixel> m_pixels_du_contour;
             // vertices of the cavity
public:
  Cavite(const array<Triangle>& triangles,
	 const Pixel& nouveau_point)
  {
    typedef std::map<double, Pixel> PixelOrdonnes;
    PixelOrdonnes pixel_ordonnes;

    for (int i=0; i<triangles.getSize(); ++i) {
      const Triangle& triangle = triangles[i];
      if (triangle.CircleContains(nouveau_point)) {
	m_numeros_anciens_triangles.add(i);
	for (int j=0; j<3; ++j) {
	  const Pixel& p = triangle(j);
	  const double& angle = atan2(p.y()-nouveau_point.y(),
				      p.x()-nouveau_point.x());
	  pixel_ordonnes[angle] = p;
	}
      }
    }

    m_pixels_du_contour.reserve(pixel_ordonnes.size());
    for (PixelOrdonnes::const_iterator i=pixel_ordonnes.begin();
	 i!=pixel_ordonnes.end(); ++i) {
      m_pixels_du_contour.add(i->second);
    }
  }

  ~Cavite()
  {
  }

public:
  const array<int>&
  numerosAnciensTriangles() const
  {
    return m_numeros_anciens_triangles;
  }

  const array<Pixel>&
  pixelsDuContour() const
  {
    return m_pixels_du_contour;
  }
};

#endif // CAVITE_HPP
