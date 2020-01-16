#ifndef IO_FUNCTIONS_H
#define IO_FUNCTIONS_H

#include <iostream>

namespace Graphs {

template<typename Graph>
void show(const Graph& g)
{
    for(int s = 0; s < g.v(); ++s) {
        std::cout << s << ':';
        typename Graph::adjIterator iter(g, s);
        for(int t = iter.beg(); !iter.end(); t = iter.nxt()) {
            std::cout.width(2);
            std::cout << t << ' ';
        }
        std::cout << '\n';
    }
}

}


#endif // IO_FUNCTIONS_H
