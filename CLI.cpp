#include "CLI.h"
CLI::CLI(Command *commandArray[])
{
    this->commandArray = commandArray;
}
CLI ::~CLI()
{
}

void CLI::start(int userChoise)
{

    if (InputValidation::menuCheck(userChoise))
    {
        commandArray[userChoise - 1]->execute();
    }
}
