
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define SWAP(x,y) {int t; t = x; x = y; y = t;} 

int N;

void openFile(FILE **, const char *);//open file
void countN();
void readInput(int []);
void creatMaxHeapTree(int []);
void printMaxHeapTree(const int []);
void deleteElement(int []);

int main()
{
	countN();
	int h[N+1];
	readInput(h);
	creatMaxHeapTree(h);
	printMaxHeapTree(h);
	deleteElement(h);
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

void countN(){
	FILE *fin;
	openFile(&fin, "in.txt");
	char tmpc;
	N = 0;
	while((tmpc = fgetc(fin)) != EOF){
		if(tmpc == ',')N++;
	}
	N = N+1;
	fclose(fin);
}

void readInput(int in[]){
	FILE *fin;
	int i;
	in[0] = N;
	openFile(&fin, "in.txt");
	for(i = 1; i < N+1; i++){
		fscanf(fin, "%d,", &in[i]);
		//printf("%d\n", in[i]);
	}
	fclose(fin);
}

void creatMaxHeapTree(int in[]){
	int i, child, parent;
	int heap[N+1];
	heap[0] = N;
	printf("Creat Max Heap:\n");
	for(i = 1; i < N+1; i++){
		heap[i] = in[i];
		child = i;
		parent = i/2;
		while(child > 1 && heap[parent] < heap[child]){
			SWAP(heap[parent], heap[child]);
			child = parent;
			parent = parent / 2;
		}
	}
	for(i = 1; i < N+1; i++){
		in[i] = heap[i];
	}
}

void printMaxHeapTree(const int heap[]){
	int i, newLineIndex = 2-1;
	printf("Max Heap:\n");
	for(i = 1; i < N+1; i++){
		printf("%d", heap[i]);
		if(i == newLineIndex || i == N){
			printf("\n");
			newLineIndex = (newLineIndex + 1)*2-1;
		}
		else
			printf(" ");
	}
}

void deleteElement(int heap[]){
	char ans;
	unsigned long long int begin, end, result = 0;
	while(1){
		printf("Delete element?(Y/N):");
		scanf("%c", &ans);
		getchar();//to get the '\n' after entering Y or N
		if(ans == 'N'){
			break;
		}
		else if(ans == 'Y'){
			int dele;
			int i, find = 0;
			int child, parent;
			printf("Choice element:");
			scanf("%d", &dele);
			LARGE_INTEGER t1, t2, ts;//count execution time
			QueryPerformanceFrequency(&ts);//count execution time
			QueryPerformanceCounter(&t1);//count execution time
			for(i = 1; i < N+1; i++){
				Sleep(1);
				if(heap[i] == dele){
					find = 1;
					break;
				}
			}
			if(find){
				heap[i] = heap[N];
				N--;
				if(2*i+1 < N+1){
					child = ((heap[2*i] > heap[2*i+1])? 2*i: 2*i+1);
				}
				else if(2*i < N+1){
					child = 2*1;
				}
				else{
					child = i;
				}
				parent = child/2;
				while(child > 1 && heap[parent] < heap[child]){
					SWAP(heap[parent], heap[child]);
					child = parent;
					parent = parent / 2;
					Sleep(1);
				}
			}
			else{
				printf("Element does not exist!\n");
				continue;
				getchar();
			}
			QueryPerformanceCounter(&t2);//count execution time
			printMaxHeapTree(heap);
			printf("%.10lf sec\n", (t2.QuadPart-t1.QuadPart)/(double)(ts.QuadPart));//count execution time
		}
		else{
			printf("Please enter 'Y' or 'N'!\n");
			continue;
			getchar();
		}
		getchar();//to get the '\n' after entering number
	}
}
