#include <iostream>
#include <list>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

#include "matrix.h"

int msize = 20;
double density = 0.2;
int low_range = 1;
int hi_range = 10;
const int SOURCE = 0;
Matrix m, s;

int main()
{
    cout << "Welcome to Span" << endl;
    cout << "   (1) load from class file data.txt (size 20)" << endl;
    cout << "   (2) calculate random graph" << endl;
    cout << "   (3) use geeks testing graph (size 9)" << endl;
    int response;
    cin >> response;
    if (response == 1)
    {
        msize = 20;
        m.resize(msize);
        m.fPopulate("data.txt");
    }
    if (response == 2)
    {
        cout << "Size:";
        cin >> msize;
        cout << "Density:";
        cin >> density;
        cout << "Range (low):";
        cin >> low_range;
        cout << "Range (high):";
        cin >> hi_range;
        m.resize(msize);
        m.rPopulate(density, low_range, hi_range);
    }
    if (response == 3)
    {
        // for testing create static graph from    
        // https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/ 

        msize = 9;
        m.resize(msize);
        m.addEdge(0, 1, 4); 
        m.addEdge(0, 7, 8); 
        m.addEdge(1, 2, 8); 
        m.addEdge(1, 7, 11); 
        m.addEdge(2, 3, 7); 
        m.addEdge(2, 8, 2); 
        m.addEdge(2, 5, 4); 
        m.addEdge(3, 4, 9); 
        m.addEdge(3, 5, 14); 
        m.addEdge(4, 5, 10); 
        m.addEdge(5, 6, 2); 
        m.addEdge(6, 7, 1); 
        m.addEdge(6, 8, 6); 
        m.addEdge(7, 8, 7); 
    }

    cout << "original matrix:" << endl;
    m.displayMatrix();
    cout << "MST (directed graph):" << endl;
    m.doPrim(SOURCE).displayMatrix();

    return 0;
}
