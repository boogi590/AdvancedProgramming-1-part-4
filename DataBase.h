#ifndef _DATABASE_H
#define _DATABASE_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class DataBase
{
public:
    static multimap<vector<double>, string> createDataBaseFromFIle(string nameOfFile);
    static multimap<vector<double>, string> createDataBaseFromString(string file);
    static vector<vector<double>> createTestVectors(string testFile);
    static void printDataBase(multimap<vector<double>, string> dataBase);
    static void printTrainFile(vector<vector<double>> test);

private:
    static bool dataBaseValidation(multimap<vector<double>, string> &);
};
#endif
