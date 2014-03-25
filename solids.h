#ifndef SOLIDS3D_H
#define SOLIDS3D_H 
#include<vector>
#include<istream>
#include<Eigen>
#include"mesh.h"

template<int dim=3>
class Solid {
	using _vec=vec<dim>;
	static int nnodes;
	public:
	std::string name;
	std::vector<std::shared_ptr<Vertex<dim>>> vertices;
	std::vector<std::shared_ptr<Face<dim>>> faces;
	Solid(const std::string &_name=""):name(_name){}

	void add_vertex(const _vec &v){
		vertices.push_back(std::shared_ptr<Vertex<dim>>(new Vertex<dim>(v, nnodes)));
		++nnodes;
		}

	void read_vertices(std::istream &in){
		_vec v;
		std::string x;
		for(auto i=0; i<dim; i++) {in>> x; 
			v(i)=std::stod(x);};
		v.normalize();
		add_vertex(v);
	}

	void read_faces(std::istream &in){
		std::vector<int> ind;
		std::string x;
		while(in>>x) ind.push_back(std::stoi(x));
		add_face(ind);
	}

	void print_vertices(){
		
		std::cout<<vertices.size()<<std::endl;
		for(auto v : vertices)
			std::cout<<v->transpose() <<std::endl;
	}

	void add_face(const std::vector<int> &ind){
		std::shared_ptr<Face<dim>> p=std::shared_ptr<Face<dim>>(new Face<dim>());
		for(auto i : ind)p->add_vertex(vertices.at(i));
		p->close();
		faces.push_back(p);
	}

	void print_faces(){
		std::cout<<faces.size()<<std::endl;
		for(auto f : faces) std::cout<<*f<<std::endl;
	}

	void parse(std::istream &inputFile);
 	private:
};

template<int dim>
int Solid<dim>::nnodes=0;

const std::string comm="#";
template<int dim>
void Solid<dim>::parse(std::istream &inputFile) {
	std::string line;
	std::string vname;

	//read OFF file
	
	if(!getline(inputFile,line)) return;
	std::stringstream ss0(line);
	std::string format;
	ss0>>format;
	if(format!="OFF"){std::cerr<<"Input file should be OFF"<<std::endl;return;}

	if(!getline(inputFile,line)) return;
	std::stringstream ss1(line);
	int n_vertices;
	int n_faces;
	int n_edges;
	ss1>>n_vertices>>n_faces>>n_edges;
	for(auto i=0; i<n_vertices && getline(inputFile,line); i++){
		std::stringstream ss(line);
		read_vertices(ss);
	}

	
	
	for(auto i=0; i<n_faces && getline(inputFile,line); i++){
		std::stringstream ss(line);
		read_faces(ss);
	}


	//std::cerr<<line <<std::endl;
//	line = line.substr( 0, line.find(comm) );
//	if(line.size()==0) continue;

	//Insert the line string into a stream
	
	

	//ss >> vname;

	//this->name=vname;
	//Skip to next line if this one starts with a # (i.e. a comment)
	//if(vname.find("#",0)==0) continue;


	//if(){
		//cerr<< "Warning: "<<vname<<" is not a valid parameter or keyword" <<endl;
		//continue;
		//}

}

#endif /* SOLIDS3D_H */
