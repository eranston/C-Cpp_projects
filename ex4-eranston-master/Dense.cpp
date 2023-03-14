#include "Dense.h"





Dense::Dense( Matrix& weights,  Matrix& biases
             ,  activ_func_ptr ActivationFunction)
{
    _weights = weights;
    _bias = biases;
    _ActivationFunction = ActivationFunction;
}

Matrix& Dense::get_weights()
{
    return _weights;
}

Matrix& Dense::get_bias()
{
    return _bias;
}

activ_func_ptr Dense::get_activation()
{
    return _ActivationFunction;
}

Matrix Dense::operator()(const Matrix& x) const
{
    Matrix result = _weights * x + _bias;
    Matrix new_m = _ActivationFunction(result);
    return new_m;
}
