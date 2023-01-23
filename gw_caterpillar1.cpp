#include <LEDA/graphics/graphwin.h>

#include "mwg_drawing.h"

using namespace leda;

void set_layout(GraphWin& gw, node_array<point>& pos)
{
  graph& G = gw.get_graph();

  node v;
  forall_nodes(v,G) {
    gw.set_width(v,16);
    gw.set_height(v,16);
    gw.set_border_width(v,1);
    gw.set_label_type(v,user_label);
  }

  edge e;
  forall_edges(e,G) {
    gw.set_width(e,1);
    gw.set_direction(e,undirected_edge);
  }

  gw.set_layout(pos);
  gw.zoom_graph();
  gw.zoom(0.85);
}


void init_handler(GraphWin& gw) 
{ // called after graph is loaded from file
  gw.zoom_graph();
}
  

int main()
{
  GraphWin gw("Caterpillar 1");

  gw.win_init(0,200,0);

  gw.set_init_graph_handler(init_handler);
  gw.set_zoom_objects(false);

  gw.display();

  gw.set_node_width(48);
  gw.set_node_height(48);
  gw.set_node_border_width(1);


  graph& G = gw.get_graph();

  while (gw.get_graph().empty())
  { // run edit loop as long graph is empty
    gw.message("Draw or load a caterpillar graph and click 'done' to duplicate the graph.");
    if (!gw.edit()) return 1;
   } 


  //int n = G.number_of_nodes();
  int n = G.max_node_index()+1; // original number of nodes

  // make a copy G1 of G and join the two components
  graph G1 = G;
  G.join(G1);


  // tell GraphWin that G has changed
  gw.update_graph();


  // now G has 2*n nodes
  // compute corresponding nodes (siblings)
  // and place them below the original nodes

  node_array<node> sibling(G,nil);

  array<node> V(2*n); // array of all nodes V[i] = node with index i

  node v;
  forall_nodes(v,G) V[G.index(v)] = v;

  gw.set_flush(false);

  forall_nodes(v,G) 
  { int i = G.index(v);
    if (i < n)
    { // v lies in first component (original node) and has sibling i+n
      // define sibling (i+n) and set color to yellow
      sibling[v] = V[i+n];
      gw.set_color(v,yellow);
    }
    else
    { // v lies in second component (new node) and has sibling nil
      // place it below the original node u (i-n) and set color to orange
      node u = V[i-n];
      sibling[v] = nil;
      point pos = gw.get_position(u);
      gw.set_position(v,pos.translate(0,-60));
      gw.set_color(v,orange);
     }
  }

  gw.set_flush(true);

  gw.zoom_graph();

  gw.message("Click 'done' to compute a mutual witness gabriel drawing.");
  gw.edit();



  // try to draw G as mutual witness gabriel graph by calling DrawCaterpillar

  node_array<point> pos(G);

  double x = 0;
  double y = 0;
  double h = 1;

  if (DrawCaterpillar(G,sibling,x,y,h,pos))
  { 
    // show computed layout
    set_layout(gw,pos);

    // print coordinates to cout
    node v;
    forall_nodes(v,G) {
      double x = pos[v].xcoord();
      double y = pos[v].ycoord();
      cout << string("%2d:  %6.2f  %6.2f",G.index(v),x,y) << endl;
    }
  }
  else {
    // something went wrong
    cout << "ERROR: G is not two-fold caterpillar graph." << endl;
  }

  gw.message("A mutual witness gabriel drawing");
  gw.edit();


  gw.message("Save Drawing to a File.");
  string gname = gw.get_graphname();
  gw.set_graphname(gname + "-result");
  gw_save_handler(gw);
  
  return 0;
}
