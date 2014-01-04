#ifndef MAILLAGE_HPP
#define MAILLAGE_HPP

#include "pgm.hpp"
#include "array.hpp"
#include "Triangle.hpp"

class Maillage
{
private:
  const PGMImage& m_image;
  // TODO: A complèter (champs m_triangles)
  array<bool> m_pixel_utilises;
  int _ajoute(const int& precision);
  array<Triangle> m_triangles;

public:
  Maillage(const PGMImage& image);
  ~Maillage() {}

  void ajoute(const int& n, const int& precision);

  // TODO: A complèter
  void sauvegarde(const char * filename) const;
};

#endif // MAILLAGE_HPP
