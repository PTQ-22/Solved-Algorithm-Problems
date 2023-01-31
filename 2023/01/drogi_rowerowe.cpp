#include<bits/stdc++.h>
using namespace std;

constexpr int MAXN = 50'002;
vector<int> G[MAXN];
vector<int> TG[MAXN];
bitset<MAXN> vis;
vector<int> postorder;

int scc[MAXN];

void postDfs(int v)
{
	vis[v] = 1;
	for (int u : G[v])
		if (!vis[u]) 
			postDfs(u);
	postorder.push_back(v);
}

void trDfs(int v, int cnt)
{
	scc[v] = cnt;
	vis[v] = 1;
	for (int u : TG[v])
		if (!vis[u]) 
			trDfs(u, cnt);
}


void dpDfs(vector<int>& dp, int v, vector<set<int>>& sG, vector<int>& ssc_size)
{
	vis[v] = 1;
	for (int u : sG[v]) {
		if (!vis[u]) dpDfs(dp, u, sG, ssc_size);
	}
	
	for (int u : sG[v]) {
		dp[v] += dp[u];
	}
	dp[v] += ssc_size[v];
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	int n, m;
	cin >> n >> m;
	
	int a, b;
	while(m--)
	{
		cin >> a >> b;
		G[a].push_back(b);
		TG[b].push_back(a);
	}
	
	for (int i = 1; i <= n; ++i)
		if (!vis[i])
			postDfs(i);
	
	vis.reset();
	reverse(postorder.begin(), postorder.end());
	
	int cnt = 0;
	for (int i : postorder) 
		if (!vis[i]) 
			trDfs(i, ++cnt);
	
	vector<int> scc_size(cnt + 1);
	for (int i = 1; i <= n; ++i) {
		scc_size[scc[i]]++;
	}
	
	vector<set<int>> scc_children(cnt + 1);
	for (int i = 1; i <= n; ++i) {
		for (int v : G[i]) {
			if (scc[v] != scc[i]) {
				scc_children[scc[i]].insert(scc[v]);
			}
		}
	}
	vector<int> dp(cnt + 1);
	vis.reset();
	for (int i = 1; i <= cnt; ++i) {
		if (!vis[i]) dpDfs(dp, i, scc_children, scc_size);
	}
	for (int i = 1; i <= n; ++i) {
		cout << dp[scc[i]] - 1 << '\n';
	}
	
	return 0;
}