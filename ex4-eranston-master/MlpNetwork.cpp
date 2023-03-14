
#include "MlpNetwork.h"
#include "Activation.h"
#include "Matrix.h"
#define LAYER_WEIGHT_SIZE 4
#define BIASES_SIZE 4

MlpNetwork::MlpNetwork( Matrix weights[4], Matrix biases[4]) :
layer1(Dense(weights[0] , biases[0] ,activation::relu)),
layer2(Dense(weights[1] , biases[1] ,activation::relu)),
layer3(Dense(weights[2] , biases[2] ,activation::relu)),
layer4(Dense(weights[3] , biases[3] ,activation::softmax))
{
}




digit MlpNetwork::operator()( Matrix& m)
{
    Matrix r1 = layer1(m);
    Matrix r2 = layer2(r1);
    Matrix r3 = layer3(r2);
    Matrix x;
    x = layer4(r3);
    digit d;
    float max = 0;
    for(int i= 0 ; i< x.get_rows()* x.get_cols() ; i++ )
    {
        if(x[i] > max)
        {
            d.value = i;
            d.probability = x[i];
            max = x[i];
        }
    }
    return d;
}