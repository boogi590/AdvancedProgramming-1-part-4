#include "KNN.h"

/**
 * constructor.
 * @param k a number that define the number of neighbors we will use.
 * @param database map of vector as key and the tag of the vector as value.
 * @param whichD string that represents the distance function we wiil use in order to find the k nearest neighbors.
 */
KNN::KNN(int k, multimap<vector<double>, string> database, string whichD)
{
    this->k = k;
    this->database = database;
    this->whichD = whichD;
}

/**
 * calculates the distance of the input vector from all the vectors in the database.
 * @param vec the input vector.
 * @return map with key = the distance batween the input vector to the vector in the database,
 * value = the tagging of the vactor in the database.
 */
multimap<double, string> KNN::distanceFromVector(vector<double> vec)
{
    double tempDistance;
    multimap<double, string> distanceAndTag;
    for (const auto &pair : database)
    {
        tempDistance = Distance::distanceAcorddingTo(vec, pair.first, whichD);
        distanceAndTag.emplace(tempDistance, pair.second);
    }
    return distanceAndTag;
}

/**
 * Calculates the most common tag from the k vectors closest to the input vector.
 * @param vec the input vector (to do KNN on).
 * @return the most common tag from the k vectors closest to the input vector.
 */
string KNN::mostCommonFromK(vector<double> vec)
{

    // map of distances of each vector from the input vector and their tags sorted in ascending order.
    multimap<double, string> distanceAndTag = distanceFromVector(vec);

    // initialize a map to store the number of times each tag appers in database.
    map<string, int> counts;

    // iterate over the first K elements in the distanceAndTag map
    auto last = next(distanceAndTag.begin(), k);
    for (map<double, string>::iterator iter = distanceAndTag.begin(); iter != last; iter++)
    {
        string &tag = iter->second;

        // if the string is not already in the counts map, add it with a count of 1
        if (!counts.count(tag))
        {
            counts[tag] = 1;
        }
        // otherwise, increment the count for the string
        else
        {
            counts[tag]++;
        }
    }

    // initialize a variable to store the string with the highest count
    string mostCommonValue;
    int max = 0;

    // iterate over the keys (strings) in the counts map
    for (const auto &pair : counts)
    {
        // if the current count is higher than the current most frequent value,
        // update the most frequent value
        if (pair.second > max)
        {
            mostCommonValue = pair.first;
            max = pair.second;
        }
    }

    // return the most frequent value
    return mostCommonValue;
}
