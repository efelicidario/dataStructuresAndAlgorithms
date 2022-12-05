#include "graph.h"

// CS311 graph.cpp
// Name: Tyler Felicidario

// @brief Construct a Graph with the given number of vertices.
// @param nV The number of vertices in the graph.

Graph::Graph(int nV)
{
    this->numVerts = nV;
    vertices = vector<Vertex>(nV);
    for (int i = 0; i < nV; i++) {
        vector<Edge> list;
        adjList.push_back(list);
    }
    
}

// @brief destructor
Graph::~Graph()
{
}

// @brief add a vertex to the graph
void Graph::addVertex(Vertex v)
{
    vertices.push_back(v);
    vector<Edge> list;
    adjList.push_back(list);
    numVerts++;
    // vertices[v.id] = v;

}

// @brief add a directed edge v1->v2 to the graph
void Graph::addDirectedEdge(int v1, int v2, float weight)
{
    Edge e(v1, v2, weight);

    adjList[v1].push_back(e);
}

// @brief add an undirected edge to the graph
void Graph::addUndirectedEdge(int v1, int v2, float weight)
{
    Edge edge1(v1, v2, weight);
    Edge edge2(v2, v1, weight);

    adjList[v1].push_back(edge1);
    adjList[v2].push_back(edge2);

}

// @brief the number of outgoing edges from a vertex
int Graph::outDegree(int v)
{
    return adjList[v].size();
}

// @brief depth first search from vertex v
vector<int> Graph::DepthFirstSearch(int v)
{
    vector<bool> visited(numVerts, false);
    vector<int> list;
    vector<int> stack;

    // Push v to stack
    stack.push_back(v);
    int currentV;

    // While stack is not empty
    while (stack.size() != 0) {
        // Save currentV, 
        // pop_back() does not return anything
        currentV = stack[stack.size() - 1];
        stack.pop_back();
        // If currentV is not visited
        if (visited[currentV] == false) {
            // Visit currentV
            // then mark as visited
            visited[currentV] = true;
            list.push_back(currentV);
        }
        // For each vertex, i, adjacent to current V
        for (int i = outDegree(currentV) - 1; i >= 0; i--) {
            // If i isn't visited
            // push adjacent vertex to stack
            // and set previous to currentV
            if (visited[adjList[currentV][i].to_vertex] == false) {
                stack.push_back(adjList[currentV][i].to_vertex);
            }
        }
    }
    return list;
}

// @brief breadth first search from a vertex
vector<int> Graph::BreadthFirstSearch(int v)
{
    vector<bool> discovered(numVerts, false);
    vector<int> list;
    queue<int> frontierQueue;
    int currentV;

    // Enqueue v in frontierQueue
    // mark v as discovered
    frontierQueue.push(v);
    discovered[v] = true;

    // While frontierQueue is not empty
    while (frontierQueue.size() != 0) {
        // currentV = Dequeue from frontierQueue
        // "visit" curentV
        currentV = frontierQueue.front();
        frontierQueue.pop();
        list.push_back(currentV);
        // For each vertex adjV adjacent to currentV
        for (int i = 0; i < adjList[currentV].size(); i++) {
            // If adjV is not discovered
            if (discovered[adjList[currentV][i].to_vertex] == false) {
                // Enqueue adjV in frontierQueue
                // mark adjV as discovered
                frontierQueue.push(adjList[currentV][i].to_vertex);
                discovered[adjList[currentV][i].to_vertex] = true;
            }
        }
    }
    return list;
}

/**
 * @brief Check if the graph has cycles
 * @return true if the graph has cycles
 */
bool Graph::checkCycle()
{
    // EC: Implement the algorithm to check if the graph has cycles
    // Assume an undirected graph
    return false;
}

// @brief print the graph
void Graph::printGraph()
{
    cout << "Graph:" << endl;
    for (int i = 0; i < numVerts; i++)
    {
        cout << i << ": ";
        for(auto j = adjList[i].begin(); j != adjList[i].end(); ++j) {
            cout << (*j).to_vertex << " " ;
        }
        cout << endl;
    }
    cout << endl;
}
