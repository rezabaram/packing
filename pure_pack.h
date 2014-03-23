#ifndef PURE_PACK_H
#define PURE_PACK_H 

Packing pure_packing(int N=4){

double ir=tan(M_PI/N);
double id=ir/sin(M_PI/N);
double r=sin(M_PI/N);
double a=sqrt(2/(1+cos(M_PI/(1+2))));
double b=sqrt((1-a*a*r*r)/(r*r));
double rp=b*r;
r*=a;
rp/=(1+r);
r/=(1+r);

double d=1-r;

Packing pack;
pack.add_init(Sphere<2>(Vector2d(0,0),-1));

for(double i=0; i<N; i++){
	double theta1=2*i*M_PI/N;
	double theta2=(2*i+1)*M_PI/N;
	Vector2d v1(cos(theta1),sin(theta1)), v2(cos(theta2),sin(theta2));
	v1*=d;
	v2*=id;
	pack.add_inv(Sphere<2>(v1,r));
	pack.add_inv(Sphere<2>(v2,ir));
	//InvSphere<2> &a=pack.invs.back();
	//EigenSolver<MatrixXd> es(a._M);
	//cerr<<es.eigenvalues()<<endl;
	//cerr<<es.eigenvectors()<<endl;
	
	}

Vector2d v3(0,0);
//pack.add_inv(Sphere<2>(v3,id-ir));
pack.add_inv(Sphere<2>(v3,rp));

return std::move(pack);
}
#endif /* PURE_PACK_H */
