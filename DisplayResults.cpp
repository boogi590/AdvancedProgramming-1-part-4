#include "DisplayResults.h"
DisplayResults :: DisplayResults(map<int, string> &classify_data,FlowControl &fc){
    this->classify_data = classify_data;
    this->flow_control = fc;
}
void DisplayResults :: execute() {
    if(!flow_control.did_data_classified)
    {
        IO->write("please classify the data");
        return;
    }
     if(!flow_control.did_files_uploaded)
    {
        IO->write("please upload data");
        return;
    }
    
    for(map<int,string>::iterator mit = classify_data.begin(); mit != classify_data.end(); mit++)
    {
        pair<int,string> data = *mit;
        IO->write(to_string(data.first));
        IO->write(" ");
        IO->write(data.second);
        IO->write("\n");
    }
    IO->write(".Done");
    
}