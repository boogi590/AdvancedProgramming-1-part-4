#ifndef _DiSTANCE_H
#define _DiSTANCE_H
#include <stdio.h>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

class Distance
{
public:
    static double euclidean(vector<double> vec1, vector<double> vec2);
    static double manhattan(vector<double> vec1, vector<double> vec2);
    static double minkowski(vector<double> vec1, vector<double> vec2);
    static double chebyshev(vector<double> vec1, vector<double> vec2);
    static double canberra(vector<double> vec1, vector<double> vec2);
    static double distanceAcorddingTo(vector<double> vec1, vector<double> vec2, string whichD);

private:
    static double minkowskiWithP(vector<double> vec1, vector<double> vec2, double p);
};
#endif
