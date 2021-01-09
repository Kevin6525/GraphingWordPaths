#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <assert.h>
#include <queue>

using namespace std;

class graph
{
	public:
    graph() {};
    int size();
    void addVertex();
    void addEdge(int a, int b);
    bool isEdge(int a, int b);
    list<int> shortest_path(int start, int end);

private:
    vector<list<int>> v;
    void bfs(int start, vector<int> &parent);
};

int graph::size() 
{
    return v.size();
}

void graph::addVertex()
{
    v.push_back(list<int>());
}

void graph::addEdge(int source, int target) 
{
    assert(source < size() && target < size());
    if (!isEdge(source, target))
    {
        v[source].push_front(target);
        v[target].push_front(source);
    }
}

bool graph::isEdge(int source, int target) 
{
	if(source >= size() || target >= size())
	{
		return false;
	}
    for (auto i: v[source])
    {
    	if (i == target)
    	{
    		return true;
		}
	}
    return false;
}

list<int> graph::shortest_path(int start, int end) 
{
    vector<int> parent(size(), -1); 
    bfs(start, parent);

    if (parent[end] == -1) 
	{
		cout<<"No path found"<<endl;
        return list<int>();
    }

    list<int> path;

    for(int i = end; i != start; i = parent[i]) 
	{
        path.push_front(i);
    }
    path.push_front(start);

    return path;
}

void graph::bfs(int start, vector<int> &parent) {
    queue<int> vertices;

    vertices.push(start);
    parent[0] = start;
    while (!vertices.empty())
    {
        int current = vertices.front();
        vertices.pop();
        for (auto i: v[current])
        {
            if(parent[i] == -1) 
			{
                parent[i] = current;
                vertices.push(i);
            }
        }
    }
}

