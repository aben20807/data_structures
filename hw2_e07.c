#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char fileName[1000+1];
FILE *fin;

int value(const int, int, int, int, int, int[]);
void openFile(FILE **, char *);//open file
void printAnsLine(const int, const int, const int, const int);//print answer

int main(){
	int n, a, b;
	int i, j;
	printf("Please input the file name(need .txt followed):");
	scanf("%s", fileName);
	openFile(&fin, fileName);
	printf("a:");
	scanf("%d", &a);
	printf("b:");
	scanf("%d", &b);
	//printf("a:%d, b:%d\n", a, b);
	fscanf(fin, "%d", &n);
	//printf("%d\n", n);
	int numOfBand = (-(a*a)/2 + a/2 + a*n - n) + (-(b*b)/2 + b/2 + b*n - n) + n;
	//printf("%d\n", numOfBand);
	int e[numOfBand];
	value(n, a, b, i, j, e);
	fclose(fin);
	return 0;
}

int value(const int n, int a, int b, int i, int j, int e[]){
	int D[n][n];
	int numOfBand = (-(a*a)/2 + a/2 + a*n - n) + (-(b*b)/2 + b/2 + b*n - n) + n;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			fscanf(fin, "%d", &D[i][j]);
		}
	}
	int indexOfe = 0;
	int headOfRow = a - 1;
	int headOfCol = 0;
	i = headOfRow;
	j = 0;
	while(1){
		if((j == (n - 1)) && ((j - i) == (b - 1))){//the final
			e[indexOfe] = D[i][j];
			printAnsLine(indexOfe, e[indexOfe], i, j);
			break;
		}
		if((i > (n - 1)) && (headOfRow > 0)){
			i = --headOfRow;
			j = 0;
		}
		if((j > (n - 1)) && (headOfRow == 0)){
			i = 0;
			j = ++headOfCol;
		}
		e[indexOfe] = D[i][j];
		printAnsLine(indexOfe, e[indexOfe], i++, j++);
		indexOfe++;
	}
	return 0;
}

void openFile(FILE **fin, char *fileName){
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

void printAnsLine(const int index, const int dij, const int i, const int j){
	printf("e[%d]=%d\td(%d,%d)\n", index, dij, i, j);
}
