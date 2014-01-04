#include "Maillage.hpp"
#include "Cavite.hpp"
#include "pixel.hpp"

#include <cmath>
#include <fstream>
#include <sstream>

Maillage::
Maillage(const PGMImage& image)
  : m_image(image)
{
  m_pixel_utilises.resize(m_image.width()*m_image.height());
  for(int i=0; i<m_pixel_utilises.getSize(); ++i) {
    m_pixel_utilises[i]=false;
  }

  // TODO: Déclarations des Pixels utiles

  const Pixel coin_bas_gauche  = image.pixel(0,0);
  const Pixel coin_bas_droite  = image.pixel(image.width()-1,0);
  const Pixel coin_haut_gauche = image.pixel(0,image.height()-1);
  const Pixel coin_haut_droite = image.pixel(image.width()-1,image.height()-1);

  m_pixel_utilises[image.number(coin_bas_gauche)] =true;
  m_pixel_utilises[image.number(coin_bas_droite)] =true;
  m_pixel_utilises[image.number(coin_haut_gauche)]=true;
  m_pixel_utilises[image.number(coin_haut_droite)]=true;

  Triangle t1(coin_bas_gauche, coin_bas_droite, coin_haut_gauche);
  Triangle t2(coin_bas_droite, coin_haut_droite, coin_haut_gauche);
  
  m_triangles.add(t1);
  m_triangles.add(t2);
}

int Maillage::
_ajoute(const int& precision)
{
  int ecart_max=0;
  Pixel nouveau_point;
  for (int i=0; i<m_triangles.getSize(); ++i) {
    const Triangle & tr = m_triangles[i];
    Pixel candidat = tr.barycenter();
    if (not m_pixel_utilises[m_image.number(candidat)])
    {
      const int ecart = std::abs(candidat.getColor() - m_image.pixel(candidat).getColor());

      // TODO: Sélection d'un point d'erreur maximale dabs nouveau_point
      if ( ecart > ecart_max ) { 
	ecart_max = ecart;
      }
    } // end if: pixel not already in use
  } // end for: all triangles

  if (ecart_max>precision) {
    Cavite cavite(m_triangles, nouveau_point);
    m_pixel_utilises[m_image.number(nouveau_point)]=true;

    // TODO: Vider la cavité
    int j;
    for ( j = cavite.numerosAnciensTriangles().getSize()-1 ; j >=0 ; j++ ) {
      const int& gone = cavite.numerosAnciensTriangles()[j];
      m_triangles.remove(gone);
    }

    // TODO: Remplir la cavité par un étoilement en triangles
    const int numPixels = cavite.pixelsDuContour().getSize();
    for ( j = 0 ; j < numPixels ; j++ ) {
      Pixel one, two, three;
      one = nouveau_point;
      two = cavite.pixelsDuContour()[(j+0)%numPixels];
      three = cavite.pixelsDuContour()[(j+1)%numPixels];
      
      Triangle newTri(one,two,three);
      m_triangles.add(newTri);
    }

  }
  return ecart_max;
}

void Maillage::
ajoute(const int& n,
       const int& precision)
{
  for (int i=0; i<n; ++i) {
    int nbtr = m_triangles.getSize();
    int ecart = _ajoute(precision);
    if (ecart <= precision ) return;
    if (nbtr == m_triangles.getSize()) return;
    if (i%1000 == 0)
      std::cout << "Processing " << m_triangles.getSize() << " triangles; ecart=" << ecart << "\n"; // performance hit - not really necessary if you trust your work
  }
}


