#include "mwg_drawing.h"


LEDA_BEGIN_NAMESPACE

inline long long gcd(long long int a, long long int b)
{ // Recursive function to return gcd of a and b
  if (b == 0) return a;
  return gcd(b, a % b);
}
 
inline long long lcm(int a, int b)
{ // Function to return LCM of two numbers
  return (a / gcd(a, b)) * b;
 }


static list<node> TestCaterpillar(const graph& G, node_array<int>& leaves,
                                           edge_array<bool>& on_path)
{
  // returns the path (backbone) of G as a list of nodes 
  // (the empty list if G is not a caterpillar)

  // computes the number of leaves (legs) of each node v (leaves[v])
  // marks each edge e as path or non-path edge (on_path[e])

  // G is directed:
  // we assume that each backbone node has exactly one incoming edge
  // (these edges define the backbone path) and all other edges are
  // directed towards a leaf node.
  // A node v is a leaf node exactly if outdeg(v) = 0.

  // the root (start of backbone) is the unique node v with indeg(v) = 0
  // all other nodes have an indegree > 0


  node v;
  forall_nodes(v,G) leaves[v] = 0;

  edge e;
  forall_edges(e,G) on_path[e] = false;


  // find root node v (node with indeg 0 in first component);

  forall_nodes(v,G) {
     if (G.indeg(v) == 0) break;
  }

  assert(v != nil && G.indeg(v) == 0);


  // traverse backbone and append nodes to path list

  list<node> path;

  while (v)
  {
    path.append(v);

    node next_v = nil;

    edge e;
    forall_out_edges(e,v) {

       node w = G.target(e);

       if (G.outdeg(w) == 0) {
         // edge to leaf node w
         leaves[v]++;
       }
       else
       { // backbone edge
         on_path[e] = true;
         next_v = w;
        }
    }

    v = next_v;
  }

  return path;
}



static void DrawLeaves(const graph& G, const node_array<node>& sibling,
                       node v, double& x, double& y, double h, double d, 
                       node_array<point>& pos,
                       edge_array<bool>& on_path)
{ edge e;
  forall_out_edges(e,v) {
    if (on_path[e]) continue; // ignore backbone edges
    node w  = G.target(e);
    node ws = sibling[w];
    pos[w]  = point(x,y);
    pos[ws] = point(x+d,y-2*h);
    x += 2*d;
  }
}


// extern function

bool DrawCaterpillar(const graph& G, 
                     const node_array<node>& sibling,
                     double x, double y, double h,
                     node_array<point>& pos)
{

  // Input
  // G consists of two copies G1,G2 of the same caterpillar graph 
  // sibling[v] gives for each node in G1 its corresponding node in G2
  // (x,y) defines the position of the root node (path.front())
  // h = half the vertical distance between sibling leaves

  // Output
  // computes positions pos[v] and pos[sibling[v]] for each node v
  // return false if G is not a caterpillar graph



  node_array<int> leaves(G);   // leaves[v] = #number of leaves of v
  edge_array<bool> on_path(G); // on_path[e] iff e lies on backbone path

  list<node> path = TestCaterpillar(G,leaves,on_path);

  int k = path.size(); // number of backbone vertices v1 ... vk

  if (k == 0) {
   // graph is not a caterpillar
   return false;
  }
  

  int max_leaves = 0; // maximum number of leaves for any spine vertex

  node v;
  forall(v,path) max_leaves = max(max_leaves,leaves[v]);

  
  // compute b and a

  long long int b = 4; // lowest common denominator of spine degrees. 
                       // Has to be divisible by 4 such that +/- b/4 
                       // leads to integer coordinates.

  // compute LCM for coordinates required

  list_item it;
  forall_items(it,path)
  { 
    node v  = path[it];
    node u = (it == path.first()) ? nil : path[path.pred(it)];
    node w = (it == path.last())  ? nil : path[path.succ(it)];

    node vs = sibling[v];
    node us = u ? sibling[u] : nil;
    node ws = w ? sibling[w] : nil;

    if (w == nil) 
    { if (leaves[u] > 0)
       b = lcm(b, 2*leaves[v] - 1);
      else 
       b = lcm(b, 2*leaves[v]);
      continue;
    }

    if (leaves[v] == 0) continue;


    // here we have leaves[v] > 0

    if ((u == nil || leaves[u] > 0) && leaves[w] > 0)
    { b = lcm(b, 2*leaves[v] - 1);
      continue;
     }


    if ((u == nil || leaves[u] > 0) && leaves[w] == 0)
    { b = lcm(b, 2*leaves[v]);
      continue;
     }

    if (u && leaves[u] == 0 && leaves[w] > 0)
    { b = lcm(b, 2*leaves[v]);
      continue;
     }

    if (u && leaves[u] == 0 && leaves[w] == 0)
    { b = lcm(b, 2*leaves[v]+1);
      continue;
     }
  }

  b = fmax(b, 8);

  double a = (b * b) / (4 * h) + h;


  node v1 = path.front();
  node u1 = sibling[v1];

  pos[v1] = point(x,y);

  if (leaves[v1] == 0)
    pos[u1] = point(x + (a+b/2), y - (a+2*h));
  else
    pos[u1] = point(x, y - (2*a+2*h));


  // main loop: iterate over all backbone nodes (v1 ... vk)

  forall_items(it,path)
  { 
    // Let v = path[it] be the current vertex (v_i in Carolina's Code)

    // Invariant: positions of v and all path redecessors of v are defined

    // Let w be the successor of v on the backbone (v_(i+1))
    // and u be the predecessor of v on the backbone (v_(i-1)) 
    // Note: u or w might not exist !

    // i-1    i    (i+1)
    //  u-----v------w

    // we compute the position of w and positions of the leaves of v
    // and of the corresponding sibling nodes in the second component

     node v  = path[it];
     node u = (it == path.first()) ? nil : path[path.pred(it)];
     node w = (it == path.last())  ? nil : path[path.succ(it)];

     node vs = sibling[v];
     node us = u ? sibling[u] : nil;
     node ws = w ? sibling[w] : nil;


     if (w == nil) 
     { // v is last backbone node
       // EMBED LEAVES of v !
       // missing in Carolina's Algorithm ?
      double dist = b/(2*leaves[v]);
      double x = pos[v].xcoord() - b/2;
      double y = pos[v].ycoord() - a;
      if(leaves[u] > 0){
        dist = b/(2*leaves[v] - 1);
      } 
      if(leaves[u] == 0){
        x = x + dist;
        if (leaves[v] == 1) {
            x -= b / 4;
            dist = 3 * b / 4;
        }
      } 

       DrawLeaves(G,sibling,v,x,y,h,dist,pos,on_path);

       continue;
     }


     if (leaves[v] == 0)
     { 
       double x1 = pos[v].xcoord();
       double y1 = pos[v].ycoord();

       double x2 = pos[vs].xcoord();
       double y2 = pos[vs].ycoord();

       pos[w] = point(x1 + (a+b), y1);

       if (leaves[w] == 0) 
         pos[ws] = point(x2 + (a+b), y2);
       else 
         pos[ws] = point(x2 + b/2, y2 - a);
      
       continue;
     }

     // here we have: leaves[v] > 0
     
     if ((u == nil || leaves[u] > 0) && leaves[w] > 0)
     { 
       double dist = b/(2*leaves[v] -1 );
       double x = pos[v].xcoord() - b/2;
       double y = pos[v].ycoord() - a;

       DrawLeaves(G,sibling,v,x,y,h,dist,pos,on_path);

       pos[w]  = pos[v].translate(a+b,0);
       pos[ws] = pos[vs].translate(a+b,0);

       continue;
      }


     if ((u == nil || leaves[u] > 0) && leaves[w] == 0)
     { 
       double dist = b/(2*leaves[v]);
       double x = pos[v].xcoord() - b/2;
       double y = pos[v].ycoord() - a;
       
       if (leaves[v] == 1) { // shift leaf sibling to the right
           dist = 3 * b / 4;
           DrawLeaves(G,sibling,v,x,y,h,dist,pos,on_path);
           x -= b / 2;
       } else
           DrawLeaves(G,sibling,v,x,y,h,dist,pos,on_path);

       pos[w]  = point(x,y);
       pos[ws] = pos[vs].translate(a+b,0);

       continue;
      }

     if (u && leaves[u] == 0 && leaves[w] > 0)
     { 
       double dist = b/(2*leaves[v]);
       double x = pos[us].xcoord() + dist;
       double y = pos[us].ycoord() + 2*h;
       
       if (leaves[v] == 1) { // shift leaf to the left
           x -= b / 4;
           dist = 3 * b / 4;
       }
       
	   DrawLeaves(G,sibling,v,x,y,h,dist,pos,on_path);

       pos[w]  = pos[v].translate(a+b,0);
       pos[ws] = pos[vs].translate(a+b,0);

       continue;
      }

     if (u && leaves[u] == 0 && leaves[w] == 0)
     { 
       double dist = b/(2*leaves[v] + 1);
       double x = pos[us].xcoord() + dist;
       double y = pos[us].ycoord() + 2*h;

       DrawLeaves(G,sibling,v,x,y,h,dist,pos,on_path);

       pos[w]  = point(x,y);
       pos[ws] = pos[vs].translate(a+b,0);

       continue;
      }

   }

   return true;
}

LEDA_END_NAMESPACE

