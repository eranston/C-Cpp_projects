//
// Created by 1eran on 20/05/2022.
//
#include "Activation.h"
#include <cmath>


Matrix activation::relu(const Matrix& m )
{

    Matrix new_m(m.get_rows(),m.get_cols());
    for(int i = 0 ; i< m.get_rows() ; i++)
    {
        for(int j = 0; j< m.get_cols(); j++)
        {

            if(m(i,j) >= 0)
            {
                new_m(i,j) = m(i,j);
            }
            else{
                new_m(i,j) = 0;
            }
        }

    }
    return new_m;

}

Matrix activation::softmax(const Matrix& m)
{
    float sum = 0;
    Matrix new_x(m.get_rows() , m.get_cols());


    for(int i = 0 ; i< m.get_rows() ; i++)
    {
        for(int j = 0 ; j< m.get_cols() ; j++)
        {
            sum+= std::exp(m(i,j));
            new_x(i,j) = std::exp(m(i,j));
        }
    }
    sum = 1/sum;

    Matrix result = sum * new_x;

    return  sum * new_x;
}
