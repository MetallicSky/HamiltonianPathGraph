#include "coordgraphbuilder.h"

using std::to_string;
using std::uniform_int_distribution;
using std::min;

void CoordGraphBuilder::isValidInt(const int number, const int min, const size_t max) const
{
    if (number < min) {
        throw std::out_of_range("Value can't be smaller than " + to_string(min) + " (" + to_string(number) + ")");
    }
    if (number > max) {
        throw std::out_of_range("Value can't be bigger than " + to_string(max) + " (" + to_string(number) + ")");
    }
}

void CoordGraphBuilder::dfs(size_t current, size_t end, vector<size_t> &path, vector<bool> &visited, int currentDist, vector<pair<int, vector<size_t> > > &results) const
{
    size_t n = myGraph.size();
    if (current == end && path.size() == n) {
        results.emplace_back(currentDist, path);
        return;
    }

    for (size_t next = 0; next < n; ++next) {
        int weight = myGraph.getWeight(current, next);
        if (weight != -1 && !visited[next]) {
            visited[next] = true;
            path.emplace_back(next);
            dfs(next, end, path, visited, currentDist + weight, results);
            path.pop_back();
            visited[next] = false;
        }
    }
}




void CoordGraphBuilder::fillCircle(const pair<int, int> &center, const int radius, const int amount) // Creates graph with all its vertices placed inside circle
{
    isValidInt(radius, 1, min(center.first, center.second));
    isValidInt(amount, 1, myGraph.size());
    isValidInt(center.first - radius, 0);
    isValidInt(center.second - radius, 0);

    std::set<pair<int, int>> coords;

    std::mt19937 rng(std::random_device{}());
    uniform_int_distribution<int> xDist(center.first - radius, center.first + radius);
    uniform_int_distribution<int> yDist(center.second - radius, center.second + radius);

    while (coords.size() < amount) {
        int x = xDist(rng);
        int y = yDist(rng);

        // Check if inside the circle
        if (std::hypot(x - center.first, y - center.second) <= radius) {
            pair<int, int> newCoord = {x, y};
            if (coords.find(newCoord) == coords.end()) {
                myGraph.setCoord(coords.size(), newCoord);
                coords.insert(newCoord);  // Add unique coordinate

                qDebug().noquote() << "Generated: (" << x << "," << y << ")\n";
            }
        }
    }
}

void CoordGraphBuilder::fillCircle(const int x, const int y, const int radius, const int amount)
{
    pair<int, int> center(x, y);
    fillCircle(center, radius, amount);
}

void CoordGraphBuilder::connectGraph(const size_t min, const size_t max)
{
    isValidInt(min, 0, max);
    isValidInt(max, min, myGraph.getWeights(0).size());
    size_t vCount = myGraph.size();

    // For each vertex, we will find its closest vertices
    for (size_t i = 0; i < vCount; ++i) {
        vector<pair<size_t, int>> distances;

        // Calculate the distance from vertex i to all other vertices
        for (size_t j = 0; j < vCount; ++j) {
            if (i == j || myGraph.edgesAmount(j) >= max) { // Skip the connection to itself or if j already has max connections
                continue;
            }
            if (myGraph.edgesAmount(i) >= max ) { // once i  vertex reaches max amount of edges, skip
                break;
            }
            bool duplicate = false;
            vector<pair<size_t, int> > iEdges = myGraph.getEdges(i);
            for (size_t k = 0; k < iEdges.size(); k++) {
                if (iEdges[k].first == j) {
                    duplicate = true;
                    break;
                }
            }
            if (duplicate) {
                continue;
            }
            pair<int, int> coord1 = myGraph.getCoord(i);
            pair<int, int> coord2 = myGraph.getCoord(j);

            // Calculate squared Euclidean distance to avoid square root
            int dist = (coord2.first - coord1.first) * (coord2.first - coord1.first) +
                       (coord2.second - coord1.second) * (coord2.second - coord1.second);

            distances.emplace_back(j, dist);
        }
        if (myGraph.edgesAmount(i) >= max) { // once i vertex reaches max amount of edges, skip
            continue;
        }

        // Sort distances in ascending order
        std::sort(distances.begin(), distances.end(), [](const pair<size_t, int>& a, const std::pair<size_t, int>& b) {
            return a.second < b.second;  // Sort by the distance (second element)
        });

        int connections = rand()%(max-min + 1) + min;
        // Connect the closest vertices (2-6 closest)
        for (size_t j = 0; j < connections && j < distances.size(); j++) {
            if (myGraph.edgesAmount(i) >= max) { // once i vertex reaches max amount of edges, stop
                break;
            }
            if (myGraph.edgesAmount(j) >= max) { // once j vertex reaches max amount of edges, skip
                continue;
            }
            size_t closestVertex = distances[j].first;
            int weight = sqrt(distances[j].second);

            myGraph.setWeight(i, closestVertex, weight);
        }
    }
}

void CoordGraphBuilder::printEdges() const
{
    for (int i = 0; i < myGraph.size(); i++) {
        vector<pair<size_t, int> > v = myGraph.getEdges(i);
        qDebug().noquote() << "[" << i << "]: " << v.size() << " edges";
        for (int j = 0; j < v.size(); j++) {
            qDebug().noquote() << "(" << v[j].first << " : " << v[j].second << "), ";
        }
        qDebug().noquote() << "\n";
    }
}

vector<vector<size_t> > CoordGraphBuilder::hamiltonianPaths(const size_t start, const size_t finish, const size_t pathAmount)
{
    const int graphSize = myGraph.getWeights(0).size();
    isValidInt(start, 0, graphSize - 1);
    isValidInt(finish, 0, graphSize - 1);
    isValidInt(pathAmount, 1);


    vector<pair<int, vector<size_t>>> results;
    vector<size_t> path = {start};
    vector<bool> visited(graphSize, false);
    visited[start] = true;

    dfs(start, finish, path, visited, 0, results);

    // Sort paths by distance
    sort(results.begin(), results.end(),
         [](const auto& a, const auto& b) { return a.first < b.first; });

    // Extract paths
    paths.clear();
    for (size_t i = 0; i < min(pathAmount, results.size()); ++i) {
        paths.emplace_back(results[i].second);
    }
    return paths;
}

vector<size_t> CoordGraphBuilder::getPath(const size_t pNum) const
{
    isValidInt(pNum, 0, paths.size() - 1);
    return paths[pNum];
}

const CoordGraph CoordGraphBuilder::getGraph() const
{
    return myGraph;
}

bool CoordGraphBuilder::isConnected() const
{
    size_t n = myGraph.size();
    if (n == 0) {
        return true;
    }

    vector<bool> visited(n, false);
    std::queue<size_t> q;
    q.push(0);
    visited[0] = true;

    size_t visitedCount = 1;

    while (!q.empty()) {
        size_t current = q.front();
        q.pop();

        for (size_t i = 0; i < n; ++i) {
            if (myGraph.getWeight(current, i) != -1 && !visited[i]) {
                visited[i] = true;
                q.push(i);
                ++visitedCount;
            }
        }
    }

    return visitedCount == n;
}

int CoordGraphBuilder::totalWeight(const vector<size_t> &path) const
{
    int total = 0;
    for (size_t i = 0; i < path.size() -1; i++) {
        total += myGraph.getWeight(path[i], path[i + 1]);
    }
    return total;
}

void CoordGraphBuilder::printPath(const vector<size_t> &path) const
{
    qDebug().noquote() << "Total: " << totalWeight(path) << "\n";
    for (size_t i = 0; i < path.size() -1; i++) {
        qDebug().noquote().nospace() << "[" << path[i] << "] - " << myGraph.getWeight(path[i], path[i + 1]) << " - ";
    }
    qDebug().noquote().nospace() << "[" << path[path.size() - 1] << "]";
}

string CoordGraphBuilder::pathToString(const size_t id) const
{
    vector<size_t> path = getPath(id);
    string output = "";
    output += "Total: " + to_string(totalWeight(path)) + "\n";
    for (size_t i = 0; i < path.size() -1; i++) {
        output += "[" + to_string(path[i]) + "] - " + to_string(myGraph.getWeight(path[i], path[i + 1])) + " - ";
    }
    output += "[" + to_string(path[path.size() - 1]) + "]";

    return output;
}

void CoordGraphBuilder::clear()
{
    myGraph.clear();
}

void CoordGraphBuilder::repopulate(int n)
{
    isValidInt(n);
    myGraph.clear();
    for (size_t i = 0; i < n; i++) {
        myGraph.addVertex();
    }
}
