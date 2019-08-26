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

