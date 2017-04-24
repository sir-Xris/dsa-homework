// `Accepted' Oriented Program
// Implemented By Xris
// 来打我呀

#include <cctype>
#include <cstdio>
#include <algorithm>
#include <list>
using namespace std;

struct edge {
	int u, v, w;
	edge() = default;
	edge(int u, int v, int w): u(u), v(v), w(w) {}
	bool operator<(const edge &e) {
		return this->w < e.w;
	}
};

size_t n, m;
char nodename[20];
edge edges[25];
list<edge> adjacency[20];
char u, v; int w;
int set[20];

int find(int x) {
	if (x == set[x]) return x;
	return set[x] = find(set[x]);
}

void unite(int x, int y) {
	set[find(y)] = find(x);
}

bool same(int x, int y) {
	return find(x) == find(y);
}

int kruskal() {
	int treeweight = 0;
	sort(edges, edges + m);
	for (size_t i = 0; i != n; ++i) set[i] = i;
	size_t cur = 0;
	for (size_t i = 0; i != n - 1; ++i) {
		while (same(edges[cur].u, edges[cur].v) && cur < m) ++cur;
		if (cur == m) {
			puts("the graph is not connected");
			exit(EXIT_FAILURE);
		}
		int u = edges[cur].u, v = edges[cur].v, w = edges[cur].w;
		unite(u, v);
		printf("%c-->%c %d\n", nodename[u], nodename[v], w);
		treeweight += w;
	}
	return treeweight;
}

int main() {
	puts("顶点输入：");
	while (true) {
		printf("NO %2zd: ", n + 1);
		nodename[n] = getchar();  // flush input
		while (getchar() != '\n');
		if (nodename[n] == '*') break;
		++n;
	}
	puts("边输入：input u    v    w");
	while (true) {
		printf("              ");
		int u, v, w;
		while (isspace(u = getchar()));
		while (isspace(v = getchar()));
		scanf("%d", &w);
		if (u == '*' && v == '*' && !w) break;
		for (size_t i = 0; i != n; ++i)
			if (nodename[i] == u) { u = i; break; }
		for (size_t i = 0; i != n; ++i)
			if (nodename[i] == v) { v = i; break; }
		edges[m] = edge(u, v, w);
		adjacency[u].push_back(edges[m]);
		adjacency[v].push_back(edges[m]);
		++m;
	}
	puts("adjlist:");
	for (size_t i = 0; i != n; ++i) {
		printf("NO %2zd:  %c", i + 1, nodename[i]);
		for (auto &it: adjacency[i]) {
			size_t to = i ^ it.u ^ it.v;
			printf("-->%c(%d)", nodename[to], it.w);
		}
		putchar('\n');
	}
	puts("minispantree");
	printf("total lowcost: %d\n", kruskal());
	return 0;
}

