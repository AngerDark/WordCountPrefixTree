#pragma once

#include <set>
#include <map>
#include <vector>
#include <string>

/*
	Simple prefix tree with WordCount metadata
*/
struct PTNode
{
	std::map<char, PTNode*> Childs;		// Child nodes
	int WordCount = 0;						//If count more than 0, take it as a word

	PTNode()
	{
		WordCount = 0;
	}

	~PTNode()
	{
		for (auto node : Childs)
		{
			delete node.second;
		}

		Childs.clear();
	}
};


/*
	Prefix tree with word counting
*/
class PTree
{
private:	
	//All symbols that identifies the end of the word
	std::set<char> wordSeparatorSymbols;
	//Root of the prefix tree
	PTNode* Root;
	//Current position in tree
	PTNode* Current;

private:
	//Try to add new New to the tree, if any of separator appeared - return to root
	void AddNode(char Symbol);
	//Returns to root and increment word appearance count
	void ReturnToRoot();
	//Internal function for printing tree
	void PrintWordInfo_Internal(PTNode* Node, std::string const& Prefix);
public:
	PTree();

	//Initialize tree with string
	void InitTree(std::string && InString);

	//Prints words count
	void PrintWordInfo();

	//Removes all Nodes
	void Clear();

	virtual ~PTree();
};

