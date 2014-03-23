#ifndef SPHERE_H
#define SPHERE_H 
using namespace Eigen;
#include<iostream>
#include<ostream>


template<int dim=2>
class Sphere
	{
	public:

	using vec=Matrix<double, dim,1>;
	using ivec=Matrix<double, dim+2, 1>;
	//using vec=Matrix<double, 2, 1>;
	//using ivec=Matrix<double,2+2, 1>;
	vec _c;
	ivec _ic;
	//Matrix<double, 2+2, 1> _ic;
	double _r;
	bool need_update;

	Sphere(vec c=vec(), double r=1):_c{c},_r{r},need_update{true} {inv_coord();}
	Sphere& scale(const double a){
		_r*=a;
		need_update=true;
		return *this;
		};
	Sphere& shift(const vec & a){
		_c+=a;
		need_update=true;
		return *this;
		};

	
	ivec inv_coord(){
		if(need_update){
		_ic.template block<dim,1>(0,0)=_c/_r;
		_ic(dim)=(_c.dot(_c)-_r*_r -1)/(2*_r);
		_ic(dim+1)=(_c.dot(_c)-_r*_r +1)/(2*_r);
		need_update=false;
		}
		return _ic;
		}

	vec &coord(){
		_r=1/(_ic(dim+1)-_ic(dim));
		_c=_r*_ic.template block<dim,1>(0,0);
		return _c;
		}

	template<int _dim>
	friend std::ostream & operator<< (std::ostream &out, const Sphere<_dim> &s);
	template<int _dim>
	friend std::istream & operator>>(std::istream &in, Sphere<_dim> &s);

 	private:

	};

template<int dim>
std::ostream & operator<< (std::ostream &out, const Sphere<dim> &s){
	out<<s._c.transpose()<<"  "<<s._r<<std::endl;
	return out;
	}

template<int dim>
std::istream & operator>>(std::istream &in, Sphere<dim> &s){
	in>>s._c;
	in>>s._r;
	return in;
	}

template<int dim=2>
class InvSphere: public Sphere<dim>{
	using imat=Matrix<double, dim+2, dim+2>;
	using vec=typename Sphere<dim>::vec;
	using ivec=typename Sphere<dim>::ivec;
	public:
	imat _M;
	InvSphere(const Sphere<dim> &s):Sphere<dim>(s){
		ivec v;	
		for(auto i=0; i<dim+2; i++)v(i)=1;
		_M=v*this->_ic.transpose();
		_M.col(dim+1)*=-1;
		for(auto i=0; i<dim+2; i++){
			_M.row(i)=this->_ic(i)*_M.row(i);
			}
		_M*=-2;
		_M+=MatrixXd::Identity(dim+2,dim+2);
		}
	
	Sphere<dim> Invert(const Sphere<dim> &S){
		Sphere<dim> Sp;
		Sp._ic=_M*S._ic;
		Sp.coord();
		return std::move(Sp);
		}

	double dot (Sphere<dim> &s){
		ivec iv=s.inv_coord();
		iv(dim+1)*=-1;	
		return this->inv_coord().dot(iv);
	}
};




#endif /* SPHERE_H */
