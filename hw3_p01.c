#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MALLOC(p, s) \
	if(!((p) = malloc(s))){ \
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}

int M = 0;
int N = 0;
int numOfAnswer = 0;
typedef struct position{
	int row;
	int col;
} *pos;
pos s;
pos d;
typedef struct node *nodePointer;
typedef struct node{
	int row;
	int col;
	nodePointer direction[8];
} *nodePointer;

void openFile(FILE **, const char *);
void countMN(FILE *);
void readMaze(FILE *, char (*)[]);
nodePointer createNode(const int, const int);
nodePointer createTree(nodePointer, const char (*)[]);
nodePointer addNode(const nodePointer, const nodePointer, const int);
int checkRange(const int, const int, const int, const int);

int main(){
	FILE *fin;
	int i, j;
	openFile(&fin, "in.txt");
	countMN(fin);
	//printf("%d\n%d\n", M, N);
	char maze[M][N];
	for(i = 0; i < M; i++){
		for(j = 0; j < N; j++){
			maze[i][j] = '0';
		}
	}
	openFile(&fin, "in.txt");
	readMaze(fin, maze);
	//printf("(%d, %d), (%d, %d)\n", s -> row, s-> col, d -> row, d -> col);
	nodePointer root = createNode(s -> row, s -> col);
	//printf("%d, %d\n", root -> row, root -> col);
	nodePointer tree = createTree(root, maze);
	printf("%d\n", numOfAnswer);
	return 0;
}

void openFile(FILE **fin, const char *fileName){
	//printf("%s\n", fileName);
	if(strlen(fileName) > 1000){
		printf("The length of file name is too long\n");
		exit(1);
	}
	if(!(*fin = fopen(fileName, "r"))){
		printf("No file!\n");
		exit(1);
	}
}

void countMN(FILE *fin){
	int line = 0, numOfLine = 0;
	char c, lc = '0';
	while((c = fgetc(fin)) != EOF)//read all char until end of file
	{
		numOfLine ++;//count N
		if(c == '\n'){
			line ++;//meet '\n' then line += 1
			if(N == 0){
				N = numOfLine - 2;
			}
		}
		lc = c;//store the previous char
	}
	fclose(fin);//close file
	if(lc != '\n') line = line + 1;//handle the last line
	M = line;
}

void readMaze(FILE *fin, char (*maze)[N]){
	int i = 0, j = 0;
	char c;
	MALLOC(s, sizeof(*s));
	MALLOC(d, sizeof(*d));
	while((c = fgetc(fin)) != EOF)//read all char until end of file
	{
		if(c == 's'){
			s -> row = i;
			s -> col = j;
			//printf("%d, %d\n", i, j);
		}
		if(c == 'd'){
			d -> row = i;
			d -> col = j;
			//printf("%d, %d\n", i, j);
		}
		if(c == '\n'){//when read '\n' change to next row
			i++;
			j = 0;
		}
		else{
			maze[i][j++] = c;//store c in maze[][]
		}
	}
	//printf("%c, %c\n", maze[s -> row][s -> col], maze[d -> row][d -> col]);
	fclose(fin);//close file
}

nodePointer createNode(const int _row, const int _col){
	nodePointer tmp;
	MALLOC(tmp, sizeof(*tmp));
	tmp -> row = _row;
	tmp -> col = _col;
	int i;
	for(i = 0; i < 8; i++){
		tmp -> direction[i] = NULL;
	}
	return tmp;
}

nodePointer createTree(nodePointer root, const char (*maze)[N]){
	nodePointer tmp;
	tmp = root;
	int tmpr = tmp -> row;
	int tmpc = tmp -> col;
	if(tmpr == d -> row && tmpc == d -> col){
		numOfAnswer++;
	}
	printf("(%d, %d)\n", tmpr, tmpc);
	printf("%d, %d, %d, %d, %d, %d, %d, %d\n",
			checkRange(tmpr, tmpc, -1, -1),
			checkRange(tmpr, tmpc, -1, 0),
			checkRange(tmpr, tmpc, -1, 1),
			checkRange(tmpr, tmpc, 0, -1),
			checkRange(tmpr, tmpc, 0, 1),
			checkRange(tmpr, tmpc, 1, -1),
			checkRange(tmpr, tmpc, 1, 0),
			checkRange(tmpr, tmpc, 1, 1));
	//while(1){
		if(checkRange(tmpr, tmpc, -1, -1)){
			if(maze[tmpr-1][tmpc-1] == '0'){
				//root = createTree(addNode(tmp, createNode(tmpr-1, tmpc-1), 0), maze);
				createTree(addNode(tmp, createNode(tmpr-1, tmpc-1), 0), maze);
			}
		}
		else if(checkRange(tmpr, tmpc, -1, 0)){
			if(maze[tmpr-1][tmpc] == '0'){
				//root = createTree(addNode(tmp, createNode(tmpr-1, tmpc), 1), maze);
				createTree(addNode(tmp, createNode(tmpr-1, tmpc), 1), maze);
			}
		}
		else if(checkRange(tmpr, tmpc, -1, 1)){
			if(maze[tmpr-1][tmpc+1] == '0'){
				//root = createTree(addNode(tmp, createNode(tmpr-1, tmpc+1), 2), maze);
				createTree(addNode(tmp, createNode(tmpr-1, tmpc+1), 2), maze);
			}
		}
		else if(checkRange(tmpr, tmpc, 0, -1)){
			if(maze[tmpr][tmpc-1] == '0'){
				//root = createTree(addNode(tmp, createNode(tmpr, tmpc-1), 3), maze);
				createTree(addNode(tmp, createNode(tmpr, tmpc-1), 3), maze);	
			}
		}
		else if(checkRange(tmpr, tmpc, 0, 1)){
			if(maze[tmpr][tmpc+1] == '0'){
				//root = createTree(addNode(tmp, createNode(tmpr, tmpc+1), 4), maze);
				createTree(addNode(tmp, createNode(tmpr, tmpc+1), 4), maze);
			}
		}
		else if(checkRange(tmpr, tmpc, 1, -1)){
			if(maze[tmpr+1][tmpc-1] == '0'){
				//root = createTree(addNode(tmp, createNode(tmpr+1, tmpc-1), 5), maze);
				createTree(addNode(tmp, createNode(tmpr+1, tmpc-1), 5), maze);
			}
		}
		else if(checkRange(tmpr, tmpc, 1, 0)){
			if(maze[tmpr+1][tmpc] == '0'){
				//root = createTree(addNode(tmp, createNode(tmpr+1, tmpc), 6), maze);
				createTree(addNode(tmp, createNode(tmpr+1, tmpc), 6), maze);
			}
		}
		else if(checkRange(tmpr, tmpc, 1, 1)){
			if(maze[tmpr+1][tmpc+1] == '0'){
				//root = createTree(addNode(tmp, createNode(tmpr+1, tmpc+1), 7), maze);
				createTree(addNode(tmp, createNode(tmpr+1, tmpc+1), 7), maze);
			}
		}
		else{
			return root;
		}
	//}
	//return root;
}

nodePointer addNode(const nodePointer pre, const nodePointer tmp, const int direc){
	pre -> direction[direc] = tmp;
	return tmp;
}

int checkRange(const int r, const int c, const int i, const int j){
	if(r + i >= 0 && r + i < M && c + j >= 0 && c + j < N)
		return 1;
	else
		return 0;
}
