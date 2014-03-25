#ifndef PACKING_H
#define PACKING_H 
#include<vector>
#include"solids.h"
using namespace std;

template<int dim=2>
class Packing
	{
	public:
	using sphereVec=vector<Sphere<dim> >;
	using iSphereVec=vector<InvSphere<dim> >;
	iSphereVec invs;	
	sphereVec inits;	
	sphereVec pack;	
	Packing(sphereVec init_s=sphereVec(), iSphereVec inv_s=iSphereVec()):inits{init_s},invs{inv_s}, pack{init_s}{}

	Solid<dim> solid;

	void add_init(const Sphere<dim> &s){
		inits.push_back(s);
		cout<< s <<endl;
		return;
	}

	void add_inv(const Sphere<dim> &s){
		invs.push_back(s);
		//cout<< s <<endl;
		return;
	}

	void add_sphere(const Sphere<dim> &s){
		//pack.push_back(s);
		cout<< s <<endl;
		return;
	}

	void generate(int maxgen=1000, double minr=0.001){
		for(auto & s : inits ){
			int gen=0;	
			iterate(s, maxgen, minr);
		}
	}

	void iterate(Sphere<dim> &s, int gen, double minr){
		
		if(gen==0) return;

		Sphere<dim> temp;	
		for(auto &is : invs){
		
			if(is.dot(s)<-1+1e-12){
				temp=is.Invert(s);
				if(fabs(temp._r) < minr) continue;
				add_sphere(temp);
				iterate(temp, gen-1, minr);
			}
			
		}
	}

	void build_init_config();
 	private:
};

template<int dim>
void Packing<dim>::build_init_config(){
	
	double scale=1;
	double r=1;
	auto x1=*(solid.faces[0]->vertices[0]);
	auto x2=*(solid.faces[0]->vertices[1]);
	r= (x1-x2).norm()/2;
	scale=1/(1+r);
	r*=scale;
	//initial spheres
	for (auto &px : solid.vertices){
		auto x=scale*(*px);
		add_init(Sphere<dim>(x,r));
	}
	std::cerr<<"init r="<< r <<std::endl;

	//inversion spheres
	for (auto &face: solid.faces){

		Matrix<double,dim,dim> M;
		Matrix<double,dim,1> B;
		int i=0;
		for (auto &px : face->vertices){
			auto x=*px;
			if(i>=dim)break;//dim intersecting planes are enough
			
			M.template block<1,dim>(i,0)=x;
			B(i,0)=x.dot(x);
			i++;
		} 

		auto x=*(face->vertices[0]);
		Matrix<double,dim,1>  A=M.inverse()*B;
		double ir= (A-x).norm();
		add_inv(Sphere<dim>(A,ir));
		
		//std::cerr<< (A-*(face->vertices[0])) <<std::endl;

	std::cerr<<"inv r="<< ir <<std::endl;
	}

	//central inv sphere
	auto x=scale*(x2+x1)/2;//midpoint of an edge
	auto o=vec<dim>::Zero(); 
	add_inv(Sphere<dim>(o,x.norm()));
	//enveloping sphere
	add_init(Sphere<dim>(o,-1));

	
	
}
#endif /* PACKING_H */
