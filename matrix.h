// Header file for creation of minimum spanning tree from graph for Coursera C++

#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Matrix
{
    private:
        // Edges are a triple listing the source node number,
        // the target, and the length of the path
        class Edge 
        {
            public:
                int source;
                int target;
                int length;
            
            Edge(int source, int target, int length)
                : source(source), target(target), length(length)
            {}

            ~Edge()
            {}
        };
        vector<vector<Edge>> graph;          // holds edge matrix
        const int INFINITE = 0x3F3F3F3F;
        int getlength(int x, int y);          // returns length if there's an edge x-y
        vector<Edge> neighbors(int x);       // returns vector of all edges (x, __)
        void deleteTargetEdges(int target);   // delete target edges from graph
        
    public:
        Matrix();
        ~Matrix();
        void resize(int size);
        void addEdge(int x, int y, int len);    // create edge
        void deleteEdge(int x, int y);          // delete edge
        void displayMatrix();                    // display created graph
        void rPopulate(double density, int low_range, int hi_range);
                                                // populate graph with random density, 
                                                // random costs in range
        void fPopulate(string filename);        // read in file to populate graph
        Matrix doPrim(int source);                // do prim algorithm from source
};