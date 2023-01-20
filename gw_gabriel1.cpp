#include <LEDA/graph/graph.h>
#include <LEDA/graphics/graphwin.h>

#include "mwg_drawing.h"

using namespace leda;

static color NODE_CLR_1 = yellow;
static color NODE_CLR_2 = orange;

static color EDGE_CLR_MISSING = green;
static color EDGE_CLR_BLOCKED = red;
static color EDGE_CLR_OK = blue;


void draw_gabriel(GraphWin& gw)
{ 
  window& W = gw.get_window();
  graph&  G = gw.get_graph();

  // remove all edges of color EDGE_CLR_MISSING 
  // inserted to represent missing edges

  edge e;
  forall_edges(e,G) {
    if (gw.get_color(e) == EDGE_CLR_MISSING) gw.del_edge(e);
  }

  forall_edges(e,G) gw.set_color(e,EDGE_CLR_OK);


  node_array<point> pos(G);
  node_array<int>   comp(G);

  edge_array<bool> blocked(G);
  list<node_pair> missing_edges;

  node v;
  forall_nodes(v,G) 
  { pos[v] = gw.get_position(v);

    if (gw.get_color(v) == NODE_CLR_1) 
      comp[v] = 0;
    else
      comp[v] = 1;
   }

  MWG_TEST(G,comp,pos,blocked,missing_edges);

  gw.clear_shapes();

  forall_edges(e,G) 
  { node u = G.source(e);
    node v = G.target(e);

    point a = gw.get_position(u);
    point b = gw.get_position(v);
    point c = midpoint(a,b);
    circle circ(c,a);

    if (blocked[e])
    { gw.set_color(e,EDGE_CLR_BLOCKED);
      gw.set_width(e,2);
      gw.new_shape(circ,"",EDGE_CLR_BLOCKED);
     }
    else
    { gw.set_color(e,EDGE_CLR_OK);
      gw.set_width(e,2);
      gw.new_shape(circ,"",grey3);
     }
  }

  // draw missing edges

  node_pair n_pair;
  forall(n_pair,missing_edges) 
  { 
    node v = n_pair.first();
    node w = n_pair.second();

    point a = gw.get_position(v);
    point b = gw.get_position(w);
    point c = midpoint(a,b);

    edge e = gw.new_edge(v,w);
    gw.set_color(e,EDGE_CLR_MISSING);
    gw.set_width(e,2);

    circle circ(c,a);
    gw.new_shape(circ,"",EDGE_CLR_MISSING);
  }

  gw.redraw(gw.get_xmin(),gw.get_ymin(),gw.get_xmax(),gw.get_ymax());
}



void init_graph_handler(GraphWin& gw)
{ 
  graph& G = gw.get_graph();

  if (G.empty())
  { node a = gw.new_node(point(100,200));
    gw.set_color(a,NODE_CLR_1);

    node b = gw.new_node(point(400,200));
    gw.set_color(b,NODE_CLR_2);
  }

  gw.set_flush(false);

  node v;
  forall_nodes(v,G) {
    gw.set_width(v,15);
    gw.set_height(v,15);
    gw.set_border_width(v,1);
    gw.set_label_type(v,user_label);
  }

  edge e;
  forall_edges(e,G) gw.set_width(e,1);

  draw_gabriel(gw); 

  gw.zoom_graph();
  gw.set_flush(true);
  gw.zoom(0.85);
}

void new_node_handler(GraphWin& gw,node){ draw_gabriel(gw); }
void new_edge_handler(GraphWin& gw,edge){ draw_gabriel(gw); }
void del_edge_handler(GraphWin& gw)     { draw_gabriel(gw); }
void del_node_handler(GraphWin& gw)     { draw_gabriel(gw); }


bool pre_new_edge_handler(GraphWin& gw,node v, node w){ 
  color clr_v = gw.get_color(v);
  color clr_w = gw.get_color(w);

  if (clr_v == ivory && clr_w == ivory) return false;

  if (clr_v != clr_w && clr_v != ivory && clr_w != ivory) return false;

  if (clr_v == ivory) gw.set_color(v,clr_w);
  if (clr_w == ivory) gw.set_color(w,clr_v);

  return true;
}

bool start_move_node_handler(GraphWin& gw, node u)
{ graph& G = gw.get_graph();
  edge e;
  forall_edges(e,G) {
    if (gw.get_color(e) == EDGE_CLR_MISSING) 
      gw.del_edge(e);
    else
      gw.set_color(e,black);
  }

  gw.clear_shapes();
  gw.redraw();
  return true;
}

bool end_move_node_handler(GraphWin& gw, node v, const point & pos)
{ draw_gabriel(gw);
  return true;
}

void end_move_component_handler(GraphWin& gw, node v)
{ draw_gabriel(gw); }



int main()
{
  GraphWin gw("Gabriel Demo");

  gw.set_start_move_node_handler(start_move_node_handler);
  gw.set_end_move_node_handler(end_move_node_handler);

  gw.set_move_component_handler(start_move_node_handler);
  gw.set_move_component_handler(end_move_component_handler);

  gw.set_init_graph_handler(init_graph_handler);
  gw.set_new_edge_handler(new_edge_handler);
  gw.set_del_edge_handler(del_edge_handler);
  gw.set_new_node_handler(new_node_handler);
  gw.set_del_node_handler(del_node_handler);

  gw.set_new_edge_handler(pre_new_edge_handler);

  gw.set_directed(false);

  gw.set_action(A_LEFT | A_DRAG | A_FRAME,NULL);
  gw.set_action(A_LEFT | A_DRAG | A_EDGE,NULL);


  gw.set_node_label_type(user_label);

  gw.set_node_width(15);
  gw.set_node_height(15);
  gw.set_edge_width(1);
  gw.set_node_border_width(1);

  gw.set_zoom_objects(false);

  gw.display();


  node a = gw.new_node(point(100,200));
  gw.set_color(a,NODE_CLR_1);

  node b = gw.new_node(point(400,200));
  gw.set_color(b,NODE_CLR_2);

  gw.edit();

  return 0;
}

