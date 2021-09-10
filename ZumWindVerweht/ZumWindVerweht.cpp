#include "include.h"
#include "fileManager.h"

int main(int argc, char* argv[])
{
    SetConsoleTitle(L"Bwinf Vom Winde Verweht : Arwed | Fynn | Damian");

    fileManager fmanager = fileManager(fileManager::GetFile(argc, argv));

    std::vector<std::vector<int>> content{};

    fmanager.ExtractInfo(content, false);
    int Houses = content[0][0];
    int pinwheels = content[0][1];

    for (int i = 0; i < Houses; i++)
    {
        fmanager.ExtractInfo(content, false); //Add to content
    }

    for (int i = 0; i < pinwheels; i++)
    {
        fmanager.ExtractInfo(content, false); //Add to content
    }

    return 0;
}
