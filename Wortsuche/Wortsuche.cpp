#include "include.h"
#include "fileManager.h"
#include "wordJumble.h"

int main(int argc, char* argv[])
{
    SetConsoleTitle(L"Bwinf MarktWaage : Arwed | Fynn | Damian");

    //testing

    wordJumble wj = wordJumble(vec2{ 10 , 10, 100 }, std::vector<std::string>{"lol"});

    std::vector<Inhalt> lololol{};

    for (int i = 0; i < 100; i++)
    {
        Inhalt temp;
        temp.isWord = false;
        temp.letter = false;
        lololol.push_back(temp);
    }

    lololol[20].isWord = true;

    std::string lol1 {"lol"};
    word Word{ &lol1, vec2{3, 2, 12}, 1 , false};

    std::cout << std::boolalpha << wj.Possible(&lololol, Word, true);

    return 0;
    fileManager fmanager = fileManager(fileManager::GetFile(argc, argv));

    std::vector<std::vector<int>> content1{};
    std::vector<std::vector<std::string>> content{};
    std::vector<std::string> words{};

    fmanager.ExtractInfo(content1, false);
    vec2 RaetselworldSize = vec2{ content1[0][0], content1[0][1], content1[0][0] * content1[0][1]};

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

