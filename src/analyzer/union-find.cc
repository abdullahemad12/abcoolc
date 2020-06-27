#include <cassert>  
#include <cool-tree.h>
#include <union-find.h>

UnionFind::UnionFind(Classes classes) : n(classes->len())
{
    parents = new unsigned int[n];
    rank = new unsigned int[n];
    for(unsigned int i = 0; i < n; i++)
    {
        parents[i] = i;
        rank[i] = 1;
        mapping[classes->nth(i)->get_name()] = i;

    }
}

UnionFind::~UnionFind()
{
    delete[] parents;
    delete[] rank;
}

unsigned int UnionFind::find(unsigned int i)
{
    unsigned int cur_parent = i;
    while(parents[cur_parent] != cur_parent)
    {
        cur_parent = parents[cur_parent];
    }
    
    parents[i] = cur_parent;
    
    return cur_parent;
}

bool UnionFind::disjoint(unsigned int i, unsigned int j)
{
    return find(i) != find(j);
}

void UnionFind::union_components(unsigned int i, unsigned int j)
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

bool UnionFind::disjoint(Symbol class1, Symbol class2)
{
    return disjoint(mapping[class1], mapping[class2]);
}


void UnionFind::union_components(Symbol class1, Symbol class2)
{
    union_components(mapping[class1], mapping[class2]);
}