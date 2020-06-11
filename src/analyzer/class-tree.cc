#include <cassert>  
#include "class-tree.h"


union_find::union_find(unsigned int n) : n(n)
{
    parents = new unsigned int[n];
    rank = new unsigned int[n];
    for(unsigned int i = 0; i < n; i++)
    {
        parents[i] = i;
        rank[i] = 1;
    }
}

union_find::~union_find()
{
    delete[] parents;
    delete[] rank;
}

unsigned int union_find::find(unsigned int i)
{
    unsigned int cur_parent = i;
    while(parents[cur_parent] != cur_parent)
    {
        cur_parent = parents[cur_parent];
    }
    
    parents[i] = cur_parent;
    
    return cur_parent;
}

bool union_find::disjoint(unsigned int i, unsigned int j)
{
    return find(i) != find(j);
}

void union_find::union_components(unsigned int i, unsigned int j)
{
    if(!disjoint(i, j))
    {
        return;
    }
    
    // at this point this will take constant time 
    unsigned int parentI = find(i);
    unsigned int parentJ = find(j);
    
    if(rank[parentI] < rank[parentJ])
    {
        parents[parentI] = parentJ;
    }
    else if(rank[parentI] > rank[parentJ])
    {
        parents[parentJ] = parentI;
    }
    else
    {
        parents[parentI] = parentJ;
        ++rank[parentI];
    }
}


lub_tree::lub_tree(std::vector<class_tree::node*> nodes) : n(nodes.size())
{
    // to be on the safe side, I will check that none of the nodes is NULL
    // this should not hurt the performance a lot
    for(unsigned int i = 0; i < nodes.size(); i++)
    {
        assert(nodes[i] != NULL);
    }
    
    tree = new class_tree::node*[4 * n];
    for(unsigned int i = 0, m = 4 * n; i < m; i++)
    {
        tree[i] = NULL;
    }
    construct_tree(nodes, 1, 0, n-1);
}

void lub_tree::construct_tree(std::vector<class_tree::node*> nodes, unsigned int curnode, 
				  unsigned int l, unsigned int r)
{
    if(l == r)
    {
        tree[curnode] = nodes[l]; 
        return;
    }
    
    unsigned int lchild = 2 * curnode, rchild = lchild + 1, mid = (l + r) / 2;
    construct_tree(nodes, lchild, l, mid);
    construct_tree(nodes, rchild, mid + 1, r);

    assert(tree[lchild] != NULL);
    assert(tree[rchild] != NULL);    
    class_tree::node* min = MIN_DEPTH_NODE(tree[lchild], tree[rchild]);
    tree[curnode] = min;
}

class_tree::node* lub_tree::query(unsigned int l, unsigned int r)
{
    assert(l >= 0);
    assert(r < n);
    return query(1, l, r, 0, n-1);
}

class_tree::node* lub_tree::query(unsigned int curnode, unsigned int l, unsigned int r, unsigned int tl, unsigned int tr)
{
    if(tl >= l && tr <= r)
    {
        return tree[curnode];
    }
    if(r < tl || l > tr)
    {
        return NULL;
    }
    unsigned int leftnode = 2 * curnode, rightnode = leftnode + 1, mid = (tl + tr) / 2;
    class_tree::node* ml = query(leftnode, l, r, tl, mid);
    class_tree::node* rl = query(rightnode, l, r, mid + 1, tr);
    assert(ml || rl); // one of them must not be NULL, otherwise a bug
    if(!ml)
    {
        return rl;
    }
    else if(!rl)
    {
        return ml;
    }
    else 
    {
        return MIN_DEPTH_NODE(ml, rl);
    }
}

lub_tree::~lub_tree()
{
	delete[] tree;
}
