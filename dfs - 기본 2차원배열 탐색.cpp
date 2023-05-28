#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 100

// ���� ������ �ִ� ��θ� ������ �迭 ����
int shortestPath[MAX_SIZE][2];
int memoShortestPath[MAX_SIZE][2];
int shortestDistance = MAX_SIZE;
int cnt = 0;

// �湮�� ��ǥ�� ǥ���ϱ� ���� �迭
int visited[MAX_SIZE][MAX_SIZE];

// ��ǥ �̵��� ���� ���� �迭
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int n, m; // �迭�� ũ��

int is_valid(int x, int y) {
    // �־��� ��ǥ�� ��ȿ�� �������� Ȯ���ϴ� �Լ�
    return (x >= 0 && x < n && y >= 0 && y < m);
}

void dfs(int x, int y, int distance) {
	
	cnt++;
	
	if(distance > shortestDistance) return;
	
    visited[x][y] = 1; // ���� ��ǥ�� �湮 ó��

    shortestPath[distance][0] = x;
    shortestPath[distance][1] = y;

    if (x == n - 1 && y == m - 1) {
        // �������� ������ ���
        if(distance < shortestDistance){
        	shortestDistance = distance;
        	for(int i = 0; i <= distance; i++){
        		memoShortestPath[i][0] = shortestPath[i][0];
        		memoShortestPath[i][1] = shortestPath[i][1];
			}
		}
        
        return;
    }

    for (int i = 0; i < 4; i++) {
        int new_x = x + dx[i];
        int new_y = y + dy[i];

        if (is_valid(new_x, new_y) && !visited[new_x][new_y]) {
            dfs(new_x, new_y, distance + 1);
            visited[new_x][new_y] = 0;
//            if (shortestPath[distance + 1][0] != -1)
//                return; // ���ư����� ���� ���� ã�� �Ŵ� ������. 
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

    dfs(0, 0, 0);

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

