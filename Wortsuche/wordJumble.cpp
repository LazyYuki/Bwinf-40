#include "wordJumble.h"

wordJumble::wordJumble(vec2 worldSize, std::vector<std::string> words)
{
	this->worldSize = worldSize;
	this->words = words;
}

//--------------------------- Difficulties ---------------------------

std::vector<Inhalt> wordJumble::Einfach()
{
	//Create Playingfield and input words
	std::vector<Inhalt> field = this->CreateField(false);

	//fill the rest of the spaces
	std::vector<char> fillers = {'Q', 'X', 'Y', 'J', 'V', 'P', 'Z', 'K', 'F', 'W', 'B', 'O'}; //most unused charackters in german language

	//erase start all starter charackters (so its easier)
	for (int i = 0; i < this->words.size(); i++)
		for (int x = 0; x < fillers.size(); x++)
			if (fillers[x] == this->words[i].at(0))
				fillers.erase(fillers.begin() + x);

	this->Fill(&field, fillers, false);

	return field;
}

std::vector<Inhalt> wordJumble::Mittel()
{
	std::vector<Inhalt> field = this->CreateField(false);
	std::vector<char> fillers{};

	for (int i = 65; i < 91; i++)  //generating alphabet
		fillers.push_back((char)i);

	this->Fill(&field, fillers, true);

	return field;
}

std::vector<Inhalt> wordJumble::Schwer()
{

	return std::vector<Inhalt>{};
}

//--------------------------- Helper Functions ---------------------------

void wordJumble::DisplayPlayfield(std::vector<Inhalt> playfield)
{
	for (int i = 0; i < this->worldSize.produkt; i++)
	{
		std::cout << playfield[i].letter << " ";

		if ((i + 1) % this->worldSize.x == 0 && i != 0) std::cout << std::endl;
	}
}
void wordJumble::DisplayPlayfield(std::vector<Inhalt> playfield, HANDLE hConsole)
{
	for (int i = 0; i < this->worldSize.produkt; i++)
	{
		if(playfield[i].isWord) SetConsoleTextAttribute(hConsole, 10);
		else if(playfield[i].isExtraWord) SetConsoleTextAttribute(hConsole, 12);
		else SetConsoleTextAttribute(hConsole, 15);

		std::cout << playfield[i].letter << " ";

		if ((i+1) % this->worldSize.x == 0 && i != 0) std::cout << std::endl;
	}

	SetConsoleTextAttribute(hConsole, 15);
}

std::vector<Inhalt> wordJumble::CreateField(bool Kreuzung)
{
	std::vector<word> declaratedwords{};
	std::vector<Inhalt> output{};

	for (int i = 0; i < this->worldSize.produkt; i++) output.push_back(Inhalt{ NULL, false }); //init vector

	for (int i = 0; i < this->words.size(); i++)
	{
		word w{};
		w.word = &this->words[i];
		w.endIndex = 0;

		if (rand() % 2 == 1) this->reverseStr(this->words[i]); //reverse word

		do
		{
			w.ausrichtung = rand() % 4;
			w.startpoint = vec2{ rand() % worldSize.x + 1, rand() % worldSize.y + 1 };
			w.startpoint.produkt = w.startpoint.x + ((w.startpoint.y - 1) * worldSize.x) - 1; //x - y coords -> continues playfield || last -1 because vector started with 0
			//std::cout << "Word: " << *w.word << " | x: " << w.startpoint.x << " y: " << w.startpoint.y << " pro: " << w.startpoint.produkt << std::endl;
		} while (!Possible(&output, w, Kreuzung));
	}

	return output;
}

bool wordJumble::Possible(std::vector<Inhalt>* playfield, word Word, bool Kreuzung)
{
	std::vector<Inhalt> playfieldCopy = *playfield;
	int index{0};
	//end of word check
	if(Word.endIndex != 0)
		std::cout << "Word: " << *Word.word << " | x: " << Word.startpoint.x << " y: " << Word.startpoint.y << " pro: " << Word.startpoint.produkt << " | EndIndex: " << Word.endIndex << " | ausrichtung: " << Word.ausrichtung << std::endl;
	if (Word.ausrichtung == 0 && Word.startpoint.x + Word.word->size() - 1 <= worldSize.x) //waagerecht -> start.x + word.worldSize < spielfeld.worldSize
	{
		for (int i = Word.startpoint.produkt; i < Word.startpoint.produkt + Word.word->size(); i++, index++)
			if (!this->Check(&playfieldCopy, Word, Kreuzung, i, index)) return false;
		
		
		std::cout << "True" << std::endl;
		*playfield = playfieldCopy;
		return true;
	}
	else if (Word.ausrichtung == 1 && Word.startpoint.y + Word.word->size() - 1 <= worldSize.y) //senkrecht -> start.y + word.worldSize < spielfeld.worldSize
	{
		for (int i = Word.startpoint.produkt; i < Word.startpoint.produkt + (Word.word->size() * worldSize.x); i += worldSize.x, index++)
			if (!this->Check(&playfieldCopy, Word, Kreuzung, i, index)) return false;
		
		std::cout << "True" << std::endl;
		*playfield = playfieldCopy;
		return true;
	}
	else if (Word.ausrichtung == 2 && Word.startpoint.x + Word.word->size() - 1 <= worldSize.x && Word.startpoint.y + Word.word->size() - 1 <= worldSize.y) //diagonale (rechts)
	{
		for (int i = Word.startpoint.produkt; i < Word.startpoint.produkt + (Word.word->size() * worldSize.x); i += worldSize.x + 1, index++)
			if (!this->Check(&playfieldCopy, Word, Kreuzung, i, index)) return false;

		std::cout << "True" << std::endl;
		*playfield = playfieldCopy;
		return true;
	}
	else if (Word.ausrichtung == 3 && (signed int)Word.startpoint.x - (signed int)Word.word->size() + 1 > 0 && (signed int)Word.startpoint.y + (signed int)Word.word->size() - 1 <= this->worldSize.y) //diagonale (links)
	{
		for (int i = Word.startpoint.produkt; i < Word.startpoint.produkt + ((Word.word->size() - 1) * (static_cast<signed __int64>(worldSize.x) - 1)) + 1; i += worldSize.x - 1, index++)
			if (!this->Check(&playfieldCopy, Word, Kreuzung, i, index)) return false;

		std::cout << "True" << std::endl;
		*playfield = playfieldCopy;
		return true;
	}

	return false;
}

bool wordJumble::Check(std::vector<Inhalt>* playfieldCopy, word Word, bool Kreuzung, int i, int index)
{
	if (!Kreuzung && (*playfieldCopy)[i].isWord) return false;
	else if (Kreuzung && (*playfieldCopy)[i].letter != NULL && (*playfieldCopy)[i].letter != Word.word->at(index)) return false;
	else if (!Kreuzung && Word.endIndex > 0 && Word.endIndex < index) (*playfieldCopy)[i] = Inhalt{ Word.word->at(index), false, true };
	else if (Word.endIndex == 0) (*playfieldCopy)[i] = Inhalt{ Word.word->at(index), true };

	return true;
}

void wordJumble::Fill(std::vector<Inhalt>* playfield, std::vector<char> fillers, bool wordSnippets)
{
	for (int i = 0; i < this->worldSize.produkt; i++)
	{
		if (wordSnippets)
		{
			word Word{};
			Word.word = &this->words[rand() % this->words.size()];
			Word.startpoint = vec2{ i - (((int)i / this->worldSize.x) * this->worldSize.x) + 1,(int)i / this->worldSize.x + 1, i };
			Word.ausrichtung = rand() % 4;
			Word.endIndex = (int)(rand() % (Word.word->size() - 1) + 1);

			this->Possible(playfield, Word, false); //rest
		}
			

		if (!(*playfield)[i].isWord && (*playfield)[i].letter == NULL)
		{
			(*playfield)[i] = Inhalt{fillers[rand() % fillers.size() + 0], false};
		}
	}
}
void wordJumble::Fill(std::vector<Inhalt>* playfield, std::vector<char> fillers, std::vector<std::string> extraWords)
{
	for (int i = 0; i < this->worldSize.produkt; i++)
	{
		

		if (!(*playfield)[i].isWord && (*playfield)[i].letter == NULL)
		{
			(*playfield)[i] = Inhalt{ fillers[rand() % fillers.size() + 0], false };
		}
	}
}

std::string wordJumble::toUpper(std::string s)
{
	for (int i = 0; i < s.size(); i++) s[i] = toupper(s[i]);
	return s;
}
void wordJumble::reverseStr(std::string& str)
{
	for (int i = 0; i < str.length() / 2; i++) std::swap(str[i], str[str.length() - i - 1]);
}