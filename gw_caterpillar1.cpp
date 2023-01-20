#include <LEDA/graphics/graphwin.h>

#include "mwg_drawing.h"

using namespace leda;

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
   // called after graph is loaded from file
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


  graph& G = gw.get_graph();
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

  double h = 1;

  if (DrawCaterpillar(G,sibling,x,y,h,pos))
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


  gw.message("A mutual witness gabriel drawing");
  gw.edit();

  gw.message("Save Drawing to a File.");
  string gname = gw.get_graphname();
  gw.set_graphname(gname + "-result");
  gw_save_handler(gw);
  
  return 0;
}
