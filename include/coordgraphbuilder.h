#ifndef COORDGRAPHBUILDER_H
#define COORDGRAPHBUILDER_H

#include <cmath>
#include <set>
#include <random>
#include <utility>
#include <iostream>
#include <queue>
#include <QDebug>

#include "coordgraph.h"

class CoordGraphBuilder
{
    CoordGraph myGraph;
    vector<vector<size_t> > paths; // Since calculating paths is expensive, they are stored and only cleared when vertices / edges are changed in any way

    void isValidInt(const int number, const int min = 1, const size_t max = 0 - 1) const;
    void dfs(size_t current, size_t end, vector<size_t>& path,
             vector<bool>& visited, int currentDist, vector<pair<int, vector<size_t>>>& results) const; // Helper method for hamiltonianPaths()
public:
    CoordGraphBuilder(){}
    CoordGraphBuilder(int n)
        : myGraph(n) // Call the base class constructor
    {}

    void fillCircle(const pair<int, int>& center, const int radius, const int amount); // Creates graph with all its vertices placed inside circle
    void fillCircle(const int x, const int y, const int radius, const int amount);

    void connectGraph(const size_t min, const size_t max); // Attempts to give every vertex between min and max edges

    void printEdges() const; // prints edges in Qt console (debug)

    vector<vector<size_t> > hamiltonianPaths(const size_t start, const size_t finish); // Finds all unique paths from start to finish that visit all vertices once

    [[nodiscard]] const vector<vector<size_t> > getPaths() const; // Get all paths

    [[nodiscard]] vector<size_t> getPath(const size_t pNum) const; // Get specified path

    [[nodiscard]] size_t pathsSize() const; // Get paths amount

    const CoordGraph getGraph() const; // Returns copy of myGraph

    [[nodiscard]] bool isConnected() const; // BFS to check connectivity

    [[nodiscard]] int totalWeight(const vector<size_t>& path) const; // Returns total distance (weight) of a given path

    void printPath(const vector<size_t>& path) const; // Print given path to Qt console (debug)
    void printPath(const size_t id) const;

    [[nodiscard]] string pathToString(const size_t id) const; // Returns given path as string
    [[nodiscard]] string pathToString(const vector<size_t>& path) const;

    void clear(); // Delete all vertices, edges and paths

    void repopulate(int n); // Call clear() and create n vertices
};

#endif // COORDGRAPHBUILDER_H
