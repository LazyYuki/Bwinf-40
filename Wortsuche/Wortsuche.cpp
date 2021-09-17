#include "include.h"
#include "fileManager.h"
#include "wordJumble.h"

int main(int argc, char* argv[])
{
    SetConsoleTitle(L"Bwinf MarktWaage : Arwed | Fynn | Damian");

    fileManager fmanager = fileManager(fileManager::GetFile(argc, argv));

    std::vector<std::vector<int>> content1{};
    std::vector<std::vector<std::string>> content{};
    std::vector<std::string> words{};

    fmanager.ExtractInfo(content1, false);
    vec2 RaetselSize = vec2{ content1[0][0], content1[0][1] };

    fmanager.ExtractInfo(content1, false);
    int AnzahlWoerter = content1[1][0];

    content1.clear();

    for (int i = 0; i < AnzahlWoerter; i++) //iterate throught Mitglieder
    {
        fmanager.ExtractInfo(content, false, false); //Add to content
        words.push_back(content[i][0]); //not the best but yeahhh
    }

    for (std::string c : words)
    {
        std::cout << c << std::endl;
    }

    int lol{};
    std::cin >> lol;

    return 0;
}

