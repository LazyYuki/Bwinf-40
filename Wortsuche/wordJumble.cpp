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
	std::vector<Inhalt> playfieldCopy = *playfield;
	int index{0};
	//end of word check
	if (Word.ausrichtung == 0 && Word.startpoint.x + Word.word->size() - 1 <= worldSize.x) //waagerecht -> start.x + word.worldSize < spielfeld.worldSize
	{
		for (int i = Word.startpoint.produkt; i < Word.startpoint.produkt + Word.word->size(); i++, index++)
		{
			if (!Kreuzung && (*playfield)[i].isWord) return false;
			else if (!Kreuzung && (*playfield)[i].letter != NULL && (*playfield)[i].letter != Word.word->at(index)) return false;
			else playfieldCopy[i] = Inhalt{ Word.word->at(index), true };
		}
		
		*playfield = playfieldCopy;
		return true;
	}
	else if (Word.ausrichtung == 1 && Word.startpoint.y + Word.word->size() - 1 <= worldSize.y) //senkrecht -> start.y + word.worldSize < spielfeld.worldSize
	{
		for (int i = Word.startpoint.produkt; i < Word.startpoint.produkt + (Word.word->size() * worldSize.x); i += worldSize.x, index++)
		{
			if (!Kreuzung && (*playfield)[i].isWord) return false;
			else if (!Kreuzung && (*playfield)[i].letter != NULL && (*playfield)[i].letter != Word.word->at(index)) return false;
			else playfieldCopy[i] = Inhalt{ Word.word->at(index), true };
		}
				
		*playfield = playfieldCopy;
		return true;
	}
	else if (Word.ausrichtung == 2 && Word.startpoint.x + Word.word->size() - 1 <= worldSize.x && Word.startpoint.y + Word.word->size() - 1 <= worldSize.y) //diagonale (rechts)
	{
		for (int i = Word.startpoint.produkt; i < Word.startpoint.produkt + (Word.word->size() * worldSize.x); i += worldSize.x + 1, index++)
		{
			if (!Kreuzung && (*playfield)[i].isWord) return false;
			else if (!Kreuzung && (*playfield)[i].letter != NULL && (*playfield)[i].letter != Word.word->at(index)) return false;
			else playfieldCopy[i] = Inhalt{ Word.word->at(index), true };
		}

		*playfield = playfieldCopy;
		return true;
	}
	else if (Word.ausrichtung == 3 && (signed int)Word.startpoint.x - (signed int)Word.word->size() + 1 > 0 && (signed int)Word.startpoint.y + (signed int)Word.word->size() - 1 > 0) //diagonale (links)
	{
		for (int i = Word.startpoint.produkt; i < Word.startpoint.produkt + ((Word.word->size() - 1) * (static_cast<unsigned __int64>(worldSize.x) - 1)) + 1; i += worldSize.x - 1, index++)
		{
			if (!Kreuzung && (*playfield)[i].isWord) return false;
			else if (!Kreuzung && (*playfield)[i].letter != NULL && (*playfield)[i].letter != Word.word->at(index)) return false;
			else playfieldCopy[i] = Inhalt{ Word.word->at(index), true };
		}

		*playfield = playfieldCopy;
		return true;
	}

	return false;
}

void wordJumble::Fill(std::vector<Inhalt>* playfield, std::vector<char> fillers, bool withExtraWords)
{

}