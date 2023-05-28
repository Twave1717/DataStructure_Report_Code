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
            
            // Ⱦ�ܺ��� �ǳԴ��� �ƴ��� check && ��� Ⱦ�ܺ��� �ǳԴ��� ��� -> �ǳ����� Ⱦ�ܺ��� ��ȣ. �ƴϸ� 0 �Է�. 
            int crossNumber;
            if(dx[i] == 1 && newX % 2){ // Ⱦ�ܺ��� �ǳ� ��� 
            	crossNumber = (newY % 2) ? 3 : 1;
			}
			else if(dy[i] == 1 && newY % 2){ // Ⱦ�ܺ��� �ǳ� ��� 
				crossNumber = newX % 2 ? 2 : 4;
			}
			else if(dx[i] == -1 && (newX % 2 == 0)){ // Ⱦ�ܺ��� �ǳ� ��� 
            	crossNumber = newY % 2 ? 3 : 1;
			}
			else if(dy[i] == -1 && (newY % 2 == 0)){ // Ⱦ�ܺ��� �ǳ� ��� 
				crossNumber = newX % 2 ? 2 : 4;
			}
			else crossNumber = 0;
			// Ⱦ�ܺ��� �ǳ��� �ʾҴٸ� �׳� + 1 
			if(!crossNumber){
				nextTime = time + 1;
			}
			// Ⱦ�ܺ��� �ǳԴٸ� Ⱦ�ܺ��� ������ ��ġ�ϴ��� Ȯ�� �� ��ġ���� ������ �� �� ��ٸ�. 
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
    
    return -1;  // ��ΰ� ���� ���
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
    
    printf("�ִ� �Ÿ�: %d\n", shortestDistance + 1);
    printf("CNT: %d", cnt);
    
    return 0;
}

