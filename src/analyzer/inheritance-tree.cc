#include <cassert>  
#include "inheritance-tree.h"

using namespace std;

union_find::union_find(int n) : n(n)
{
    parents = new int[n];
    rank = new int[n];
    for(int i = 0; i < n; i++)
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

int union_find::find(int i)
{
    int cur_parent = i;
    while(parents[cur_parent] != cur_parent)
    {
        cur_parent = parents[cur_parent];
    }
    
    parents[i] = cur_parent;
    
    return cur_parent;
}

bool union_find::disjoint(int i, int j)
{
    return find(i) != find(j);
}

void union_find::union_components(int i, int j)
{
    if(!disjoint(i, j))
    {
        return;
    }
    
    // at this point this will take constant time 
    int parentI = find(i);
    int parentJ = find(j);
    
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


segment_tree::segment_tree(vector<inheritance_tree::node*> nodes) : n(nodes.size()), nodes(nodes)
{
    // to be on the safe side, I will check that none of the nodes is NULL
    // this should not hurt the performance a lot
    for(unsigned int i = 0; i < nodes.size(); i++)
    {
        assert(nodes[i] != NULL);
    }
    
    tree = new inheritance_tree::node*[4 * n];
    for(int i = 0, m = 4 * n; i < m; i++)
    {
        tree[i] = NULL;
    }
    construct_tree(1, 0, n-1);
}

void segment_tree::construct_tree(int curnode, int l, int r)
{
    if(l == r)
    {
        tree[curnode] = nodes[l]; 
        return;
    }
    
    int lchild = 2 * curnode, rchild = lchild + 1, mid = (l + r) / 2;
    construct_tree(lchild, l, mid);
    construct_tree(rchild, mid + 1, r);

    assert(tree[lchild] != NULL);
    assert(tree[rchild] != NULL);    
    inheritance_tree::node* min = MIN_DEPTH_NODE(tree[lchild], tree[rchild]);
    tree[curnode] = min;
}

inheritance_tree::node* segment_tree::query(int l, int r)
{
    assert(l >= 0);
    assert(r < n);
    return query(1, l, r, 0, n-1);
}

inheritance_tree::node* segment_tree::query(int curnode, int l, int r, int tl, int tr)
{
    if(tl >= l && tr <= r)
    {
        return tree[curnode];
    }
    if(r < tl || l > tr)
    {
        return NULL;
    }
    int leftnode = 2 * curnode, rightnode = leftnode + 1, mid = (tl + tr) / 2;
    inheritance_tree::node* ml = query(leftnode, l, r, tl, mid);
    inheritance_tree::node* rl = query(rightnode, l, r, mid + 1, tr);
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
