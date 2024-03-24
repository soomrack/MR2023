#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

int Correction(int n, int start, int end, vector<vector<int>>& graph)
{
    bool state_start = 0, state_end = 0;
    for (int idx = 0; idx < n; idx++)
    {
        if (graph[start][idx] < INT_MAX)
            state_start = 1;
        if (graph[idx][end] < INT_MAX)
            state_end = 1;
    }
    return state_end & state_start;
}

void Dijkstra(int n, int start, int end, vector<vector<int>>& graph) {
    vector<bool> visited(n, false);
    vector<int> dist_from_start_vert(n, INT_MAX);
    vector<int> path(n, -1); 
    dist_from_start_vert[start] = 0; 

    while (true) {
        int vertex = -1;
        for (int idx = 0; idx < n; ++idx)
            if (!visited[idx] && (vertex == -1 || dist_from_start_vert[idx] < dist_from_start_vert[vertex]))
                vertex = idx;           
       
        if (vertex == -1 || vertex == end) break;

        visited[vertex] = true;

        for (int vert_idx = 0; vert_idx < n; ++vert_idx)
            if (!visited[vert_idx] && graph[vertex][vert_idx] != INT_MAX && dist_from_start_vert[vertex] != INT_MAX && (dist_from_start_vert[vertex] + graph[vertex][vert_idx] < dist_from_start_vert[vert_idx])) {
                dist_from_start_vert[vert_idx] = dist_from_start_vert[vertex] + graph[vertex][vert_idx];
                path[vert_idx] = vertex;
            }       
    }

    vector<int> shortestPath;
    for (int vert_idx = end; vert_idx != -1; vert_idx = path[vert_idx]) 
        shortestPath.push_back(vert_idx);
 
    reverse(shortestPath.begin(), shortestPath.end());

    cout << "The shortest path from the top " << start << " To the top " << end << ":\n";
    cout << "Path length: " << dist_from_start_vert[end] << endl;
    cout << "A sequence of vertices: ";
    for (int idx = 0; idx < shortestPath.size(); ++idx) {
        cout << shortestPath[idx];
        if (idx != shortestPath.size() - 1)
            cout << " -> ";       
    }
    cout << endl;
}


void filling_graph(vector<vector<int>>& graph)
{
    ifstream datafile;
    datafile.open("data_after_parse.txt");

    if (not datafile.is_open()) {
        cout << "Couldn't open datafile\n";
        return;
    }

    std::string txtline;
    while (not datafile.eof()) {
        std::getline(datafile, txtline);
        stringstream inputString(txtline);

        int str, col, time;
        string tempString;

        getline(inputString, tempString, '\t');
        str = atoi(tempString.c_str());
        
        getline(inputString, tempString, '\t');
        col = atoi(tempString.c_str());

        getline(inputString, tempString, '\t');
        time = atoi(tempString.c_str());

        //cout << str << "\t" << col << "\t" << time << endl;

        if (graph[str][col] > time)
            graph[str][col] = time;
    }
}


int main() {
    int n = 40 * 1000;
    int start = 34570; 
    int end = 30561;


    vector<vector<int>> graph(n, vector<int>(n, INT_MAX));

    filling_graph(graph);
    if (Correction(n, start, end, graph))
        Dijkstra(n, start, end, graph);
    else
        cout << "wrong choise of start or end\n";

    return 0;
}
