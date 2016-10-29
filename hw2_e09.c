#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int imove[] = {-1, 0, 1, 1, 1, 0, -1, -1};
int jmove[] = {1, 1, 1, 0, -1, -1, -1, 0};

void checkInput(const int, const int, const int, const int);
int countDigit(int);

int main(){
	int n, m, ibug, jbug;
	int i, j;
	printf("N:");
	scanf("%d", &n);
	printf("M:");
	scanf("%d", &m);
	printf("Initial bug position X:");
	scanf("%d", &ibug);
	printf("Initial bug position Y:");
	scanf("%d", &jbug);
	checkInput(n, m, ibug, jbug);
	int count[n][m];
	for(i = 0; i < n; i++){
		for(j = 0; j < m; j++){
			count[i][j] = 0;
		}
	}
	count[ibug][jbug]++;
	int legalMoves = 0+1;
	int remain = n*m;//to record how many element value in count[][] are 0
	int maxValue = 0;//to record the max number among all element in count[][]
	srand(time(NULL));
	int k;
	FILE *fout = fopen("Sample_Output.txt", "w");//open file
	while(1){
		if(remain == 1 || legalMoves > 50000){
			break;
		}
		k = rand()%8;
		//printf("i=%d, j=%d\n", ibug, jbug);
		ibug += imove[k];
		jbug += jmove[k];
		if(ibug >= 0 && ibug < n && jbug >= 0 && jbug < m){
			legalMoves++;
			//printf("%d\n", legalMoves);
			if(count[ibug][jbug] == 0){
				remain--;
			}
			count[ibug][jbug]++;
			if(count[ibug][jbug] > maxValue){
				maxValue = count[ibug][jbug];
			}
		}
		else{//hitting the wall is illegal move, ignore it
			ibug -= imove[k];
			jbug -= jmove[k];
		}
	}
	int printWidth = countDigit(maxValue);//count the tab width
	fprintf(fout, "總共%d步\r\n", legalMoves);//new line in windows is \r\n
	for(i = 0; i < n; i++){
		for(j = 0; j < m ; j++){
			fprintf(fout, "%*d", printWidth, count[i][j]);
		}
		fprintf(fout, "\r\n");
	}
	fclose(fout);//close file
	return 0;
}

void checkInput(const int n, const int m, const int x, const int y){
	if(n < 2 || n > 40 || m < 2 || m > 20){
		printf("The range of n or m is wrong!\n");
		exit(1);
	}
	if(x < 0 || x >= n || y < 0 || y >= m){
		printf("The initial bug position is wrong!\n");
		exit(1);
	}
}

int countDigit(int num){
	int digit = 2;
	while(num /= 10){
		digit++;
	}
	return digit;
}
