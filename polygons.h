#ifndef POLYGONS_H
#define POLYGONS_H 
#include"packing.h"
#include"solids.h"

Packing<2> polygon_packing(int N=3){

double ir=tan(M_PI/N);
double id=ir/sin(M_PI/N);
double r=sin(M_PI/N)/(1+sin(M_PI/N));
double d=1-r;

Packing<2> pack;
pack.add_init(Sphere<2>(Vector2d(0,0),-1));

for(double i=0; i<N; i++){
	double theta1=2*i*M_PI/N;
	double theta2=(2*i+1)*M_PI/N;
	Vector2d v1(cos(theta1),sin(theta1)), v2(cos(theta2),sin(theta2));
	v1*=d;
	v2*=id;
	pack.add_init(Sphere<2>(v1,r));
	pack.add_inv(Sphere<2>(v2,ir));
	InvSphere<2> &a=pack.invs.back();
	EigenSolver<MatrixXd> es(a._M);
	cerr<<es.eigenvalues()<<endl;
	cerr<<es.eigenvectors()<<endl;
	
	}

Vector2d v3(0,0);
pack.add_inv(Sphere<2>(v3,id-ir));

return std::move(pack);
}

#endif /* POLYGONS_H */
