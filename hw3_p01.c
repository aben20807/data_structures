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
int numOfStep = 0;
/*start and destination point*/
typedef struct position{
	int row;
	int col;
} *pos;
pos s;//start
pos d;//destination
/*element of stack*/
typedef struct stack_node{
	int row;
	int col;
	struct stack_node *next;
} stack_list;
typedef stack_list *link;
link path = NULL;
/*all kinds of move*/
int move[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
/*function*/
void openFile(FILE **, const char *);
void countMN(FILE *);
void readMaze(FILE *, char (*)[]);
void createMark(char (*)[], int (*)[]);
link push(link, int, int);
link pop(link, int *, int *);
int seekPath(int (*)[]);
void printAns(FILE **, char (*)[], int (*)[]);

int main(){
	FILE *fin, *fout;
	int i, j;
	openFile(&fin, "in.txt");
	countMN(fin);
	//printf("%d\n%d\n", M, N);//test for M, N
	char maze[M][N];
	int mark[M+2][N+2];
	memset(maze, '0', sizeof(maze));//init of maze
	openFile(&fin, "in.txt");
	readMaze(fin, maze);//input maze from file
	createMark(maze, mark);//creat mark for seeking path
	if(seekPath(mark)){//if there is a solution
		fout = fopen("out.txt", "w");
		printAns(&fout, maze, mark);
		fprintf(fout, "%d %s\n", numOfStep, ((numOfStep > 1) ? "steps" : "step"));
	}
	else{
		printf("No route\n");
	}
	fclose(fout);
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
		if(c == 's'){//define the position of start
			s -> row = i;
			s -> col = j;
		}
		if(c == 'd'){//define the position of destination
			d -> row = i;
			d -> col = j;
		}
		if(c == '\n'){//when read '\n' change to next row
			i++;
			j = 0;
		}
		else{
			maze[i][j++] = c;//store c in maze[][]
		}
	}
	fclose(fin);//close file
}

void createMark(char (*maze)[N], int (*mark)[N+2]){
	int i, j;
	//create a array with one more layer in four side and full of 1, which is used to be walls
	for(i = 0; i < M+2; i++){
		for(j = 0; j < N+2; j++){
			mark[i][j] = 1;
		}
	}
	for(i = 1; i < M+1; i++){//let maze set in the walls
		for(j = 1; j < N+1; j++){
			if(maze[i-1][j-1] == 's' || maze[i-1][j-1] == 'd'){
				mark[i][j] = 0;
			}
			else{
				mark[i][j] = (int)maze[i-1][j-1] - '0';
			}
		}
	}
}

link push(link stack, int row, int col)
{//push function of stack
   link new_node;
   new_node = (link)malloc(sizeof(stack_list));
   if ( !new_node )
   {
	   printf("Cannot malloc!\n");
	   return NULL;
   }
   new_node->row = row;
   new_node->col = col;
   new_node->next = stack;
   stack = new_node;
   return stack;
}

link pop(link stack, int *row, int *col)
{//pop function of stack

   if (stack != NULL)
   {
	  link top = stack;
      stack = stack->next;
      *row = stack->row;
      *col = stack->col;
      free(top);
      return stack;
   }
   else
      *row = -1;
}

int seekPath(int (*mark)[N+2]){
	int success = 0;//check if have solution
	int row = d->row+1;//seek from destination
	int col = d->col+1;
	while(1){
		if(row == s->row+1 && col == s->col+1){//arrive at start
			success = 1;
			break;
		}
		if(numOfStep > M*N+10){//num of steps more than num of maze, in case of other situation, so +10
			success = 0;
			break;
		}
		mark[row][col] = 2;//change to 2 when having passed
		if(mark[row-1][col-1] <= 0){
			row = row - 1;
			col = col - 1;
			numOfStep++;
			path = push(path, row, col);
		}
		else if(mark[row-1][col] <= 0){
			row = row - 1;
			numOfStep++;
			path = push(path, row, col);
		}
		else if(mark[row-1][col+1] <= 0){
			row = row - 1;
			col = col + 1;
			numOfStep++;
			path = push(path, row, col);
		}
		else if(mark[row][col-1] <= 0){
			col = col - 1;
			numOfStep++;
			path = push(path, row, col);
		}
		else if(mark[row][col+1] <= 0){
			col = col + 1;
			numOfStep++;
			path = push(path, row, col);
		}
		else if(mark[row+1][col-1] <= 0){
			row = row + 1;
			col = col - 1;
			numOfStep++;
			path = push(path, row, col);
		}
		else if(mark[row+1][col] <= 0){
			row = row + 1;
			numOfStep++;
			path = push(path, row, col);
		}
		else if(mark[row+1][col+1] <= 0){
			row = row + 1;
			col = col + 1;
			numOfStep++;
			path = push(path, row, col);
		}
		else{//no next step can keep going, so pop out
			mark[row][col] = 3;
			path = pop(path, &row, &col);
		}
	}
	return success;
}

void printAns(FILE **fout, char (*maze)[N], int (*mark)[N+2]){
	int i, j;
	for(i = 1; i < M+1; i++){
		for(j = 1; j < N+1; j++){
			if(i-1 == s->row && j-1 == s->col)
				fprintf(*fout, "s");
			else if(i-1 == d->row && j-1 == d->col)
				fprintf(*fout, "d");
			else if(mark[i][j] == 2 || mark[i][j] == 3)
				fprintf(*fout, "*");
			else
				fprintf(*fout, "%d", maze[i-1][j-1]-'0');
		}
		fprintf(*fout, "\r\n");
	}
}
