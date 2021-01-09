#include <vector>
#include <fstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <assert.h>
#include <queue>
#include "Hw9.h"

using namespace std;

class Solver {
	public:
		Solver() {};
		void buildDict(string dict);
		void buildGraph();
		void solve(string start, string end);
	private:
		graph g;
		vector<string> dictionary;
		int intersections(string start, string end);
		int wordSize = 5;
};

void Solver::buildDict(string dict)
{
	ifstream input(dict);
	string line;
	while(getline(input, line))
	{
		g.addVertex();
		dictionary.push_back(line);
	}
	input.close();
	buildGraph();
}

void Solver::buildGraph()
{
	string word1, word2;
	for(int i = 0; i < dictionary.size(); i ++)
	{
		word1 = dictionary[i];
		for(int k = i; k < dictionary.size(); k ++)
		{
			word2 = dictionary[k];
			if(intersections(word1, word2) == 4)
			{
				g.addEdge(i, k);
			}
		}
	}
}

int Solver::intersections(string start, string end)
{
	int match = 0;
	for(int i = 0; i < wordSize; i ++)
	{
		if(start[i] == end[i])
		{
			match ++;
		}
	}
	return match;
}

void Solver::solve(string start, string end)
{
	int indexStart, indexEnd;
	for(int i = 0; i < dictionary.size(); i ++)
	{
		if(start == dictionary[i])
		{
			indexStart = i;
		}
		if(end == dictionary[i])
		{
			indexEnd = i;
		}
	}
	cout<<"Path from: "<<start<<" to "<<end<<":"<<endl;
	list<int>path = g.shortest_path(indexStart, indexEnd);
	list<int>::iterator itr;
	for(itr = path.begin(); itr!= path.end(); itr ++)
	{
		cout<<dictionary[*itr]<<" -> ";
	}
	cout<<"complete!"<<endl;
}

int main()
{
	Solver wordGrid;
	wordGrid.buildDict("knuth.txt");
	wordGrid.solve("black", "white");
	wordGrid.solve("tears", "smile");
	wordGrid.solve("small", "giant");
    wordGrid.solve("stone", "money");
    wordGrid.solve("angel", "devil");
    wordGrid.solve("amino", "right");
    wordGrid.solve("amigo", "signs");
    return 0;
}
