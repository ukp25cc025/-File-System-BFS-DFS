#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int visited[MAX];
int queue[MAX];
int n;

void BFS(int start) {
    int front = 0, rear = 0;

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    queue[rear++] = start;
    visited[start] = 1;

    printf("BFS traversal: ");
    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current);

        for (int i = 0; i < n; i++) {
            if (graph[current][i] && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

void DFS_Visit(int current) {
    visited[current] = 1;
    printf("%d ", current);

    for (int i = 0; i < n; i++) {
        if (graph[current][i] && !visited[i])
            DFS_Visit(i);
    }
}

void DFS(int start) {
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    printf("DFS traversal: ");
    DFS_Visit(start);
    printf("\n");
}

int searchBFS(int start, int target) {
    int front = 0, rear = 0;
    int seen[MAX] = {0};

    queue[rear++] = start;
    seen[start] = 1;

    while (front < rear) {
        int current = queue[front++];

        if (current == target)
            return 1;

        for (int i = 0; i < n; i++) {
            if (graph[current][i] && !seen[i]) {
                queue[rear++] = i;
                seen[i] = 1;
            }
        }
    }
    return 0;
}

void searchDFSVisit(int current, int target, int seen[], int *found) {
    if (*found)
        return;

    seen[current] = 1;
    if (current == target) {
        *found = 1;
        return;
    }

    for (int i = 0; i < n; i++) {
        if (graph[current][i] && !seen[i])
            searchDFSVisit(i, target, seen, found);
    }
}

int searchDFS(int start, int target) {
    int seen[MAX] = {0};
    int found = 0;
    searchDFSVisit(start, target, seen, &found);
    return found;
}

int main(void) {
    int start, target;

    printf("FILE SYSTEM GRAPH - BFS AND DFS\n");
    printf("Enter number of files/directories (1-%d): ", MAX);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of nodes.\n");
        return 1;
    }

    printf("Enter the adjacency matrix (%d x %d), using 0 or 1:\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &graph[i][j]) != 1 ||
                (graph[i][j] != 0 && graph[i][j] != 1)) {
                printf("Invalid matrix value. Use only 0 or 1.\n");
                return 1;
            }
        }
    }

    printf("Enter starting node (0 to %d): ", n - 1);
    if (scanf("%d", &start) != 1 || start < 0 || start >= n) {
        printf("Invalid starting node.\n");
        return 1;
    }

    printf("Enter target node to search (0 to %d): ", n - 1);
    if (scanf("%d", &target) != 1 || target < 0 || target >= n) {
        printf("Invalid target node.\n");
        return 1;
    }

    BFS(start);
    DFS(start);

    if (searchBFS(start, target))
        printf("Target node %d was found using BFS.\n", target);
    else
        printf("Target node %d was not found using BFS.\n", target);

    if (searchDFS(start, target))
        printf("Target node %d was found using DFS.\n", target);
    else
        printf("Target node %d was not found using DFS.\n", target);

    return 0;
}
