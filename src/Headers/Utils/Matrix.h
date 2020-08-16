#ifndef MATRIX_H
#define MATRIX_H
#include <typeinfo>
#include <cmath>
/*
 *
 * This Matrix Header File Created By Rahul Mishra
 * ABLE TO PERFORM BASIC OPERATION LIKE
 * +,-,/,*,Determinant
 * YET TO BE ADD
 * ADJ MATRIX AND INVERSE MATRIX
 *  --ITS NECESSAY TO USE THIS HEADER FILE WITH <cmath> <typeinfo> <iostream> <vector>--
 *  <typeinfo> IS FOR typeid() operator
 *   cmath for pow()
 */

namespace Basic_C {
	template<typename type>
	class Matrix
	{
		unsigned int ncol;
		unsigned int nrow;
		unsigned int size;


		type def;
		type** Mat;
	public :
		Matrix();
		Matrix(unsigned int, unsigned int, type def = type());
		~Matrix();

		bool Transpose();
		type det();
		Matrix<type> operator+ (Matrix<type>);
		Matrix<type> operator- (Matrix<type>);
		Matrix<type> operator* (Matrix<type>);
		Matrix<type> operator* (type);
        void operator*= (Matrix<type>);
        void operator*= (type);

        void operator+= (Matrix<type>);
        void operator-= (Matrix<type>);

	    type* operator[] (unsigned int);


		static Matrix<type> getIdentity(unsigned int);

		unsigned int getncol();
		unsigned int getnrow();

		type* getLinearPtr(bool colm = false);
		void Print();
	};
	template<typename type>
	Matrix<type>::Matrix() {
		def = 0;
		ncol = nrow = size = 0;
		Mat = NULL;
	}
	template<typename type>
	Matrix<type>::Matrix(unsigned int arow,unsigned int acol,type adef): nrow(arow), ncol(acol), def(adef) {
		size = ncol * nrow;
		Mat = (type**)calloc(nrow, sizeof(type*));
		if (!Mat) {
			STOP("CANT ALLOCATED");
		}
		for (unsigned int i = 0;i < nrow; i++) {
			Mat[i] = (type*)calloc(ncol, sizeof(type));
			for (unsigned int j = 0;j < ncol;j++) {
				Mat[i][j] = def;
			}
		}
	}
	template<typename type>
	bool Matrix<type>::Transpose() {
		if (ncol != nrow)
			return false;
		for (unsigned int i = 0; i < nrow; i++) {
			for (unsigned int j = 0;j < ncol;j++) {
				if (i == j)
					continue;
				type tmp = Mat[i][j];
				Mat[i][j] = Mat[j][i];
				Mat[j][i] = tmp;
			}
		}
		return true;
	}
	template<typename type>
	Matrix<type> Matrix<type>::operator+ (Matrix<type> am) {
		if (am.nrow == nrow && am.ncol == ncol) {
			Matrix<type> tmp(nrow,ncol,0);
			for (unsigned int i = 0;i < nrow;i++) {
				for (unsigned int j = 0;j < ncol;j++) {
					tmp[i][j] = (*this)[i][j] + am[i][j];
				}
			}
			return tmp;
		}
		return Matrix<type>();
	}
	template<typename type>
	Matrix<type> Matrix<type>::operator- (Matrix<type> am) {
		if (am.nrow == nrow && am.ncol == ncol) {
			Matrix<type> tmp(nrow,ncol,0);
			for (unsigned int i = 0;i < nrow;i++) {
				for (unsigned int j = 0;j < ncol;j++) {
					tmp[i][j] = (*this)[i][j] - am[i][j];
				}
			}
			return tmp;
		}
		return Matrix<type>();
	}
	template<typename type>
	Matrix<type> Matrix<type>::operator* (Matrix<type> am) {
		if (ncol == am.nrow) {
			Matrix<type> tmp(nrow, am.ncol, 0);
			for (unsigned int i = 0; i < nrow; i++) {
				for (unsigned int j = 0; j < am.ncol;j++) {
					for (unsigned int k = 0; k < ncol;k++) {
						tmp[i][j] += (*this)[i][k] * am[k][j];
					}
				}
			}
			return tmp;
		}
		return Matrix<type>();
	}

	template<typename type>
	void Matrix<type>::operator*= (Matrix<type> am) {
		if (ncol == am.nrow) {
			Matrix<type> tmp(nrow, am.ncol, 0);
			for (unsigned int i = 0; i < nrow; i++) {
				for (unsigned int j = 0; j < am.ncol;j++) {
					for (unsigned int k = 0; k < ncol;k++) {
						tmp[i][j] += (*this)[i][k] * am[k][j];
					}
				}
			}
			(*this) = tmp;
		}
	}
	template<typename type>
    void Matrix<type>::operator+= (Matrix<type> am){
       if(ncol == am.ncol && nrow == am.nrow){
        for(unsigned int i = 0; i < nrow; i++)
            for(unsigned int j = 0; j < ncol; j++)
             (*this)[i][j] += am[i][j];
       }
    }
    template<typename type>
    void Matrix<type>::operator-= (Matrix<type> am){
       if(ncol == am.ncol && nrow == am.nrow){
        for(unsigned int i = 0; i < nrow; i++)
            for(unsigned int j = 0; j < ncol; j++)
             (*this)[i][j] += am[i][j];
       }
    }

	template<typename type>
	Matrix<type> Matrix<type>::operator* (type scalar) {
		Matrix<type> tmp(nrow, ncol, 0);
		for (unsigned int i = 0; i < nrow; i++)
			for (unsigned int j = 0;j < ncol;j++)
				tmp[i][j] = (*this)[i][j] * scalar;
		return tmp;
	}

	template<typename type>
	void Matrix<type>::operator*= (type scalar) {
		for (unsigned int i = 0; i < nrow; i++)
			for (unsigned int j = 0;j < ncol;j++)
				(*this)[i][j] *= scalar;
	}
	template<typename type>
	type* Matrix<type>::operator[] (unsigned int i) {
		if (i > nrow - 1)
			return NULL;
		return Mat[i];
	}
	template<typename type>
	Matrix<type> Matrix<type>::getIdentity(unsigned int order) {
		Matrix<type> tmp(order, order, 0);
		for (unsigned int i = 0; i < order;i++)
			tmp[i][i] = 1;
		return tmp;
	}
	template<typename type>
	type* Matrix<type>::getLinearPtr(bool colm ) {
		type* tmp = (type*)malloc(size * sizeof(type));
		if (!tmp)
			return NULL;
		for (unsigned int i = 0; i < size;i++) {
            if(!colm)
			tmp[i] = Mat[i/nrow][i % ncol];
            else
            tmp[i] = Mat[i % nrow][i / ncol];
		}
		return tmp;
	}
	template<typename type>
	unsigned int Matrix<type>::getncol() {
		return ncol;
	}
	template<typename type>
	unsigned int Matrix<type>::getnrow() {
		return nrow;
	}
	
	template<typename type>
	void Matrix<type>::Print() {
		for (unsigned int i = 0;i < nrow;i++) {
			for (unsigned int j = 0;j < ncol;j++)
				std::cout << Mat[i][j] << " ";
			std::cout << std::endl;
		}
	}
	template<typename type>
	Matrix<type>::~Matrix() {
	}
}//END OF NAMESPACE
#endif
namespace Basic {
	template<typename type>
	class Matrix
	{
		unsigned int ncol;
		unsigned int nrow;
		unsigned int size;


		type def;
		std::vector<std::vector<type> > Mat;
	public:
		Matrix();
		Matrix(unsigned int, unsigned int, type def = type());
		~Matrix();

		bool Transpose();
		type det();
		Matrix<type> operator+ (Matrix<type>);
		Matrix<type> operator- (Matrix<type>);
		Matrix<type> operator* (Matrix<type>);
		Matrix<type> operator* (type);
		void operator*= (Matrix<type>);
		void operator*= (type);

		void operator+= (Matrix<type>);
		void operator-= (Matrix<type>);

		std::vector<type>& operator[] (unsigned int);


		static Matrix<type> getIdentity(unsigned int);

		unsigned int getncol();
		unsigned int getnrow();

		type* getLinearPtr(bool colm = false);
		void Print();
	};
	template<typename type>
	Matrix<type>::Matrix() {
		def = 0;
		ncol = nrow = size = 0;
	}
	template<typename type>
	Matrix<type>::Matrix(unsigned int arow, unsigned int acol, type adef) : nrow(arow), ncol(acol), def(adef) {
		size = ncol * nrow;
		Mat.resize(nrow);
		for (unsigned int i = 0;i < nrow; i++) {
			Mat[i].resize(ncol);
		}
	}
	template<typename type>
	bool Matrix<type>::Transpose() {
		if (ncol != nrow)
			return false;
		for (unsigned int i = 0; i < nrow; i++) {
			for (unsigned int j = 0;j < ncol;j++) {
				if (i == j)
					continue;
				type tmp = Mat[i][j];
				Mat[i][j] = Mat[j][i];
				Mat[j][i] = tmp;
			}
		}
		return true;
	}
	template<typename type>
	Matrix<type> Matrix<type>::operator+ (Matrix<type> am) {
		if (am.nrow == nrow && am.ncol == ncol) {
			Matrix<type> tmp(nrow, ncol, 0);
			for (unsigned int i = 0;i < nrow;i++) {
				for (unsigned int j = 0;j < ncol;j++) {
					tmp[i][j] = Mat[i][j] + am[i][j];
				}
			}
			return tmp;
		}
		return Matrix<type>();
	}
	template<typename type>
	Matrix<type> Matrix<type>::operator- (Matrix<type> am) {
		if (am.nrow == nrow && am.ncol == ncol) {
			Matrix<type> tmp(nrow, ncol, 0);
			for (unsigned int i = 0;i < nrow;i++) {
				for (unsigned int j = 0;j < ncol;j++) {
					tmp[i][j] = Mat[i][j] - am[i][j];
				}
			}
			return tmp;
		}
		return Matrix<type>();
	}
	template<typename type>
	Matrix<type> Matrix<type>::operator* (Matrix<type> am) {
		if (ncol == am.nrow) {
			Matrix<type> tmp(nrow, am.ncol, 0);
			for (unsigned int i = 0; i < nrow; i++) {
				for (unsigned int j = 0; j < am.ncol;j++) {
					for (unsigned int k = 0; k < ncol;k++) {
						tmp[i][j] += Mat[i][k] * am[k][j];
					}
				}
			}
			return tmp;
		}
		return Matrix<type>();
	}

	template<typename type>
	void Matrix<type>::operator*= (Matrix<type> am) {
		if (ncol == am.nrow) {
			Matrix<type> tmp(nrow, am.ncol, 0);
			for (unsigned int i = 0; i < nrow; i++) {
				for (unsigned int j = 0; j < am.ncol;j++) {
					for (unsigned int k = 0; k < ncol;k++) {
						tmp[i][j] += Mat[i][k] * am[k][j];
					}
				}
			}
			(*this) = tmp;
		}
	}
	template<typename type>
	void Matrix<type>::operator+= (Matrix<type> am) {
		if (ncol == am.ncol && nrow == am.nrow) {
			for (unsigned int i = 0; i < nrow; i++)
				for (unsigned int j = 0; j < ncol; j++)
					Mat[i][j] += am[i][j];
		}
	}
	template<typename type>
	void Matrix<type>::operator-= (Matrix<type> am) {
		if (ncol == am.ncol && nrow == am.nrow) {
			for (unsigned int i = 0; i < nrow; i++)
				for (unsigned int j = 0; j < ncol; j++)
					Mat[i][j] += am[i][j];
		}
	}

	template<typename type>
	Matrix<type> Matrix<type>::operator* (type scalar) {
		Matrix<type> tmp(nrow, ncol, 0);
		for (unsigned int i = 0; i < nrow; i++)
			for (unsigned int j = 0;j < ncol;j++)
				tmp[i][j] = (*this)[i][j] * scalar;
		return tmp;
	}

	template<typename type>
	void Matrix<type>::operator*= (type scalar) {
		for (unsigned int i = 0; i < nrow; i++)
			for (unsigned int j = 0;j < ncol;j++)
				Mat[i][j] *= scalar;
	}
	template<typename type>
	std::vector<type>& Matrix<type>::operator[] (unsigned int i) {
		if (i > nrow - 1) {
			STOP("OUT Of Bounds");
		}

		return Mat[i];
	}
	template<typename type>
	Matrix<type> Matrix<type>::getIdentity(unsigned int order) {
		Matrix<type> tmp(order, order, 0);
		for (unsigned int i = 0; i < order;i++)
			tmp[i][i] = 1;
		return tmp;
	}
	template<typename type>
	type* Matrix<type>::getLinearPtr(bool colm) {
		type* tmp = (type*)malloc(size * sizeof(type));
		if (!tmp)
			return NULL;
		for (unsigned int i = 0; i < size;i++) {
			if (!colm)
				tmp[i] = Mat[i / nrow][i % ncol];
			else
				tmp[i] = Mat[i % nrow][i / ncol];
		}
		return tmp;
	}
	template<typename type>
	unsigned int Matrix<type>::getncol() {
		return ncol;
	}
	template<typename type>
	unsigned int Matrix<type>::getnrow() {
		return nrow;
	}

	template<typename type>
	void Matrix<type>::Print() {
		for (unsigned int i = 0;i < nrow;i++) {
			for (unsigned int j = 0;j < ncol;j++)
				std::cout << Mat[i][j] << " ";
			std::cout << std::endl;
		}
	}
	template<typename type>
	Matrix<type>::~Matrix() {
	}

}