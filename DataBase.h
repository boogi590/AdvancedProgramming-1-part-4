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

private:
    static bool dataBaseValidation(multimap<vector<double>, string> &);
};
#endif
