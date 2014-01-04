#ifndef MESH_HPP
#define MESH_HPP

#include "array.hpp"
#include "Triangle.hpp"
#include "Image.hpp"
#include "pgm.hpp"
#include "Cavite.hpp"

#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <fstream>


/* Summary
   private:
     array<Triangle> m_triangles;
     Image m_image;
     bool *m_used.
   public:
     void saveMESH(const char) const
     void add(const int, const int)
     void saveVTK(const char * filename) const
 */

class Mesh
{
private:
  array<Triangle> m_triangles;
  Image m_image;
  bool *m_used;

private:
  Mesh() {}

public:
  Mesh(const char* file_init){
    PGMImage raw(file_init);
    Image tmp(raw);
    m_image = tmp;
    m_used = new bool[m_image.nbRows()*m_image.nbCols()];
    for ( int i = 0 ; i < m_image.nbRows()*m_image.nbCols() ; i++ ) {
      m_used[i] = false;
    }
  }
  ~Mesh() {}

  void saveMESH(const char *filename) const;
  void saveVTK(const char * filename) const;
  void add(const int& n, const int& precision);
};

void Mesh::add(const int& n, const int& precision) {
  int cnt = 0;

  // create first two triangles if uninitialized
  // ?? Should this be in the constructor ??
  if ( m_triangles.getSize() == 0 ) {
    Triangle top(  m_image.pixel( 0 , 0 ), 
		   m_image.pixel( m_image.nbCols()-1 , 0)  ,
		   m_image.pixel( 0 , m_image.nbRows()-1 ) );
    Triangle bottom(  m_image.pixel(m_image.nbCols()-1,0), 
		      m_image.pixel(m_image.nbCols()-1,m_image.nbRows()-1),
		      m_image.pixel(0, m_image.nbRows()-1) );

    m_used[m_image.number(0,0)] = true;
    m_used[m_image.number(0, m_image.nbRows()-1)] = true;
    m_used[m_image.number(m_image.nbCols()-1, 0)] = true;
    m_used[m_image.number(m_image.nbCols()-1, m_image.nbRows()-1 )] = true;

    m_triangles.add(top);
    m_triangles.add(bottom);

    cnt = 1;
  }


  while ( cnt < n ) {
    int change = cnt;

    for ( int i = 0 ; i < m_triangles.getSize() ; i++ ) {
      // current <- comparison triangle
      const Triangle current = m_triangles[i];
      bool valid = false; // valid = "Should I add the barycenter?"
      // compare barycenter color to m_image color at the same point
      int diff = current.barycenter().getColor() - m_image.pixel( current.barycenter().x(), current.barycenter().y() ).getColor() ;

      if ( fabs(diff) > precision ) {
	valid = true;
      } // end if: is a new point needed?

      if ( m_used[m_image.number(current.barycenter())] == true ) {
	valid = false;
      } // end if: "Is the point already assigned?"

      if ( true == valid ) {
	const Pixel newpoint = m_image.pixel( current.barycenter().x(), current.barycenter().y());
	// list newpoint as assigned
	m_used[m_image.number(newpoint)] = true;

	// create cavity around the point to be added
	Cavite cavity(m_triangles, newpoint );

	// remove triangles that need removing
	// work backwards, otherwise risk numbers being changed while removing
	for ( int k = cavity.numerosAnciensTriangles().getSize() -1; k >= 0 ; k-- ) {
	  const int & gone = cavity.numerosAnciensTriangles()[k];
	  m_triangles.remove(gone);
	} // end for k: triangle removal

	// add new triangles
	const int numPixels = cavity.pixelsDuContour().getSize();
	for ( int k = 0 ; k < numPixels ; k++ ) {	  
	  Pixel one, two, three;
	  one = newpoint;
	  two = cavity.pixelsDuContour()[(k+0)%numPixels];
	  three = cavity.pixelsDuContour()[(k+1)%numPixels];

	  Triangle newTri(one,two,three);
	  m_triangles.add(newTri);

	} // end for k: add triangles
	// done adding/removing triangles

	cnt++;
	if ( cnt >= n ) {
	  std::cout << n << " iterations completed.\n";
	  return;
	}
      } // end if diff > precision
    } // end for i: triangles in mesh

    // If we iterated through the whole array without changing anything, finish
    if ( change == cnt ) {
      std::cout << "Desired precision reached after " << cnt << " iterations.\n";
      return;
    }
    
  } // end while cnt < n
}

//====================================================
void Mesh::
saveMESH(const char * filename) const
{
  std::ofstream file(filename);
  file << "MeshVersionFormatted 1\n"
       << "Dimension\n"
       << "  2\n"
       << "Vertices\n";

  std::ostringstream oss;
  std::map<int,int> coord_to_pos;
  for(int i=0;i<m_triangles.getSize();++i)
    {
      const Triangle & tr = m_triangles[i];
      for(int j=0;j<3;++j)
	{
	  const Pixel & pixel = tr(j);
	  std::pair<std::map<int,int>::iterator,bool> inserter
	    = coord_to_pos.insert(std::make_pair<int,int>(m_image.number(pixel),coord_to_pos.size()+1));
	  if (inserter.second)
	    {
	      oss << +pixel.x() << " " << -pixel.y() << " 1\n";
	    }
	}
    }
  file << coord_to_pos.size() << "\n";
  file << oss.str();

  file << "Triangles\n"
       << m_triangles.getSize() << "\n";
  for(int i=0;i<m_triangles.getSize();++i)
    {
      const Triangle & tr = m_triangles[i];
      int mean_color = 0;
      for(int j=0;j<3;++j)
	{
	  const Pixel & pixel = tr(j);
	  file << coord_to_pos[m_image.number(pixel)] << " ";
	  mean_color += pixel.getColor();
	}
      mean_color /= 3;
      file << mean_color << "\n";
    }
}

//==================================================
void Mesh::
saveVTK(const char * filename) const
{
  std::ofstream file(filename);
  file << "# vtk DataFile Version 3.0\n"
       << "Triangle mesh of image\n"
       << "ASCII\n"
       << "DATASET UNSTRUCTURED_GRID\n\n";

  std::ostringstream oss;
  std::map<int,int> coord_to_pos;

  for(int i=0;i<m_triangles.getSize();++i)
    {
      const Triangle & tr = m_triangles[i];
      for(int j=0;j<3;++j)
	{
	  const Pixel & pixel = tr(j);
	  std::pair<std::map<int,int>::iterator,bool> inserter
	    = coord_to_pos.insert(std::make_pair<int,int>(m_image.number(pixel),coord_to_pos.size()+1));
	  if (inserter.second)
	    {
	      oss << +pixel.x() << " " << -pixel.y() << " 0\n";
	    }
	}
    }

  file << "POINTS " << coord_to_pos.size() << " float\n";
  file << oss.str();

  file << "\nCELLS "
       << m_triangles.getSize()
       << " " << 4*m_triangles.getSize()
       << "\n";
  for(int i=0;i<m_triangles.getSize();++i)
    {
      file << 3 << " ";
      const Triangle & tr = m_triangles[i];
      for(int j=0;j<3;++j)
	{
	  const Pixel & pixel = tr(j);
	  file << coord_to_pos[m_image.number(pixel)]-1 << " ";
	}
      file << "\n";
      //file << mean_color << "\n"; this goes into the lookup table now

    } // end for i: print triangles

  file << "\nCELL_TYPES "
       << m_triangles.getSize()
       << "\n";

  for ( int i = 0 ; i < m_triangles.getSize(); ++i ) {
    file << 5 << "\n";
  }
  
  file << "\nCELL_DATA " << m_triangles.getSize() << "\n"
       << "SCALARS CellColor int 1\n"
       << "LOOKUP_TABLE default\n";

  for(int i = 0; i < m_triangles.getSize(); ++i)
    {
      const Triangle & tr = m_triangles[i];
      const Pixel & pixel = tr.barycenter();
      file << pixel.getColor() << "\n";
    }

}


#endif
