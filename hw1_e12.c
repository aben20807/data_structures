#include <stdio.h>
#include <string.h>

void recursive(char **, int *, const int, const int, const int, const int);

int main(){
	while(1){
		/*read input*/
		printf("Please enter a string ex:{a,b,c}. enter '-1' to end program\n");
		char readString[100];
		gets(readString);
		if(strcmp(readString, "-1") == 0)break;
		int numOfElements = 0;
		int len = strlen(readString);
		int i;//used for index in for-loop
		for(i = 0; i < len; i++){
			if(readString[i] == ','){
				numOfElements++;//count the number of elements
			}
		}
		numOfElements += 1;//add the last element
		
		/*split input*/
		char *element[numOfElements];//array of string
		char *del = "{,}";//the symbols to split string
		char *p;
		int count = 0;//index to store string
		element[count++] = strtok(readString, del);//split
		while(p = strtok(NULL, del)){
			element[count++] = p;
		}
		
		/*use recursive to compute all set*/
		int index[numOfElements];
		for(i = 0; i < numOfElements; i++){
			index[i] = 0;//initialize the index to all false at begin
		}
		for(i = 0; i <= numOfElements; i++){//follow a sequence in size from 0 to number of elements
			recursive(element, index, i, 0, 0, numOfElements);
		}
		
		/*print the number of all kinds of set*/
		int numOfSet = 1;
		while(numOfElements--){
			numOfSet *= 2;
		}
		printf("Powerset 裡總共有 %d 個集合\n", numOfSet);
	}
	return 0;
}

void recursive(char **ele, int *index, const int incrementSize, const int positionOfIndex, const int n, const int numOfElements){
	/*print answer*/
	int i;//used for index in for-loop
	if(n == incrementSize){//when size is matched print one solution
		int numOfComma = incrementSize - 1;
		printf("{");
		for(i = 0; i < numOfElements; i++){
			if(index[i] == 1){//print element whose index is true
				printf("%s", ele[i]);
				if(numOfComma > 0){
					printf(",");//if the element is the last one don't print ","
					numOfComma--;
				}
			}
		}
		printf("}\n");
		return;
	}
	if(positionOfIndex == numOfElements)return;
	
	/*recursive*/
	index[positionOfIndex] = 1;
	recursive(ele, index, incrementSize, positionOfIndex+1, n+1, numOfElements);
	index[positionOfIndex] = 0;
	recursive(ele, index, incrementSize, positionOfIndex+1, n, numOfElements);
}
