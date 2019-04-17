#include "function.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <climits>
#include <list>
using namespace std;
bool isInit = false;

//VertexArr

using namespace std;
# define INF 0x3f3f3f3f

// iPair ==>  Integer Pair
typedef pair<int, int> iPair;

// This class represents a directed graph using
// adjacency list representation
class Graph
{
    int V;    // No. of vertices
    int E;    //No. of edges
    
    // In a weighted graph, we need to store vertex
    // and weight pair for every edge
    list< pair<int, int> > *adj;
    vector< pair<int, iPair> > edges;
    list<int> *adjj;
    
public:
    Graph(int V);  // Constructor
    
    // function to add an edge to graph
    void addMyEdge(int u, int v, int w);
    
    // prints shortest path from s
    int myShortestPath(int s,int dest);
    
    int kruskalMST();
    
    bool greedyColoring();
};

// Allocates memory for adjacency list
Graph::Graph(int V)
{
    this->V = V;
    E = 0;
    adj = new list<iPair> [V];
    adjj = new list<int>[V];
}

void Graph::addMyEdge(int u, int v, int w)
{
    E++;
    edges.push_back({w, {u, v}});
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
    adjj[u].push_back(v);
    adjj[v].push_back(u);
}

// Prints shortest paths from src to all other vertices
int Graph::myShortestPath(int src, int dest)
{
    // Create a priority queue to store vertices that
    // are being preprocessed. This is weird syntax in C++.
    // Refer below link for details of this syntax
    // https://www.geeksforgeeks.org/implement-min-heap-using-stl/
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
    
    // Create a vector for distances and initialize all
    // distances as infinite (INF)
    vector<int> dist(V, INF);
    
    // Insert source itself in priority queue and initialize
    // its distance as 0.
    pq.push(make_pair(0, src));
    dist[src] = 0;
    
    /* Looping till priority queue becomes empty (or all
     distances are not finalized) */
    while (!pq.empty())
    {
        // The first vertex in pair is the minimum distance
        // vertex, extract it from priority queue.
        // vertex label is stored in second of pair (it
        // has to be done this way to keep the vertices
        // sorted distance (distance must be first item
        // in pair)
        int u = pq.top().second;
        pq.pop();
        
        // 'i' is used to get all adjacent vertices of a vertex
        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            // Get vertex label and weight of current adjacent
            // of u.
            int v = (*i).first;
            int weight = (*i).second;
            
            //  If there is shorted path to v through u.
            if (dist[v] > dist[u] + weight)
            {
                // Updating distance of v
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    
    return dist[dest];
    // Print shortest distances stored in dist[]
    //printf("Vertex   Distance from Source\n");
    //for (int i = 0; i < V; ++i)
    //printf("%d \t\t %d\n", i, dist[i]);
}

// To represent Disjoint Sets
struct DisjointSets
{
    int *parent, *rnk;
    int n;
    
    // Constructor.
    DisjointSets(int n)
    {
        // Allocate memory
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];
        
        // Initially, all vertices are in
        // different sets and have rank 0.
        for (int i = 0; i <= n; i++)
        {
            rnk[i] = 0;
            
            //every element is parent of itself
            parent[i] = i;
        }
    }
    
    // Find the parent of a node 'u'
    // Path Compression
    int find(int u)
    {
        /* Make the parent of the nodes in the path
         from u--> parent[u] point to parent[u] */
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }
    
    // Union by rank
    void merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        
        /* Make tree with smaller height
         a subtree of the other tree  */
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else // If rnk[x] <= rnk[y]
            parent[x] = y;
        
        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};

/* Functions returns weight of the MST*/

int Graph::kruskalMST()
{
    int mst_wt = 0; // Initialize result
    
    // Sort edges in increasing order on basis of cost
    sort(edges.begin(), edges.end());
    
    // Create disjoint sets
    DisjointSets ds(V);
    
    // Iterate through all sorted edges
    vector< pair<int, iPair> >::iterator it;
    for (it=edges.begin(); it!=edges.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;
        
        int set_u = ds.find(u);
        int set_v = ds.find(v);
        
        // Check if the selected edge is creating
        // a cycle or not (Cycle is created if u
        // and v belong to same set)
        if (set_u != set_v)
        {
            // Current edge will be in the MST
            // so print it
            //cout << u << " - " << v << endl;
            
            // Update MST weight
            mst_wt += it->first;
            
            // Merge two sets
            ds.merge(set_u, set_v);
        }
    }
    
    return mst_wt;
}

// Assigns colors (starting from 0) to all vertices and prints
// the assignment of colors
bool Graph::greedyColoring()
{
    int result[V];
    
    // Assign the first color to first vertex
    result[0]  = 0;
    
    // Initialize remaining V-1 vertices as unassigned
    for (int u = 1; u < V; u++)
        result[u] = -1;  // no color is assigned to u
    
    // A temporary array to store the available colors. True
    // value of available[cr] would mean that the color cr is
    // assigned to one of its adjacent vertices
    bool available[V];
    for (int cr = 0; cr < V; cr++)
        available[cr] = false;
    
    // Assign colors to remaining V-1 vertices
    for (int u = 1; u < V; u++)
    {
        // Process all adjacent vertices and flag their colors
        // as unavailable
        list<int>::iterator i;
        for (i = adjj[u].begin(); i != adjj[u].end(); ++i)
            if (result[*i] != -1)
                available[result[*i]] = true;
        
        // Find the first available color
        int cr;
        for (cr = 0; cr < V; cr++)
            if (available[cr] == false)
                break;
        
        result[u] = cr; // Assign the found color
        if(cr>1) return false;
        // Reset the values back to false for the next iteration
        for (i = adjj[u].begin(); i != adjj[u].end(); ++i)
            if (result[*i] != -1)
                available[result[*i]] = false;
    }
    return true;
}

Graph g(0);

void Implement::addEdge(const int label_1, const int label_2 , const int weight){
    if(label_2==label_1) return;
    if(!isInit){
        g = *new Graph((int)VertexArr.size());
        isInit = true;
    }
    g.addMyEdge(label_1,label_2,weight);
    //VertexArr[label_1].neighbors.push_back(*new Neighbor(label_2, weight));
    //VertexArr[label_2].neighbors.push_back(*new Neighbor(label_1, weight));
}
int Implement::shortest_path(const int label_1 , const int label_2){
    if(label_2 == label_1) return 0;
    else return g.myShortestPath(label_1, label_2);
}
int Implement::mst_weight(){
    return g.kruskalMST();
}
bool Implement::two_colorable(){
    return g.greedyColoring();
}


