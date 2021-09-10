#include "include.h"
#include "fileManager.h"
#include "structs.h"

int main(int argc, char* argv[])
{
    SetConsoleTitle(L"Bwinf Treffsicherheit : Arwed | Fynn | Damian");

    fileManager fmanager = fileManager(fileManager::GetFile(argc, argv));

    std::vector<std::vector<int>> content{};
    std::vector<Member> member{};
    std::vector<Tag> besttage{}; //vector mit besten tagen

    fmanager.ExtractInfo(content, false);
    int Mitglieder = content[0][0];
    int Tage = content[0][1];
    content.clear();
    
    for (int i = 0; i < Mitglieder; i++) //iterate throught Mitglieder
    {
        fmanager.ExtractInfo(content, false); //Add to content
        Member temp{};
        temp.Tage = content[i];
        temp.BeliebtesterTag();
        member.push_back(temp);
    }

    int bestveränderung{-1};

    for (int i = 1; i < Tage + 1; i++) //loop Tage
    {   
        //create Temptag
        Tag tempTag;
        tempTag.index = i;

        for (Member mem : member) //lopp members
        {
            if (mem.beliebtestes >= mem.Tage[i - 1]) tempTag.beliebtheit++; //if beliebteste
            else
            {
                tempTag.veränderteEinträge += mem.VeränderteTage(i-1); //veränderungs calculation
            }
        }

        //ranking
        if (tempTag.veränderteEinträge == bestveränderung) //gleich
        {
            besttage.push_back(tempTag);
        }
        else if (tempTag.veränderteEinträge < bestveränderung || bestveränderung == -1) //besser / niedriger
        {
            besttage.clear();
            besttage.push_back(tempTag);
            bestveränderung = tempTag.veränderteEinträge;
        }
    }

    for (int i = 0; i < besttage.size(); i++) //output
    {
        std::cout << "Moeglicher Tag: Tag " << besttage[i].index << " mit " << besttage[i].veränderteEinträge
            << " veraenderten eintraegen und einer beliebtheit von " << besttage[i].beliebtheit << "." << std::endl;
    }

    int lol{};
    std::cin >> lol; //waitpoint

    return 0;
}

