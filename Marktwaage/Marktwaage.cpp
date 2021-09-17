#include "include.h"
#include "fileManager.h"
#include "waage.h"

int main(int argc, char* argv[])
{
    SetConsoleTitle(L"Bwinf MarktWaage : Arwed | Fynn | Damian");

    fileManager fmanager = fileManager(fileManager::GetFile(argc, argv));

    std::vector<std::vector<int>> content{};
    std::vector<Gewicht> gewichte{};

    fmanager.ExtractInfo(content, false);
    int AnzahlGewichte = content[0][0];
    content.clear();

    for (int i = 0; i < AnzahlGewichte; i++) //iterate throught Mitglieder
    {
        fmanager.ExtractInfo(content, false); //Add to content
        for (int x = 0; x < content[i][1]; x++)
        {
            gewichte.push_back(Gewicht{content[i][0]});
            std::cout << content[i][1] << " " << x << std::endl;
        }
    }

    std::cout << "lol";

    std::cout << waage::Possible(gewichte, 0, 10) << std::endl;

    return 0;
}