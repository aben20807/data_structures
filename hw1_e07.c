#include <stdio.h>

int iterative(int);
int recursive(int);

int main(){
	int n;
	while(1){
		printf("Please enter a number bigger than 0. enter '-1' to end program\n");
		scanf("%d", &n);
		if(n == -1)break;
		if(n >= 13){
			printf("overflow\n");
			continue;
		}
		/*iterative*/
		int ans_i = iterative(n);
		printf("Iterative : %d\n", ans_i);
		
		/*recursive*/
		int ans_r = recursive(n);
		printf("Recursive : %d\n", ans_r);
	}
	return 0;
}

int iterative(int num){
	int sum = 1;//init sum of using iterative
	int i;
	for(i = 1; i <= num; i++){
		sum *= i;
	}
	return sum;
}

int recursive(int num){
	if(num <= 1){
		return 1;
	}
	else{
		return num * recursive(num - 1);//recursive
	}
}
