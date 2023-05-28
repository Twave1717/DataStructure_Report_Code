#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 1000007
#define ROW 100
#define COL 100
int globalDistance[COL][ROW];
int cnt = 0;

typedef struct {
    int x;
    int y;
} Coordinate;

typedef struct {
    Coordinate point;
    int time;
} QueueNode;

typedef struct {
    QueueNode *array;
    int front;
    int rear;
    int capacity;
} Queue;

Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->array = (QueueNode*)malloc(capacity * sizeof(QueueNode));
    queue->front = 0;
    queue->rear = -1;
    queue->capacity = capacity;
    return queue;
}

bool isQueueEmpty(Queue* queue) {
    return queue->front > queue->rear;
}

void enqueue(Queue* queue, QueueNode item) {
    queue->array[++queue->rear] = item;
}

QueueNode dequeue(Queue* queue) {
    return queue->array[queue->front++];
}

bool isValid(int x, int y) {
    return (x >= 0 && x < COL && y >= 0 && y < ROW);
}

int shortestPathBFS(int grid[COL][ROW]) {
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
	for (int i = 0; i < COL; i++) {
        for (int j = 0; j < ROW; j++) {
            globalDistance[i][j] = MAX;
        }
    }
    
    Queue* queue = createQueue(ROW * COL * 1000);
    Coordinate start = {0, 0};
    Coordinate end = {COL - 1, ROW - 1};
    QueueNode startNode = {start, 0};
    globalDistance[0][0] = 0;
    enqueue(queue, startNode);
    cnt++;
    
    while (!isQueueEmpty(queue)) {
    	
    	cnt++;
    	
        QueueNode current = dequeue(queue);
        Coordinate point = current.point;
        int time = current.time;
        
        if (point.x == end.x && point.y == end.y && time <= globalDistance[point.x][point.y]){
        	return time;
		}
        
        for (int i = 0; i < 4; i++) {
            int newX = point.x + dx[i];
            int newY = point.y + dy[i];
            int nextTime = time;
            
            if(!isValid(newX, newY)) continue;
            
            // 횡단보도 건넜는지 아닌지 check && 몇번 횡단보도 건넜는지 기록 -> 건넜으면 횡단보도 번호. 아니면 0 입력. 
            int crossNumber;
            if(dx[i] == 1 && newX % 2){ // 횡단보도 건넌 경우 
            	crossNumber = (newY % 2) ? 3 : 1;
			}
			else if(dy[i] == 1 && newY % 2){ // 횡단보도 건넌 경우 
				crossNumber = newX % 2 ? 2 : 4;
			}
			else if(dx[i] == -1 && (newX % 2 == 0)){ // 횡단보도 건넌 경우 
            	crossNumber = newY % 2 ? 3 : 1;
			}
			else if(dy[i] == -1 && (newY % 2 == 0)){ // 횡단보도 건넌 경우 
				crossNumber = newX % 2 ? 2 : 4;
			}
			else crossNumber = 0;
			// 횡단보도 건너지 않았다면 그냥 + 1 
			if(!crossNumber){
				nextTime = time + 1;
			}
			// 횡단보도 건넜다면 횡단보도 순서와 일치하는지 확인 후 일치하지 않으면 한 턴 기다림. 
            else{
            	if(crossNumber - 1 != time % 4){
            		while(crossNumber - 1 != nextTime % 4) nextTime++;
				}
				nextTime++;
			}
            
            if (globalDistance[newX][newY] > nextTime) {
            	globalDistance[newX][newY] = nextTime;
                QueueNode newNode = {{newX, newY}, nextTime};
                enqueue(queue, newNode);
            }
        }
    }
    
    return -1;  // 경로가 없는 경우
}

int main() {
	
	printf("MAP size : ROW = %d, COL = %d\n", ROW, COL);
	
	int grid[COL][ROW];
	for(int i = 0; i < COL; i++)
		for(int j = 0; j < ROW; j++)
			grid[i][j] = 0;

    int shortestDistance = shortestPathBFS(grid);
    
    for(int i = 0; i < COL; i++){
    	for(int j = 0; j < ROW; j++){
    		printf("%d\t", globalDistance[i][j]);
		}
		puts("");
	}
    
    printf("최단 거리: %d\n", shortestDistance + 1);
    printf("CNT: %d", cnt);
    
    return 0;
}

