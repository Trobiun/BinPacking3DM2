#include <stdio.h>
#include "mxnet-cpp/MxNetCpp.h"

using namespace std;
using namespace mxnet::cpp;


int main(int argc, char** argv) {
    int batch_size = 10;
    auto train_iter = MXDataIter("MNISTIter")
    .SetParam("image", "../IA/train-images-idx3-ubyte")
    .SetParam("label", "../IA/train-labels-idx1-ubyte")
    .SetParam("batch_size", batch_size)
    .SetParam("flat", 1)
    .CreateDataIter();
    auto val_iter = MXDataIter("MNISTIter")
    .SetParam("image", "../IA/t10k-images-idx3-ubyte")
    .SetParam("label", "../IA/t10k-labels-idx1-ubyte")
    .SetParam("batch_size", batch_size)
    .SetParam("flat", 1)
    .CreateDataIter();
    printf("fini\n");
    return 0;
}
