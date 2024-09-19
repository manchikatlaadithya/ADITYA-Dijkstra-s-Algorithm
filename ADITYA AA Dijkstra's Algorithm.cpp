#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <algorithm>
#include <cctype> // For toupper

using namespace std;

// Function to convert a character to uppercase
char toUpperCase(char c) {
    return toupper(c);
}

// Function to find the shortest path using Dijkstra's algorithm
void dijkstra(const unordered_map<char, vector<pair<char, int>>>& graph, char start, char end) {
    // Step 1: Set up distances and priority queue
    unordered_map<char, int> distances;
    unordered_map<char, char> previous;
    for (const auto& node : graph) {
        distances[node.first] = numeric_limits<int>::max(); // Initialize distances to infinity
    }
    distances[start] = 0;

    // Min-heap to find the node with the smallest distance
    priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> pq;
    pq.push({0, start}); // Push the start node with distance 0

    // Step 2: Process nodes
    while (!pq.empty()) {
        char current = pq.top().second;
        int current_distance = pq.top().first;
        pq.pop();

        // If we reached the end node, break
        if (current == end) break;

        // Process each neighbor of the current node
        for (const auto& neighbor : graph.at(current)) {
            char neighbor_node = neighbor.first;
            int edge_weight = neighbor.second;

            // Calculate new distance to the neighbor
            int new_distance = current_distance + edge_weight;
            if (new_distance < distances[neighbor_node]) {
                distances[neighbor_node] = new_distance; // Update the distance
                previous[neighbor_node] = current; // Keep track of the path
                pq.push({new_distance, neighbor_node}); // Push the neighbor to the queue
            }
        }
    }

    // Step 3: Output the results
    if (distances[end] == numeric_limits<int>::max()) {
        cout << "There is no route from " << start << " to " << end << "." << endl;
    } else {
        cout << "The shortest distance from " << start << " to " << end << " is " << distances[end] << "." << endl;

        // Reconstruct the path
        vector<char> path;
        for (char at = end; at != start; at = previous[at]) {
            path.push_back(at);
        }
        path.push_back(start);
        reverse(path.begin(), path.end());

        cout << "The path followed: ";
        for (char node : path) {
            cout << node;
            if (node != end) cout << " -> ";
        }
        cout << endl;
    }
}

int main() {
    // Step 1: Hardcode the graph
    unordered_map<char, vector<pair<char, int>>> graph;
    graph['A'] = {{'B', 10}, {'E', 3}};
    graph['B'] = {{'C', 2}, {'E', 4}};
    graph['C'] = {{'D', 9}};
    graph['D'] = {{'C', 7}};
    graph['E'] = {{'B', 1}, {'C', 8}};

    // Available nodes
    vector<char> nodes = {'A', 'B', 'C', 'D', 'E'};

    // Step 2: Input starting and ending nodes
    char start, end;

    // Display available nodes
    cout << "Available nodes: ";
    for (char node : nodes) {
        cout << node << " ";
    }
    cout << endl;

    cout << "Enter the starting node : ";
    cin >> start;
    cout << "Enter the ending node : ";
    cin >> end;

    // Convert input to uppercase to match graph keys
    start = toUpperCase(start);
    end = toUpperCase(end);

    // Check if the nodes exist in the graph
    if (graph.find(start) == graph.end() || graph.find(end) == graph.end()) {
        cout << "Invalid node(s) entered. Please ensure the nodes exist in the graph." << endl;
        return 1;
    }

    // Step 3: Apply Dijkstra's algorithm
    dijkstra(graph, start, end);

    return 0;
}
