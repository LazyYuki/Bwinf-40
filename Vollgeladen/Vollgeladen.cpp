#include "include.h"
#include "fileManager.h"
#include "Hotel.h"

int main(int argc, char* argv[])
{
    SetConsoleTitle(L"Bwinf MarktWaage : Arwed | Fynn | Damian");

    fileManager fmanager = fileManager(fileManager::GetFile(argc, argv));
  
    std::vector<std::vector<std::string>> content{};
    std::vector<Hotel> Hotels{};
    
    fmanager.ExtractInfo(content, false, true);
    int AnzahlHotels = std::atoi(content[0][0].c_str());

    fmanager.ExtractInfo(content, false, true);
    int Gesamtfahrzeit = std::atoi(content[1][0].c_str());

    content.clear();

    for (int i = 0; i < AnzahlHotels; i++) //iterate throught Mitglieder
    {
        fmanager.ExtractInfo(content, false, true);
        Hotels.push_back(Hotel(std::atoi(content[i][0].c_str()), std::atof(content[i][1].c_str()), i));
        std::cout << Hotels[i].Bewertung << std::endl;
        std::cout << Hotels[i].Entfernung << std::endl;
        std::cout << Hotels[i].Nummer << std::endl << std::endl;
    }
}

