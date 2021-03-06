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
matrixPtr multiplication(const matrixPtr, const matrixPtr, int *);
void printMatrix(const matrixPtr);
void printTransposeMatrix(const matrixPtr);

int main(){
	int ok;
	matrixPtr m1 = readMatrix();
	matrixPtr m2 = readMatrix();
	matrixPtr m = multiplication(m1, m2, &ok);
	if(ok)
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

	//int tmpMatrix[numORow][numOfCol];
	if(!numOfHead){
		smat -> right = smat;
		return smatNode;
	}

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
				colHeaderNode[j] = tmp;
			}
		}
		last -> right = NULL;
	}
	for(i = 0; i < numOfCol; i++){
		colHeaderNode[i] -> down = NULL;
	}
	return smatNode;
}

matrixPtr multiplication(const matrixPtr m1, const matrixPtr m2, int *ok){
	*ok = 1;
	int mRow = m1->u.entry.row;
	int mCol = m2->u.entry.col;
	if(m1->u.entry.col != m2->u.entry.row){
		printf("Two input matrix cannot do multiplication.\n");
		*ok = 0;
		return m1;
	}
	int i, j, k;
	int mHead = ((mRow > mCol)? mRow: mCol);

	matrixPtr m, tmp1, tmp2, tmp1Row, tmp2Col;
	matrixPtr last, tmp;
	matrixPtr rowHeaderNode[mHead];
	matrixPtr colHeaderNode[mHead];
	MALLOC(m, sizeof(*m));
	m -> tag = entry;
	m -> u.entry.row = mRow;
	m -> u.entry.col = mCol;

	for(i = 0; i < mHead; i++){
		MALLOC(tmp1, sizeof(*tmp1));
		colHeaderNode[i] = tmp1;
		colHeaderNode[i] -> tag = head;
		colHeaderNode[i] -> right = NULL;
		colHeaderNode[i] -> down = NULL;
		colHeaderNode[i] -> u.next = NULL;
		if(i > 0){
			colHeaderNode[i-1] -> u.next = colHeaderNode[i];
		}
	}
	for(i = 0; i < mHead; i++){
		MALLOC(tmp1, sizeof(*tmp1));
		rowHeaderNode[i] = tmp1;
		rowHeaderNode[i] -> tag = head;
		rowHeaderNode[i] -> right = NULL;
		rowHeaderNode[i] -> down = NULL;
		rowHeaderNode[i] -> u.next = NULL;
		if(i > 0){
			rowHeaderNode[i-1] -> u.next = rowHeaderNode[i];
		}
	}
	m -> right = colHeaderNode[0];
	m -> down = rowHeaderNode[0];
	tmp1Row = m1 -> down;
	tmp2Col = m2 -> right;
	//printf("(%d, %d)\n", mRow, mCol);
	int tmpValue;
	for(i = 0; i < mRow; i++){
		last = rowHeaderNode[i];
		//printf("i=%d\n", i);
		tmp1 = tmp1Row -> right;
		for(j = 0; j < mCol; j++){
			//printf("j=%d\n", j);
			tmpValue = 0;
			tmp2 = tmp2Col -> down;
			for(k = 0; k < m1 -> u.entry.col; k++){
				if(tmp1 != NULL && tmp2 != NULL){
					if((i == tmp1 -> u.entry.row) && (k == tmp1 -> u.entry.col) &&
					   (k == tmp2 -> u.entry.row) && (j == tmp2 -> u.entry.col)){
						tmpValue += (tmp1 -> u.entry.value)*(tmp2 -> u.entry.value);
						tmp1 = tmp1 -> right;
						tmp2 = tmp2 -> down;
						//printf("(%d, %d)*(%d, %d)=%d\n", i, k, k, j, tmpValue);
					}
					else if((i == tmp1 -> u.entry.row) && (k == tmp1 -> u.entry.col)){
						tmp1 = tmp1 -> right;
					}
					else if((k == tmp2 -> u.entry.row && j == tmp2 -> u.entry.col)){
						tmp2 = tmp2 -> down;
					}
				}
			}
			//printf(">%d\n", tmpValue);
			tmp = newEntryNode(i, j, tmpValue);
			last -> right = tmp;
			last = tmp;
			colHeaderNode[j] -> down = tmp;
			colHeaderNode[j] = tmp;
			tmp1 = tmp1Row -> right;
			tmp2Col = tmp2Col -> u.next;
		}
		last -> right = NULL;
		tmp1Row = tmp1Row -> u.next;
		tmp2Col = m2 -> right;//back to first col
	}
	for(i = 0; i < mCol; i++){
		colHeaderNode[i] -> down = NULL;
	}
	return m;
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
				if((i == (tmp -> u.entry.row)) && (j == (tmp -> u.entry.col))){
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

void printTransposeMatrix(const matrixPtr m){
	int i, j;
	int row = m -> u.entry.row;
	int col = m -> u.entry.col;
	matrixPtr tmp, tmpCol;
	tmpCol = m -> right;
	for(i = 0; i < col; i++){
		tmp = tmpCol -> down;
		for(j = 0; j < row; j++){
			if(tmp != NULL){
				//printf("%d, %d\n", tmp->u.entry.row, tmp->u.entry.col);
				if((i == (tmp -> u.entry.col)) && (j == (tmp -> u.entry.row))){
					printf("%d", tmp->u.entry.value);
					tmp = tmp -> down;
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
		tmpCol = tmpCol -> u.next;
	}
}
