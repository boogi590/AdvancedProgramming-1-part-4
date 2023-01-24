#include "InputValidation.h"

/**
 * checks if a number is double or round.
 * @param num is the number to check.
 * @returns true if its round and false otherwise.
 */
bool InputValidation::intOrDouble(double num)
{
    num = abs(num);
    return num == floor(num);
}

/**
 * checking if the vectors are on the same size.
 * @param[vec1] vector of numbers.
 * @param[vec2] vector of numbers.
 * @return true if the vectors are on the same size false otherwise.
 */
bool InputValidation::isVectorsLengthEquals(vector<double> vec1, vector<double> vec2)
{
    if (vec1.size() != vec2.size())
    {
        return false;
    }
    return true;
}

/**
 * reciving vectors of number from the user, \n reprsents the end of the input.
 * in case of mix of numbers and chars it reads up until the char and marks a number
 * statring with char as invalid input by returning execption.
 * the execption is handeld by the main function.
 * the execption is thrown by the stod fucntion.
 * @return the vector recived from the user.
 */
vector<double> InputValidation::inputFromUser()
{
    vector<double> vector;
    string input;
    double num;
    while (true)
    {
        cin >> input;
        num = stod(input);

        vector.push_back(num);
        if (cin.peek() == '\n')
        {
            break;
        }
    }
    return vector;
}

bool InputValidation::menuCheck(int num)
{
    // the menu num are 1-5(including) and 8.
    if (num < 1 || num > 8 || num == 6 || num == 7)
    {
        return false;
    }
    return true;
}
