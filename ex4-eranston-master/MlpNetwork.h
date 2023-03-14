//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Dense.h"


#define MLP_SIZE 4

/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit {
	unsigned int value;
	float probability;
} digit;

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
									{64,  128},
									{20,  64},
									{10,  20}};
const matrix_dims bias_dims[] = {{128, 1},
								 {64,  1},
								 {20,  1},
								 {10,  1}};


/**
 * class of the nuron network that is made of 4 layers of Dense
 */
class MlpNetwork
{
private:
Dense layer1;
Dense layer2;
Dense layer3;
Dense layer4;
public:

    /**
     * constructor function that get array of size 4 of weight matrix and
     * array of bias vector of size 4 and create a neuron network
     * @param weights array of size 4 that are the weight matrixs for the
     * mlpnetwork layers
     * @param biases array of size 4 that are the bias vectors for the
     * mlpnetwork layers
     */
    MlpNetwork( Matrix weights[4], Matrix biases[4]);

    /**
     * overloading the ()operator , getting a matrix and use it on every layer
     * of the mlpnetwork and return the output after using the input on all the
     * mlpnetwork layers
     * @param m the input matrix
     * @return the output after running the input metrix throw the layer of
     * the mlp network
     */
    digit operator()( Matrix& m) ;
};

#endif // MLPNETWORK_H