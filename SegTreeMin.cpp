/*
Segment Tree which support 3 types of queries:
1) Increase each value in range [a,b] by x.
2) Set each value in range [a,b] to x.
3) Calculate the min of values in range [a,b].
*/
#include "bits/stdc++.h"
using namespace std;

vector<int> seg, lazy, a;
vector<bool> isset;
int n = 8;

void propogate(int l, int r, int id)
{
    if (isset[id])
    {
        seg[id] = lazy[id];
    }
    else
        seg[id] += lazy[id];
    if (l + 1 != r)
    {
        int mid = (l + r) >> 1LL, left = 2 * id + 1, right = 2 * id + 2;
        if (isset[id])
        {
            lazy[left] = lazy[right] = lazy[id];
            isset[left] = isset[right] = 1;
        }
        else
        {
            lazy[left] += lazy[id];
            lazy[right] += lazy[id];
        }
    }
    lazy[id] = 0;
    isset[id] = 0;
}

int query(int ql, int qr, int l = 1, int r = n + 1, int id = 0)
{
    propogate(l, r, id);
    if (ql >= r || l >= qr)
    {
        return INT_MAX;
    }
    if (ql <= l && r <= qr)
    {
        return seg[id];
    }
    int mid = (l + r) >> 1LL, left = 2 * id + 1, right = 2 * id + 2;
    int l1 = query(ql, qr, l, mid, left), r1 = query(ql, qr, mid, r, right);
    return min(l1, r1);
}

void update(int ql, int qr, int val, bool st, int l = 1, int r = n + 1, int id = 0)
{
    propogate(l, r, id);
    if (ql >= r || l >= qr)
    {
        return;
    }
    assert(lazy[id] == 0);
    if (ql <= l && r <= qr)
    {
        isset[id] = st;
        lazy[id] = val;
        propogate(l, r, id);
        return;
    }
    int mid = (l + r) >> 1LL, left = 2 * id + 1, right = 2 * id + 2;
    update(ql, qr, val, st, l, mid, left);
    update(ql, qr, val, st, mid, r, right);
    seg[id] = min(seg[left], seg[right]);
}

void build(int l = 1, int r = n + 1, int id = 0)
{
    if (l + 1 == r)
    {
        seg[id] = a[l];
        return;
    }
    int mid = (l + r) >> 1LL, left = 2 * id + 1, right = 2 * id + 2;
    build(l, mid, left);
    build(mid, r, right);
    seg[id] = min(seg[left], seg[right]);
}
void printnode(int id, int l, int r, int space = 0)
{
    for (int i = 0; i < space; i++)
        cout << " ";
    cout << "[" << l << "," << r << ")-||" << seg[id] << "|" << isset[id] << "|" << lazy[id] << "||";
    for (int i = 0; i < space; i++)
        cout << " ";
}
void line(int lim)
{
    for (int i = 0; i < lim; i++)
        cout << "-";
    cout << endl;
}
void display()
{
    line(150);
    line(150);
    cout << "Virtual Array is as follows:\n";
    for (int i = 1; i <= n; i++)
        cout << a[i] << " ";
    cout << endl;
    cout << "Node is : [l,r)-||seg|isset|lazy||\n";
    line(150);
    cout << endl;
    {
        printnode(0, 1, 9, 65);
        cout << endl
             << endl;
    }
    {
        printnode(1, 1, 5, 28);
        printnode(2, 5, 9, 28);
        cout << endl
             << endl
             << endl;
    }
    {
        printnode(3, 1, 3, 10);
        printnode(4, 3, 5, 10);
        printnode(5, 5, 7, 10);
        printnode(6, 7, 9, 10);
        cout << endl
             << endl
             << endl;
    }
    {
        printnode(7, 1, 2, 1);
        printnode(8, 2, 3, 1);
        printnode(9, 3, 4, 1);
        printnode(10, 4, 5, 1);
        printnode(11, 5, 6, 1);
        printnode(12, 6, 7, 1);
        printnode(13, 7, 8, 1);
        printnode(14, 8, 9, 1);
        cout << endl;
    }
    line(150);
    line(150);
}
int main()
{
    seg.resize(4 * (n + 1), 0);
    lazy.resize(4 * (n + 1), 0);
    isset.resize(4 * (n + 1), 0);
    a.resize(n + 1, 0);

    for (int i = 1; i <= n; i++)
        a[i] = rand() % 15 + 1;

    build();
    display();
    cout << "update(1,6,2,0)->Increase each value in range [1,6) by 2\n";
    {
        for (int i = 1; i < 6; i++)
            a[i] += 2;
    }
    update(1, 6, 2, 0);
    display();
    cout << "update(3,8,12,1)->Set each value in range [3,8) to 12\n";
    {
        for (int i = 3; i < 8; i++)
            a[i] = 12;
    }
    update(3, 8, 12, 1);
    display();
    cout << "Query(2,9)->Calculate min value in range [2,9) = " << query(2, 9) << endl;
}