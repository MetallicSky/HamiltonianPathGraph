#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cout;
using std::string;
using std::ostream;
using std::pair;

class Graph
{
protected:
    vector<vector<int> > adjMatrix;

    void isValid(const size_t index) const; // Throws exception if provided vertex index is incorrect

public:
    Graph();
    Graph(const int n); // Generates Graph with n amount of vertices and no edges
    virtual ~Graph() = default;

    void setWeight(const size_t firstV, const size_t secondV, const int weight = 1); // Changes edge weight between two specified vertices and creates it if it wasn't in place before
    [[nodiscard]] int getWeight(const size_t firstV, const size_t secondV) const; // Returns weight between two specified vertices. Returns -1 if edge doesn't exist

    virtual void addVertex(const size_t index); // Creates new vertex at specified position and adjusts matrix
    virtual size_t addVertex(); // Creates new vertex at the end, adjusts matrix and returns its index

    void clearWeights(); // Removes all edges

    virtual size_t eraseVertex(const size_t index, size_t n = 1); // Deletes n (1 if not specified) vertices starting from index, returns remaining vertices amount
    virtual void popVertex(); // Deletes last vertex and associated edges
    virtual void clear(); // Deletes the entire graph

    [[nodiscard]] vector<int> getWeights(const size_t vertex) const; // returns <vector<int> that represents all edges and their weights associated with this vertex. -1 means edge does not exist

    [[nodiscard]] string toString(const size_t index) const; // Prints edges for specified vertex
    [[nodiscard]] string toString() const; // Prints entire matrix into console

    [[nodiscard]] vector<pair<size_t, int>> getEdges(size_t index) const; // Returns all pairs of vertex index and edge weight that lead from given vertex

    [[nodiscard]] size_t size() const; // Returns the amount of vertices graph has
    [[nodiscard]] size_t edgesAmount(const size_t index) const; // Returns the amount of edges given vertex has

    [[nodiscard]] const vector<int>& operator[](const size_t index) const; // Returns read-only reference, similar to getEdges(). Also allows to use [][], similar to getEdge()
};

inline ostream& operator<<(ostream& os, const Graph& g) { // Allows for operations such as "cout << Graph"
    os << g.toString();
    return os;
}

#endif // GRAPH_H
