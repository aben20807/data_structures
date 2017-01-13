#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILE_NAME "Sample_input.txt"

typedef struct node *nodePtr;
typedef struct node{
    int vertex;
    nodePtr link;
} node;
typedef struct{
    int count;
    nodePtr link;
} headNode;

void openFile(FILE **, const char *);//open file

nodePtr readData(FILE *, headNode [], const int);

int main()
{
    FILE *fin;
    openFile(&fin, FILE_NAME);
    int numOfVertex = 0;
    fscanf(fin, "%d", &numOfVertex);
    headNode hNode[numOfVertex];
    readData(fin, hNode, numOfVertex);

    
    for(int i = 0; i < numOfVertex; i++){
        printf("%d\n", hNode[i].count);
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

nodePtr readData(FILE *fin, headNode hNode[], const int numOfVertex){
    int i, j;
    for(i = 0; i < numOfVertex; i++){
        hNode[i].count = 0;
        hNode[i].link = NULL;
    }
    int tmpValue;
    headNode tmpHead;
    node tmpCurrent;
    for(i = 0; i < numOfVertex; i++){
        tmpHead = hNode[i];
        for(j = 0; j < numOfVertex; j++){
            fscanf(fin, "%d", &tmpValue);
            if(tmpValue){
                printf("in (%d, %d)\n", i, j);
                node tmpNode;
                tmpNode.vertex = j;
                tmpNode.link = NULL;
                if(tmpHead.count == 0){
                    tmpHead.link = &tmpNode;
                }
                else{
                    tmpCurrent.link = &tmpNode;
                }
                hNode[i].count ++;
                tmpCurrent = tmpNode;
            }
        }
    }
    fclose(fin);
}
