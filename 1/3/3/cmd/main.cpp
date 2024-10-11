#include <iostream>
#include "./../lib/transform/Handler.h"

// TODO не работает на exe
// TODO диаграмма

void Test()
{
    HandleCommand({});
    HandleCommand({});
    HandleCommand({});
    HandleCommand({});
}

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        Test();
        return 0;
    }

    std::vector<std::string> command;
    for (int i = 1; i < argc; i++)
    {
        command.push_back(argv[i]);
    }
    HandleCommand(command);
    return 0;
}
