#pragma once
#include "include.h"

struct word
{
	std::string* word;
	vec2 startpoint;
	int ausrichtung; //0 - waagerecht | 1 - Senkrecht | 2 - Diagonal (rechts) | 3 - Diagonal (links)
	bool richtung; // false - Vorw�rts | true - R�ckwarts
};

struct Inhalt
{
	char letter;
	bool isWord;
};

class wordJumble
{
public:
	wordJumble(vec2 worldSize, std::vector<std::string> words);

	std::vector<Inhalt> Einfach();
	std::vector<Inhalt> Mittel();
	std::vector<Inhalt> Schwer();

	bool Possible(std::vector<Inhalt>* playfield, word Word, bool Kreuzung);

private:
	vec2 worldSize{};
	std::vector<std::string> words{};
	std::vector<Inhalt> CreateField(bool Kreuzung);
	//bool Possible(std::vector<Inhalt>* playfield, word Word, bool Kreuzung);
};

