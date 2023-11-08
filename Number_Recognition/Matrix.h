

// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
using std::ostream;
using std::istream;
/**
 *
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
	int rows, cols;
} matrix_dims;


class Matrix{
private:
    int _rows;
    int _cols;
    float* _matrix;

public:

    Matrix( int rows, int cols);
    Matrix();
    Matrix(const Matrix& m);
    ~Matrix();
    int get_rows() const;
    int get_cols() const;
    Matrix& transpose();
    Matrix& vectorize();
    void plain_print() const;
    Matrix dot(Matrix& m );
    float operator()(int i  , int j) const;
    float& operator()(int i  , int j);
    float& operator[](int k) ;
    float operator[](int k) const ;
    friend Matrix operator+(const Matrix& m1 , const Matrix& m);
    Matrix& operator=(const Matrix& m);
    float norm();
    friend Matrix operator*(const Matrix& m1 , const Matrix& m ) ;
    Matrix operator*(float c) const;
    friend Matrix operator*(float c , const Matrix& m);
    Matrix& operator+=(const Matrix& m );
    friend ostream& operator<<(ostream& os ,const Matrix& m);
    friend istream& operator>> (istream& is, Matrix& m);
};

#endif //MATRIX_H