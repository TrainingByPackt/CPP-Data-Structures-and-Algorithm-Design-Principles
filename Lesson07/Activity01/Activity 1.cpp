// Chapter 7 : Activity 1

#include <iostream>
#include <vector>
#include <stack>
#include <climits>

using namespace std;

struct Edge
{
	int start;  // The starting vertex
	int end;    // The destination vertex
	int weight; // The edge weight

	// Constructor
	Edge(int s, int e, int w) : start(s), end(e), weight(w) {}
};


// Constant assigned the highest 32-bit integer value, used to designate
// untraversed vertices

const int UNKNOWN = INT_MAX;

vector<Edge*> edges; // Collection of pointers to edge objects
int V; 				 // Total number of vertices in graph

void FillStack(int node, vector<vector<int>> &adj, vector<bool> &visited, vector<int> &stack)
{
	visited[node] = true;

	for(auto next : adj[node])
	{
		if(!visited[next])
		{
			FillStack(next, adj, visited, stack);
		}
	}
	stack.push_back(node);
}

vector<bool> isStuck;
vector<int> inComponent;
int componentIndex;

void GetComponent(int node, vector<vector<int>> &adj, vector<bool> &visited, vector<int> &component)
{
	component.push_back(node);
	visited[node] = true;

	inComponent[node] = componentIndex;

	for(auto next : adj[node])
	{
		if(!visited[next])
		{
			GetComponent(next, adj, visited, component);
		}
		else if(inComponent[node] != inComponent[next])
		{
			isStuck[inComponent[next]] = false;
		}
	}
}

vector<vector<int>> GetTranspose(int V, vector<vector<int>> adj)
{
	vector<vector<int>> transpose(V);

	for(int i = 0; i < V; i++)
	{
		for(auto next : adj[i])
		{
			transpose[next].push_back(i);
		}
	}
	return transpose;
}

vector<vector<int>> Kosaraju(int V, vector<vector<int>> adj)
{
	vector<bool> visited(V, false);
	vector<int> stack;

	for(int i = 0; i < V; i++)
	{
		if(!visited[i])
		{
			FillStack(i, adj, visited, stack);
		}
	}
	vector<vector<int>> transpose = GetTranspose(V, adj);
	vector<vector<int>> components;

	fill(visited.begin(), visited.end(), false);

	while(!stack.empty())
	{
		int node = stack.back();
		stack.pop_back();

		if(!visited[node])
		{
			vector<int> component;

			GetComponent(node, transpose, visited, component);

			components.push_back(component);
			componentIndex++;
		}
	}
	return components;
}

bool HasNegativeCycle(vector<int> distance, vector<Edge*> edges)
{
	// Iterate through edges one last time
	for(auto edge : edges)
	{
		int u = edge->start;
		int v = edge->end;
		int w = edge->weight;

		if(distance[u] == UNKNOWN) continue;

		// If we can still find any path shorter than one we have already found, the graph must contain
		// a negative cycle.

		if(distance[u] + w < distance[v])
		{
			cout << "NEGATIVE CYCLE FOUND" << endl;
			return true;
		}
	}
	return false;
}

int BellmanFord(int V, int start, vector<Edge*> edges)
{
	vector<int> score(V, UNKNOWN);

	score[start] = 0;

	for(int i = 1; i < V; i++)
	{
		for(auto edge : edges)
		{
			int start = edge->start;
			int end = edge->end;
			int weight = edge->weight;

			if(score[start] != UNKNOWN && score[start] + weight < score[end])
			{
				score[end] = score[start] + weight;
			}
		}
	}
	if(HasNegativeCycle(score, edges))
	{
		return UNKNOWN;
	}

	int result = UNKNOWN;

	for(int i = 0; i < V; i++)
	{
		if(i == start) continue;

		result = min(result, score[i]);
	}
	return result;
}


int main()
{
	int V, E;
	cin >> V >> E;

	vector<Edge*> edges;
	vector<vector<int>> adj(V + 1);
	isStuck.resize(V, true);
	inComponent.resize(V, -1);

	for(int i = 0; i < E; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;

		edges.push_back(new Edge(u, v, w));
		adj[u].push_back(v);
	}

	vector<int> results;

	for(int i = 0; i < V; i++)
	{
		if(adj[i].empty())
		{
			results.push_back(UNKNOWN);
			continue;
		}
		int shortest = BellmanFord(V, i, edges);

		if(shortest == UNKNOWN)
		{
			cout << "INVALID MAZE" << endl;
			return 0;
		}
		results.push_back(shortest);
	}
	for(int i = 0; i < V; i++)
	{
		cout << i << ": ";

		(results[i] == UNKNOWN) ? cout << "DEAD END" << endl
								: cout << results[i] << endl;
	}
	auto components = Kosaraju(V, adj);	

	for(int i = 0; i < components.size(); i++)
	{
		if(isStuck[i])
		{
			for(auto node : components[i])
			{
				cout << node << " ";
			}
			cout << endl;
		}
	}
	return 0;
}

/*
 9 14
 0 1 5
 0 3 -3
 1 2 3
 1 4 5
 2 3 -7
 2 5 8
 3 7 10
 4 2 -5
 5 4 12
 5 6 13
 6 2 -6
 6 7 8
 7 8 5
 8 3 4



 */

/*

 6 8
 0 1 3
 1 3 -8
 2 1 3
 3 2 3
 2 4 2
 2 5 5
 4 5 -1
 5 1 8

 10
 5
 5
 0 1 3
 1 2 5
 1 3 10
 3 2 -7
 2 4 2

 1
 7 9
 0 1 50
 1 0 -10
 1 2 -50
 2 0 0
 3 0 3
 3 4 0
 4 5 1
 5 3 -2
 6 0 -25

 INVALID MAZE

 */

/*
 15 26
 0 4 -40
 1 6 92
 2 3 77
 3 1 61
 3 6 7
 3 2 81
 4 2 93
 5 2 48
 6 0 -27
 6 4 -77
 7 5 -1
 8 3 -49
 8 6 52
 8 1 70
 9 6 20
 9 0 95
 9 3 1
 10 5 -17
 11 1 75
 11 0 -57
 12 1 -62
 12 4 -5
 13 3 -19
 13 6 17
 13 4 94
 14 1 63

 0: -40
 1: 15
 2: 7
 3: -70
 4: 93
 5: 48
 6: -77
 7: -1
 8: -119
 9: -69
 10: -17
 11: -97
 12: -62
 13: -89
 14: 63

 */

/*
 8 16
 0 3 54
 1 0 -5
 1 3 6
 2 0 -44
 2 3 -38
 2 1 -17
 3 1 96
 4 0 -44
 4 3 15
 5 2 11
 5 0 44
 5 3 91
 6 1 53
 6 2 62
 6 0 77
 7 3 68

 0: 54
 1: -5
 2: -44
 3: 91
 4: -44
 5: -33
 6: 18
 7: 68

 */

/*
 10 17
 0 1 90
 1 2 -16
 1 0 79
 1 3 95
 2 3 -89
 3 1 -23
 3 0 -38
 4 1 -34
 5 3 -38
 6 0 59
 6 2 85
 7 4 47
 7 1 85
 7 0 -44
 8 0 -25
 8 2 11
 9 4 -95

 INVALID MAZE
 */
