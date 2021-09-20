#pragma once
#include "include.h"

struct word
{
	std::string* word;
	vec2 startpoint;
	int ausrichtung; //0 - waagerecht | 1 - Senkrecht | 2 - Diagonal (rechts) | 3 - Diagonal (links)
	int endIndex{ 0 }; //0 - normal word | -1 - extraword | > 0 - endIndex of Filler
};

struct Inhalt
{
	char letter;
	bool isWord;
	bool isExtraWord;
};

class wordJumble
{
public:
	wordJumble(vec2 worldSize, std::vector<std::string> words);

	std::vector<Inhalt> Einfach();
	std::vector<Inhalt> Mittel();
	std::vector<Inhalt> Schwer();

	void DisplayPlayfield(std::vector<Inhalt> playfield);
	void DisplayPlayfield(std::vector<Inhalt> playfield, HANDLE hConsole);

private:
	vec2 worldSize{};
	std::vector<std::string> words{};
	std::vector<Inhalt> CreateField(bool Kreuzung);
	bool Possible(std::vector<Inhalt>* playfield, word Word, bool Kreuzung); // false - keine Kreuzungen | true - Kreuzungen
	bool Check(std::vector<Inhalt>* playfieldCopy, word Word, bool Kreuzung, int i, int index); // false - keine Kreuzungen | true - Kreuzungen
	void Fill(std::vector<Inhalt>* playfield, std::vector<char> fillers, bool wordSnippets); //fill empty space
	void Fill(std::vector<Inhalt>* playfield, std::vector<char> fillers, std::vector<std::string> extraWords); //with extrawords
	std::string toUpper(std::string s);
	void reverseStr(std::string& str);
};

