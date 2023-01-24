#include "FlowControl.h"
FlowControl::FlowControl()
{
    this->did_files_uploaded = false;
    this->did_data_classified = false;
}

void FlowControl::setDidFilesUploaded(bool value)
{
    this->did_files_uploaded = value;
}

void FlowControl::setDidDataClassified(bool value)
{
    this->did_data_classified = value;
}