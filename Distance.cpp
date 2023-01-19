
#include "Distance.h"

/**
 * calculates the euclidean distance between two vectors.
 * euclidean distance is calculated by using the minkowski formula with p = 2.
 * @param vec1 vector of numbers.
 * @param vec2 vector of numbers.
 * @return the euclidean distance between the two vectors.
 */
double Distance::euclidean(vector<double> vec1, vector<double> vec2)
{
    return minkowskiWithP(vec1, vec2, 2);
}

/**
 * calculates the manhattan distance between two vectors.
 * manhattan distance is calculated by using the minkowski formula with p = 1.
 * @param vec1 vector of numbers.
 * @param vec2 vector of numbers.
 * @return the manhattan distance between the two vectors.
 */
double Distance::manhattan(vector<double> vec1, vector<double> vec2)
{
    return minkowskiWithP(vec1, vec2, 1);
}

/**
 * calculates the minkowski distance between two vectors when p = 2.
 * minkowski distance is calculated by using the minkowski formula with p = 2.
 * @param vec1 vector of numbers.
 * @param vec2 vector of numbers.
 * @return the euclidean distance between the two vectors.
 */
double Distance::minkowski(vector<double> vec1, vector<double> vec2)
{
    return minkowskiWithP(vec1, vec2, 2);
}

/**
 * calculates the chebyshev distance between two vectors.
 * chebyshev distance is calculated as follows:
 * given two vectors x and y: Dc = max(|xi-yi|).
 * @param vec1 vector of numbers.
 * @param vec2 vector of numbers.
 * @return the chebyshev distance between the two vectors.
 */
double Distance::chebyshev(vector<double> vec1, vector<double> vec2)
{
    double max = 0;
    double temp = 0;
    for (int i = 0; i < vec1.size(); i++)
    {
        temp = abs(vec1[i] - vec2[i]);
        if (temp > max)
        {
            max = temp;
        }
    }
    return max;
}

/**
 * calculates the canberra distance between two vectors.
 * canberra distance is calculated as follows:
 * given two vectors x and y from length n:
 * Dc = (|x1 - y1|) / (|x1| + |y1|) + ... + (|xn - y1n|) / (|xn| + |y1n|).
 * @param vec1 vector of numbers.
 * @param vec2 vector of numbers.
 * @return the canberra distance between the two vectors.
 */
double Distance::canberra(vector<double> vec1, vector<double> vec2)
{
    double distance;
    for (int i = 0; i < vec1.size(); i++)
    {
        // in case of zero division we define 0 / 0 = 0.
        if (vec1[i] != 0 || vec2[i] != 0)
        {
            distance += abs(vec1[i] - vec2[i]) / (abs(vec1[i]) + abs(vec2[i]));
        }
    }
    return distance;
}

/**
 * Calculates the distance between 2 vectors according to the given string:
 * 1) Euclidean distance = AUC
 * 2) Manhattan distance = MAN
 * 3) Chebyshev distance = CHB
 * 4) Canberra distance = CAN
 * 5) Minkowski distance = MIN
 * If there is no match returns -1.
 * @param vec1 vector of numbers.
 * @param vec2 vector of numbers.
 * @param whichD Marks which distance metric we will use for the calculation.
 * @return the distance between the two vectors according to whichD and -1 if there is no match.
 */
double Distance::distanceAcorddingTo(vector<double> vec1, vector<double> vec2, string whichD)
{
    if (whichD == "AUC")
    {
        return euclidean(vec1, vec2);
    }
    if (whichD == "MAN")
    {
        return manhattan(vec1, vec2);
    }
    if (whichD == "CHB")
    {
        return chebyshev(vec1, vec2);
    }
    if (whichD == "CAN")
    {
        return canberra(vec1, vec2);
    }
    if (whichD == "MIN")
    {
        return minkowski(vec1, vec2);
    }
    return -1;
}

//================================= Auxiliary functions =========================================================

/**
 * calculates the minkowski distance between two vectors with the desired.
 * canberra distance is calculated as follows:
 * given two vectors x and y from length n:
 * Dm = (|x1 - y1|) / (|x1| + |y1|) + ... + (|xn - y1n|) / (|xn| + |y1n|)
 * when each |x - y| is by power of p and then the result is by the power of 1/p.
 * @param vec1 vector of numbers.
 * @param vec2 vector of numbers.
 * @return the euclidean distance between the two vectors.
 */
double Distance::minkowskiWithP(vector<double> vec1, vector<double> vec2, double p)
{
    double sum = 0;
    for (int i = 0; i < vec1.size(); i++)
    {
        sum += pow(abs(vec1[i] - vec2[i]), p);
    }
    sum = pow(sum, 1 / p);
    return sum;
}
