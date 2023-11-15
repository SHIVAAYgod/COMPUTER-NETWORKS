#include <bits/stdc++.h>
using namespace std;
#define MAX_ROUTER_CNT 1000
#define INF 1e9

int node, edge, v1, v2, cost;
vector<int> graph[MAX_ROUTER_CNT];

class RoutingTable {
	private:
		int** rt;
		int n, a;
	public:
		RoutingTable(){

		}

		RoutingTable(int router_number, int router_cnt){
			a = router_number;
			n = router_cnt;
			rt = new int*[n];
			for(int i=0; i<n; i++) rt[i] = new int[n];
			for(int i=0; i<n; i++){
				for(int j=0; j<n; j++){
					rt[i][j] = INF;
				}
			}
		}

		int get(int to, int via){
			return rt[to][via];
		}

		void add_node(int v1, int v2, int cost){
			assert(v1==a || v2==a);
			if(v1==a) rt[v2][v2] = cost;
			else rt[v1][v1] = cost;
		}

		void show(){
			cout<<"********** Routing Table for "<<a<<" *************\n";
			for(int i=0; i<n; i++){
				for(int j=0; j<n; j++){
					if(rt[i][j]<INF) 
						cout<<"From "<<a<<" to "<<i<<" via "<<j<<" cost: "<<rt[i][j]<<"\n";
				}
			}
		}

		void update(RoutingTable nrt){
			int via = nrt.a;
			int mini = rt[via][via];
			for(int intrm=0; intrm<n; intrm++){
				if(intrm!=a){
					mini = min(mini, rt[via][intrm]);
				}
			}
			for(int dest=0; dest<n; dest++){
				if(dest!=a){
					int mn = nrt.get(dest, dest);
					for(int intrm=0; intrm<n; intrm++) 
						if(intrm!=via) mn = min(mn, nrt.get(dest, intrm));
					rt[dest][via] = min(rt[dest][via], mini + mn);
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
	for(int i=0; i<edge; i++){
		cin>>v1>>v2>>cost;
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
		rt[v1].add_node(v1, v2, cost);
		rt[v2].add_node(v1, v2, cost);
	}
	cout<<"\n--------------- At Time T=0 ---------------\n";
	for(int i=0; i<node; i++) rt[i].show();
	for(int t=1; t<=node-1; t++){
		cout<<"\n--------------- At Time T="<<t<<" ---------------\n";
		for(int i=0; i<node; i++){
			for(int j: graph[i]){
				cout<<"* "<<j<<" sends its routing table to "<<i<<" *\n";
				rt[i].update(rt[j]);
			}
		}
		for(int i=0; i<node; i++) rt[i].show();
	}
	cout<<"\n*********************************\n";
	cout<<"End to end delay = "<<node-1<<" time units\n";
	cout<<"*********************************\n";
	return 0;
}

