
#include <LEDA/graph/graph.h>
#include <LEDA/geo/point.h>
#include <LEDA/core/tuple.h>


namespace leda {

typedef two_tuple<node,node> node_pair;

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


extern void MWG_TEST(const graph& G, 
                     const node_array<int>& comp,
                     const node_array<point>& pos,
                     edge_array<bool>& blocked, 
                     list<node_pair>& missing_edges);

  // Input: a graph G consisting of two components
  // For all nodes v in the first  component comp[v] = 0
  // For all nodes v in the second component comp[v] = 1
  // pos[v] = position of v

  // marks edges as blocked if blocked by some node in the other component 
  // and computes list of missing edges (unblocked node pairs)

}
