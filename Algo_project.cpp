#include<bits/stdc++.h>
using namespace std;
#define N 100


void print_map(int map[], int i){   // To print the map from source vertex to destination vertex
    if(map[i] == -1){
        return;
    }

    print_map(map,map[i]);
    cout << i << " ";
}

void dijkstra(int dis[][N], int src, int dst,int m){
    vector<int> srt_dis(m);                            // To store the shortest distance of vertex from source vertex
    vector<bool> vis(m,false);                          // To check vertex is visited or not
    int map[m];                                          // To store the map from source vertex to destination vertex
    map[src] = -1;

    int inf = INT_MAX;

    for(int i = 0; i< m; i++)                     // Initializing all indicies of srt_dis array as infinity
        srt_dis[i] = inf;
    srt_dis[src] = 0;                           // Initializing index of source vertex in srt_dis as zero

    for(int i = 0; i < m-1; i++){

        int min_dis = inf,r_idx = 0;

        for(int j = 0; j < m; j++){
            if(vis[j] == false && srt_dis[j] <= min_dis){
                min_dis = srt_dis[j];
                r_idx = j;
            }
        }

        vis[r_idx] = true;

        for(int j = 0; j < m; j++){
            if(vis[j] == false && dis[r_idx][j] != 0 && srt_dis[r_idx] != INT_MAX){
                if(srt_dis[r_idx] + dis[r_idx][j] < srt_dis[j]){
                    srt_dis[j] = srt_dis[r_idx] + dis[r_idx][j];
                    map[j] = r_idx;
                }
            }
        }

    }

    cout << endl;
    cout << "Minimum distance from city " << src << " to city " << dst <<": " << srt_dis[dst] << endl;
    cout << "Path from city " << src << " to city " << dst << ": ";
    cout << src << " ";
    print_map(map,dst);

}

int main()
{
    int n;
    cout << "Write the number of cities: ";
    cin >> n;
    vector<vector<int>> adj(n+1);
    cout << "Write -1 to indicate the end of neighbors" << endl;
    int y;
    for(int i = 1; i < n+1; i++){
        cout << "Write neighbours of city in ascending order" << i << ": ";
        while(1){
            cin >> y;
            if(y == -1)
                break;
            adj[i].push_back(y);
        }
    }
    int weight[N][N];                          // To store the weight of edges
    for(int i = 0; i < n+1; i++){
        for(int j = 0; j < n+1; j++){
            weight[i][j] = 0;
        }
    }
    for(int i = 1; i < n+1; i++){
        for(auto j: adj[i]){
            if(j > i){
                cout << "Enter distance(in km) between city {" << i << "," << j << "}: ";
                cin >> weight[i][j];
                weight[j][i] = weight[i][j];
            }
        }
    }
    int src = 0;
    cout << "Write the city in which delivery firm is located: ";
    cin >> src;
    int dst = 0;
    cout << "Write destination city: ";
    cin >> dst;

    dijkstra(weight,src,dst,n+1);
    return 0;
}

