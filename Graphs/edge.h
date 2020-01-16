#ifndef EDGE_H
#define EDGE_H

namespace Graphs {

    struct Edge {
        int v;
        int w;
        Edge(int v, int w)
            : v {v},
              w {w}
        {}
    };

}

#endif // EDGE_H
