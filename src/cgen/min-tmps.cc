#include <algorithm>
#include "cool-tree.h"

using namespace std;


int attr_class::mintmps()
{
    return init->mintmps();
}

int method_class::mintmps()
{
    return expr->mintmps();
}

int assign_class::mintmps()
{
    return expr->mintmps() + 1;
}

int static_dispatch_class::mintmps()
{
    int n, ans;
    
    ans = expr->mintmps();
    n = actual->len();
    for(int i = 0; i < n; i++)
        ans = max(actual->nth(i)->mintmps(), ans);
    
    return ans;
}

int dispatch_class::mintmps()
{
    int n, ans;
    ans = expr->mintmps();
    n = actual->len();
    for(int i = 0; i < n; i++)
        ans = max(actual->nth(i)->mintmps(), ans);

    return ans;   
}

int cond_class::mintmps()
{
  int ans;

  ans = pred->mintmps();
  ans = max(ans, then_exp->mintmps());
  ans = max(ans, else_exp->mintmps());

  return ans;
}

int loop_class::mintmps()
{
    int ans;

    ans = pred->mintmps();
    ans = max(ans, body->mintmps());

    return ans;
}

int typcase_class::mintmps()
{
    int ans, n;

    ans = expr->mintmps();
    n = cases->len();
    for(int i = 0; i < n; i++)
        ans = max(cases->nth(i)->mintmps(), ans);

    // ancestor table must be store somewhere 
    // object itself should be stored somewhere
    return ans + 2;
}

int branch_class::mintmps()
{
    return expr->mintmps();
}

int block_class::mintmps()
{
    int ans, n;
    ans = 0;
    n = body->len();
    for(int i = 0; i < n; i++)
        ans = max(ans, body->nth(i)->mintmps());
    return ans;
}

int let_class::mintmps()
{
    int ans;
    ans = init->mintmps();
    ans = max(ans, body->mintmps() + 1);

    return ans;
}

int plus_class::mintmps()
{
    return max(e1->mintmps(), e2->mintmps() + 1);
}

int sub_class::mintmps()
{
    return max(e1->mintmps(), e2->mintmps() + 1);
}

int mul_class::mintmps()
{
    return max(e1->mintmps(), e2->mintmps() + 1);
}

int divide_class::mintmps()
{
    return max(e1->mintmps(), e2->mintmps() + 1);
}

int neg_class::mintmps()
{
    return max(1, e1->mintmps());
}

int lt_class::mintmps()
{
    return max(e1->mintmps(), e2->mintmps() + 1);
}

int eq_class::mintmps()
{
    return max(e1->mintmps(), e2->mintmps() + 1);
}

int leq_class::mintmps()
{
    return max(e1->mintmps(), e2->mintmps() + 1);
}

int comp_class::mintmps()
{
    return e1->mintmps();
}

int int_const_class::mintmps()
{
    return 0;
}

int bool_const_class::mintmps()
{
    return 0;
}

int string_const_class::mintmps()
{
    return 0;
}

int new__class::mintmps()
{
    return 0;
}

int isvoid_class::mintmps()
{
    return e1->mintmps();
}

int no_expr_class::mintmps()
{
    return 0;
}

int object_class::mintmps()
{
    return 0;
}

