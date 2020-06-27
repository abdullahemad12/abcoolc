#include <cassert>  
#include <class-tree.h>
#include <cool-tree.h>
#include <unordered_map>
#include <type-table.h>

using namespace std;

#define MAP_CONTAINS(map, element) (map.find(element) != map.end())
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) >= (y)) ? (x) : (y))

// prototypes of helpers
static void create_nodes(Classes& classes, unordered_map<Symbol, ClassTree::Node*>& nodes);
void add_child_parent_edge(unordered_map<Symbol, ClassTree::Node*>& nodes, Symbol name, Symbol parent);


/* it is assumed at this point that classes have valid connections 
(i.e all the referenced classes are defined) 
and basic classes are installed*/

ClassTree::ClassTree(Classes classes, Symbol root_symbol)
{
  initialize_constants();
  
  // declarations
  vector<pair<Symbol, Symbol>> edges;
  vector<Node*> euler_trip_nodes;
  
  // initialization
  construct_graph(classes, root_symbol, edges);
  root->euler_walk(0, this->euler_trip, euler_trip_nodes);
  lubtree = new SegmentTree(euler_trip_nodes);
  compute_first_occurance();
}

void ClassTree::construct_graph(Classes classes, Symbol root_symbol, vector<pair<Symbol, Symbol>>& edges)
{   
    unordered_map<Symbol, Node*> nodes;
    create_nodes(classes, nodes);
    // set the root and size
    assert(MAP_CONTAINS(nodes, root_symbol));
    this->root = nodes[root_symbol];
    this->n = nodes.size();
    nodes[No_class] = NULL;
    // adds child to the parent and creates a new edge
    for(int i = 0; i < n; i++)
    {
      Class_ class_ = classes->nth(i);
      add_child_parent_edge(nodes, class_->get_name(), class_->get_parent());
    }

}



void ClassTree::compute_first_occurance(void)
{
  for(int i = euler_trip.size() - 1; i >= 0; i--)
    euler_first[euler_trip[i]] = i;
}

Symbol ClassTree::lub(Symbol type1, Symbol type2)
{
  int min = MIN(euler_first[type1], euler_first[type2]);
  int max = MAX(euler_first[type1], euler_first[type2]);

  Node* node = lubtree->query(min, max);
  return node->class_symbol;
}

bool ClassTree::is_derived(Symbol derived, Symbol base)
{
  Symbol self_type = idtable.add_string("SELF_TYPE");
  // self type as base is always false
  return ((base != self_type) || (base == derived)) && (lub(base, derived)) == base;
}

ClassTree::~ClassTree(void)
{
  delete root;
  delete lubtree;
}

void ClassTree::Node::euler_walk(unsigned int depth, vector<Symbol>& trip, vector<Node*>& nodes_trip)
{
  this->depth = depth;
  trip.push_back(this->class_symbol);
  nodes_trip.push_back(this);
  for(auto child : children)
  {
    child->euler_walk(depth + 1, trip, nodes_trip);
    trip.push_back(this->class_symbol);
    nodes_trip.push_back(this);
  }
}

ClassTree::Node::~Node(void)
{
  for(Node* child : children)
    delete child;
}


/*******************
 *      Helpers    *
 *******************/
void ClassTree::create_nodes(Classes& classes, unordered_map<Symbol, ClassTree::Node*>& nodes)
{
  // set this to NULL so the parent of object is NULL
  Symbol no_type_symb = idtable.add_string(no_type);
  nodes[no_type_symb] = NULL;
  int n = classes->len();
  for(int i = 0; i < n; i++)
  {
    Class_ cur_class = classes->nth(i);
    Symbol name = cur_class->get_name();
    assert(!MAP_CONTAINS(nodes, name));
    nodes[name] = new Node(name);
  }
}

void add_child_parent_edge(unordered_map<Symbol, ClassTree::Node*>& nodes, Symbol name, Symbol parent)
{
  // catch bugs
    assert(MAP_CONTAINS(nodes, name));
    assert(MAP_CONTAINS(nodes, parent));
    
    if(nodes[parent] != NULL)
    {
      nodes[parent]->children.push_back(nodes[name]);
      // create edge
      pair<Symbol, Symbol> p(parent, name);
      edges.push_back(p);
    } 
}