#include "DisplayResults.h"
DisplayResults ::DisplayResults(map<int, string> &classify_data, FlowControl &fc) : classify_data(classify_data),
                                                                                    flow_control(fc)
{
}
void DisplayResults ::execute()
{
    if (!flow_control.did_files_uploaded)
    {
        IO->write("1");
        return;
    }

    if (!flow_control.did_data_classified)
    {
        IO->write("2");
        return;
    }

    else
    {
        IO->write("3");
    }

    string classification;
    for (map<int, string>::iterator mit = classify_data.begin(); mit != classify_data.end(); mit++)
    {
        pair<int, string> data = *mit;
        classification += to_string(data.first) + "   " + data.second + "\n";
    }
    classification += "Done.\n";
    IO->sendSize(classification.length());

    IO->write(classification);
}