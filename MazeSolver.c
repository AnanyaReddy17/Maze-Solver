/*****************************************
 *
 * Name: Ananya S Reddy
 * Email: [ma22btech11004@iith.ac.in]
 * Class and Section: MA btech 22
 * Date Submitted: 20/11
 *
 * Description: Maze solver Using BFS and Graph Representation
 *
 *****************************************/

#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include <math.h>

#define MAX_ROWS 100
#define MAX_COLS 100

// Queue structure
struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};

struct Queue* createQueue(unsigned capacity) {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->capacity = capacity;
    q->front = q->size = 0;
    q->rear = capacity - 1;
    q->array = (int*)malloc(q->capacity * sizeof(int));
    return q;
}

int isFull(struct Queue* q) {
    return (q->size == q->capacity);
}

int isEmpty(struct Queue* q) {
    return (q->size == 0);
}

void enqueue(struct Queue* q, int item) {
    if (isFull(q))
        return;
    q->rear = (q->rear + 1) % q->capacity;
    q->array[q->rear] = item;
    q->size = q->size + 1;
}

int dequeue(struct Queue* q) {
    if (isEmpty(q))
        return -1;
    int item = q->array[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size = q->size - 1;
    return item;
}

// Function to create a graph based on maze
void createGraph(char maze[MAX_ROWS][MAX_COLS], int rows, int cols,int graph[rows*cols][rows*cols]) {
    
    for(int i=0;i<rows*cols;i++){
        for(int j=0;j<rows*cols;j++){
            graph[i][j]=0;
        }
}
    
    int rowNum[] = { 1, -1, 0, 0 };
    int colNum[] = { 0, 0, 1, -1 };

    // Create edges based on the maze structure
    for (int i = 0; i<rows *cols;i++) {
        for (int j = 0; j < rows* cols;j++) {
            
                for (int k = 0; k < 4; k++) {
                    int newRow = i + rowNum[k];
                    int newCol = j + colNum[k];
                    if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && maze[newRow][newCol] != '#') {
                        graph[i*cols+j][newRow*cols+newCol]=1;
                    }
                }
            }
        }
}

//Function to perform BFS traversal on the graph
bool BFS(int start, int end, char maze[MAX_ROWS][MAX_COLS], int rows, int cols, int graph[rows * cols][rows * cols]) {
    int visited[rows * cols];
    for (int i = 0; i < rows * cols; i++) {
        visited[i] = 0;
    }
    visited[start] = 1;
    struct Queue* q = createQueue(rows * cols);
    enqueue(q, start);
    bool pathfound = false;

    while (!isEmpty(q)) {
        int current = dequeue(q);
        int x = current / cols;
        int y = current % cols;

        if (current == end) {
            pathfound = true;
            break;
        }

        // Update the maze with the path ('.')
        if (maze[x][y] != 'S' && maze[x][y] != 'E') {
            maze[x][y] = '.';
        }

        for (int adjCell = 0; adjCell < rows * cols; adjCell++) {
            if (graph[current][adjCell] && !visited[adjCell]) {
                visited[adjCell] = 1;
                enqueue(q, adjCell);
            }
        }
    }
    return pathfound;
}


int main() {
    char file_name[20];
    printf("Select maze input file :(out of maze1.txt,maze2.txt,maze3.txt) ");
    scanf("%s",file_name);
    FILE* file = fopen(file_name, "r");
    
    int rows = 0;
    int cols = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            rows++;
        }
        if (rows == 0) {
            cols++;
        }
    }

    fclose(file);
    file = fopen(file_name, "r");
    char maze[MAX_ROWS][MAX_COLS];

    int startx = 0;
    int starty = 0;
    int endx, endy;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            do {
                ch = fgetc(file);
            } while (ch == '\n');
            maze[i][j] = ch;
            if (maze[i][j] == 'S') {
                startx = i;
                starty = j;
            }
            if (maze[i][j] == 'E') {
                endx = i;
                endy = j;
            }
        }
    }

    fclose(file);
    
    int graph[rows*cols][rows*cols];
    
    createGraph(maze,rows,cols,graph);
    int start = startx * cols + starty;
    int end = endx * cols + endy;
    
    bool pathexists=BFS(start, end, maze, rows, cols,graph);

    if(!pathexists){
        printf("No path found.\n");
    }
    else{
    // Print the maze after BFS traversal
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
    }
    return 0;
}
