#pragma once
#include <map>
#include <vector>
#include <string>
#include <iterator>
#include <iomanip> // for set precision (rounding)

using namespace std;

class AdjacencyList {
private:
    map<string,map<string,double>> graph; // Adj list implementation (M)
    map<string, double> ranking;          // List to multiply ranking (r(t))
    map<string, double> outCount;         // Helper to initialize M

public:
    void insertVertex(string from, string to);
    void PageRank(int p);
    void initializeRank();
    void initializeList();
    void printRank();
    void printList();
};

void AdjacencyList::insertVertex(string from, string to) {
    if (graph.find(from) == graph.end()) {
        graph[from] = {}; // Takes care of edge case, where the 'from' node isn't declared
    }
    if (graph.find(to) == graph.end()) {
        graph[to] = {}; // Adds the 'to' node if it doesn't exist
        outCount[to] = 0;
    }

    graph[to][from] = 0;  // Initialize to 0 (ONLY for existing edges, so still a list not a Matrix)
    // Note that it's to -> from, as this makes the calculations easier

    outCount[from]++;
}

void AdjacencyList::initializeRank() {
    // Distribute the weights based on the correct outdegree of the source vertex
    for (auto& website : graph) {
        ranking[website.first] = 1.0 / graph.size();
    }
}

void AdjacencyList::initializeList() {
    // Initialize list based on the out-degree of a given node
    for(auto& row:graph){
        for(auto& cell:row.second){
            cell.second += 1 / outCount[cell.first];
        }
    }
}

void AdjacencyList::PageRank(int p){
    initializeRank();
    initializeList();

    if (p > 1) { // since power 1 is just the initialized ranks
        for (int i = 1; i < p; i++) {
            map<string, double> tempR;  // use a temp map for the ranks, so you can change them after full iteration of the list
            for(auto& website : ranking){
                for(auto& row : graph){
                    if (row.second.empty()) {
                        tempR[row.first] = 0.0; // Set ranking to 0 for nodes with no outgoing edges
                    }
                    else {
                        for (auto &cell: row.second) {
                            if (website.first == cell.first) {
                                tempR[row.first] += cell.second * ranking[website.first]; // Matrix multiplication
                            }
                        }
                    }
                }
            }
            ranking = tempR;
        }
    }

    printRank();
}

void AdjacencyList::printRank() {
    // Prints the ranks with 2 decimal spots
    for (const auto& website : ranking) {
        cout << website.first << " " << fixed << setprecision(2) << website.second << endl;
    }
}

void AdjacencyList::printList() {
    cout << "Adjacency List:" << endl;
    for (const auto& row : graph) {
        cout << row.first << " -> ";
        for (const auto& cell : row.second) {
            cout << "(" << cell.first << ", " << cell.second << ") ";
        }
        cout << endl;
    }
    cout << endl;
}
