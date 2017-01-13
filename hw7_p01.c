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
void createEe(const headNode [], int [], const int);

int main()
{
    FILE *fin;
    openFile(&fin, FILE_NAME);
    int numOfVertex = 0;
    fscanf(fin, "%d", &numOfVertex);
    headNode hNode[numOfVertex];
    int isStart[numOfVertex];
    readData(fin, hNode, numOfVertex);
    fclose(fin);

    int ee[numOfVertex];
    createEe(hNode, ee, numOfVertex);
    int i;
    // for(i = 0; i < numOfVertex; i++){//print Adjacency lists
    //     printf("%d : %d(count) ", i, hNode[i]->count);
    //     nodePtr test = hNode[i]->link;
    //     while(test != NULL){
    //         printf("%d(dur%d)", test->vertex, test->dur);
    //         test = test->link;
    //     }
    //     printf("\n");
    // }
	for(i = 0; i < numOfVertex; i++){
		printf("%d\n", ee[i]);
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
				hNode[j]->count++;
                tmpNode->dur = tmpValue;
                tmpNode->link = NULL;
                if(tmpHead->link == NULL){
                    tmpHead->link = tmpNode;
                }
                else{
                    tmpCurrent->link = tmpNode;
                }
                // hNode[i]->count ++;
                tmpCurrent = tmpNode;
            }
        }
    }
}

void createEe(const headNode hNode[], int ee[], const int numOfVertex){
	int i, j, k, top;
	for(i = 0; i < numOfVertex; i++){
        ee[i] = 0;//init ee
    }
	nodePtr ptr;
	top = -1;
	for(i = 0; i < numOfVertex; i++){
		if(!hNode[i]->count){
			hNode[i]->count = top;
			top = i;
		}
	}
	for(i = 0; i < numOfVertex; i++){
		if(top == -1){
			printf("has a cycle\n");
			exit(1);
		}
		else{
			j = top;
			top = hNode[top]->count;
			for(ptr = hNode[j]->link; ptr; ptr = ptr->link){
				k = ptr->vertex;
				if(ee[k] < ee[j] + ptr->dur){
					ee[k] = ee[j] + ptr->dur;
				}
				hNode[k]->count--;
				if(!hNode[k]->count){
					hNode[k]->count = top;
					top = k;
				}
			}
		}
	}
}
