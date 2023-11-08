#include "Matrix.h"
#include <iostream>
#include <cmath>
using std::iostream;
#define MINIMAL_REQ 0.1


Matrix::Matrix( int rows, int cols)
{
    if (rows < 1 || cols <1)
    {
        throw std::length_error("matrix instalziation error");
    }
    _cols = cols;
    _rows = rows;
    int length = rows * cols;
    _matrix = new float[length];
    for(int i= 0 ; i< length ; i++)
    {
        _matrix[i] = 0;
    }
}

Matrix::Matrix()
{
    _cols = 1;
    _rows = 1;
    _matrix = new float[1];
    _matrix[0] = 0;

}
Matrix::Matrix(const Matrix& m )
{

    _cols = m.get_cols();
    _rows = m.get_rows();
    int length = _cols*_rows;

    _matrix = new float[length];
    for (int i = 0; i < _cols * _rows; ++i) {
        _matrix[i]=m._matrix[i];
    }
}

Matrix::~Matrix()
{
    delete[] _matrix;
}

int Matrix::get_rows() const
{
    return _rows;
}

int Matrix::get_cols() const
{
    return _cols;
}

Matrix& Matrix::transpose()
{

    Matrix new_m(_cols , _rows);
    for(int i = 0 ; i < _rows ; i++)
    {
        for(int j = 0 ; j<_cols ; j++)
        {
            new_m(j,i) = (*this)(i,j);

        }
    }
    *this = new_m;
    return (*this);
}


Matrix& Matrix::vectorize()
{

    _rows = _rows*_cols;
    _cols = 1;
    return (*this);
}

void Matrix::plain_print() const
{
    for (int i =0 ; i < _rows ; i++)
    {
        for(int j = 0 ; j< _cols ; j++)
        {
            std::cout << _matrix[i*get_cols() + j] <<" ";
        }
        std::cout<< std::endl;

    }
}

Matrix Matrix::dot(Matrix& m)
{
    if(_cols!= m._cols || _rows != m._rows)
    {
        throw std::length_error(" in dot function lengths are ");
    }
    Matrix new_m(_rows , _cols);
    for(int i = 0 ; i< _rows  ; i++)
    {
        for(int j = 0 ; j< _cols; j++)
        {
            new_m(i,j) =  (*this)(i,j) * m(i,j);
        }
    }
    return new_m;

}


float& Matrix::operator[](int k)
{
    if(k < 0 || k>= _cols*_rows)
    {
        throw std::out_of_range("indexes out of range");
    }
    return _matrix[k];
}
float& Matrix::operator()(int i  , int j)
{
    if((i < 0 || i>= _rows || j<0 || j >= _cols))
    {
        throw std::out_of_range("indexes out of range");
    }
    return (*this)._matrix[(i)*_cols + (j)];
}

float Matrix::operator[](int k) const
{
    if(k < 0 || k >= _cols*_rows)
    {
        throw std::out_of_range("indexes out of range");
    }
    return _matrix[k];
}
float Matrix::operator()(int i  , int j) const
{
    if((i < 0 || i>= _rows|| j<0 || j >= _cols))
    {
        throw std::out_of_range("indexes out of range");
    }
    return ((*this)._matrix[i*_cols + j]);
}

Matrix operator+(const Matrix& m1 ,const Matrix& m)
{
    if(m1.get_cols() != m.get_cols() || m1.get_rows() != m.get_rows())
    {
        throw std::length_error("matrix dont have same sizes");
    }
    Matrix new_m(m1.get_rows() , m1.get_cols());
    for(int i=0; i< m1.get_rows() ; i++)
    {
        for(int j = 0 ; j< m1.get_cols() ; j++)
        {
            int index= i*m1.get_cols() + j;
            new_m[index] = m1[index] + m[index];
        }
    }
    return new_m;
}

Matrix& Matrix::operator=(const Matrix& m)
{
    if(this == &m)
    {
        return *this;
    }
    delete[] _matrix;

    _rows = m._rows;
    _cols = m._cols;
    int length = _rows * _cols;
    _matrix = new float[length];
    for(int i = 0 ; i<_rows ; i++)
    {
        for(int j = 0; j<_cols ; j++)
        {
            _matrix[i*_cols +j ] = m._matrix[i*_cols +j ];
        }
    }
    return *this;
}

float Matrix::norm()
{
    float sum = 0;
    for (int i = 0; i<_rows  ; i++)
    {
        for(int j = 0; j<_cols  ; j++)
        {
            float index_num = (*this)(i,j);
            sum += pow(index_num , 2);
        }

    }
    sum = sqrt(sum);
    return sum;
}

Matrix operator*(const Matrix& m , const Matrix& m1 )
{
    if(m1.get_rows() != m.get_cols())
    {
        throw std::length_error("matrixs dont have same length");
    }
    float sum = 0;
    Matrix new_m(m.get_rows(),m1.get_cols());
    for(int i=0 ; i<new_m.get_rows() ; i++)
    {
        for(int j=0 ; j < new_m.get_cols() ; j++)
        {
            for(int index_r = 0; index_r< m.get_cols() ; index_r ++)
            {
                sum+=  m(i,index_r) * m1(index_r,j);
            }
            new_m(i,j) = sum;
            sum = 0;
        }
    }
    return new_m;
}

Matrix Matrix::operator*(float c) const
{
    Matrix new_m(_cols , _rows);
    new_m = (*this);
    for(int i= 0 ; i< _rows ; i++)
    {
        for(int j = 0 ; j<_cols ; j++)
        {
            new_m._matrix[i*_cols +j] = c * new_m._matrix[i*_cols +j] ;
        }
    }
    return new_m;
}

Matrix operator*(float c,const Matrix& m )
{
    Matrix new_m(m.get_rows() , m.get_cols());
    new_m = m*c;
    return new_m;
}


Matrix& Matrix::operator+=(const Matrix& m )
{
    (*this) = (*this) + m;
    return (*this);
}

ostream& operator<<(ostream& os ,const Matrix& m)
{
    for(int i = 0 ; i< m.get_rows() ; i++)
    {
        for (int j= 0 ; j<  m.get_cols()   ; j++)
        {

            if(m(i,j) > MINIMAL_REQ)
            {
                os << "**";
            }
            else
            {
                os<< "  ";
            }
        }
        os<<std::endl;
    }
    return os;
}

istream& operator>>(istream& is, Matrix& m)
{
    int length = m.get_cols() * m.get_rows();
    is.read((char*)m._matrix , length * sizeof(float));
    return is;
}