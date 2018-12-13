#include "pch.h"

#include <iostream>
#include <fstream>
#include <filesystem>

#include "PTree.h"

using namespace std;

bool CheckForFile(const string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

int main(int argc, char *argv[])
{
	//Checking for args
	if (argc < 2)
	{
		cerr << "Error. Empty argument list\n";

		return 0;
	}

	string fileName(argv[1]);

	bool isCaseSensivive = true;
	if (std::strcmp("ToLower", argv[2]))
	{
		isCaseSensivive = false;
	}

	//For testing
	//string fileName = "alice.txt";

	//Checking file accessibility
	if (!CheckForFile(fileName))
	{
		cerr << "Error. File not found\n";

		return 0;
	}

	//Open filestream
	ifstream ifs(fileName);
	//Read whole file to the string 
	string text((istreambuf_iterator<char>(ifs)),
		(istreambuf_iterator<char>()));	

	text.erase(remove(text.begin(), text.end(), '\''), text.end());

	if (!isCaseSensivive)
	{
		transform(text.begin(), text.end(), text.begin(), ::tolower);
	}

	PTree pTree;
	//Init tree with text
	pTree.InitTree(move(text));
	//Print word infos
	pTree.PrintWordInfo();	
	
	pTree.Clear();
	//Close filestream
	ifs.close();

	return 1;
}