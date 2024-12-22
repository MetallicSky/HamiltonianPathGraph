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
    vector<vector<size_t> > paths;

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

    void connectGraph(const size_t min, const size_t max);

    void printEdges() const;

    [[nodiscard]] vector<vector<size_t> > hamiltonianPaths(const size_t start, const size_t finish, const size_t pathAmount); // Finds all unique paths from start to finish that visit all vertices once

    [[nodiscard]] vector<size_t> getPath(const size_t pNum) const;

    const CoordGraph getGraph() const;

    [[nodiscard]] bool isConnected() const; // BFS to check connectivity

    [[nodiscard]] int totalWeight(const vector<size_t>& path) const;

    void printPath(const vector<size_t>& path) const;

    [[nodiscard]] string pathToString(const size_t id) const;

    void clear();

    void repopulate(int n);
};

#endif // COORDGRAPHBUILDER_H
