#ifndef ADJACENCYLISTSGRAPH_H
#define ADJACENCYLISTSGRAPH_H

#include <edge.h>
#include <vector>

namespace Graphs {

class AdjacencyListsGraph
{
    struct Node {
        int v;
        Node* next;
        Node(int v, Node* next)
            : v (v),
              next (next)
        {}
    };

    std::vector<Node*> adj;
    int v_count;
    int e_count;
    bool digraph;

    void clear_memory() {
        Node* t;
        for(int i = 0; i < adj.size(); ++i) {
            t = adj[i];
            Node* n;
            while(t) {
                n = t->next;
                delete t;
                t = n;
            }
        }
    }
    void copy_from(const AdjacencyListsGraph& rhs) {
        adj.assign(rhs.v_count, nullptr);
        adj.shrink_to_fit();
        v_count = rhs.v_count;
        e_count = rhs.e_count;
        digraph = rhs.digraph;
        for(int i = 0; i < rhs.v_count; ++i) {
            Node* t = rhs.adj[i];
            while(t) {
                adj[i] = new Node(t->v, adj[i]);
                t = t->next;
            }
        }
    }
    void move_from(AdjacencyListsGraph& rhs) {
        adj = move(rhs.adj);
        v_count = rhs.v_count;
        e_count = rhs.e_count;
        digraph = rhs.digraph;
        rhs.e_count = 0;
        rhs.v_count = 0;
        rhs.digraph = false;
    }

public:
    AdjacencyListsGraph(int v, bool digraph = false)
        : v_count (v),
          e_count (0),
          digraph (digraph)
    {
        adj.assign(v, nullptr);
    }
    AdjacencyListsGraph(const AdjacencyListsGraph& rhs) { copy_from(rhs); }
    AdjacencyListsGraph& operator=(const AdjacencyListsGraph& rhs) {
        if(this == &rhs) return *this;
        if(e_count) clear_memory();
        copy_from(rhs);
        return *this;
    }
    AdjacencyListsGraph(AdjacencyListsGraph&& rhs) { move_from(rhs); }
    AdjacencyListsGraph& operator=(AdjacencyListsGraph&& rhs) {
        if(this == &rhs) return *this;
        if(e_count) clear_memory();
        move_from(rhs);
        return *this;
    }
    ~AdjacencyListsGraph() { clear_memory(); }
    int v() const { return v_count; }
    int e() const { return e_count; }
    bool directed() const { return digraph; }
    void insert(int v, int w) {
        adj[v] = new Node(w, adj[v]);
        if(!digraph) adj[w] = new Node(v, adj[w]);
        ++e_count;
    }
    void insert(const Graphs::Edge& edge) {
        adj[edge.v] = new Node(edge.w, adj[edge.v]);
        if(!digraph) adj[edge.w] = new Node(edge.v, adj[edge.w]);
        ++e_count;
    }
    bool edge(int v, int w) {
        Node* t = adj[v];
        while(t && t->v != w) t = t->next;
        if(t) return true;
        return false;
    }
    bool edge(const Graphs::Edge& edge) {
        Node* t = adj[edge.v];
        while(t && t->v != edge.w) t = t->next;
        if(t) return true;
        return false;
    }
    void remove(const Graphs::Edge& edge) {
        Node* t = adj[edge.v];
        Node* p = t;
        while(t && t->v != edge.w) {
            p = t;
            t = t->next;
        }
        if(!t) return;
        if(t == adj[edge.v] && t->next == nullptr) {
            delete t;
            adj[edge.v] = nullptr;
        }
        else {
            p->next = t->next;
            delete t;
        }
        --e_count;
        if(digraph) return;
        t = adj[edge.w];
        p = t;
        while(t && t->v != edge.v) {
            p = t;
            t = t->next;
        }
        if(t == adj[edge.w] && t->next == nullptr) {
            delete t;
            adj[edge.w] = nullptr;
        }
        else {
            p->next = t->next;
            delete t;
        }
    }
    void remove(int v, int w) {
        Node* t = adj[v];
        Node* p = t;
        while(t && t->v != w) {
            p = t;
            t = t->next;
        }
        if(!t) return;
        if(t == adj[v] && t->next == nullptr) {
            delete t;
            adj[v] = nullptr;
        }
        else {
            p->next = t->next;
            delete t;
        }
        --e_count;
        if(digraph) return;
        t = adj[w];
        p = t;
        while(t && t->v != v) {
            p = t;
            t = t->next;
        }
        if(t == adj[w] && t->next == nullptr) {
            delete t;
            adj[w] = nullptr;
        }
        else {
            p->next = t->next;
            delete t;
        }
    }

    class adjIterator {
        const Graphs::AdjacencyListsGraph& graph;
        int v;
        Node* t;

    public:
        adjIterator(const Graphs::AdjacencyListsGraph& graph, int v)
            : graph (graph),
              v (v),
              t (nullptr)
        {}
        int beg() {
            t = graph.adj[v];
            return t ? t->v : -1;
        }
        int nxt() {
            if(t) t = t->next;
            return t ? t->v : -1;
        }
        bool end() {
            return t == nullptr;
        }
    };
};

}


#endif // ADJACENCYLISTSGRAPH_H
