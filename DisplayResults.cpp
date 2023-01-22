#include "DisplayResults.h"
void DisplayResults :: execute() {
    
    for(map<int,string>::iterator mit = calssify_data.begin(); mit != calssify_data.end(); mit++)
    {
        pair<int,string> data = *mit;
        IO->write(to_string(data.first));
        IO->write(" ");
        IO->write(data.second);
    }
    IO->write(".Done");
    
}