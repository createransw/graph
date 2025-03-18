#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

void search(
        const std::vector<std::vector<size_t>> &graph,
        size_t beginnig, 
        std::vector<int32_t> &result
        )
// BFS algorithm
{
    result.resize(graph.size(), -1); // -1 indicates unvisited
    result[beginnig] = 0;

    std::queue<size_t> order; // FIFO collection
    order.push(beginnig);

    while (!order.empty()) {
        size_t current = order.front();
        order.pop();
        int32_t distance = result[current] + 1; // one more edge for connected

        for (auto i : graph[current]) {
            if (result[i] < 0) { // still unvisited
                result[i] = distance;
                order.push(i);
            }
        }
    }
}


int main() {
    std::ifstream input("graph.txt");

    size_t vertexes, edges;
    input >> vertexes >> edges;

    std::vector<std::vector<size_t>> graph(vertexes); // connections list
    for (size_t i = 0; i < edges; ++i) {
        size_t a, b;
        input >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a); // undirected graph
    }

    size_t beginning;
    input >> beginning;

    std::vector<int32_t> result; // vector of distances
    search(graph, beginning, result);
    for (auto i : result) {
        std::cout << i << std::endl;
    }
    return 0;
}
