#include "graph.h"

using std::to_string;

void Graph::isValid(const size_t index) const // Throws exception if provided vertex index is incorrect
{
    if (index < 0) {
        throw std::out_of_range("Vertex index can't be smaller than 0 (" + to_string(index) + ")");
    }
    if (index >= adjMatrix.size()) {
        throw std::out_of_range("Vertex index (" + to_string(index) + ") out of bounds (last index is " + to_string(adjMatrix.size() - 1) + ")");
    }
}

Graph::Graph() {}

Graph::Graph(const int n)  // Generates Graph with n amount of vertices and no edges
{
    if (n < 0) {
        throw std::invalid_argument("Number of vertices cannot be negative.");
    }
    adjMatrix = vector<vector<int> >(n, vector<int>(n, -1));
}

void Graph::setWeight(const size_t firstV, const size_t secondV, const int weight)  // Changes edge weight between two specified vertices
{
    isValid(firstV);
    isValid(secondV);
    if (firstV == secondV) {
        throw std::invalid_argument("Two vertices can't have same index");
    }
    if (weight <= 0) {
        throw std::invalid_argument("Weight can't be of non-positive value");
    }
    adjMatrix[firstV][secondV] = weight;
    adjMatrix[secondV][firstV] = weight;
}

int Graph::getWeight(const size_t firstV, const size_t secondV) const // Returns weight between two specified vertices. Returns -1 if edge doesn't exist
{
    isValid(firstV);
    isValid(secondV);
    return adjMatrix[firstV][secondV];
}

void Graph::addVertex(const size_t index)  // Creates new vertex at specified position and adjusts matrix
{
    int newSize = adjMatrix.size() + 1;
    if (index != adjMatrix.size()) {
        isValid(index);

        for (int i = 0; i < adjMatrix.size(); i++) {
            adjMatrix[i].insert(adjMatrix[i].begin() + index, -1);
        }
        adjMatrix.insert(adjMatrix.begin() + index, vector<int>(newSize, -1));
    }
    else {
        for (int i = 0; i < adjMatrix.size(); i++) {
            adjMatrix[i].emplace_back(-1);
        }
        adjMatrix.emplace_back(vector<int>(newSize, -1));
    }
}

size_t Graph::addVertex()  // Creates new vertex at the end, adjusts matrix and returns its index
{
    const int lastIndex = adjMatrix.size();
    addVertex(lastIndex);
    return lastIndex;
}

void Graph::clearWeights() // Removes all edges
{
    for (size_t i = 0; i < adjMatrix.size(); i++) {
        for (size_t i = 0; i < adjMatrix.size(); i++) {
            std::fill(adjMatrix[i].begin(), adjMatrix[i].end(), -1);
        }
    }
}

size_t Graph::eraseVertex(const size_t index, size_t n) // Deletes n (1 if not specified) vertices starting from index
{
    isValid(index);
    if (n == 0) {
        throw std::invalid_argument("Attempt to delete 0 elements");
    }
    if (index + n > adjMatrix.size()) {
        throw std::invalid_argument("Deleting more vertices than there are after index");
    }
    adjMatrix.erase(adjMatrix.begin() + index,
                    adjMatrix.begin() + index + n);
    for (size_t i = 0; i < adjMatrix.size(); i++) {
        adjMatrix[i].erase(adjMatrix[i].begin() + index,
                        adjMatrix[i].begin() + index + n);
    }
    return adjMatrix.size();
}

void Graph::popVertex() // Deletes last vertex and associated edges
{
    if (adjMatrix.size() == 0) {
        throw std::invalid_argument("Graph doesn't contain any vertices");
    }
    adjMatrix.pop_back();
    for (size_t i = 0; i < adjMatrix.size(); i++) {
        adjMatrix[i].pop_back();
    }
}

void Graph::clear() // Deletes the entire graph
{
    adjMatrix.clear();
}

vector<int> Graph::getWeights(const size_t vertex) const // returns <vector<int> that represents all edges and their weights associated with this vertex. -1 means edge does not exist
{
    isValid(vertex);
    return adjMatrix[vertex];
}

string Graph::toString(const size_t index) const // Prints edges for specified vertex
{
    string output = "";
    for (int i = 0; i < adjMatrix.size(); i++) {
        if (adjMatrix[index][i] == -1) {
            output += "_";
        }
        else {
            output += std::to_string(adjMatrix[index][i]);
        }
        output += " ";
    }
    output += '\n';
    return output;
}

string Graph::toString() const // Prints entire matrix into console
{
    string output = "";
    for (int i = 0; i < adjMatrix.size(); i++) {
        output += toString(i);
    }
    return output;
}

vector<pair<size_t, int>> Graph::getEdges(size_t index) const  // Returns all pairs of vertex index and edge weight that lead from given vertex
{
    isValid(index);
    vector<pair<size_t, int>> output;
    for (size_t i = 0; i < adjMatrix[index].size(); i++) {
        const int weight = adjMatrix[index][i];
        if (weight != -1) {
            output.emplace_back(i, weight);
        }
    }
    return output;
}

size_t Graph::size() const  // Returns the amount of vertices graph has
{
    return adjMatrix.size();
}

size_t Graph::edgesAmount(const size_t index) const // Returns the amount of edges given vertex has
{
    isValid(index);
    size_t amount = 0;
    for (size_t i = 0; i < adjMatrix[index].size(); i++) {
        if (adjMatrix[index][i] != -1) {
            amount++;
        }
    }
    return amount;
}

const vector<int> &Graph::operator[](const size_t index) const  // Returns read-only reference, similar to getEdges(). Also allows to use [][], similar to getEdge()
{
    isValid(index);
    return adjMatrix[index];
}
