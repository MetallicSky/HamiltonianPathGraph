#include "coordgraph.h"
pair<int, int> CoordGraph::getCoord(const size_t index) const  // Returns coords pair for given vertex
{
    isValid(index);
    return coords[index];
}

void CoordGraph::setCoord(const size_t index, const pair<int, int>& coord) // Sets new coords for given vertex;
{
    isValid(index);
    if (coord.first < 0 || coord.second < 0) {
        throw std::invalid_argument("Coordinates can't be negative");
    }
    coords[index] = coord;
}

void CoordGraph::setCoord(const size_t index, const int x, const int y)
{
    pair<int, int> coord(x, y);
    setCoord(index, coord);
}

void CoordGraph::addVertex(const size_t index)
{
    Graph::addVertex(index);
    coords.insert(coords.begin() + index, pair<int, int>(-1, -1));
}

size_t CoordGraph::addVertex()
{
    const size_t lastIndex = adjMatrix.size();
    addVertex(lastIndex);
    return lastIndex;
}

size_t CoordGraph::eraseVertex(const size_t index, size_t n)
{
    Graph::eraseVertex(index, n);
    coords.erase(coords.begin() + index,
                    coords.begin() + index + n);
    return coords.size();
}

void CoordGraph::popVertex()
{
    Graph::popVertex();
    coords.pop_back();
}

void CoordGraph::clear()
{
    Graph::clear();
    coords.clear();
}
