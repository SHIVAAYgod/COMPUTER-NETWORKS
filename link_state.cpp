#include <bits/stdc++.h>
using namespace std;
#define MAX_ROUTER_CNT 1000
#define INF 1e9

int node, edge, v1, v2, cost;
int graph[MAX_ROUTER_CNT][MAX_ROUTER_CNT];

class RoutingTable {
	private:
		int *rt, *par;
		int n, a;
	public:
		RoutingTable(){

		}

		RoutingTable(int router_number, int router_cnt){
			a = router_number;
			n = router_cnt;
			rt = new int[n];
			par = new int[n];
			for(int i=0; i<n; i++) rt[i] = INF;
			for(int i=0; i<n; i++) par[i] = -1;
		}


		void update(){
			// dijkstra algorithm
			for(int i=0; i<n; i++) rt[i] = INF;
			rt[a] = 0;
			int visited[n];
			fill_n(visited, n, false);
			priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
			pq.push({0, a});
			while(!pq.empty()){
				pair<int, int> p = pq.top();
				pq.pop();
				visited[p.second] = true;
				for(int i=0; i<n; i++){
					if(!visited[i] && p.first+graph[p.second][i]<rt[i]){
						rt[i] = p.first+graph[p.second][i];
						par[i] = p.second;
						pq.push({rt[i], i});
					}
				}
			}
		}

		void show(){
			cout<<"*********** Routing Table for "<<a<<" **************\n";
			for(int i=0; i<n; i++){
				if(i!=a && rt[i]<INF){
					int next = i;
					while(par[next]!=a) next = par[next];
					cout<<"From "<<a<<" to "<<i<<" next: "<<next<<" cost: "<<rt[i]<<"\n";
				}
			}
		}
};

int main(){
	cout<<"Enter the number of routers: ";
	cin>>node;
	RoutingTable* rt = new RoutingTable[node];
	for(int i=0; i<node; i++){
		rt[i] = RoutingTable (i, node);
	}
	cout<<"Enter the number of edges: ";
	cin>>edge;
	cout<<"Enter "<<edge<<" edges in (vertex1 vertex2 cost) format: \n";
	for(int i=0; i<node; i++){
		for(int j=0; j<node; j++){
			int val = (i==j ? 0 : INF);
			graph[i][j] = val;
		}
	}
	for(int i=0; i<edge; i++){
		cin>>v1>>v2>>cost;
		graph[v1][v2] = cost;
		graph[v2][v1] = cost;
	}
	cout<<"\n--------------- Initially ---------------\n";
	for(int i=0; i<node; i++){
		cout<<"*********** Routing Table for "<<i<<" **************\n";
		for(int j=0; j<node; j++){
			if(i!=j && graph[i][j]<INF){
				cout<<"From "<<i<<" to "<<j<<" next: NIL"<<" cost: "<<graph[i][j]<<"\n";
			}
		}
	}
	cout<<"\n*************** All routers flood their routing tables ***************\n\n";
	for(int i=0; i<node; i++){
		rt[i].update();
		rt[i].show();
	}
	cout<<"\n*******************************************\n";
	cout<<"End to end delay = diameter of graph + constant time units\n";
	cout<<"*******************************************\n";
	return 0;
}
