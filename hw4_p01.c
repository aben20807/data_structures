#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s) \
		if(!((p) = malloc(s))){ \
			fprintf(stderr, "Insufficient memory"); \
			exit(EXIT_FAILURE); \
		}
#define MAX_SIZE 50

typedef enum {head, entry} tagField;
typedef struct matrixNode *matrixPtr;
typedef struct entryNode{
	int row;
	int col;
	int value;
	} entryNode;
typedef struct matrixNode{
	matrixPtr down;
	matrixPtr right;
	tagField tag;
	union{
		matrixPtr next;
		entryNode entry;
	} u;
} matrixNode;

matrixPtr newEntryNode(const int, const int, const int);
matrixPtr readMatrix();
void printMatrix(const matrixPtr);

int main(){
	int i;
	matrixPtr m = readMatrix();
	printMatrix(m);
	return 0;
}

matrixPtr newEntryNode(const int row, const int col, const int value){
	matrixPtr tmp;
	MALLOC(tmp, sizeof(*tmp));
	tmp -> tag = entry;
	tmp -> u.entry.row = row;
	tmp -> u.entry.col = col;
	tmp -> u.entry.value = value;
	tmp -> right = NULL;
	tmp -> down = NULL;
	return tmp;
}

matrixPtr readMatrix(){
	int numOfRow, numOfCol, numOfHead, numOfItem;
	int row, col, value;
	matrixPtr smat, tmp, last, node;
	int i, j;
	
	scanf("%d%d", &numOfRow, &numOfCol);
	numOfHead = ((numOfRow > numOfCol)? numOfRow: numOfCol);
	
	matrixPtr smatNode;
	matrixPtr rowHeaderNode[numOfHead];
	matrixPtr colHeaderNode[numOfHead];
	
	MALLOC(smatNode, sizeof(*smatNode));
	smatNode -> tag = entry;
	smatNode -> u.entry.row = numOfRow;
	smatNode -> u.entry.col = numOfCol;
	
	//int tmpMatrix[numORow][numOfCol];
	if(!numOfHead){
		smat -> right = smat;
		return smatNode;
	}
	for(i = 0; i < numOfHead; i++){
		MALLOC(tmp, sizeof(*tmp));
		colHeaderNode[i] = tmp;
		colHeaderNode[i] -> tag = head;
		colHeaderNode[i] -> right = NULL;
		colHeaderNode[i] -> down = NULL;
		colHeaderNode[i] -> u.next = NULL;
		if(i > 0){
			colHeaderNode[i-1] -> u.next = colHeaderNode[i];
		}
	}
		for(i = 0; i < numOfHead; i++){
		MALLOC(tmp, sizeof(*tmp));
		rowHeaderNode[i] = tmp;
		rowHeaderNode[i] -> tag = head;
		rowHeaderNode[i] -> right = NULL;
		rowHeaderNode[i] -> down = NULL;
		rowHeaderNode[i] -> u.next = NULL;
		if(i > 0){
			rowHeaderNode[i-1] -> u.next = rowHeaderNode[i];
		}
	}
	smatNode -> right = colHeaderNode[0];
	smatNode -> down = rowHeaderNode[0];
	
	int tmpValue;
	for(i = 0; i < numOfRow; i++){
		last = rowHeaderNode[i];
		for(j = 0; j < numOfCol; j++){
			scanf("%d", &tmpValue);
			if(tmpValue != 0){
				numOfItem++;
				tmp = newEntryNode(i, j, tmpValue);
				last -> right = tmp;
				last = tmp;
				colHeaderNode[j] -> down = tmp;
			}
		}
		last -> right = NULL;
	}
	return smatNode;
}

void printMatrix(const matrixPtr m){
	int i, j;
	int row = m -> u.entry.row;
	int col = m -> u.entry.col;
	matrixPtr tmp, tmpRow;
	tmpRow = m -> down;
	for(i = 0; i < row; i++){
		tmp = tmpRow -> right;
		for(j = 0; j < col; j++){
			if(tmp != NULL){
				//printf("%d, %d\n", tmp->u.entry.row, tmp->u.entry.col);
				if((i == (tmp->u.entry.row)) && (j == (tmp->u.entry.col))){
					printf("%d", tmp->u.entry.value);
					tmp = tmp -> right;
				}
				else{
					printf("0");
				}
			}
			else{
				printf("0");
			}
			if(j != col-1){
				printf(" ");
			}
		}
		printf("\n");
		tmpRow = tmpRow -> u.next;
	}
}
