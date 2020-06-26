#include <cassert>  
#include <class-tree.h>
#include <cool-tree.h>
#include <unordered_map>
#include <class-table.h>
#include <exceptions.h>

using namespace std;

#define MAP_CONTAINS(map, element) (map.find(element) != map.end())
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) >= (y)) ? (x) : (y))

// prototypes of helpers
static vector<pair<int, int>> convert_to_int_edges(vector<pair<Symbol, Symbol>>& edges);
static void create_nodes(Classes& classes, unordered_map<Symbol, ClassTree::Node*>& nodes);



void ClassTree::init(Classes classes, Symbol root_symbol)
{

  assert(!is_init);
  // declarations
  vector<pair<Symbol, Symbol>> edges;
  vector<Node*> euler_trip_nodes;
  
  // initialization
  construct_graph(classes, root_symbol, edges);
  check_for_cycles(edges);
  root->euler_walk(0, this->euler_trip, euler_trip_nodes);
  lubtree = new SegmentTree(euler_trip_nodes);
  compute_first_occurance();
  is_init = true;
}

void ClassTree::construct_graph(Classes classes, Symbol root_symbol, vector<pair<Symbol, Symbol>>& edges)
{   
    unordered_map<Symbol, Node*> nodes;
    create_nodes(classes, nodes);
    // set the root and size
    assert(MAP_CONTAINS(nodes, root_symbol));
    root = nodes[root_symbol];
    this->n = nodes.size();

    // adds child to the parent and creates a new edge
    for(int i = 0, n = classes->len(); i < n; i++)
    {
      Class_ class_ = classes->nth(i);
      Symbol name = class_->get_name();
      Symbol parent = class_->get_parent();

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

}

void ClassTree::check_for_cycles(vector<pair<Symbol, Symbol>>& edges)
{
    
  // because this is a tree constructed through 
  // single inheritance classes i.e every class has 
  // one parent except for the root, the number of nodes = number of edges + 1
  unsigned int n = edges.size() + 1;

  auto int_edges = convert_to_int_edges(edges);
  assert(int_edges.size() == edges.size());

  // Note: n includes the dummy _no_type symbol but it does not really matter as it 
  // does not add a cycle
  UnionFind uf(n);

  for(unsigned int i = 0; i < int_edges.size(); i++)
  {
      //cycle detected 
      if(!uf.disjoint(int_edges[i].first, int_edges[i].second))
      {
        throw CyclicClassException(edges[i].second);
      }
      uf.union_components(int_edges[i].first, int_edges[i].second);
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
static vector<pair<int, int>> convert_to_int_edges(vector<pair<Symbol, Symbol>>& edges)
{
    int cur_id = 0;
    unordered_map<Symbol, int> mapping;
    vector<pair<int, int>> int_edges;
    for(auto& p : edges)
    {
      if(!MAP_CONTAINS(mapping, p.first))
        mapping[p.first] = cur_id++;
      if(!MAP_CONTAINS(mapping, p.second))
        mapping[p.second] = cur_id++;
      pair<int, int> int_p(mapping[p.first], mapping[p.second]);
      int_edges.push_back(int_p);
    }
    return int_edges;
}



void ClassTree::create_nodes(Classes& classes, unordered_map<Symbol, ClassTree::Node*>& nodes)
{
  /* it is assumed at this point that classes have valid connections 
  (i.e all the referenced classes are defined) 
  and basic classes are installed*/

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

