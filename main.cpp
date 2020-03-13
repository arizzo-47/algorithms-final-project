//Anthony Rizzo
//April 9, 2019

#include <iostream>
#include <fstream>  
#include <stdexcept>
#include <string>
#include <stdio.h>
#include <limits.h>
#define V 10
#define numPoints 10

using namespace std;

//list of node names
string locationArray[10] = {"Snell", "Curry", "Forsyth", "Rebecca", "BofA", "HaydenDunkin", "Lou", "Subway", "ShillmanDunkin", "Marino"};

string IndexToString(int index){
    return locationArray[index];
}

int LocationIndex(string vertex){

    //search for equality
    for(int i = 0; i < 10; i++){
        if(vertex == locationArray[i]){
            return i;
        }
    }   
}

void InitializeAdjMatrix(int graph[numPoints][numPoints]){
    ifstream inf;
    int colSize = 3;                //number of text file data columns
    int vertex1, vertex2, distance; //text file parameters
    string x;                       //text file read variable

    int count = 0;      //data counter

    //Initialize array contents
    for(int i = 0; i < numPoints; i++){
        for(int j = 0; j < numPoints; j++){
            graph[i][j] = 0;
        }
    }

    inf.open("graph.txt");
    
    if (inf.fail()){
        cerr << "Error: Could not open input file\n";
        exit(1);
    }

    //activate the exception handling of inf stream
    inf.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    //until end of file
    while (!inf.eof()){  

        //pull data from text file delimited by spaces
        try{
            inf >> x;
        }
    
        //Check for reading failure due to end of file or
        // due to reading a non‐integer value from the file.
        catch (std::ifstream::failure e){
            break;
        }

        //Three fields to handle
        switch(count%colSize){
            case 0:
                //convert location name to vertex index
                vertex1 = LocationIndex(x); 
                break;
            case 1:
                //convert location name to vertex index
                vertex2 = LocationIndex(x);
                break;
            case 2:
                //convert distance string to integer
                distance = stoi(x);  
                graph[vertex1][vertex2] = distance;
                break;
            default:
                cout << "DEFAULT" << endl;
        }

        count++;    //increment counter
    }

    inf.close(); //Close the file at the end of your program.

}

void printAdjMatrix(int matrix[numPoints][numPoints]){
    //Output adjacency matrix for debugging
    for(int i = 0; i < numPoints; i++){
        for(int j = 0; j < numPoints; j++){
            cout << matrix[i][j] << '\t';
        }

        cout << endl;
    }
}

int minDistance(int dist[], bool sptSet[]){ 
	
	// Initialize min value 
	int min = INT_MAX, min_index; 

	for (int v = 0; v < V; v++) 
		if (sptSet[v] == false && 
				dist[v] <= min) 
			min = dist[v], min_index = v; 

	return min_index; 
} 

void printPath(int parent[], int j){ 
	
	// Base Case : If j is source 
	if (parent[j] == - 1) 
		return; 

	printPath(parent, parent[j]); 

    string strPoint = IndexToString(j);
	cout << strPoint << endl;
} 

int printSolution(int dist[], int n, int parent[], int destination){ 
	int src = 0; 
    string stringBegin = IndexToString(src);
    string stringDest = IndexToString(destination);

    cout << endl << "The optimal path from " << stringBegin << " to " << stringDest << endl;
    cout << "Total Distance: " << dist[destination] << endl << endl;
    cout << "Node traversal sequence: " << endl;
    cout << stringBegin << endl;  

	printPath(parent, destination); 
	
} 

void dijkstra(int graph[V][V], int src, int destination){
	//Used GeeksForGeeks.org as reference for algorithm


	// The output array. dist[i] 
	// will hold the shortest 
	// distance from src to i 
	int dist[V]; 

	// sptSet[i] will true if vertex 
	// i is included / in shortest 
	// path tree or shortest distance 
	// from src to i is finalized 
	bool sptSet[V]; 

	// Parent array to store 
	// shortest path tree 
	int parent[V]; 

	// Initialize all distances as 
	// INFINITE and stpSet[] as false 
	for (int i = 0; i < V; i++) 
	{ 
		parent[i] = -1; 
		dist[i] = INT_MAX; 
		sptSet[i] = false; 
	} 

	// Distance of source vertex 
	// from itself is always 0 
	dist[src] = 0; 

	// Find shortest path 
	// for all vertices 
	for (int count = 0; count < V - 1; count++) 
	{ 
		// Pick the minimum distance 
		// vertex from the set of 
		// vertices not yet processed. 
		// u is always equal to src 
		// in first iteration. 
		int u = minDistance(dist, sptSet); 

		// Mark the picked vertex 
		// as processed 
		sptSet[u] = true; 

		// Update dist value of the 
		// adjacent vertices of the 
		// picked vertex. 
		for (int v = 0; v < V; v++) 

			// Update dist[v] only if is 
			// not in sptSet, there is 
			// an edge from u to v, and 
			// total weight of path from 
			// src to v through u is smaller 
			// than current value of 
			// dist[v] 
			if (!sptSet[v] && graph[u][v] && 
				dist[u] + graph[u][v] < dist[v]) 
			{ 
				parent[v] = u; 
				dist[v] = dist[u] + graph[u][v]; 
			} 
	} 

	// print the constructed 
	// distance array 
	printSolution(dist, V, parent, destination); 
} 

string askDestination(){
    string destination;

    cout << "What dining location would you like to visit?" << endl <<
        "The option are listed here:" << endl;
    
    for(int i = 0; i < V; i++){
        cout << "(" << i << "). " << locationArray[i] << endl;
    }

    while(true){
        cin >> destination;

        for(int i = 0; i < V; i++){
            if(destination == locationArray[i]){
                return destination;
            }
        }

        cout << "We cannot find the requested destination, try again." << endl;
    }
    

    return destination;
}

int main(){
    int destIndex;
    int matrix[numPoints][numPoints];
    string destination = askDestination();
    destIndex = LocationIndex(destination);
    InitializeAdjMatrix(matrix);
    //printAdjMatrix(matrix);
    dijkstra(matrix, 0, destIndex);



    return 0;
}