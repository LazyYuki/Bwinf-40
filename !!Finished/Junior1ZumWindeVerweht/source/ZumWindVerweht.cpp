#include "include.h"
#include "fileManager.h"
#include "struct.h"

double AbstandZwichenVec2(vec2 coorA, vec2 coorB)
{
    return sqrt(((coorA.x - coorB.x) * (coorA.x - coorB.x)) + ((coorA.y - coorB.y) * (coorA.y - coorB.y)));
}

int main(int argc, char* argv[])
{
    SetConsoleTitle(L"Bwinf Zum Winde Verweht : Arwed | Fynn | Damian");

    fileManager fmanager = fileManager(fileManager::GetFile(argc, argv));

    std::vector<std::vector<int>> content{};
    std::vector<house> houses{};
    std::vector<pinwheel> pinwheels{};

    fmanager.ExtractInfo(content, false);
    int Houses = content[0][0];
    int pinwheelnum = content[0][1];
    content.clear();

    for (int i = 0; i < Houses; i++)
    {
        fmanager.ExtractInfo(content, false); //Add to content
        houses.push_back(house{ vec2{ (double)content[i][0], (double)content[i][1] } });
    }

    for (int i = Houses; i < pinwheelnum + Houses; i++)
    {
        fmanager.ExtractInfo(content, false); //Add to content
        pinwheels.push_back(pinwheel{ vec2{ (double)content[i][0], (double)content[i][1] }, -1 });
    }

    for (int i = 0; i < houses.size(); i++)
    {
        for (int x = 0; x < pinwheels.size(); x++)
        {
            double maximalhoehe = AbstandZwichenVec2(houses[i].coordinaten, pinwheels[x].coordinaten) / 10;

            if (maximalhoehe < pinwheels[x].maximalhoehe || pinwheels[x].maximalhoehe == -1) pinwheels[x].maximalhoehe = maximalhoehe;
        }
    }

    for (pinwheel p : pinwheels)
    {
        std::cout << "Windrad: x - " << p.coordinaten.x << " y - " << p.coordinaten.y << " | Maximalhoehe: " << p.maximalhoehe << std::endl;
    }

    int lol{};
    std::cin >> lol;

    return 0;
}
