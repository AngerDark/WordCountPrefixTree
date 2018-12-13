#include "pch.h"
#include "PTree.h"

#include <iostream>

PTree::PTree():
	wordSeparatorSymbols({ ',' , '.', '-', ':', ';', '!', '?', '\'', '"', ' ', '(', ')', '\n', '\r' })
{
}

void PTree::InitTree(std::string const* InString)
{
	Root = new PTNode();
	
	Current = Root;

	for (auto symbol : *InString)
	{
		AddNode(symbol);
	}
	ReturnToRoot();
}

void PTree::AddNode(char Symbol)
{
	for (auto extremeSymbol : wordSeparatorSymbols)
	{
		if (Symbol == extremeSymbol)
		{
			ReturnToRoot();
			return;
		}
	}

	//If there is no childs - add new one
	if (Current->Childs.find(Symbol) == Current->Childs.end())
	{
		Current->Childs[Symbol] = new PTNode();
		Current = Current->Childs[Symbol];
	}
	else
	{
		Current = Current->Childs[Symbol];
	}
}

void PTree::ReturnToRoot()
{
	if (Current != Root)
	{
		Current->WordCount++;
	}
	
	Current = Root;
}

void PTree::PrintWordInfo()
{
	std::string output;

	for (auto node : Root->Childs)
	{	
		output = node.first;
		PrintWordInfo_Internal(node.second, output);
	}
}

void PTree::PrintWordInfo_Internal(PTNode* Node, std::string const& Prefix)
{
	if (Node->WordCount >= 1)
		std::cout << Prefix << " - " << Node->WordCount << std::endl;

	for (auto node : Node->Childs)
	{	
		PrintWordInfo_Internal(node.second, Prefix + node.first);
	}
}

void PTree::Clear()
{		
	if (Root != nullptr)
	{
		delete Root;
		Root = nullptr;
	}
}

PTree::~PTree()
{
	Clear();
}
