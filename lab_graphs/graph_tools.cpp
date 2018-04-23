/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    //TODO: YOUR CODE HERE
    vector<Vertex> v = graph.getVertices();
    vector<Edge> e = graph.getEdges();

    for (size_t i = 0; i < v.size(); ++i) {
        graph.setVertexLabel(v[i], "UNEXPLORED");
    }

    for (size_t i = 0; i < e.size(); ++i) {
        graph.setEdgeLabel(e[i].source, e[i].dest, "UNEXPLORED");
    }

    queue<Vertex> q;
    q.push(v[0]);

    graph.setVertexLabel(v[0], "VISITED");

    Vertex min1 = v[0];
    Vertex min2 = graph.getAdjacent(v[0])[0];
    Vertex w = Vertex();

    int minWeight = graph.getEdgeWeight(v[0], min2);
    int currWeight = 0;

    while (!q.empty()) {
        currWeight = 0;
        w = q.front();
        q.pop();

        vector<Vertex> adj = graph.getAdjacent(w);

        for (size_t i = 0; i < adj.size(); ++i) {
            if (graph.getVertexLabel(adj[i]) == "UNEXPLORED") {
                graph.setEdgeLabel(w, adj[i], "DISCOVERY");
                graph.setVertexLabel(adj[i], "VISITED");

                currWeight = graph.getEdgeWeight(adj[i], w);

                if (currWeight < minWeight) {
                    minWeight = currWeight;
                    min1 = w;
                    min2 = adj[i];
                }

                q.push(adj[i]);
            } else if (graph.getEdgeLabel(w, adj[i]) == "UNEXPLORED") {
                graph.setEdgeLabel(w, adj[i], "CORSS");

                currWeight = graph.getEdgeWeight(adj[i], w);

                if (currWeight < minWeight) {
                    minWeight = currWeight;
                    min1 = w;
                    min2 = adj[i];
                }
            }
        }
    }

    graph.setEdgeLabel(min1, min2, "MIN");

    return minWeight;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    //TODO: YOUR CODE HERE
    vector<Vertex> v = graph.getVertices();
    vector<Edge> e = graph.getEdges();
    unordered_map<Vertex, Vertex> parent;

    for (size_t i = 0; i < v.size(); ++i) {
        graph.setVertexLabel(v[i], "UNEXPLORED");
    }

    for (size_t i = 0; i < e.size(); ++i) {
        graph.setEdgeLabel(e[i].source, e[i].dest, "UNEXPLORED");
    }

    queue <Vertex> q;
    q.push(start);

    graph.setVertexLabel(start, "VISITED");

    Vertex w = Vertex();

    while (!q.empty()) {
        w = q.front();
        q.pop();

        vector<Vertex> adjacent = graph.getAdjacent(w);

        for (size_t i = 0; i < adjacent.size(); ++i) {
            if (graph.getVertexLabel(adjacent[i]) == "UNEXPLORED") {
                graph.setEdgeLabel(w, adjacent[i], "DISCOVERY");
                graph.setVertexLabel(adjacent[i], "VISITED");
                pair<Vertex, Vertex> pairVertex (adjacent[i], w);
                parent.insert(pairVertex);
                q.push(adjacent[i]);
            } else if (graph.getEdgeLabel(w, adjacent[i]) == "UNEXPLORED") {
                graph.setEdgeLabel(w, adjacent[i], "CORSS");
            }
        }
    }

    int distance = 0;

    while (end != start) {
        graph.setEdgeLabel(end, parent[end], "MINPATH");
        end = parent[end];
        ++distance;
    }

    return distance;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the dsets.h and dsets.cpp .
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    //TODO: YOUR CODE HERE
}
