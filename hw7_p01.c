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
	int acti;
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
void createEe(const headNode [], int [], const int, int *, int *);
void createE(int [], const int, const int, const int [], const headNode []);

int main()
{
    FILE *fin;
    openFile(&fin, FILE_NAME);
    int numOfVertex = 0, numOfActivity =0, start;
    fscanf(fin, "%d", &numOfVertex);
    headNode hNode[numOfVertex];
    int isStart[numOfVertex];
    readData(fin, hNode, numOfVertex);
    fclose(fin);

    int ee[numOfVertex];
    createEe(hNode, ee, numOfVertex, &numOfActivity, &start);
	int e[numOfActivity+1];
	createE(e, start, numOfVertex, ee, hNode);
    int i;
    // for(i = 0; i < numOfVertex; i++){//print Adjacency lists
    //     printf("%d : %d(count) ", i, hNode[i]->count);
    //     nodePtr test = hNode[i]->link;
    //     while(test != NULL){
    //         printf("%d(dur%d, acti%d)", test->vertex, test->dur, test->acti);
    //         test = test->link;
    //     }
    //     printf("\n");
    // }
	for(i = 1; i < numOfActivity+1; i++){
		printf("%d\n", e[i]);
	}
	printf("%d\n", start);
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
    int tmpValue, actiCount = 1;
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
				tmpNode->acti = actiCount++;
				hNode[j]->count++;
                tmpNode->dur = tmpValue;
                tmpNode->link = NULL;
                if(tmpHead->link == NULL){
                    tmpHead->link = tmpNode;
                }
                else{
                    tmpCurrent->link = tmpNode;
                }
                tmpCurrent = tmpNode;
            }
        }
    }
}

void createEe(const headNode hNode[], int ee[], const int numOfVertex, int *numOfActivity, int *start){
	int i, j, k, top;
	for(i = 0; i < numOfVertex; i++){
        ee[i] = 0;//init ee
		*numOfActivity += hNode[i]->count;
    }
	nodePtr ptr;
	top = -1;
	*start = -1;
	for(i = 0; i < numOfVertex; i++){
		if(!hNode[i]->count){
			hNode[i]->count = top;
			top = i;
			*start = i;
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

void createE(int e[], int start, const int numOfVertex, const int ee[], const headNode hNode[]){
	int i, tmpCount = 0;
	// nodePtr ptr;
	// MALLOC(ptr, sizeof(*ptr));
	// ptr = hNode[start]->link;
	// printf("%d\n",ptr->acti);
	for(i = 0; i < numOfVertex; i++){//print Adjacency lists
        printf("%d : %d(count) ", i, hNode[i]->count);
        nodePtr ptr = hNode[i]->link;
        while(ptr != NULL){
            printf("%d ", ee[tmpCount]);
			e[ptr->acti] = ee[tmpCount];
            ptr = ptr->link;
        }
		tmpCount++;
        printf("\n");
    }
	
	// for(i = 0; i < numOfActivity;){
	// 	while(!ptr->link){
	// 		i++;
	// 		printf("%d\n", ptr->acti);
	// 		e[ptr->acti] = ee[tmpCount];
	// 		ptr = ptr->link;
	// 	}
	// 	tmpCount++;
	// 	ptr = hNode[++start]->link;
	// }
	// int count = 0;
	// for(i = 1; i < numOfActivity+1; i++){
	// 	if(ptr!=NULL){
	// 		e[i] = ee[count];
	// 	}
	// 	else{
	// 		count++;
	// 		ptr = hNode[]->link;
	// 	}
	// }
}
