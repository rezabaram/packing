#ifndef MATRIX_H
#define MATRIX_H 
#include<assert.h>

using indexT=unsigned int;

template<indexT dim1=3, indexT dim2=3> 
class Matrix{
	double data[dim1*dim2]; //suppose this will poindexT to data
	double _get1(indexT i, indexT j){return data[i*M+j];} //used to access normally
	double _get2(indexT i, indexT j){return data[j*N+i];} //used when transposed

	indexT M, N; //dimensions
	public:
	double (Matrix::*get_p)(indexT, indexT); //functor to access elements  
	Matrix():M(dim1), N(dim2){
		get_p=&Matrix::_get1; // initialised with normal access 
		}

	double get(indexT i, indexT j){
		assert(i<M && j<N);
		return (this->*get_p)(i,j);
		}

	void init(){
		for(indexT i=0; i<N*M; i++){
			data[i]=i;
			}
		 }

	void transpose(){ //twice transpose gives the original
		if(get_p==&Matrix::_get1) get_p=&Matrix::_get2;
		else get_p=&Matrix::_get1; 
		swap(M,N);
		}
	~Matrix(){ }
};

#endif /* MATRIX_H */
