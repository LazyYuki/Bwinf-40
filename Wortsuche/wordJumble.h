#pragma once
#include "include.h"

class wordJumble
{
public:
	wordJumble(vec2 size, std::vector<std::string> words);

	std::vector<char> Einfach();
	std::vector<char> Mittel();
	std::vector<char> Schwer();

private:
	vec2 size{};
	std::vector<std::string> words{};
};

