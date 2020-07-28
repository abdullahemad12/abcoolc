#include <cassert>  
#include <unordered_map>
#include "cool-tree.h"
#include <type-table.h>
#include <class-tree.h>

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
  vector<ClassTree::Node*> euler_trip_nodes;
  
  // initialization
  construct_graph(classes, root_symbol, edges);
  root->euler_walk(0, this->euler_trip, euler_trip_nodes);
  lubtree = new SegmentTree(euler_trip_nodes);
  compute_first_occurance();
}

void ClassTree::construct_graph(Classes classes, Symbol root_symbol, vector<pair<Symbol, Symbol>>& edges)
{   
    unordered_map<Symbol, ClassTree::Node*> nodes;
    create_nodes(classes, nodes);
    // set the root and size
    assert(MAP_CONTAINS(nodes, root_symbol));
    this->root = nodes[root_symbol];
    this->n = nodes.size();
    nodes[No_class] = NULL;
    // adds child to the parent and creates a new edge
    for(int i = 0, n = classes->len(); i < n; i++)
    {
      Class_ class_ = classes->nth(i);
      Symbol name = class_->get_name();
      Symbol parent = class_->get_parent();
      // catch bugs
      assert(MAP_CONTAINS(nodes, name));
      
      if(nodes[parent] != NULL)
      {
        assert(MAP_CONTAINS(nodes, parent));
        nodes[parent]->children.push_back(nodes[name]);
        // create edge
        pair<Symbol, Symbol> p(parent, name);
        edges.push_back(p);
      } 
    }

}



void ClassTree::compute_first_occurance(void)
{
  for(int i = euler_trip.size() - 1; i >= 0; i--)
    euler_first[euler_trip[i]] = i;
}

Symbol ClassTree::lub(Symbol cur_class, Symbol type1, Symbol type2)
{
  assert(cur_class != SELF_TYPE);
  
  if(type1 == type2)
      return type1;

  // handle no_type
  if(type1 == No_type)
    return type2;
  else if (type2 == No_type)
    return type1;

  // handle self_type cases
  if(type1 == SELF_TYPE)
    type1 = cur_class;
    
  if(type2 == SELF_TYPE)
    type2 = cur_class;

  int min = MIN(euler_first[type1], euler_first[type2]);
  int max = MAX(euler_first[type1], euler_first[type2]);

  Node* node = lubtree->query(min, max);
  return node->class_symbol;
}

bool ClassTree::is_derived(Symbol cur_class, Symbol derived, Symbol base)
{
  // note no_type is treated as if it inherits from all the classes
  assert(cur_class != SELF_TYPE);
  return (base == derived) || 
         ((base != SELF_TYPE || derived == No_type) && (lub(cur_class, base, derived) == base));
}

void ClassTree::visit_all(ClassVisitor& visitor, TypeTable& type_table, Environment& env)
{
  root->visit_all(*this, visitor, type_table, env);
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



void ClassTree::Node::visit_all(ClassTree& ct, ClassVisitor& visitor, TypeTable& type_table, Environment& env)
{
    visitor.on_enter(class_, ct, type_table, env);

    visitor.visit(class_, ct, type_table, env);

    for(auto child : children)
      child->visit_all(ct, visitor, type_table, env);

    visitor.on_exit(class_, ct, type_table, env);
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
    nodes[cur_class->get_name()] = new Node(cur_class);
  }
}
