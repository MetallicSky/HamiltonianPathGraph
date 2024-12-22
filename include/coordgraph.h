#ifndef COORDGRAPH_H
#define COORDGRAPH_H

#include "graph.h"

using std::pair;

class CoordGraph : public Graph
{
    vector<pair<int, int>> coords;

public:
    CoordGraph();
    CoordGraph(int n)
        : Graph(n), // Call the base class constructor
        coords(n, pair<int, int>(-1, -1)) // Initialize coords
    {}
    ~CoordGraph() override = default;

    [[nodiscard]] pair<int, int> getCoord(const size_t index) const; // Returns coords pair for given vertex
    void setCoord(const size_t index, const pair<int, int>& coord); // Sets new coords for given vertex;
    void setCoord(const size_t index, const int x, const int y);

    void addVertex(const size_t index) override; // This and overrides below also adjust coords
    size_t addVertex() override;

    size_t eraseVertex(const size_t index, size_t n = 1) override;
    void popVertex() override;
    void clear() override;
};

#endif // COORDGRAPH_H
