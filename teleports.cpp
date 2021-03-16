#include <stdio.h>
#include <stdlib.h>  // qsort
#include <vector>
#include <string.h>

struct Portal
{
    int u;
    int v;
    int weight;
};

int comparePortalsDesc(const void* p1, const void* p2) {
    struct Portal c1 = * ( (struct Portal *) p1 );
    struct Portal c2 = * ( (struct Portal *) p2 );

    if (c1.weight > c2.weight) return -1;
    if (c1.weight < c2.weight) return 1;
    else return 0;
}

void BFS(int prevVertex, int curVertex, std::vector<int>** adj, int* visited, int curSet) {
    if (!visited[curVertex]) {   
        visited[curVertex] = curSet;
        for (int i = 0; i < (int) (*adj)[curVertex].size(); i++) {
            if (prevVertex != -1) {
                if ((*adj)[curVertex][i] == prevVertex) {
                    continue;
                }
            }
            BFS(curVertex, (*adj)[curVertex][i], adj, visited, curSet);
        }
    }
}

bool isCapable(struct Portal** portals, int mid,const int* Mortys, int N, int M) {
    int maxWeight = (*portals)[mid].weight;
    int upTo = mid;
    while ((*portals)[++upTo].weight == maxWeight && upTo < M);
    
    std::vector<int>* adj = new std::vector<int>[N + 1];
    for (int i = 0; i < upTo; i++) {
        adj[(*portals)[i].u].push_back((*portals)[i].v);
        adj[(*portals)[i].v].push_back((*portals)[i].u);
    }
    int visited[N + 1];
    int curSet = 1;
    memset(visited, 0, sizeof(int) * (N + 1));
    for (int i = 0; i < N; i++) {
        if (Mortys[i] == i + 1 || ((visited[i+1] == visited[Mortys[i]]) && visited[i+1] != 0)) {
            continue;
        } else {
            BFS(-1, i + 1, &adj, visited, curSet++);
            if (!(visited[Mortys[i]] == visited[i+1])) {
                return false;
            }
        }
    }
    return true;
}

int main () {
    int N, M;
    scanf("%d %d", &N, &M);

    int Mortys[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &Mortys[i]);
    }

    struct Portal* portals = new struct Portal[M];
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &(portals[i].u), &(portals[i].v), &(portals[i].weight));
    }

    struct Portal a;
    qsort(portals, M, sizeof(a), comparePortalsDesc);

    int start = 0;
    int end = M;
    int answer = -1;
    while(start <= end) {
        int mid = (start + end) / 2;
        if (isCapable(&portals, mid, Mortys, N, M)) {
            end = mid -1;
            answer = mid;
        } else {
            start = mid + 1;
        }
    }

    if (answer == -1) {
        printf("WTF\n");
    } else {
        printf("%d\n", portals[answer].weight);
    }
}