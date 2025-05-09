#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
void train_test_split(Dataset &X, Dataset &Y, double test_size,
                      Dataset &X_train, Dataset &X_test, Dataset &y_train, Dataset &y_test)
{
    if (X.getData()->length() != Y.getData()->length() || test_size >= 1 || test_size <= 0)
        return;
    
    double min = 1.0e-15;
    int row = X.getData()->length();
    double rowtest = row * (1 - test_size);

    if (abs(round(rowtest) - rowtest) < min * row)
        rowtest = round(rowtest);

    X_train = X.extract(0, rowtest - 1, 0, -1);
    y_train = Y.extract(0, rowtest - 1, 0, -1);

    X_test = X.extract(rowtest, -1, 0, -1);
    y_test = Y.extract(rowtest, -1, 0, -1);
}
