#include <bits/stdc++.h>

using namespace std;

class RoutingTable{
    private:
        int *dist;
        int numberOfNodes;
        vector<vector<int> >*path;

    public:
        RoutingTable(){

        }

        RoutingTable(int numberOfNodes) :numberOfNodes(numberOfNodes){
            dist = new int[numberOfNodes];
            for(int i=0;i<numberOfNodes;i++)
                dist[i] = INT32_MAX;
            path = new vector<vector<int> >(numberOfNodes);
        }

        vector<int>& getPath(int node){
            return (*path)[node];
        }

        int getDistance(int node){
            return dist[node];
        }

        void setDistance(int node,int distance){
            dist[node] = distance;
        }

        void print(){
            for(int i=0;i<numberOfNodes;i++){
                cout<<"Distance to "<<i<<" is "<<(dist[i] == INT32_MAX ? "INFINITY" : to_string(dist[i]))<<" and path is ";
                for(int j: (*path)[i])
                    cout<<j<<" ";
                cout<<endl;
            }
        }

        void setPath(int node,vector<int>& newPath){
            (*path)[node] = newPath;
        }

        ~RoutingTable(){
            delete dist;
            delete path;
        }
};

class Network{
    private:
        int numberOfNodes;
        map<int,vector<pair<int,int> > >adjacencyList;
        bool *working;
        RoutingTable **routingTables;
        public: 
        void ShortestDistance(int source,int destination){
            vector<int>parent(numberOfNodes);
            for(int i=0;i<numberOfNodes;i++)
                parent[i] = -1;
            set<pair<int,int> >distance;
            map<int,int>dist;
            for(int node=0;node<numberOfNodes;node++)
                dist[node] = INT32_MAX;
            dist[source] = 0;
            distance.insert({0,source});

            while(!distance.empty()){
                int currentNode = (*distance.begin()).second;
                for(pair<int,int> adjacentNodeDetails: adjacencyList[currentNode]){
                    int adjNode = adjacentNodeDetails.first;
                    int adjNodeDist = adjacentNodeDetails.second;
                    if((dist[currentNode] + adjNodeDist < dist[adjNode])){
                        if(distance.find({dist[adjNode],adjNode}) != distance.end())
                            distance.erase(distance.find({dist[adjNode],adjNode}));
                        dist[adjNode] = dist[currentNode] + adjNodeDist;
                        distance.insert({dist[adjNode],adjNode});
                        parent[adjNode] = currentNode;
                    }
                }
                distance.erase(distance.begin());
            }
            
            vector<int> path;
            if(parent[destination] == -1)
                return;
            int aux = destination;
            while(destination!=source){
                path.push_back(destination);
                destination = parent[destination];
            }
            path.push_back(source);
            reverse(path.begin(),path.end());
            routingTables[source]->setPath(aux,path);
            routingTables[source]->setDistance(aux,dist[aux]);
        }

    public:
        Network(int numberOfNodes): numberOfNodes(numberOfNodes){

                working = new bool[numberOfNodes];
                for(int i=0; i<numberOfNodes ; i++)
                    working[i] = true;              
                routingTables = new RoutingTable*[numberOfNodes];
                for(int node =0 ; node< numberOfNodes; node++)
                    routingTables[node] = new RoutingTable(numberOfNodes);
        }

        void addEdge(int first, int second, int distance){
            adjacencyList[first].push_back({second,distance});
            adjacencyList[second].push_back({first,distance});
        }

        void alterWorkingNode(int node){
            working[node] = !working[node];
        }

        void updateRoutingTable(){
            for(int src=0; src<numberOfNodes; src++){
                for(int dest=0;dest<numberOfNodes;dest++){
                    ShortestDistance(src,dest);
                }
            }
        }

        void displayRoutingTable(){
            for(int i=0; i<numberOfNodes; i++){
                cout<<"Routing Table for "<<i<<endl;
                routingTables[i]->print();
            }
        }

        ~Network(){
            for(int node = 0; node<numberOfNodes; node++){
                delete routingTables[node];
            }
            delete routingTables;
            delete working;
        }

};

int main(){
    int nodes; 
    int edges;
	cout<<"Enter the number of nodes and edges: ";
    cin>>nodes>>edges;
    Network network(nodes);
    while(edges--){
        int a,b,c;
		cout<<"Enter vertices of edges and the weight of the edge: ";
        cin>>a>>b>>c;
        network.addEdge(a,b,c);
    }
    network.updateRoutingTable();
    network.displayRoutingTable();
}
