
#include <iostream>
#include "AdjacencyList.h"

using namespace std;

int main()
{
    AdjacencyList Graph;

    int n, p;
    string from, to;

    cin >> n;
    cin >> p;

    for(int i = 0; i < n; i++) // repeat based on the first line
    {
        cin >> from;
        cin >> to;

        Graph.insertVertex(from, to);
    }

    Graph.PageRank(p);

    return 0;
}