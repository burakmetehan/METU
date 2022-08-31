#include "Graph.h"
#include "GraphExceptions.h"

#include <iostream>
#include <iomanip>
#include <queue>
#include <fstream>
#include <sstream>
#include <cstdlib>

// Literally do nothing here
// default constructors of the std::vector is enough
Graph::Graph()
{}

Graph::Graph(const std::string& filePath)
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    // Tokens
    std::string tokens[3];

    std::ifstream mapFile(filePath.c_str());
    // Read line by line
    std::string line;
    while (std::getline(mapFile, line))
    {
        // Empty Line Skip
        if(line.empty()) continue;
        // Comment Skip
        if(line[0] == '#') continue;

        // Tokenize the line
        int i = 0;
        std::istringstream stream(line);
        while(stream >> tokens[i]) i++;

        // Single token (Meaning it is a vertex)
        if(i == 1)
        {
            InsertVertex(tokens[0]);
        }
        // Exactly three tokens (Meaning it is an edge)
        else if(i == 3)
        {
            int weight = std::atoi(tokens[0].c_str());
            if(!ConnectVertices(tokens[1], tokens[2], weight))
            {
                std::cerr << "Duplicate edge on "
                          << tokens[0] << "-"
                          << tokens[1] << std::endl;
            }
        }
        else std::cerr << "Token Size Mismatch" << std::endl;
    }
}

void Graph::InsertVertex(const std::string& vertexName)
{
    // Checking the duplication of vertex
    if (duplicate_vertex_check(vertexName))
        throw DuplicateVertexNameException();
    else {
        // Inserting the vertex
        vertexList.push_back(GraphVertex(vertexName)); // Using added default struct constructor
    }
}

bool Graph::ConnectVertices(const std::string& fromVertexName, const std::string& toVertexName, int weight)
{
    // Finding the index of the vertex
    int vertex_id_0 = find_vertex(fromVertexName);
    int vertex_id_1 = find_vertex(toVertexName);

    if (vertex_id_0 == -1 || vertex_id_1 == -1) {
        throw VertexNotFoundException();
    }
    else if (vertexList[vertex_id_0].edgeCount >= MAX_EDGE_PER_VERTEX || vertexList[vertex_id_1].edgeCount >= MAX_EDGE_PER_VERTEX) {
        throw TooManyEdgeOnVertexExecption();
    }
    else if (vertex_id_0 == vertex_id_1) { // Same vertices
        return false;
    }
    else { // No problem. Needs to insert
        int i;
        // Checking the possible previous connection
        GraphVertex &vertex0 = vertexList[vertex_id_0];
        GraphVertex &vertex1 = vertexList[vertex_id_1];

        for (i = 0; i < vertex0.edgeCount; i++)
        {
            if (edgeList[vertex0.edgeIds[i]].vertexId0 == vertex_id_0 && edgeList[vertex0.edgeIds[i]].vertexId1 == vertex_id_1) { // there is previous connection
                return false;
            }else;
        }

        // Inserting connection
        edgeList.push_back(GraphEdge(vertex_id_0, vertex_id_1, weight)); // adding to edgeList
        vertex0.edgeIds[vertex0.edgeCount++] = edgeList.size() - 1;
        vertex1.edgeIds[vertex1.edgeCount++] = edgeList.size() - 1;

        return true;
    }
}

bool Graph::ShortestPath(std::vector<int>& orderedVertexIdList, const std::string& from, const std::string& to) const
{
    int vertex_id_from = find_vertex(from);
    int vertex_id_to = find_vertex(to);

    if (vertex_id_from == -1 || vertex_id_to == -1) {
        throw VertexNotFoundException();
    }
    else
    {
        // Initialization
        int size_of_vertexList = vertexList.size();
        int *dist = new int[size_of_vertexList]; // Track the distance
        int *prev = new int[size_of_vertexList]; // Track the previous

        std::priority_queue<DistanceVertexIdPair> pq;
        
        // Loop variables
        int i, vertex_id;
        GraphVertex vertex;

        for (i = 0; i < size_of_vertexList; i++)
        {
            vertex = vertexList[i];

            if (vertex.name != from) {
                dist[i] = LARGE_NUMBER;
                prev[i] = -1; // May be changed
            } else {
                dist[i] = 0;
                prev[i] = -1;
                pq.push(DistanceVertexIdPair(i, 0));
            }
        }

        while (!pq.empty())
        {
            // deque the top element
            vertex_id = pq.top().vId;
            vertex = vertexList[vertex_id];
            pq.pop();

            for (i = 0; i < vertex.edgeCount; i++)
            {
                int adjacent_id, alt;
                // Retrieving the connection information to determine adjacent vertices
                // edgeList[vertex.edgeIds[i]] gives the connection of the vertex has. One of the id between vertexId0 and vertexId1 is vertex_id and the other one is the id of the adjacent vertex.
                // If the connection is masked the loop will continue.
                // If it is not the case, it means ConnectVertices is not working properly.
                if (edgeList[vertex.edgeIds[i]].masked) { // masked connection
                    continue;
                }
                else if (edgeList[vertex.edgeIds[i]].vertexId0 == vertex_id) {
                    adjacent_id = edgeList[vertex.edgeIds[i]].vertexId1;
                }
                else {
                    adjacent_id = edgeList[vertex.edgeIds[i]].vertexId0;
                }

                alt = dist[vertex_id] + edgeList[vertex.edgeIds[i]].weight;

                if (alt < dist[adjacent_id]) {
                    dist[adjacent_id] = alt;
                    prev[adjacent_id] = vertex_id;
                    pq.push(DistanceVertexIdPair(adjacent_id, alt));
                }else;
            }
        }

        // Checking whether there is a path between "from" and "to". It will be done by checking the dist of "to" in dist array. If it is not LARGE_NUMBER it means, the vertex is accessed. Otherwise, vertex is not accessible by using "from" vertex.
        if (dist[vertex_id_to] == LARGE_NUMBER) { // No access
            delete[] dist;
            delete[] prev;
            return false;
        }
        else {
            int j, *temp_array = new int[size_of_vertexList];

            for (int i = 0; i < size_of_vertexList; i++)
                temp_array[i] = -1;

            i = 0;
            j = vertex_id_to;
            
            while (j != vertex_id_from && i < size_of_vertexList)
            {
                temp_array[i++] = j;
                j = prev[j];
            }
            temp_array[i] = j;

            for (; i >= 0; i--)
            {
                orderedVertexIdList.push_back(temp_array[i]);
            }

            delete[] dist;
            delete[] prev;
            delete[] temp_array;
            return true;
        }
    }
}

int Graph::MultipleShortPaths(std::vector<std::vector<int> >& orderedVertexIdList,
                              const std::string& from,
                              const std::string& to,
                              int numberOfShortestPaths)
{
    int i;

    UnMaskAllEdges();

    for (i = 0; i < numberOfShortestPaths; i++) {
        std::vector<int> shortest_path;
        
        if (ShortestPath(shortest_path, from, to)) {
            orderedVertexIdList.push_back(shortest_path);
            
            int max_weighted_index = find_max_weighted_edge(shortest_path);

            if (max_weighted_index == -1) { // Problem
                continue;
            } else {
                edgeList[max_weighted_index].masked = true;
            }

            shortest_path.clear();
        } else {
            break;
        }
    }

    UnMaskAllEdges();

    return i;
}

void Graph::MaskEdges(const std::vector<StringPair>& vertexNames)
{
    int i, size = vertexNames.size();

    for (i = 0; i < size; i++)
    {
        const StringPair &temp = vertexNames[i];

        int vertex_id_0 = find_vertex(temp.s0);
        int vertex_id_1 = find_vertex(temp.s1);

        if (vertex_id_0 == -1 || vertex_id_1 == -1) {
            throw VertexNotFoundException();
        }
        else
        {
            int connection_id = find_connection(vertex_id_0, vertex_id_1);
            if (connection_id != -1) {
                edgeList[connection_id].masked = true;
            }else;
        }
    }
}

void Graph::UnMaskEdges(const std::vector<StringPair>& vertexNames)
{
    int i, size = vertexNames.size();

    for (i = 0; i < size; i++)
    {
        const StringPair &temp = vertexNames[i];

        int vertex_id_0 = find_vertex(temp.s0);
        int vertex_id_1 = find_vertex(temp.s1);

        if (vertex_id_0 == -1 || vertex_id_1 == -1) {
            throw VertexNotFoundException();
        }
        else 
        {
            int connection_id = find_connection(vertex_id_0, vertex_id_1);
            if (connection_id != -1) {
                edgeList[connection_id].masked = false;
            }else;
        }
    }
}

void Graph::UnMaskAllEdges()
{
    int i, size = edgeList.size();

    for (i = 0; i < size; i++)
        edgeList[i].masked = false;
}

void Graph::MaskVertexEdges(const std::string& name)
{
    int vertex_id = find_vertex(name);
    if (vertex_id == -1) {
        throw VertexNotFoundException();
    }
    else
    {
        int i;
        for (i = 0; i < vertexList[vertex_id].edgeCount; i++)
        {
            edgeList[vertexList[vertex_id].edgeIds[i]].masked = true;
        }
    }
}

void Graph::UnMaskVertexEdges(const std::string& name)
{
    int vertex_id = find_vertex(name);
    if (vertex_id == -1) {
        throw VertexNotFoundException();
    }
    else
    {
        int i;
        for (i = 0; i < vertexList[vertex_id].edgeCount; i++)
        {
            edgeList[vertexList[vertex_id].edgeIds[i]].masked = false;
        }
    }
}

void Graph::ModifyEdge(const std::string& vName0, const std::string& vName1, float newWeight)
{
    int vertex_id_0 = find_vertex(vName0);
    int vertex_id_1 = find_vertex(vName1);

    if (vertex_id_0 == -1 || vertex_id_1 == -1) {
        throw VertexNotFoundException();
    }
    else
    {
        int edge_index = find_connection(vertex_id_0, vertex_id_1);
        
        if (edge_index != -1) {
            edgeList[edge_index].weight = newWeight;
        }else;
    }
}

void Graph::ModifyEdge(int vId0, int vId1, float newWeight)
{
    int edge_index = find_connection(vId0, vId1);
    
    if (edge_index != -1) {
        edgeList[edge_index].weight = newWeight;
    }else;
}

void Graph::PrintAll() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    for(size_t i = 0; i < vertexList.size(); i++)
    {
        const GraphVertex& v = vertexList[i];
        std::cout << v.name << "\n";
        for(int j = 0; j < v.edgeCount; j++)
        {
            int edgeId = v.edgeIds[j];
            const GraphEdge& edge = edgeList[edgeId];
            // Skip printing this edge if it is masked
            if(edge.masked)
                continue;

            // List the all vertex names and weight
            std::cout << "-" << std::setfill('-')
                             << std::setw(2) << edge.weight
                             << "-> ";
            int neigVertexId = (static_cast<int>(i) == edge.vertexId0)
                                 ? edge.vertexId1
                                 : edge.vertexId0;
            std::cout << vertexList[neigVertexId].name << "\n";
        }
    }
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

void Graph::PrintPath(const std::vector<int>& orderedVertexIdList, bool sameLine) const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this file !       //
    // ============================= //
    for(size_t i = 0; i < orderedVertexIdList.size(); i++)
    {
        int vertexId = orderedVertexIdList[i];
        if(vertexId >= static_cast<int>(vertexList.size()))
            throw VertexNotFoundException();

        const GraphVertex& vertex = vertexList[vertexId];
        std::cout << vertex.name;
        if(!sameLine) std::cout << "\n";
        // Only find and print the weight if next is available
        if(i == orderedVertexIdList.size() - 1) break;
        int nextVertexId = orderedVertexIdList[i + 1];
        if(nextVertexId >= static_cast<int>(vertexList.size()))
            throw VertexNotFoundException();

        // Find the edge between these two vertices
        int edgeId = INVALID_INDEX;
        if(vertexId     < static_cast<int>(vertexList.size()) &&
           nextVertexId < static_cast<int>(vertexList.size()))
        {
            // Check all of the edges of vertex
            // and try to find
            const GraphVertex& fromVert = vertexList[vertexId];
            for(int i = 0; i < fromVert.edgeCount; i++)
            {
                int eId = fromVert.edgeIds[i];
                // Since the graph is not directional
                // check the both ends
                if((edgeList[eId].vertexId0 == vertexId &&
                    edgeList[eId].vertexId1 == nextVertexId)
                ||
                   (edgeList[eId].vertexId0 == nextVertexId &&
                    edgeList[eId].vertexId1 == vertexId))
                {
                    edgeId = eId;
                    break;
                }
            }
        }
        if(edgeId != INVALID_INDEX)
        {
            const GraphEdge& edge = edgeList[edgeId];
            std::cout << "-" << std::setfill('-')
                      << std::setw(2)
                      << edge.weight << "->";
        }
        else
        {
            std::cout << "-##-> ";
        }
    }
    // Print endline on the last vertex if same line is set
    if(sameLine) std::cout << "\n";
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

int Graph::TotalVertexCount() const
{
    return vertexList.size();
}

int Graph::TotalEdgeCount() const
{
    return edgeList.size();
}

std::string Graph::VertexName(int vertexId) const
{
    if (vertexId < vertexList.size())
        return vertexList[vertexId].name;
    else
        return "";
}

int Graph::TotalWeightInBetween(std::vector<int>& orderedVertexIdList)
{
    int size = orderedVertexIdList.size();

    if (orderedVertexIdList.size() == 0)
        return -1;
    else
    {
        int i, total_weight = 0, connection_index;

        for (i = 0; i < size - 1; i++)
        {
            connection_index = find_connection(orderedVertexIdList[i], orderedVertexIdList[i+1]);
            total_weight += edgeList[connection_index].weight;
        }

        return total_weight;
    }
}
