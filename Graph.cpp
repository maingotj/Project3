
#include "Graph.h"
#include <set>
#include <queue>

//MODIFIERS
void Graph::insertEdge(string from, vector<string> to) //get vertex and all nearby counties
{

    for (int i = 0; i < to.size(); i++) {//iterate through to vector
        if (!isEdge(from, to[i])) { //if edge doesn't exist make one
            graph[from].push_back(to[i]);   //make and edge to and from the vertices
            graph[to[i]].push_back(from);
        }
    }
}

//CHECKERS
bool Graph::isEdge(string from, string to)//checks if edge exists
{
    if (graph[from].empty()) {
        return false;
    }
    for (int i = 0; i < graph[from].size(); i++) {
        if (graph[from][i] == to) //checks if any members of from are the to string
            return true;
    }
    return false;
}
bool Graph::has(string s)
{
    if (graph.count(s)) //if vertex exists return true
        return true;
    return false;
}

//STATISTICS
vector<string> Graph::connectingPath(string firstCounty, string secondCounty) //makes a path between two counties
{
    vector<string> path;
    map<string, string> pred;
    queue<string> q;
    set<string> visited;
    pred[firstCounty] = "end";
    visited.insert(firstCounty);
    q.push(firstCounty);

    //shortest path function
    while (!q.empty())
    {
        string county = q.front(); //retrieves first county then takes it of queue
        q.pop();
        for (string adjCounty : graph[county]) //iterate through the edges
        {
            if (visited.count(adjCounty) == 0)//checks if county has been visited
            {
                visited.insert(adjCounty); //marks as visited
                pred[adjCounty] = county;  //marks the parent vertex
                q.push(adjCounty);         //adds it to the queue

                if (adjCounty == secondCounty) //checks if the county is the target county
                {
                    while (pred[secondCounty] != "end") //iterates as long as the end isn't reaches
                    {
                        path.push_back(secondCounty); //constructs the path
                        secondCounty = pred[secondCounty]; //makes the second county = the parent county
                    }
                    path.push_back(firstCounty); //pushes back the starting county
                }
            }
        }
    }
    return path;
}


void Graph::printGraph() //print graph function in case we need to check if the inputs and graph are correct
{
    map<string, vector<string>>::iterator it;
    for (it = graph.begin(); it != graph.end(); it++)
    {
        cout << it->first;
        for (int j = 0; j < it->second.size(); j++)
            cout << " " << it->second[j];
        cout << "\n";
    }
}


