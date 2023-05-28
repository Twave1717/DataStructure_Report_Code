#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 100

// 전역 변수로 최단 경로를 저장할 배열 선언
int shortestPath[MAX_SIZE][2];
int memoShortestPath[MAX_SIZE][2];
int shortestDistance = MAX_SIZE;
int cnt = 0;

// 방문한 좌표를 표시하기 위한 배열
int visited[MAX_SIZE][MAX_SIZE];

// 좌표 이동을 위한 방향 배열
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int n, m; // 배열의 크기

int is_valid(int x, int y) {
    // 주어진 좌표가 유효한 범위인지 확인하는 함수
    return (x >= 0 && x < n && y >= 0 && y < m);
}

void dfs(int x, int y, int distance) {
	
	cnt++;
	
	if(distance > shortestDistance) return;
	
    visited[x][y] = 1; // 현재 좌표를 방문 처리

    shortestPath[distance][0] = x;
    shortestPath[distance][1] = y;

    if (x == n - 1 && y == m - 1) {
        // 목적지에 도착한 경우
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
//                return; // 돌아가더라도 가는 길을 찾는 거는 빠르다. 
        }
    }

}

void findShortestPath(int row, int col) {
    n = row;
    m = col;

    // 전역 변수 초기화
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
    int n; // 배열의 행 개수
    int m; // 배열의 열 개수

	printf("이동할 지도의 가로와 세로 크기를 입력하세요\n");
	printf("가로: ");
	scanf("%d", &m);
	printf("세로: ");
	scanf("%d", &n);
	
    findShortestPath(n, m);

    printf("배열의 크기: 가로 = %d, 세로 = %d\n", m, n);
    printf("최단 경로 길이: %d\n", shortestDistance + 1);
    printf("cnt의 크기: %d\n", cnt);

    // 최단 경로 출력
    printf("최단 경로: ");
    for (int i = 0; i <= shortestDistance; i++) {
        printf("(%d, %d) ", memoShortestPath[i][0], memoShortestPath[i][1]);
    }
    printf("\n");
    
    return 0;
}

