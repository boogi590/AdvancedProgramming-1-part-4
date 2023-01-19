
#include "Distance.h"
#include "InputValidation.h"
#include "DataBase.h"
#include "KNN.h"

/**
 * The arguments that the main function expects (in the expected order):
 * 1)K for the KNN fucntion that indicates the number of neighbors in the function.
 * 2)the file name of the database to run the KNN function on.
 * 3)a string representation of the distance formula to use for calculating the distances in the KNN function.
 *   the string representation of the formulas are as follows:
 *   1)AUC - auclidian distance.
 *   2)MAN - manhattan distance.
 *   3)CHB - chebyshev distance.
 *   4)CAN - canberra distance.
 *   5)MIN - minkowski distance.
 * 4) receive from the user a vector in run time.
 * the main function runs the KNN algorithm on the input vector and passed arguments.
 */

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        cout << "wrong number of arguments. there should be 3 arguments" << endl;
        return 0;
    }

    multimap<vector<double>, string> dataBase;
    dataBase = DataBase::createDataBaseFromFIle(argv[2]);
    if (dataBase.empty())
    {
        cout << "an error has occurred in the data base" << endl;
        return 0;
    }
    int k = stoi(argv[1]);
    if (k <= 0)
    {
        cout << "k should be positive" << endl;
        return 0;
    }
    // CHECK: If K is greater than the number of vectors in the database we define him to be the size of the database.
    if (k > dataBase.size())
    {
        k = dataBase.size();
    }

    string whichD = argv[3];
    // CHECK: if the user entered a non-existent distance function - not one of the existing options.
    vector<double> v1 = {1, 2};
    vector<double> v2 = {2, 3};

    double tempDistance = Distance::distanceAcorddingTo(v1, v2, whichD);
    if (tempDistance == -1)
    {
        cout << "No matching distance function" << endl;
        return 0;
    }

    KNN calculateKNN(k, dataBase, whichD);

    while (1)
    {
        vector<double> vector;
        try
        {
            vector = InputValidation::inputFromUser();
        }
        catch (...)
        {
            cout << "Please enter NUMBERS" << endl;
            continue;
        }

        // CHECK: if the input vector is not the same length as the vectors in the database.
        if (!InputValidation::isVectorsLengthEquals(vector, dataBase.begin()->first))
        {
            cout << "the input vector should be of length " << dataBase.begin()->first.size() << endl;
            continue;
        }
        cout << calculateKNN.KNN::mostCommonFromK(vector) << endl;
    }
};
