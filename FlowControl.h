#ifndef _FLOWCONTROL_H
#define _FLOWCONTROL_H
class FlowControl
{
public:
    bool did_files_uploaded;
    bool did_data_classified;
    // constructor.
    FlowControl();
    // setters.
    void setDidFilesUploaded(bool value);
    void setDidDataClassified(bool value);
};
#endif
