#include "fileManager.h"

std::string fileManager::GetFile(int argc, char* argv[])
{
    std::string path{ "" };

    if (argc > 1) path = GetFileArgs(argv);
    else path = GetFileConsole();

    if (fileExists(path))
    {
        std::cout << "File is Valid\n\n";
        return path;
    }
    else
    {
        std::cout << "\n\nFile does not exist\n\n";
        exit(ERROR);
    }
}

//Get File Per Args
std::string fileManager::GetFileArgs(char* argv[])
{
    std::cout << "Argv Path: " << argv[1] << std::endl;
    return argv[1];
}

//Get File Console
std::string fileManager::GetFileConsole()
{
    std::string path{ "" };
    std::cout << "Enter FilePath: ";
    std::cin >> path;

    return path;
}

//-----------------------
//Process File -- requires object for easier extracting
//-----------------------

fileManager::fileManager(std::string path)
{
    this->path = path;
    this->Content = (std::istringstream)FilepathToContent();
}

void fileManager::ExtractInfo(std::vector<std::vector<std::string>>& output, bool All, bool SplitOnSpace)
{
    std::string line{ "" };

    if (All)
    {
        while (std::getline(this->Content, line))
        {
            if (SplitOnSpace)
            {
                output.push_back(split(line, ' '));
            }
            else
            {
                std::vector<std::string> temp{ line };
                output.push_back(temp);
            }
        }
    }
    else
    {
        std::getline(this->Content, line);

        if (SplitOnSpace)
        {
            output.push_back(split(line, ' '));
        }
        else
        {
            std::vector<std::string> temp{ line };
            output.push_back(temp);
        }
    }
}

void fileManager::ExtractInfo(std::vector<std::vector<int>>& output, bool All)
{
    std::string line{ "" };

    if (All)
    {
        while (std::getline(this->Content, line))
        {
            output.push_back(VstringToVint(split(line, ' ')));
        }
    }
    else
    {
        std::getline(this->Content, line);
        output.push_back(VstringToVint(split(line, ' ')));
    }
}

void fileManager::IterateVector(std::vector<std::vector<std::string>> VVstring)
{
    for (std::vector<std::string> Vstring : VVstring)
    {
        for (std::string s : Vstring)
        {
            std::cout << s << " ";
        }

        std::cout << std::endl;
    }
}

void fileManager::IterateVector(std::vector<std::vector<int>> VVint)
{
    for (std::vector<int> Vint : VVint)
    {
        for (int i : Vint)
        {
            std::cout << i << " ";
        }

        std::cout << std::endl;
    }
}

//Helper Functions

std::istringstream fileManager::FilepathToContent()
{
    std::ifstream input_file(this->path);
    if (!input_file.is_open())
    {
        std::cout << "\n\nCould not open the file - '" << path << "'" << std::endl;
        exit(EXIT_FAILURE);
    }
    return std::istringstream(std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>()));
}

template <typename Out>
void fileManager::split(const std::string& s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> fileManager::split(const std::string& s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

std::vector<int> fileManager::VstringToVint(std::vector<std::string> Vstring)
{
    std::vector<int> out{};

    for (std::string c : Vstring)
    {
        out.push_back(std::atoi(c.c_str()));
    }

    return out;
}

bool fileManager::fileExists(std::string path)
{
    std::ifstream test(path);
    return (test) ? true : false;
}