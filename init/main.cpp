#include "kNN.hpp"

void tc1(){
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    dataset.printHead();
    dataset.printTail();
    int nRows, nCols;
    dataset.getShape(nRows, nCols);
    cout << "Shape: " << nRows << "x" << nCols << endl;

    kNN knn;
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, -1, 1, -1);
    Dataset label = dataset.extract(0, -1, 0, 0);
    
    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);

    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);
    double accuracy = knn.score(y_test, y_pred);
    cout << "Accuracy: " << accuracy << endl;
}
void tc1160()
{
int nRows, nCols;
Dataset dataset;
dataset.loadFromCSV("mnist.csv");
Dataset dataset_extract = dataset.extract(30, 20, 0, -1);
Dataset dataset_extract2 = dataset_extract;
dataset_extract2.getShape(nRows, nCols);
cout << "Dataset extract shape: " << nRows << "x" << nCols << endl;
}

int main() {
    tc1();
    return 0;
}
