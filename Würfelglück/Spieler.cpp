#include "Spieler.h"

Spieler::Spieler(std::string wuerfelS, int team)
{
    this->wuerfel.Zahlen = fileManager::VstringToVint(fileManager::split(wuerfelS, ' '));

    int Startpoint{};
    if (team == 0) Startpoint = 0; //startpoints on field
    else Startpoint = 20; //startpoints on field

    for (int i = 0; i < 4; i++) //save figur in Spieler
    {
        Figur figur;
        figur.Startpoint = Startpoint;
        figur.teampos = i;
        figur.spieler = this;
        this->figuren.push_back(figur);
    }
}

int Spieler::GiveTeamPos()
{
    return ++this->FigursActive - 1;
}

int Spieler::lowestZielFeld()
{
    for (int i = 3; i > 0; i--)
    {
        if (this->ZielFeldArray[i] == nullptr) return i; //field has no contant yet
    }

    return 0;
}

void Spieler::updateTeamPos()
{
    std::array<Figur*, 4> teamparray = {nullptr};
    int check{};
    for (Figur* fig : this->OnField)
    {
        if (fig->Startpoint == 0) check = 40; //check = field bevor start
        else check = 20;

        for (int i = 0; i < 4; i++) //4 = temparray.size()
        {

            if (fig->Startpoint == 0 && (teamparray[0] == nullptr || fig->pos > teamparray[i]->pos || fig->pos < 0))
            {
                //insert Figur

            }
            else if (fig->Startpoint == 21 && (teamparray[0] == nullptr || (fig->pos > teamparray[i]->pos && fig->pos > fig->Startpoint || fig->pos < teamparray[i]->pos && fig->pos < fig->Startpoint) || fig->pos < 0))
            {

            }
        }

    }
}

bool Spieler::onSpawnField(int index)
{
    if (index - 1 > 3) return false; //if index is bigger then size
    if (this->ZielFeldArray[(index-1)] == nullptr) return true;
    return false;
}

void Spieler::InsertFigur(std::array< Figur*, 4>& arr, int index, Figur* fig)
{
    Figur* temp;
    Figur* temp2;

    for (int i = index; i < arr.size(); i++)
    {
        

        if (i == index)
        {
            temp = arr[i];
            arr[i] = fig;
        }
    }
}