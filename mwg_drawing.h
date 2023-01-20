
#include <LEDA/graph/graph.h>
#include <LEDA/geo/point.h>

namespace leda {

extern bool DrawCaterpillar(const graph& G, 
                            const node_array<node>& sibling,
                            double x, double y, double h,
                            node_array<point>& pos);

  // Input:
  // G consists of two copies G1,G2 of the same caterpillar graph 
  // sibling[v] gives for each node in G1 its corresponding node in G2
  // (x,y) defines the position of the root node (path.front())
  // h = half the vertical distance between sibling leaves

  // Output:
  // computes positions pos[v] for each node v in G
  // returns false if G is not a (two fold) caterpillar graph 
  // and true otherwise

}

