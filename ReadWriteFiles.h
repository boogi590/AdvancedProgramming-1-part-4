#include <iostream>
#include <fstream>
using namespace std;

class ReadWriteFiles
{
    
public:
    ReadWriteFiles(/* args */);
    ~ReadWriteFiles();
    string readFromFile();
    static void writeToFile(string data, string fileName);
};



