#include "DataBase.h"

multimap<vector<double>, string> DataBase::createDataBaseFromFIle(string nameOfFile)
{
    // Open the file for reading
    ifstream file(nameOfFile);

    multimap<vector<double>, string> dataBase;
    string line;

    while (getline(file, line))
    {
        vector<double> values;
        string type;
        // Use a stringstream to parse the values from the line
        stringstream lineStream(line);

        // Use a temporary variable to hold each value as it is read
        string value;
        bool inputFlag = true;
        // Iterate over each value in the line
        while (getline(lineStream, value, ','))
        {
            // If this is the last value in the line, store it in the string variable
            if (lineStream.peek() == EOF)
            {
                type = value;
            }
            else
            {
                try
                {
                    values.push_back(stod(value));
                }
                catch (const invalid_argument &)
                {
                    inputFlag = false;
                    continue;
                }
                catch (const out_of_range &)
                {
                    inputFlag = false;
                    continue;
                }
            }
        }
        if (inputFlag)
        {
            dataBase.emplace(values, type);
        }
    }

    file.close(); // Close the file

    if (dataBaseValidation(dataBase))
    {
        return dataBase;
    }
    else
    {
        return multimap<vector<double>, string>();
    }
}

multimap<vector<double>, string> DataBase::createDataBaseFromString(string nameOfFile)
{
    // Open the file for reading
    stringstream file(nameOfFile);

    multimap<vector<double>, string> dataBase;
    string line;

    while (getline(file, line))
    {
        vector<double> values;
        string type;
        // Use a stringstream to parse the values from the line
        stringstream lineStream(line);

        // Use a temporary variable to hold each value as it is read
        string value;
        bool inputFlag = true;
        // Iterate over each value in the line
        while (getline(lineStream, value, ','))
        {
            // If this is the last value in the line, store it in the string variable
            if (lineStream.peek() == EOF)
            {
                type = value;
            }
            else
            {
                try
                {
                    values.push_back(stod(value));
                }
                catch (const invalid_argument &)
                {
                    inputFlag = false;
                    continue;
                }
                catch (const out_of_range &)
                {
                    inputFlag = false;
                    continue;
                }
            }
        }
        if (inputFlag)
        {
            dataBase.emplace(values, type);
        }
    }

    if (dataBaseValidation(dataBase))
    {
        return dataBase;
    }
    else
    {
        return multimap<vector<double>, string>();
    }
}

vector<vector<double>> DataBase::createTestVectors(string testFile)
{
    // Open the file for reading
    stringstream file(testFile);

    vector<vector<double>> dataBase;
    string line;

    while (getline(file, line))
    {
        vector<double> values;
        string type;
        // Use a stringstream to parse the values from the line
        stringstream lineStream(line);

        // Use a temporary variable to hold each value as it is read
        string value;
        bool inputFlag = true;
        // Iterate over each value in the line
        while (getline(lineStream, value, ','))
        {
            // If this is the last value in the line, store it in the string variable

            try
            {
                values.push_back(stod(value));
            }
            catch (const invalid_argument &)
            {
                inputFlag = false;
                continue;
            }
            catch (const out_of_range &)
            {
                inputFlag = false;
                continue;
            }
        }
        if (inputFlag)
        {
            dataBase.push_back(values);
        }
    }
    return dataBase;
}

bool DataBase::dataBaseValidation(multimap<vector<double>, string> &dataBase)
{
    int size = dataBase.begin()->first.size();

    for (multimap<vector<double>, string>::iterator iterator = dataBase.begin(); iterator != dataBase.end(); ++iterator)
    {

        if (iterator->first.size() != size)
        {
            return false;
        }
    }

    return true;
}

void DataBase::printDataBase(multimap<vector<double>, string> dataBase)
{
    for (auto it = dataBase.begin(); it != dataBase.end(); it++)
    {
        for (auto num : it->first)
        {
            std::cout << num << ",";
        }
        cout << " " << it->second;

        std::cout << std::endl;
    }
}

void DataBase::printTrainFile(vector<vector<double>> test)
{
    int line = 1;
    for (auto vec : test)
    {
        cout << line++ << " :";
        for (auto num : vec)
        {
            std::cout << num << ",";
        }
        std::cout << "\n";
    }
}
