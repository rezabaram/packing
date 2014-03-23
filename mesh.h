#ifndef MESH_H
#define MESH_H 
#include<vector>
#include<Eigen>

template<int dim=3>
using vec=Eigen::Matrix<double, dim, 1>;

template<int>
class Face;

template<int dim=3>
class Vertex: public Eigen::Matrix<double, dim, 1>
	{
	using _vec=vec<dim>;
	public:
	int id;
	Vertex(const _vec &v, int _id):_vec(v), id(_id){}
	std::vector<std::shared_ptr<Face<dim>>> faces;
 	private:
	};

template<int dim=3>
using pVertex=std::shared_ptr<Vertex<dim>>;
//using pVertex=std::unique_ptr<Vertex<dim>>;

template<int dim=3>
class Face 
	{
	bool closed;
	public:
	std::vector<pVertex<dim>> vertices;
	std::vector<int> vv;
	//Face(std::initializer_list<Vertex<dim> > &&vl):closed{false}{
		//for( auto v  : vl) add(*v);
		//close();
		//}

	bool add_vertex(pVertex<dim> v){
		if(closed)return false;
		vertices.push_back(v);
		return true;
		}

	bool is_closed()const {return closed;}

	bool close(){
		if(closed) return true;
		if(vertices.size()<3)return false; 
		add_vertex(*(vertices.begin()));//add the first vertex to end
		closed=true;
		return closed;
		}

	template<int dim2>
	friend std::ostream & operator<< (std::ostream &out, const Face<dim2> &s);
 	private:
	};

template<int dim>
std::ostream & operator<< (std::ostream &out, const Face<dim> &s){
	int trunc=0;
	if(s.closed)trunc=1;
	for(auto it=s.vertices.begin(); it!=s.vertices.end()-trunc ; it++)
		//out<<(*x).transpose()<<std::endl;
		out<<(*it)->id<< "  ";
	return out;
	}

#endif /* MESH_H */
