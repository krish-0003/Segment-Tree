/*
Segment Tree which support 3 types of queries:
1) Increase each value using Arithmetic Progression in range [a,b] by starting from x.
3) Calculate the sum of values in range [a,b].
*/
#include "bits/stdc++.h"
using namespace std;
 
int n;
vector<long long> seg,base,inc,a;
 
void push(int l,int r,int id)
{
    seg[id] += (2LL*base[id]+(r-l-1LL)*inc[id])*(r-l)/2LL;
    
    if(l+1!=r)
    {
        int mid=(l+r)>>1,left=2*id+1,right=2*id+2;
 
        base[left]+=base[id];
        base[right]+=base[id]+(mid-l)*inc[id];
 
        inc[left]+=inc[id];
        inc[right]+=inc[id];
    }
    
    base[id]=inc[id]=0;
}
 
void pull(int id)
{
    int left=2*id+1,right=2*id+2;
    seg[id] = seg[left] + seg[right];
}
 
long long query(int ql,int qr,int l=0,int r=n,int id=0)
{
    push(l,r,id);
 
    if(ql>=r||l>=qr)
        return 0LL;
 
    if(ql<=l&&r<=qr)
        return seg[id];
 
    int mid=(l+r)>>1,left=2*id+1,right=2*id+2;
 
    return query(ql,qr,l,mid,left)+query(ql,qr,mid,r,right);
}
void update(int ql,int qr,int qbase,int qinc,int l=0,int r=n,int id=0)
{
    push(l,r,id);
 
    if(ql>=r||l>=qr)
        return;
    
    if(ql<=l&&r<=qr)
    {
        base[id]+=qbase+(l-ql)*qinc;
        inc[id]+=qinc;
        push(l,r,id);
        return;
    }
 
    int mid=(l+r)>>1,left=2*id+1,right=2*id+2;
 
    update(ql,qr,qbase,qinc,l,mid,left);
    update(ql,qr,qbase,qinc,mid,r,right);
 
    pull(id);
}
 
void build(int l=0,int r=n,int id=0)
{
    if(l+1==r)
    {
        seg[id]=a[l];return;
    }
    
    int mid=(l+r)>>1,left=2*id+1,right=2*id+2;
    
    build(l,mid,left);
    build(mid,r,right);
    
    pull(id);
}
 
int main()
{
    int q;
    cout << "Enter no. of nodes & no. of queries : ";
    cin>>n>>q;
    
    a.resize(n);
    
    for(int i=0;i<n;i++)
    {
        cout << "Enter a[" << i << "] : ";
        cin>>a[i];
    }
        
    
    seg.assign(4*n,0);
    base.assign(4*n,0);
    inc.assign(4*n,0);
 
    build();
 
    for(int o=0;o<q;o++)
    {
        cout << "-------------------------------------------------------\n";
        cout << "Test case - " << o << "\n";
        int type,l,r;
        cout << "Enter type(0 - query / 1 - update) & leftlimit & rightlimit :";
        cin>>type>>l>>r;
        l--;
        if(type==1)
        {
            update(l,r,1,1);
        }
        else 
        {
            cout<<"query("<<l<<","<<r<<") = "<<query(l,r)<<endl;
        }
    }
    return 0;
}