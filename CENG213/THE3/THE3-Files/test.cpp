#include <bits/stdc++.h>
#include "GraphExceptions.h"
#include "Graph.h"
#include "HashTable.h"

using namespace std;

template<class T>
void print_vector(vector<T> &vec) {
    for (auto x : vec)
        cout << x << " ";
    cout << endl;
}

int main(){
    vector<int> vec1 = {0, 1, 2, 3};
    vector<int> vec2;

    //vec2.assign(&vec1[1], &vec1[3]);
    vec2.assign(vec1.begin()+1, vec1.end());

    for (int i = 0; i < vec2.size(); i++)
        cout << vec2[i] << " ";
    cout << endl;

    cout << vec2.size() << endl;



    return 0;
}


void graph_test() {
    // Graph graph;

    // graph.InsertVertex("A");
    // graph.InsertVertex("B");
    // graph.InsertVertex("C");
    // graph.InsertVertex("D");
    // graph.InsertVertex("E");
    // graph.InsertVertex("F");

    // graph.ConnectVertices("A", "B", 14);
    // graph.ConnectVertices("A", "E", 7);
    // graph.ConnectVertices("A", "F", 9);
    // graph.ConnectVertices("B", "C", 9);
    // graph.ConnectVertices("B", "F", 2);
    // graph.ConnectVertices("C", "D", 6);
    // graph.ConnectVertices("D", "F", 11);
    // graph.ConnectVertices("D", "E", 15);
    // graph.ConnectVertices("E", "F", 10);

    // StringPair pair0("A", "B");
    // StringPair pair1("A", "B");

    // vector<StringPair> vertexNames = {
    //     StringPair("A", "B"),
    //     StringPair("A", "F"),
    //     StringPair("C", "D")
    // };

    // graph.InsertVertex("Test0");
    // graph.InsertVertex("Test1");
    // graph.InsertVertex("Test2");
    // graph.InsertVertex("Test3");
    // graph.InsertVertex("Test4");
    // graph.InsertVertex("Test5");
    // graph.InsertVertex("Test6");
    // graph.InsertVertex("Test7");
    // graph.InsertVertex("Test8");
    // graph.InsertVertex("Test9");
    // graph.InsertVertex("Test10");
    // graph.InsertVertex("Test11");
    // graph.InsertVertex("Test12");
    // graph.InsertVertex("Test13");
    // graph.InsertVertex("Test14");

    // graph.ConnectVertices("Test0", "Test1", 3);
    // graph.ConnectVertices("Test0", "Test2", 6);
    // graph.ConnectVertices("Test0", "Test3", 9);
    // graph.ConnectVertices("Test0", "Test4", 12);
    // graph.ConnectVertices("Test0", "Test5", 15);
    // graph.ConnectVertices("Test0", "Test6", 18);
    // graph.ConnectVertices("Test0", "Test7", 21);
    // graph.ConnectVertices("Test0", "Test8", 24);
    // graph.ConnectVertices("Test0", "Test9", 27);
    // graph.ConnectVertices("Test0", "Test10", 30);
    // graph.ConnectVertices("Test0", "Test11", 33);

    // graph.print_vertexList();
    // graph.print_edgeList();

    // cout << "*********************" << endl;
    // graph.MaskEdges(vertexNames);
    // graph.print_edgeList();

    // cout << "*********************" << endl;
    // graph.UnMaskEdges(vertexNames);
    // graph.print_edgeList();

    // cout << "*********************" << endl;
    // vertexNames.push_back(StringPair("A", "C"));
    // vertexNames.push_back(StringPair("C", "F"));
    // graph.MaskEdges(vertexNames);
    // graph.print_edgeList();

    // cout << "*********************" << endl;
    // vertexNames.push_back(StringPair("A", "G"));
    // graph.MaskEdges(vertexNames);
    // graph.print_edgeList();

    // graph.MaskEdges(vertexNames);
    // graph.print_edgeList();

    // cout << "*********************" << endl;
    // graph.UnMaskAllEdges();
    // graph.print_edgeList();


    // graph.print_edgeList();

    // cout << "*********************" << endl;
    // graph.MaskVertexEdges("A");
    // graph.print_edgeList();

    // cout << "*********************" << endl;
    // graph.UnMaskVertexEdges("A");
    // graph.print_edgeList();

    // cout << "*********************" << endl;
    // graph.MaskVertexEdges("G");
    // graph.print_edgeList();

    // cout << "*********************" << endl;
    // graph.UnMaskVertexEdges("G");
    // graph.print_edgeList();

    // graph.InsertVertex("G");
    // vector<int> orderedVertexIdList;
    // cout << (graph.ShortestPath(orderedVertexIdList, "A", "G") ? "There is a shortest path":"There is not path") << endl;
    // print_vector(orderedVertexIdList);

    // vector<StringPair> strpair;
    // strpair.push_back(StringPair("F", "B"));
    // graph.MaskEdges(strpair);
    
    // graph.print_edgeList();
    // cout << (graph.ShortestPath(orderedVertexIdList, "A", "B") ? "There is a shortest path":"There is not path") << endl;
    // print_vector(orderedVertexIdList);

    // graph.ShortestPath(orderedVertexIdList, "H", "F");

    // graph.InsertVertex("G");
    // vector<int> orderedVertexIdList;
    // cout << (graph.ShortestPath(orderedVertexIdList, "A", "G") ? "There is a shortest path":"There is not path") << endl;
    // cout << "Total Weight: " << graph.TotalWeightInBetween(orderedVertexIdList) << endl;

    // cout << (graph.ShortestPath(orderedVertexIdList, "B", "A") ? "There is a shortest path":"There is not path") << endl;
    // cout << "Total Weight: " << graph.TotalWeightInBetween(orderedVertexIdList) << endl;
}