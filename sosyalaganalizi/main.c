#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_FRIENDS 20

typedef struct User {
    int id;
    int friends[MAX_FRIENDS];
    int friend_count;
} User;

typedef struct {
    User users[MAX_USERS];
    int user_count;
} Graph;

typedef struct BSTNode {
    int id;
    struct BSTNode *left, *right;
} BSTNode;

Graph g;
BSTNode* root = NULL;

// Kullanýcý iþlemleri
void add_user(int id) {
    g.users[g.user_count].id = id;
    g.users[g.user_count].friend_count = 0;
    g.user_count++;
}

User* find_user(int id) {
    for (int i = 0; i < g.user_count; i++)
        if (g.users[i].id == id) return &g.users[i];
    return NULL;
}

void add_friend(int id1, int id2) {
    User *u1 = find_user(id1), *u2 = find_user(id2);
    if (u1 && u2) {
        u1->friends[u1->friend_count++] = id2;
        u2->friends[u2->friend_count++] = id1;
    }
}

// Basit BST iþlemleri
BSTNode* insert_bst(BSTNode* node, int id) {
    if (!node) {
        BSTNode* temp = (BSTNode*)malloc(sizeof(BSTNode));
        temp->id = id; temp->left = temp->right = NULL;
        return temp;
    }
    if (id < node->id) node->left = insert_bst(node->left, id);
    else node->right = insert_bst(node->right, id);
    return node;
}

BSTNode* search_bst(BSTNode* node, int id) {
    if (!node || node->id == id) return node;
    if (id < node->id) return search_bst(node->left, id);
    return search_bst(node->right, id);
}

// DFS ile belirli mesafedeki arkadaþlar
void dfs(int idx, int depth, int target, int* visited) {
    if (depth == target) {
        printf("%d ", g.users[idx].id);
        return;
    }
    visited[idx] = 1;
    for (int i = 0; i < g.users[idx].friend_count; i++) {
        int friend_id = g.users[idx].friends[i];
        for (int j = 0; j < g.user_count; j++) {
            if (g.users[j].id == friend_id && !visited[j])
                dfs(j, depth + 1, target, visited);
        }
    }
}

// Ortak arkadaþlar
void common_friends(int id1, int id2) {
    User *u1 = find_user(id1), *u2 = find_user(id2);
    printf("%d ve %d ortak arkadaþlarý: ", id1, id2);
    for (int i = 0; i < u1->friend_count; i++)
        for (int j = 0; j < u2->friend_count; j++)
            if (u1->friends[i] == u2->friends[j])
                printf("%d ", u1->friends[i]);
    printf("\n");
}

// Topluluk tespiti
void dfs_community(int idx, int* visited) {
    visited[idx] = 1;
    printf("%d ", g.users[idx].id);
    for (int i = 0; i < g.users[idx].friend_count; i++) {
        int fid = g.users[idx].friends[i];
        for (int j = 0; j < g.user_count; j++)
            if (g.users[j].id == fid && !visited[j])
                dfs_community(j, visited);
    }
}

void find_communities() {
    int visited[MAX_USERS] = {0};
    int c = 0;
    for (int i = 0; i < g.user_count; i++) {
        if (!visited[i]) {
            printf("Topluluk %d: ", ++c);
            dfs_community(i, visited);
            printf("\n");
        }
    }
}

// Etki alaný hesaplama
int dfs_reach(int idx, int* visited) {
    visited[idx] = 1;
    int count = 1;
    for (int i = 0; i < g.users[idx].friend_count; i++) {
        int fid = g.users[idx].friends[i];
        for (int j = 0; j < g.user_count; j++)
            if (g.users[j].id == fid && !visited[j])
                count += dfs_reach(j, visited);
    }
    return count;
}

int main() {
    FILE* f = fopen("veriseti.txt", "r");
    if (!f) { printf("Dosya bulunamadý!\n"); return 1; }

    char cmd[10];
    int a, b;
    while (fscanf(f, "%s", cmd) != EOF) {
        if (!strcmp(cmd, "USER")) {
            fscanf(f, "%d", &a);
            add_user(a);
            root = insert_bst(root, a);
        } else if (!strcmp(cmd, "FRIEND")) {
            fscanf(f, "%d %d", &a, &b);
            add_friend(a, b);
        }
    }
    fclose(f);

    printf("\nDepth-First Search ile derinlik 2 arkadaþlarý (101): ");
    int visited[MAX_USERS] = {0};
    for (int i = 0; i < g.user_count; i++)
        if (g.users[i].id == 101)
            dfs(i, 0, 2, visited);

    printf("\n\nOrtak arkadaþ analizi (101 ve 102):\n");
    common_friends(101, 102);

    printf("\nTopluluklar:\n");
    find_communities();

    printf("\nEtki Alaný (101): ");
    memset(visited, 0, sizeof(visited));
    int etkialani = dfs_reach(0, visited) - 1; // kendisi hariç
    printf("%d\n", etkialani);

    printf("\nBST'de 104 var mý? ");
    if (search_bst(root, 104)) printf("Bulundu\n");
    else printf("Bulunamadý\n");

    return 0;
}
