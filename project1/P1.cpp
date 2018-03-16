#include <bits/stdc++.h>
#include <algorithm>
using namespace std;


#define UNVISITED -1
#define INF numeric_limits<int>::max()

vector<vector<int> > G;
vector<int> num, low, S, visited, sccG;
int SCC, N, M, dfsNC,f = 1,connected;
typedef vector <int>::iterator vi;
unordered_map<int,int> small;

void tarjan(int u) {
  low[u] = num[u] = dfsNC++;
  S.push_back(u);
  visited[u] = 1;
  for (int j = 0; j < (int)G[u].size(); j++) {
    int v = G[u][j];
    if (num[v] == UNVISITED) {
			tarjan(v);
		}

    if (visited[v])
			low[u] = min(low[u], low[v]);
  }

  if (low[u] == num[u]) {
    SCC++;
		int min = INF;
    while (1) {
      int v = S.back();
      S.pop_back();
      visited[v] = 0;
			sccG[v] = SCC;
			min = v < min ? v : min;
      if (u == v) {
				small.insert(make_pair(SCC,min));
				break;
			}
    }
  } 
}

int main() {
  scanf("%d", &N);
  scanf("%d", &M);

  G = vector<vector<int> >(N + 1, vector<int>());
  visited = vector<int>(N + 1, 0);
  num = vector<int>(N + 1, UNVISITED);
  low = vector<int>(N + 1, 0);
	sccG = vector<int>(N + 1, -1);

  for (int i = 0; i < M; i++) {
    int x, y;
    scanf("%d %d", &x, &y);
    G[x - 1].push_back(y - 1);
  }
  for (int i = 0; i < N; i++)
    if (num[i] == UNVISITED) 
			tarjan(i);

	cout << SCC << endl;
	set<pair<int,int> > connections;
	for (int u = 0; u < N; u++)
    for (vi v = G[u].begin(); v != G[u].end(); v++) 
			if(sccG[*v] != sccG[u]){
				connections.insert(make_pair(small.find(sccG[u])->second + 1,small.find(sccG[*v])->second + 1));
			}

	cout << connections.size() << endl;
	for (auto elem : connections) {
		cout << elem.first << " " << elem.second << endl;
	}
	
  return 0;
}