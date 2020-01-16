#ifndef ADJACENCYMATRIXGRAPH_H
#define ADJACENCYMATRIXGRAPH_H

#include "edge.h"
#include <vector>

namespace Graphs {

class AdjacencyMatrixGraph
{
    std::vector<std::vector<bool>> adj;
    int v_count;
    int e_count;
    bool digraph;

public:
    AdjacencyMatrixGraph(int v, bool digraph = false)
        : adj (v),
          v_count (v),
          e_count (0),
          digraph (0)
    {
        for(int i = 0; i < v_count; ++i)
            adj[i].assign(v, false);
    }
    int v() const { return v_count; }
    int e() const { return e_count; }
    bool directed() const { return digraph; }
    bool edge(int v, int w) const { return adj[v][w]; }
    bool edge(const Graphs::Edge& edge) const { return adj[edge.v][edge.w]; }
    void insert(int v, int w) {
        if(!adj[v][w]) ++e_count;
        adj[v][w] = true;
        if(!digraph) adj[w][v] = true;
    }
    void insert(const Graphs::Edge& edge) {
        if(!adj[edge.v][edge.w]) ++e_count;
        adj[edge.v][edge.w] = true;
        if(!digraph) adj[edge.w][edge.v] = true;
    }
    void remove(int v, int w) {
        if(adj[v][w] == true) --e_count;
        adj[v][w] = false;
        if(!digraph) adj[w][v] = false;
    }
    void remove(const Graphs::Edge& edge) {
        if(adj[edge.v][edge.w] == true) --e_count;
        adj[edge.v][edge.w] = false;
        if(!digraph) adj[edge.w][edge.v] = false;
    }

    class adjIterator {
        const AdjacencyMatrixGraph& graph;
        int v;
        int i;

    public:
        adjIterator(const AdjacencyMatrixGraph& graph, int v)
            : graph (graph),
              v (v),
              i (-1)
        {}
        int beg() { i = -1; return nxt(); }
        int nxt() {
            for(++i; i < graph.v(); ++i)
                if(graph.adj[v][i] == true) return i;
            return -1;
        }
        bool end() { return i >= graph.v(); }
    };

};

}

#endif // ADJACENCYMATRIXGRAPH_H
