#include <bits/stdc++.h>
using namespace std;

const int MAX_NODES = 30;
int n, e, v1, v2, s, d, pkt_cnt, pkt_sz;
vector<int> g[MAX_NODES];

struct PacketInfo{
	int curr, count_val, time_elapsed;
};

struct PacketParentInfo{
	int curr, count_val, time_elapsed, parent;
};

int bfs_all_lines(int src, int dest, int cnt){
	queue<PacketInfo> q;
	q.push({src, cnt, 0});
	cout<<"-------------------------------------------------\n";
	cout<<"Packet Leaves from "<<src<<" for destination "<<dest<<"\n";
	cout<<"-------------------------------------------------\n";
	while(!q.empty()){
		PacketInfo p = q.front();
		q.pop();
		if(p.curr==dest) return p.time_elapsed;
		if(p.count_val>1){
			for(int i: g[p.curr]){
				q.push({i, p.count_val-1, p.time_elapsed+1});
				cout<<"-------------------------------------------------\n";
				cout<<"Packet reaches "<<i<<" from "<<p.curr<<" at time "<<p.time_elapsed+1<<" with counter value "<<p.count_val-1<<"\n";
				cout<<"-------------------------------------------------\n";
			}
		}
	}
	return -1;
}

int bfs_except_incoming(int src, int dest, int cnt){
	queue<PacketParentInfo> q;
	q.push({src, cnt, 0, -1});
	cout<<"-------------------------------------------------\n";
	cout<<"Packet Leaves from "<<src<<" for destination "<<dest<<"\n";
	cout<<"-------------------------------------------------\n";
	while(!q.empty()){
		PacketParentInfo p = q.front();
		q.pop();
		if(p.curr==dest) return p.time_elapsed;
		if(p.count_val>1){
			for(int i: g[p.curr]){
				if(i!=p.parent){
					q.push({i, p.count_val-1, p.time_elapsed+1, p.curr});
					cout<<"-------------------------------------------------\n";
					cout<<"Packet reaches "<<i<<" from "<<p.curr<<" at time "<<p.time_elapsed+1<<" with counter value "<<p.count_val-1<<"\n";
					cout<<"-------------------------------------------------\n";
				}
			}
		}
	}
	return -1;
}

int main(){
	/*
	 * input: number of nodes, edges, topology, source, destination, packet counter
	 */
	cout<<"Enter the number of nodes: ";
	cin>>n;
	cout<<"Enter the number of edges: ";
	cin>>e;
	for(int i=0; i<e; i++){
		cout<<"Enter the two vertices of edge "<<i+1<<": ";
		cin>>v1>>v2;
		v1--;
		v2--;
		g[v1].push_back(v2);
		g[v2].push_back(v1);
	}
	cout<<"Enter source: ";
	cin>>s;
	cout<<"Enter destination: ";
	cin>>d;
	s--, d--;
	cout<<"Enter the packet counter initial value: ";
	cin>>pkt_cnt;
	cout<<"Enter packet size: ";
	cin>>pkt_sz;

	int time_elapsed;
	double bw;

	// flooding in all lines
	cout<<"********************Flooding all lines**********************\n";
	time_elapsed = bfs_all_lines(s, d, pkt_cnt);
	if(time_elapsed!=-1){
		cout<<"******************************************************\n";
		cout<<"One packet sent from source to destination\n";
		cout<<"Time elapsed: "<<time_elapsed<<"\n";
		bw = (double)pkt_sz / (double)time_elapsed;
		cout<<"Bandwidth: "<<bw<<"\n";
		cout<<"******************************************************\n";
	}
	else cout<<"The packet would never reach the destination\n";

	cout<<"**********************Flooding all line except incoming********************\n";
	time_elapsed = bfs_all_lines(s, d, pkt_cnt);
	if(time_elapsed!=-1){
		cout<<"******************************************************\n";
		cout<<"One packet sent from source to destination\n";
		cout<<"Time elapsed: "<<time_elapsed<<"\n";
		bw = (double)pkt_sz / (double)time_elapsed;
		cout<<"Bandwidth: "<<bw<<"\n";
		cout<<"******************************************************\n";
	}
	else cout<<"The packet would never reach the destination\n";

    return 0;
}

