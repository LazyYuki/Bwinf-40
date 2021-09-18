#include "wordJumble.h"

wordJumble::wordJumble(vec2 worldSize, std::vector<std::string> words)
{
	this->worldSize = worldSize;
	this->words = words;
}



std::vector<Inhalt> wordJumble::Einfach()
{
	return std::vector<Inhalt>{};
}

std::vector<Inhalt> wordJumble::Mittel()
{
	return std::vector<Inhalt>{};
}

std::vector<Inhalt> wordJumble::Schwer()
{

	return std::vector<Inhalt>{};
}



std::vector<Inhalt> wordJumble::CreateField(bool Kreuzung)
{
	std::vector<word> declaratedwords{};
	std::vector<Inhalt> output{};

	word w{};

	for (std::string str : this->words)
	{
		w.word = &str;
		w.ausrichtung = rand() % 3 + 0;
		w.richtung = rand() % 1 + 0;

		do
		{
			w.startpoint = vec2{ rand() % worldSize.x + 1, rand() % worldSize.y + 1 };
			w.startpoint.produkt = w.startpoint.x + ((w.startpoint.y-1) * worldSize.x) - 1; //x - y coords -> continues playfield || last -1 because vector started with 0
		} while (!Possible(&output, w, Kreuzung));
	}

	return output;
}

bool wordJumble::Possible(std::vector<Inhalt> *playfield, word Word, bool Kreuzung)
{
	//end of word check
	if (Word.ausrichtung == 0 && Word.startpoint.x + Word.word->size() - 1 <= worldSize.x) //waagerecht -> start.x + word.worldSize < spielfeld.worldSize
	{
		if (Kreuzung)
			for (int i = Word.startpoint.produkt; i < Word.startpoint.produkt + Word.word->size(); i++)
				if ((*playfield)[i].isWord) return false;

		return true;
	}
	else if (Word.ausrichtung == 1 && Word.startpoint.y + Word.word->size() - 1 <= worldSize.y) //senkrecht -> start.y + word.worldSize < spielfeld.worldSize
	{
		if (Kreuzung)
			for (int i = Word.startpoint.produkt; i < Word.startpoint.produkt + Word.word->size() * worldSize.x; i += worldSize.x)
				if ((*playfield)[i].isWord) return false;

		return true;
	}
	else if (Word.ausrichtung == 2 && Word.startpoint.x + Word.word->size() - 1 <= worldSize.x && Word.startpoint.y + Word.word->size() - 1 <= worldSize.y) //diagonale (rechts)
	{
		if (Kreuzung)
			for (int i = Word.startpoint.produkt; i < Word.startpoint.produkt + Word.word->size(); i += worldSize.x + 1)
				if ((*playfield)[i].isWord) return false;

		return true;
	}
	else if (Word.ausrichtung == 3 && (signed int)Word.startpoint.x - (signed int)Word.word->size() + 1 > 0 && Word.startpoint.y - Word.word->size() + 1 > 0) //diagonale (links)
	{
		if (Kreuzung)
			for (int i = Word.startpoint.produkt; i > Word.startpoint.produkt + Word.word->size(); i -= worldSize.x - 1)
				if ((*playfield)[i].isWord) return false;

		return true;
	}

	return false;
}