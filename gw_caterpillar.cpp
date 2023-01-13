#include<LEDA/graphics/graphwin.h>
#include<LEDA/graph/graph_alg.h>

using namespace leda;

// Recursive function to return gcd of a and b
long long gcd(long long int a, long long int b)
{
  if (b == 0)
    return a;
  return gcd(b, a % b);
}
 
// Function to return LCM of two numbers
long long lcm(int a, int b)
{
    return (a / gcd(a, b)) * b;
}

double h = 1; // half the vertical distance between sibling leaves

list<node> TestCaterpillar(const graph& G, node_array<int>& leaves,
                                           edge_array<bool>& on_path)
{
  // returns path (backbone) as list of nodes (empty if G is not a caterpillar)
  // computes number of leaves of each node v (leaves[v])
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



void DrawLeaves(const graph& G, const node_array<node>& sibling,
                node v, double& x, double& y, double d,
                node_array<point>& pos,
                edge_array<bool>& on_path)
{
  edge e;
  forall_out_edges(e,v) {
    if (on_path[e]) continue; // ignore backbone edges
    node w  = G.target(e);
    node ws = sibling[w];
    pos[w]  = point(x,y);
    pos[ws] = point(x+d,y-2*h);
    x += 2*d;
  }
}




bool DrawCaterpillar(GraphWin& gw, const node_array<node>& sibling,
                                   double x, double y, node_array<point>& pos)
{
  graph& G = gw.get_graph();

  // computes positions pos[v] and pos[sibling[v]] for each node v
  // return false if G is not a caterpillar graph

  // (x,y) position of root node (path.front())


  node_array<int> leaves(G);   // leaves[v] = #number of leaves of v
  edge_array<bool> on_path(G); // on_path[e] iff e lies on backbone path

  list<node> path = TestCaterpillar(G,leaves,on_path);

  int k = path.size(); // number of backbone vertices v1 ... vk
  int max_leaves = 0; // maximum number of leaves for any spine vertex
  long long int b = 4; // lowest common denominator of spine degrees. Has to be divisible by 4 such that +/- b/4 leads to integer coordinates.

  cout << endl;
  cout << "Backbone: ";

  node v;
  forall(v,path) {
    cout << G.index(v) << " ";
    gw.set_color(v,green2);
    gw.set_color(sibling[v],blue2);
    max_leaves = max(max_leaves,leaves[v]);
  }
  cout << endl;
  cout << endl;
  
  if (k == 0) {
   // Graph is not a caterpillar
   return false;
  }
  
  
  // compute LCM for coordinates required
  list_item it_lcm;
  forall_items(it_lcm,path)
  { 
     node v  = path[it_lcm];
     node u = (it_lcm == path.first()) ? nil : path[path.pred(it_lcm)];
     node w = (it_lcm == path.last())  ? nil : path[path.succ(it_lcm)];

     node vs = sibling[v];
     node us = u ? sibling[u] : nil;
     node ws = w ? sibling[w] : nil;


     if (w == nil) 
     { 
      if(leaves[u] > 0){
        b = lcm(b, 2*leaves[v] - 1);
      } else {
	    b = lcm(b, 2*leaves[v]);
	  }
       continue;
     }

     if (leaves[v] == 0)
     { 
       continue;
     }

     // here we have: leaves[v] > 0
     if ((u == nil || leaves[u] > 0) && leaves[w] > 0)
     { 
       b = lcm(b, 2*leaves[v] - 1);
       continue;
     }


     if ((u == nil || leaves[u] > 0) && leaves[w] == 0)
     { 
       b = lcm(b, 2*leaves[v]);
       continue;
      }

     if (u && leaves[u] == 0 && leaves[w] > 0)
     { 
       b = lcm(b, 2*leaves[v]);
       continue;
      }

     if (u && leaves[u] == 0 && leaves[w] == 0)
     { 
       b = lcm(b, 2*leaves[v]+1);
       continue;
      }

   }

  b = fmax(b, 8);
  // compute a and b
  double a = (b * b) / (4 * h) + h;
  
  ostringstream msg;
  msg << "a: " << std::to_string(a) << ", b: " << std::to_string(b);
  gw.message(msg.str().c_str());



  node v1 = path.front();
  node u1 = sibling[v1];

  pos[v1] = point(x,y);

  if (leaves[v1] == 0)
    pos[u1] = point(x + (a+b/2), y - (a+2*h));
  else
    pos[u1] = point(x, y - (2*a+2*h));

  // main loop: iterate over all backbone nodes (v1 ... vk)

  list_item it;
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

       DrawLeaves(G,sibling,v,x,y,dist,pos,on_path);

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

       DrawLeaves(G,sibling,v,x,y,dist,pos,on_path);

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
           DrawLeaves(G,sibling,v,x,y,dist,pos,on_path);
           x -= b / 2;
       } else
           DrawLeaves(G,sibling,v,x,y,dist,pos,on_path);

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
       else
         DrawLeaves(G,sibling,v,x,y,dist,pos,on_path);

       pos[w]  = pos[v].translate(a+b,0);
       pos[ws] = pos[vs].translate(a+b,0);

       continue;
      }

     if (u && leaves[u] == 0 && leaves[w] == 0)
     { 
       double dist = b/(2*leaves[v] + 1);
       double x = pos[us].xcoord() + dist;
       double y = pos[us].ycoord() + 2*h;

       DrawLeaves(G,sibling,v,x,y,dist,pos,on_path);

       pos[w]  = point(x,y);
       pos[ws] = pos[vs].translate(a+b,0);

       continue;
      }

   }

   return true;
}



void set_layout(GraphWin& gw, node_array<point>& pos)
{
  //gw.set_layout(pos);

  graph& G = gw.get_graph();
  window& W = gw.get_window();

  node_array<double> radius(G);
  edge_array<list<point> > bends(G);
  edge_array<point> anchor(G);

  node v;
  forall_nodes(v,G) {
    radius[v] = W.pix_to_real(10);
    gw.set_border_width(v,2);
  }

  edge e;
  forall_edges(e,G) {
    gw.set_width(e,2);
    gw.set_direction(e,undirected_edge);
  }

  gw.set_layout(pos,radius,radius,bends,anchor,anchor);

  gw.zoom_graph();
  gw.zoom(0.85);

  gw.center_graph();
}

void init_handler(GraphWin& gw) {
   //gw.message("Click 'done' to duplicate the graph.");
   gw.zoom_graph();
}
  

int main()
{
  GraphWin gw("Caterpillar 1");

  gw.win_init(0,200,0);
  gw.set_node_radius(4);
  gw.set_zoom_objects(false);

  gw.set_init_graph_handler(init_handler);

  gw.display();

  window& W = gw.get_window();

  double x = 0;
  double y = 0;

  while (gw.get_graph().empty())
  { gw.message("Draw or load a caterpillar graph and click 'done' to duplicate the graph.");
    if (!gw.edit()) return 1;
   } 

/*
  gw.message("Click 'done' to duplicate the graph.");
  gw.edit();
*/

  { graph& G = gw.get_graph();
    int n = G.number_of_nodes();


    graph G1 = G;
    G.join(G1);

    array<node> V(2*n);
    int i = 0;

    node v;
    forall_nodes(v,G) V[i++] = v;

    node_array<node> sibling(G,nil);

    gw.update_graph();

    gw.set_flush(false);

    i = 0;
    forall_nodes(v,G) {
      if (i < n)
        sibling[v] = V[i+n];
      else
      { node u = V[i-n];
        //sibling[v] = u;
        point pos = gw.get_position(u);
        gw.set_position(v,pos.translate(0,-100));
       }
      i++;
    }

    gw.set_flush(true);

    //gw.center_graph();
    gw.zoom_graph();

    gw.message("Click 'done' to compute a mutual witness gabriel drawing.");
    gw.edit();

    node_array<point> pos(G);

    if (DrawCaterpillar(gw,sibling,x,y,pos))
    { node v;
      forall_nodes(v,G) {
        double x = pos[v].xcoord();
        double y = pos[v].ycoord();
        cout << string("%2d:  %6.2f  %6.2f",G.index(v),x,y) << endl;
        node u = sibling[v];
        //if (u) pos[u] = pos[u].translate(0,-10);
        if (u) 
          gw.set_color(v,yellow);
        else
          gw.set_color(v,orange);
      }

      set_layout(gw,pos);
    }
    else {
      // something went wrong
      cout << "ERROR" << endl;
    }

  }

  gw.message("A mutual witness gabriel drawing");
  gw.edit();

  gw.message("Save Drawing to a File.");

  string gname = gw.get_graphname();
  gw.set_graphname(gname + "-result");
  gw_save_handler(gw);
  
  return 0;
}
