/*****************************************
 * Assignment: 1 q2
 * Name: Ananya S Reddy
 * Email: [ma22btech11004@iith.ac.in]
 * Class and Section: MA btech 22
 * Date Submitted: 03/09
 *
 * Description: Maze solver
 *
 *****************************************/

#include <stdio.h>
#include <stdlib.h>
#include<math.h>

struct deque {
    int size;
    int f,r;
    int *arr;
};
int isEmpty(struct deque* q) {
    if(q->f == -1 && q->r== -1){
        return 1;
    }
    return 0;
}

int isFull(struct deque* q) {
    if(q->f == (q->r + 1) % q->size){
        return 1;
    }
    return 0;
}

// Function to add a value to the end of the deque
// @param dq: Pointer to the deque
// @param value: Value to be added
// @return: None
void add_last(struct deque *q, int x) {
    // Function description
    if ((q->r + 1) % q->size == q->f) {
        printf("Deque is full\n");
    } else {
        q->arr[q->r] = x;
        q->r = (q->r + 1) % q->size;
    }
}

// Function to add a value to the front of the deque
// @param dq: Pointer to the deque
// @param value: Value to be added
// @return: None
void add_first(struct deque* q, int x) {
    if (isFull(q)) {
        printf("Circular Deque is full.\n");
        return;
    }

    if (isEmpty(q)) {
        q->f = q->r = 0;
    } else if (q->f == 0) {
        q->f = q->size - 1;
    } else {
        q->f = (q->f - 1) % q->size;
    }
    q->arr[q->f] = x;
}

// Function to remove and return the last value from the deque
// @param dq: Pointer to the deque
// @return: Value removed from the deque or -1 if empty
int remove_last(struct deque *dq) {
    // Function description
    if (dq->f== dq->r) {
        printf("Deque is empty\n");
        return -1;
    } else {
        int value = dq->arr[dq->r];
        dq->r= (dq->r - 1 + dq->size) % dq->size;
        return value;
    }
}

// Function to remove and return the first value from the deque
// @param dq: Pointer to the deque
// @return: Value removed from the deque or -1 if empty
int remove_first(struct deque *dq) {
    // Function description
    if (dq->f == dq->r) {
        printf("Deque is empty\n");
        return -1;
    } else {
        int value = dq->arr[dq->f];
        dq->f = (dq->f + 1) % dq->size;
        return value;
    }
}

// Function to traverse and print the elements of the deque
// @param dq: Pointer to the deque
// @return: None
void print_deque(struct deque *dq) {
    // Function description
    int present = dq->f;
    while (present != dq->r) {
        printf("%d ", dq->arr[present]);
        present = (present + 1) % dq->size;
    }
    printf("\n");
}

int c = 0;

// Function to search for a path in a matrix
// @param startx, starty, endx, endy: Coordinates of the start and end points
// @param rows, cols: Number of rows and columns in the matrix
// @param matrix: The matrix representing the maze
// @param dq: Pointer to the deque
// @return: None
void path_finder(int startx, int starty, int endx, int endy, int rows, int cols, char maze[rows][cols], struct deque *dq) {
    // Function description
    int dist= abs(endx - startx) + abs(endy - starty);
    add_first(dq, startx * cols + starty);

    for (int i = 0; dist > 1; ++i) {
        if (dq->f != dq->r) {
            int current = remove_first(dq);
            int a = current / cols;
            int b = current % cols;

            if (maze[a][b] != 'S' && maze[a][b] != 'E') {
                maze[a][b] = '.';
            }

            dist = abs(endx - a) + abs(endy - b);

            if (a== endx && b == endy) {
                break;
            }

            int new_distance;
            int x[] = {1, -1, 0, 0};
            int y[] = {0, 0, 1, -1};

            for (int i = 0; i < 4; i++) {
                int newA = a + x[i];
                int newB = b + y[i];

                if (newA >= 0 && newA < rows && newB >= 0 && newB < cols && maze[newA][newB] == ' ') {
                    int new_distance = abs(endx - newA) + abs(endy - newB);

                    if (dist< new_distance) {
                        add_last(dq, newA * cols + newB);
                    } else {
                        add_first(dq, newA * cols + newB);
                    }
                }
            }
        } else {
            printf("No Path found\n");
            c = 1;
            break;
        }
    }
}

int main() {
    char file_name[20];
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
    file = fopen("maze1.txt", "r");
    char maze[rows][cols];

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
    struct deque *dq = (struct deque *)malloc(sizeof(struct deque));
    dq->size = rows * cols;
    dq->f = dq->r = 0;
    dq->arr = (int *)malloc(dq->size * sizeof(int));

    path_finder(startx, starty, endx, endy, rows, cols, maze, dq);

    if (c == 0) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("%c", maze[i][j]);
            }
            printf("\n");
        }
    }

    free(dq->arr);
    free(dq);

    return 0;
}