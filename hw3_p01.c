#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int M = 0;
int N = 0;

void openFile(FILE **, const char *);
void countMN(FILE *);
void readMaze(FILE *, char (*)[]);

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
	for(i = 0; i < M; i++){
		for(j = 0; j < N; j++){
			printf("%c ", maze[i][j]);
		}
		printf("\n");
	}
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
	while((c = fgetc(fin)) != EOF)//read all char until end of file
	{
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
