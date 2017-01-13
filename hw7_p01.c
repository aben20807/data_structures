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
nodePtr readData(FILE *, headNode [], const int, int []);
void createEe(const headNode [], int [], const int, const int[]);

int main()
{
    FILE *fin;
    openFile(&fin, FILE_NAME);
    int numOfVertex = 0;
    fscanf(fin, "%d", &numOfVertex);
    headNode hNode[numOfVertex];
    int isStart[numOfVertex];
    readData(fin, hNode, numOfVertex, isStart);
    fclose(fin);

    int ee[numOfVertex];
    createEe(hNode, ee, numOfVertex, isStart);
    // int i;
    // for(i = 0; i < numOfVertex; i++){//print Adjacency lists
    //     printf("%d : %d(count) ", i, hNode[i]->count);
    //     nodePtr test = hNode[i]->link;
    //     while(test != NULL){
    //         printf("%d(dur%d)", test->vertex, test->dur);
    //         test = test->link;
    //     }
    //     printf("\n");
    // }
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

nodePtr readData(FILE *fin, headNode hNode[], const int numOfVertex, int isStart[]){
    int i, j;
    for(i = 0; i < numOfVertex; i++){
        MALLOC(hNode[i], sizeof(*hNode[i]));
        hNode[i]->count = 0;
        hNode[i]->link = NULL;
        isStart[i] = 1;
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
                isStart[j] = 0;
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
}

void createEe(const headNode hNode[], int ee[], const int numOfVertex, const int isStart[]){
    int i, j, startEvent = 0;
    int eeStack[numOfVertex];
	nodePtr current;
	MALLOC(current, sizeof(*current));
    for(i = 0; i < numOfVertex; i++){
        eeStack[i] = -1;//init ee stack
        ee[i] = 0;//init ee
        if(isStart[i] == 1){
			startEvent = i;
            current = hNode[i]->link;//choose start
        }
    }
    for(i = 0; i < numOfVertex; i++){
        for(j = 0; j < hNode[startEvent]->count; j++){
            ee[current->vertex] += current->dur;
            current = current->link;
        }
    }
}
