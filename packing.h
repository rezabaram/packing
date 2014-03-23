#ifndef PACKING_H
#define PACKING_H 
#include<vector>
#include"solids.h"
using namespace std;

template<int dim=3>
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
		cout<< s <<endl;
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
	
	for (auto &px : solid.vortices){
	
	Matrix<double,dim,dim>
	
	
	}
}
#endif /* PACKING_H */
