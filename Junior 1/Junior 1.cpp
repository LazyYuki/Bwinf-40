#include "include.h"
#include "fileManager.h"

int main()
{
    SetConsoleTitle(L"Bwinf Junior 1 : Arwed | Fynn | Damian");
    
    fileManager fmanager = fileManager(fileManager::GetFileConsole());

    std::vector<std::vector<int>> content{};

    fmanager.ExtractInfo(content, true, true);

    for (std::vector<int> c : content)
    {
        for (int x : c)
        {
            std::cout << x << " ";
        }

        std::cout << std::endl;
    }

    return 0;
}
