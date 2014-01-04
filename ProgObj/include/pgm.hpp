#ifndef PGM_HPP
#define PGM_HPP

#include <iostream>  // cout
#include <sstream>   // istringstream
#include <fstream>   // ifstream
#include <string>    // string
#include <iomanip>   // setw

#include "pixel.hpp"

class PGMException {
public:
  PGMException(const char * msg) : m_msg(msg) { }
  const char * message() const { return m_msg; }
private:
  const char * m_msg;
};

class PGMImage {
public:
  //! Constructeur
  PGMImage(const char * filename) throw (PGMException);
  //! Destructeur
  ~PGMImage() { delete[] m_data; }

private:
  //! Invalide le constructeur par copie et opertor= (privé + pas d'implémentation)
  /*! Réflexion: pourquoi ? */
  PGMImage(const PGMImage &);
  PGMImage & operator=(const PGMImage &);

public:
  // Réflexion (cours) : qu'apportent ces "inline" ?
  inline unsigned width() const { return m_width; }
  inline unsigned height() const { return m_height; }
  inline unsigned maxval() const { return m_maxval; }
  // Réflexion (pensez aux calculs) : pourquoi est-il plus commode de retourner un "int" qu'un "char" ?
  inline unsigned int operator()(int i, int j) const { return m_data[i*m_width+j]; }
  Pixel pixel(const N2& ref) const {
    Pixel out(ref.x(), ref.y(), m_data[ref.x()*m_width+ref.y()]);
    return out;
  }
  Pixel pixel(const int& x, const int& y) const {
    Pixel out(x, y, m_data[x*m_width + y]);
    return out;
  }
  int number(const Pixel& pix) const {
    int tmp;
    tmp = pix.x() + width()*pix.y();
    return tmp;
  }
  int number(const int& x, const int& y) const {
    int tmp;
    tmp = x + width()*y;
    return tmp;
  }

private:
  unsigned m_width;
  unsigned m_height;
  unsigned m_maxval;
  unsigned char * m_data;
};

PGMImage::PGMImage(const char * filename) throw (PGMException)
  : m_width(0),
    m_height(0),
    m_maxval(0),
    m_data(0)
{
  std::ifstream file(filename, std::ios::binary);
 
 if (file.fail()) throw PGMException("Cannot open file");

 // Description du format : http://netpbm.sourceforge.net/doc/pgm.html

  std::string line;

  // lecture de la première ligne
  std::getline(file, line);

  // Entête
  bool is_binary = true;
  if (line == "P5")
    is_binary = true;
  else if (line == "P2" )
    is_binary = false;
  else
    throw PGMException("Bad PGM Header");

  // on saute le commentaire eventuel 
  // (ie on relit une autre ligne si c'est un commentaire)
  std::getline(file, line);
  if (line[0] == '#') // commentaire si premier caractère est #
    std::getline(file, line);

  // on lit les dimensions (largeur x hauteur)
  std::istringstream is(line);
  is >> m_width >> m_height;

  // Nombre de valeurs (pixels) à lire
  const unsigned fullsize = m_height*m_width;

  // on lit la valeur max
  file >> m_maxval;

  // On ne supporte pas l'extension du format à 65536 niveaux de gris
  if (m_maxval > 255)
    throw PGMException("Too large max value");

  // on lit maintenant les données (binaire ou ascii suivant le flag is_binary)
  m_data = new unsigned char[fullsize];
  
  // Suppose fortement que le fichier respect le format
  if (is_binary)
    { // Lecture binaire
      // Réflexion++ : pourquoi ce reinterpret_cast ?
      file.read(reinterpret_cast<char*>(m_data), fullsize);
    }
  else
    { // Lecture ASCII
      for(unsigned i=0,v;i<fullsize;++i)
	  {
	    // Réflexion: pourquoi passer par une variable internmédiaire ?
	    // quel est le type de v ? pour quoi est-ce plus "simple" ainsi ?
	    file >> v; 
	    if (v > m_maxval) throw PGMException("Too big data");
	    m_data[i] = v;
	  }
    }
}


#endif
