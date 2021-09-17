#pragma once
#include "include.h"
class fileManager
{
public:
	//Try getting file throught Args and Console
	static std::string GetFile(int argc, char* argv[]);

	//Get File Per Args
	static std::string GetFileArgs(char* argv[]);
	//Get File Console
	static std::string GetFileConsole();

	//-----------------------
	//Process File -- requires object for easier extracting
	//-----------------------

	fileManager(std::string path);

	//Extracts info from textfile
	void ExtractInfo(std::vector<std::vector<std::string>>& output, bool All, bool SplitOnSpace);
	void ExtractInfo(std::vector<std::vector<int>>& output, bool All);

	//Iterates througth the vectors
	static void IterateVector(std::vector<std::vector<std::string>> VVstring);
	static void IterateVector(std::vector<std::vector<int>> VVint);

private:
	std::string path{ "" };
	std::istringstream Content{ "" }; //the file contant

	std::istringstream FilepathToContent();

	template <typename Out>
	void split(const std::string& s, char delim, Out result);
	std::vector<std::string> split(const std::string& s, char delim);
	std::vector<int> VstringToVint(std::vector<std::string> Vstring);

	static bool fileExists(std::string path);
};