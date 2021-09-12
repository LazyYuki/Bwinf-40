#include "include.h"
#include "fileManager.h"
#include "Spieler.h"
#include "Spiel.h"

int main(int argc, char* argv[])
{
    SetConsoleTitle(L"Bwinf Würfelglück : Arwed | Fynn | Damian");

    //fileManager fmanager = fileManager(fileManager::GetFile(argc, argv));

    Spieler player1 = Spieler({ 1, 2, 3, 4, 5, 6 }, 0);
    Spieler player2 = Spieler({ 1, 2, 3, 4, 5, 6 }, 1);
    player2.Wins = 1;

    Spiel spiel = Spiel(&player1, &player2);

    spiel.reset();

    spiel.SetFigureToField(player2.SpawnField[1]);
    spiel.SetFigureToField(player2.SpawnField[0]);
    spiel.SetFigureToField(player2.SpawnField[0]);

    std::cout << player2.figuren[1].teampos << std::endl;
    std::cout << player2.figuren[0].teampos << std::endl;
    std::cout << player2.figuren[2].teampos << std::endl;

    return 0;
}

