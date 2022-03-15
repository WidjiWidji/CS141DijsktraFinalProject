/*
CS141 Final Project, Spring 2022
Topic : Dijkstra's Algorithm
Karsten Widjanarko

Given a weighted graph: 

G=(V,E), a weighting function W, and a starting vertex s, 

find the single-source all-destinations shortest path. 

You can assume that all weights are non-negative. 
The function should have the following signature.

DijkstraShortestPath(Map<Int, Int[]> E, Map<(Int, Int), Float> W, int[] p, float[] d);

E: Is the list of edges in adjacency list representation.

map <int, vector<int> > edges :
    < edge, adjacent edges >
    [0], [1]
    [1], [0,2]
    [2], [1]

W: Is the weighting function as a map from an edge to its weight value.

map<pair<int,int>, float> weights :
    pair < < edge, predecessor >, weight >

p: Is the output array that will contain the shortest path tree topography (predecessor).
    push weights->first.second whenever we are done with an edge

d: Is the output array that will contain the shortest path distance to each vertex.
    push weights->second whenever we are done with an edge


Lesson Learned:
How to implement adjacency list representation for graph algorithms and in this case using priority queues to iterate
*/

#include<iostream>
#include<map>
#include<vector>
#include<queue>

using namespace std;

//main implementation
void DijkstraShortestPath(map<int, vector<int> > edges, map<pair<int,int>, float> weights, vector<int>& p, vector<float>& d, int s){
      priority_queue<pair<int,int> > q; // <dist, src>
      
      //initialize p and d:
      //fill up d with INT_MAX (represent infinity)
      //fill up p with NULL 
      map <int, vector<int> >::iterator it;
      for(it = edges.begin(); it != edges.end(); it++){
          d[it->first] = INT_MAX;
          p[it->first] = -1;
          if(it->first != s){
              q.push(make_pair(d[it->first], it->first));
          }
      }
      //our starting distance d[s] will be 0 and p[s] = NULL (start has no predecessor)
      q.push(make_pair(0, s));
      d[s] = 0; 

      //go through adjacency list and find shortest path
      while(!q.empty()){
          //priority queue will hold the minimum distance at top
          int u = q.top().second; //u will hold the next vertex to visit
          q.pop();

          //iterate through adjacent elements and relax 
          vector<int>::iterator i;
          for(i = edges[u].begin(); i != edges[u].end(); i++){
              int v = *i;
              pair<int, int> edge_pair = make_pair(v, u); //make pair to look up from weights (edge, predecessor)
              
              //if our distance exists within the weights list then calculate min path
              if(weights.find(edge_pair) != weights.end()){
                  float edge_weight = weights[edge_pair];
                  
                  //if we have found a shorter distance than current vertex distance
                  if(d[v] > d[u] + edge_weight){
                      d[v] = d[u] + edge_weight;
                      p[v] = u;
                      q.push(make_pair(d[v], v));
                      }
              }
              
          }
      }

}

int main(){
    //test variables
    map<int, vector<int> > edges; 
    map<pair<int, int>, float> weights;
    vector<int> predecessors(6,0);
    vector<float> distances(6,0);
    int start;

    cout << "Choose a start (from 0 - 5): " << endl;
    cin >> start;

    //add edges and weights of graph (edge,predecessor) = float wweight (in adjacency list representation)
    weights[make_pair(0,1)] = 4;
    weights[make_pair(1,0)] = 4;
    weights[make_pair(0,2)] = 4;
    weights[make_pair(2,0)] = 4;
    weights[make_pair(1,2)] = 2;
    weights[make_pair(2,1)] = 2;
    weights[make_pair(2,3)] = 3;
    weights[make_pair(3,2)] = 3;
    weights[make_pair(2,4)] = 1;
    weights[make_pair(4,2)] = 1;
    weights[make_pair(2,5)] = 6;
    weights[make_pair(5,2)] = 6;
    weights[make_pair(3,5)] = 2;
    weights[make_pair(5,3)] = 2;
    weights[make_pair(4,5)] = 3;
    weights[make_pair(5,4)] = 3;

    //add edges and adjacency to edges (edge, adjacent_edges)
    vector<int> adj_list;
    
    //add adjacency list for 0 to edges
    adj_list.push_back(1);
    adj_list.push_back(2);
    edges.insert(make_pair(0, adj_list));

    adj_list.clear();

    //add adj_list for 1 to edges
    adj_list.push_back(0);
    adj_list.push_back(2);
    edges.insert(make_pair(1, adj_list));

    adj_list.clear();

    //add adj_list for 2 to edges
    adj_list.push_back(0);
    adj_list.push_back(1);
    adj_list.push_back(3);
    adj_list.push_back(4);
    adj_list.push_back(5);
    edges.insert(make_pair(2, adj_list));

    adj_list.clear();

    //add adj_list for 3 to edges
    adj_list.push_back(2);
    adj_list.push_back(5);
    edges.insert(make_pair(3, adj_list));
    
    adj_list.clear();

    //add adj_list for 4 to edges
    adj_list.push_back(2);
    adj_list.push_back(5);
    edges.insert(make_pair(4, adj_list));

    adj_list.clear();

    //add adj_list for 5 to edges
    adj_list.push_back(2);
    adj_list.push_back(3);
    adj_list.push_back(4);
    edges.insert(make_pair(5, adj_list));

    adj_list.clear();

    cout << "Printing Adjacency List: \n" << endl;
    //print adjacency list
    for(int i = 0; i < edges.size(); i++){
        cout << "adjacency list for edge( " << i << " ) : ";
        for(int j = 0; j < edges[i].size(); j++){
            cout << edges[i][j] << " , ";
        }
        cout << endl;
    }

    cout << "\nRunning Dijkstra's algorithm on graph from starting vertex: " << start << "\n" << endl;
    //run dijkstra's algorithm on graph
    DijkstraShortestPath(edges, weights, predecessors, distances, start);

    
    cout << "\nPrinting predecessors with distances: \n" << endl;
    for(int i = 0; i < predecessors.size(); i++){
        cout << "predecessor of vertex " << i << " = " << predecessors[i];
        cout << " , distance = " << distances[i] << endl;
    }
    

    return 0;
}