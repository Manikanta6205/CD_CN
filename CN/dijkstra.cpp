#include <bits/stdc++.h>
using namespace std;

#define pii pair<int,int>

int djsk(int st,int en,vector<vector<pii>> &adj){
    int n=adj.size();
    vector<int>dist(n,1e9);
    dist[st]=0;
    priority_queue<pii,vector<pii>,greater<pii>>pq;
    pq.push({0,st});
    while(!pq.empty()){
        auto[d,u]=pq.top();
        pq.pop();
        if(d>dist[u])continue;
        for(auto[v,w]:adj[u]){
            if(dist[v]>dist[u]+w){
                dist[v]=dist[u]+w;
                pq.push({dist[v],v});
            }
        }
    }
    return(dist[en]==1e9?-1:dist[en]);
}

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<pii>>adj(n);
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
    }
    int st,en;
    cin>>st>>en;
    int ans=djsk(st,en,adj);
    if(ans==-1)cout<<"No path exists"<<endl;
    else cout<<"shortest distance = "<<ans<<endl;
    return 0;
}
