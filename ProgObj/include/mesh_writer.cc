// Includes à ne pas oublier
// #include <map>
// #include <sstream>
// #include <fstream>

void Mesh::
save(const char * filename) const
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
	  mean_color += pixel.couleur();
	}
      mean_color /= 3;
      file << mean_color << "\n";
    }
}
