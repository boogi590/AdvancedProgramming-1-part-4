#include <stdexcept>
#include <vector>
#include <stdio.h>
#include <cmath>
#include <iostream>
using namespace std;

class InputValidation
{
public:
    static bool intOrDouble(double num);
    static bool isVectorsLengthEquals(vector<double> vec1, vector<double> vec2);
    static vector<double> inputFromUser();
};