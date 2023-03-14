#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

/**
 * type def for pointer of function that get matrix and return a matrix
 */
typedef Matrix (*activ_func_ptr)(const Matrix& m);


/**
 * @brief class of a layer in the nuron network
 */
class Dense
{
private:

    Matrix _weights; // weight metrix of the layer
    Matrix _bias; // bias vector of the layer
    activ_func_ptr _ActivationFunction; // the function of the layer
public:

    /**
     * constructor of Dense of the layer  int he nuron network
     * @param weights the weight function of the layer
     * @param bias the bias vector of the function
     * @param ActivationFunction the activation function of the layer
     */
    Dense( Matrix& weights, Matrix& bias,
           activ_func_ptr ActivationFunction);



    /**
     * getter for the weight matrix of the layer
     * @return the weight matrix of the layer
     */
    Matrix& get_weights();

    /**
     * geeter for the bias vector of the layer
     * @return the vector of the layer
     */
    Matrix& get_bias();

    /**
     * getter for the activation function of the layer
     * @return the activation function of the layer
     */
    activ_func_ptr get_activation();

    /**
     * overloading the () operator that get a matrix and use the activation
     * function of the layer on the matrix * weight matrix + bias vector
     * @return the output of using the layer arguments on the given matrix
     */
    Matrix operator()(const Matrix&) const;
};

#endif //DENSE_H
