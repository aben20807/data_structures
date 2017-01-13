#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MALLOC(p, s) \
		if(!((p) = malloc(s))){ \
			fprintf(stderr, "Insufficient memory"); \
			exit(EXIT_FAILURE); \
		}
#define FILE_NAME "Sample_input.txt"

typedef struct node *nodePtr;
typedef struct node{
    int vertex;
    int dur;
    nodePtr link;
} node;
typedef struct{
    int count;
    nodePtr link;
} *headNode;

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
    fclose(fin);

    int i;
    for(i = 0; i < numOfVertex; i++){
        printf("%d : %d(count) ", i, hNode[i]->count);
        if(hNode[i]->link != NULL){
            printf("%d(dur1)\n", hNode[i]->link->dur);
        }
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
        MALLOC(hNode[i], sizeof(*hNode[i]));
    }
    for(i = 0; i < numOfVertex; i++){
        hNode[i]->count = 0;
        hNode[i]->link = NULL;
    }
    int tmpValue;
    headNode tmpHead;
    nodePtr tmpCurrent;
    MALLOC(tmpCurrent, sizeof(*tmpCurrent));
    for(i = 0; i < numOfVertex; i++){
        tmpHead = hNode[i];
        for(j = 0; j < numOfVertex; j++){
            fscanf(fin, "%d", &tmpValue);
            if(tmpValue){
                // printf("(%d, %d)has dur\n", i, j);
                nodePtr tmpNode;
                MALLOC(tmpNode, sizeof(*tmpNode));
                tmpNode->vertex = j;
                tmpNode->dur = tmpValue;
                tmpNode->link = NULL;
                if(tmpHead->count == 0){
                    tmpHead->link = tmpNode;
                }
                else{
                    tmpCurrent->link = tmpNode;
                }
                hNode[i]->count ++;
                tmpCurrent = tmpNode;
            }
        }
    }
    fclose(fin);
}
