#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <iterator>

using namespace std;

#include "matrix.h"

// Default constructor 
Matrix::Matrix()
{
}

Matrix::~Matrix()
{
}

void Matrix::resize(int size)
{
    graph.resize(size);
}


// add an edge with len (cost) len
// for nondirected graphs, automatically
// adds the symmetric edge
// with y, x swapped.
void Matrix::addEdge(int x, int y, int len)
{
    // set edge if not already existing
    if (Matrix::getlength(x, y) == INFINITE)
    {
        graph[x].push_back(Edge(x, y, len));
        graph[y].push_back(Edge(y, x, len));
    }
}    

// find and delete edge with target == y
// NB: the symmetric delete is not performed here and 
// if desired this function must be called with x y swapped
void Matrix::deleteEdge(int x, int y)
{
    
    for (auto it = graph[x].begin(); it != graph[x].end(); ++it)
    {
        if (it->target == y)
        {
            graph[x].erase(it);
        }
    }
}

// populate a matrix with edges/weights 
// from class file
void Matrix::fPopulate(string filename)
{
    ifstream filedata(filename);
    cout << "opening file:" << filename << endl;
    istream_iterator<int> pfin(filedata);
    istream_iterator<int> eos;
    int size = *pfin++;
    while (pfin != eos)
    {
        int x = *pfin++;
        int y = *pfin++;
        int len = *pfin++;
        addEdge(x, y, len);
    }
}

// following code populates a matrix with
// edges of probability based on density and lengths between 
// low_range and hi_range (inclusive)
void Matrix::rPopulate(double density, int low_range, int hi_range)
{
    random_device rd;       // get seed from slower funciton
    mt19937 mt(rd());       // seed faster random function
    // random(mt) generates doubles [0.0, 1)
    uniform_real_distribution<double> random(0.0, 1.0);
    
    // assign an edge based on probability density
    for (int i = 0; i < graph.size(); i++)
    {
        // put random edges in first half of matrix (all we need
        // to do for nondirected)
        for (int j = 0; j < i; j++)
        {
            if (random(mt) < density)
            {
                // length is a random int between low_range and hi_range
                int length = random(mt) * (double(hi_range) - double(low_range)) + low_range;
                addEdge(i, j, length);
            }
        }
    }
    cout << "Random graph created size:" << graph.size() << " density:" << density 
            << " range:" << low_range << "-" << hi_range << endl;
}

// looks for an existing edge and returns length
// else returns INFINITE
int Matrix::getlength(int x, int y)
{
    for (auto n : graph[x])
    {
        if (n.target == y)
        {
            return n.length;
        }
    }
    return INFINITE;
}

vector<Matrix::Edge> Matrix::neighbors(int x)
{
    return graph[x];
}

void Matrix::displayMatrix()
{
    int cost = 0;
    for (auto pvec = graph.begin(); pvec != graph.end(); ++pvec)
    {
        cout << "node " << distance(graph.begin(), pvec) << ", out-connections ";
        if (pvec->empty())
        {
            cout << "none";
        }
        else
        {
            for (auto n : *pvec)
            {
                cout << "(" << n.source << ", " << n.target << ", " << n.length << ") ";
                cost += n.length;
            }     
        }
        cout << endl;
    }
    cout << "total length of all paths: " << cost << endl;
}

bool andAll(const vector<bool> &n)
{
    bool returnval = true;
    for(bool b : n)
    {
        returnval = returnval && b;
    }
    return returnval;
}

void Matrix::deleteTargetEdges(int target)
{
    for (int i = 0; i < graph.size(); i++)
    {
        if (i != target)
        {
            for (auto it = graph[i].begin(); it != graph[i].end(); ++it)
            {
                if (it->target == target)
                {
                    graph[i].erase(it--);
                }
            }
        }
    }
}

Matrix Matrix::doPrim(int source)
{
    int size = this->graph.size();
    Matrix s;
    s.resize(size);
    vector<bool> n(size, false);

    n[source] = true;
    deleteTargetEdges(source);
    while (!andAll(n))
    {
        Edge smallest(INFINITE, INFINITE, INFINITE);
        for (int i = 0; i < size; i++)
        {
            if (n[i])
            {
                for (int j = 0; j < graph[i].size(); j++)
                {
                    if (graph[i][j].length < smallest.length)
                    {
                        smallest.source = graph[i][j].source;
                        smallest.target = graph[i][j].target;
                        smallest.length = graph[i][j].length;
                    }
                }
            }
        }
        if (smallest.target == INFINITE)
        {
            cout << "Error - unconnected graph -- no further path found" << endl;
            return s;
        }
        n[smallest.target] = true;
        // note - for this purpose we don't need to create an undirected graph
        // since the solution graph need not be undirected
        // so there is no need for the symmetric addEdge call to y, x
        s.graph[smallest.source].push_back(smallest);
        deleteTargetEdges(smallest.target);
    }
    return s;
}

