#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 100

// ���� ������ �ִ� ��θ� ������ �迭 ����
int shortestPath[MAX_SIZE][2];
int memoShortestPath[MAX_SIZE][2];
int shortestDistance = INT_MAX;

// �湮�� ��ǥ�� ǥ���ϱ� ���� �迭
int visited[MAX_SIZE][MAX_SIZE];

// ��ǥ �̵��� ���� ���� �迭
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int n, m; // �迭�� ũ��
int cnt;

int is_valid(int x, int y) {
    // �־��� ��ǥ�� ��ȿ�� �������� Ȯ���ϴ� �Լ�
    return (x >= 0 && x < n && y >= 0 && y < m);
}

void bfs(int x, int y) {
    // ť�� ����Ͽ� BFS Ž��
    int queue[MAX_SIZE * MAX_SIZE][3]; // ť�� �迭�� ����
    int front = 0, rear = 0; // ť�� front�� rear �ε���

    queue[rear][0] = x;
    queue[rear][1] = y;
    queue[rear][2] = 0; // �̵� �Ÿ� �ʱ�ȭ
    rear++;
    visited[x][y] = 1;

    while (front < rear) {
    	
    	cnt++;
    	
        int current_x = queue[front][0];
        int current_y = queue[front][1];
        int distance = queue[front][2];
        front++;

        shortestPath[distance][0] = current_x;
        shortestPath[distance][1] = current_y;

        if (current_x == n - 1 && current_y == m - 1) {
            // �������� ������ ���
            shortestDistance = distance; // �ִ� �Ÿ� ����
        	for(int i = 0; i <= distance; i++){
        		memoShortestPath[i][0] = shortestPath[i][0];
        		memoShortestPath[i][1] = shortestPath[i][1];
			}
            return;
        }
        for (int i = 0; i < 4; i++) {
            int new_x = current_x + dx[i];
            int new_y = current_y + dy[i];

            if (is_valid(new_x, new_y) && !visited[new_x][new_y]) {
                queue[rear][0] = new_x;
                queue[rear][1] = new_y;
                queue[rear][2] = distance + 1; // �̵� �Ÿ� ����
                rear++;
                visited[new_x][new_y] = 1;
            }
        }
    }
}

void findShortestPath(int row, int col) {
    n = row;
    m = col;

    // ���� ���� �ʱ�ȭ
    int i, j;
    for (i = 0; i < MAX_SIZE; i++) {
        for (j = 0; j < 2; j++) {
            shortestPath[i][j] = -1;
        }
    }
    for (i = 0; i < MAX_SIZE; i++) {
        for (j = 0; j < MAX_SIZE; j++) {
            visited[i][j] = 0;
        }
    }

    bfs(0, 0);

    return;
}

int main() {
    int n; // �迭�� �� ����
    int m; // �迭�� �� ����
    
	printf("�̵��� ������ ���ο� ���� ũ�⸦ �Է��ϼ���\n");
	printf("����: ");
	scanf("%d", &m);
	printf("����: ");
	scanf("%d", &n);

    findShortestPath(n, m);

    printf("�迭�� ũ��: ���� = %d, ���� = %d\n", m, n);
    printf("�ִ� ��� ����: %d\n", shortestDistance + 1);
    printf("cnt�� ũ��: %d\n", cnt);

    // �ִ� ��� ���
    printf("�ִ� ���: ");
    for (int i = 0; i <= shortestDistance; i++) {
        printf("(%d, %d) ", memoShortestPath[i][0], memoShortestPath[i][1]);
    }
    printf("\n");

    return 0;
}

