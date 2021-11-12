#include "include.h"
#include "fileManager.h"
#include "Tag.h"

int main(int argc, char* argv[])
{
    bool MitSchritten = true;

    SetConsoleTitle(L"Bwinf MarktWaage : Arwed | Fynn | Damian");

    fileManager fmanager = fileManager(fileManager::GetFile(argc, argv));
  
    int i;
    std::vector<std::vector<std::string>> content{};
    std::vector<Hotel> Hotels{};
    
    fmanager.ExtractInfo(content, false, true);
    int AnzahlHotels = std::atoi(content[0][0].c_str());

    fmanager.ExtractInfo(content, false, true);
    int Gesamtfahrzeit = std::atoi(content[1][0].c_str());

    content.clear();

    for (i = 0; i < AnzahlHotels; i++) //iterate throught Mitglieder
    {
        fmanager.ExtractInfo(content, false, true);
        Hotels.push_back(Hotel(std::atoi(content[i][0].c_str()), std::atof(content[i][1].c_str()), i));
    }

    std::vector<Hotel*> HotelPointerList{};
    for (i = 0; i < Hotels.size(); i++) HotelPointerList.push_back(&Hotels[i]);

    std::vector<Tag> Tage{Tag(Gesamtfahrzeit, 0, 0, Gesamtfahrzeit, HotelPointerList)};

    for (i = 0; i < 4; i++)
    {
        if (Tage[i].NochZuFahren <= 360) break;

        Tag tag = Tag(Tage[i].NochZuFahren, i + 1, Tage[i].hotel->Entfernung, Gesamtfahrzeit, HotelPointerList);

        if(MitSchritten) tag.PrintTag();

        if (tag.hotel->Nummer != -1) Tage.push_back(tag);
        else
        {
            Tage[i].HotelsInRange.erase(Tage[i].HotelsInRange.begin()); //erase best hotel (is always first hotel in list)
            Tage[i].Finden();
            if (MitSchritten) Tage[i].PrintTag();
            i--;
        }
    }

    Tage.erase(Tage.begin()); //delete Dummy
    std::cout << "Beendet nach " << i + 1 << " Tagen.\n\nBenutzte Hotels:" << std::endl;

    for (Tag t : Tage) std::cout << "Hotel Nummer: " << t.hotel->Nummer << "   Entfernung vom Startpunkt: " << t.hotel->Entfernung << "    Bewertung: " << t.hotel->Bewertung << std::endl;

    std::cin >> i;
}

