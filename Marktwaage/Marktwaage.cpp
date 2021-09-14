#include "include.h"
#include "fileManager.h"
#include "waage.h"

int main(int argc, char* argv[])
{
    SetConsoleTitle(L"Bwinf Marktwaage : Arwed | Fynn | Damian");

    fileManager fmanager = fileManager(fileManager::GetFile(argc, argv));

    std::vector<std::vector<int>> content{};
    std::vector<gewichtstuck> gewichte{};

    fmanager.ExtractInfo(content, false);
    int vorkommende = content[0][0];
    content.clear();

    for (int i = 0; i < vorkommende; i++) //iterate throught Mitglieder
    {
        fmanager.ExtractInfo(content, false); //Add to content
        gewichte.push_back(gewichtstuck{ content[i][0], content[i][1] });
    }
}