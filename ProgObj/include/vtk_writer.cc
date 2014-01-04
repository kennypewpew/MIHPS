// Includes à ne pas oublier
// #include <map>
// #include <sstream>
// #niclude <fstream>

void Maillage::
sauvegarde(const char * filename) const
{
  std::cout << "Saving '" << filename << "' with " << m_triangles.taille() << " triangles\n";

  // VTK File formats : www.vtk.org/VTK/img/file-formats.pdf

  std::ofstream file(filename);
  file << "# vtk DataFile Version 3.0\n"
       << "Maillage d'image\n"
       << "ASCII\n"
       << "DATASET UNSTRUCTURED_GRID\n"
       << "\n"
       << "POINTS ";

  std::map<int,int> coord_to_pos;
  std::ostringstream nodedata_oss;

  {
    std::ostringstream node_oss;
    for(int i=0;i<m_triangles.taille();++i)
      {
	const Triangle & tr = m_triangles[i];
	for(int j=0;j<3;++j)
	  {
	    const Pixel & pixel = tr(j);
	    std::pair<std::map<int,int>::iterator,bool> inserter
	      = coord_to_pos.insert(std::make_pair<int,int>(m_image.numero(pixel),coord_to_pos.size()));
	    if (inserter.second)
	      {
		node_oss << +pixel.x() << " " << -pixel.y() << " 0\n";
		nodedata_oss << pixel.couleur() << "\n";
	      }
	  }
      }
    file << coord_to_pos.size() << " float\n";
    file << node_oss.str() << "\n";
  }
  
  file << "CELLS " 
       << m_triangles.taille() << " "
       << 4*m_triangles.taille() << "\n";
  for(int i=0;i<m_triangles.taille();++i)
    {
      const Triangle & tr = m_triangles[i];
      file << "3 ";
      for(int j=0;j<3;++j)
	{
	  const Pixel & pixel = tr(j);
	  file << coord_to_pos[m_image.numero(pixel)] << " ";
	}
      file << "\n";
    }
  file << "\n";

  file << "CELL_TYPES " << m_triangles.taille() << "\n";
  for(int i=0;i<m_triangles.taille();++i)
    {
      file << "5\n";
    }
  file << "\n";

  file << "CELL_DATA " << m_triangles.taille() << "\n"
       << "SCALARS cell_data int 1\n"
       << "LOOKUP_TABLE default\n";
  for(int i=0;i<m_triangles.taille();++i)
    {
      const Triangle & tr = m_triangles[i];
      file << tr.barycentre().couleur() << "\n";
    }
  file << "\n";

  file << "POINT_DATA " << coord_to_pos.size() << "\n"
       << "SCALARS node_data int 1\n"
       << "LOOKUP_TABLE default\n";
  file << nodedata_oss.str();
}
