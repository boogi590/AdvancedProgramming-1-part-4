#include "Command.h";
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;
class DisplayResults : public Command
{
private:
    // classify_data = map of key = int and value =string such that the key =the line in the test CSV file and
    // value =the classifion of the vector in this line.
    map<int, string> calssify_data;

public:
    void execute();
};
