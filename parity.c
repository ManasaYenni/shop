#include<stdio.h>
int checkparity(int num){
	int count=0;
	while(num){
		count+=num&1;
		num>>=1;
	}
	return count%2==0;
}
int main(){
	int number;
	printf("enter a number:");
	scanf("%d",&number);
	if(checkparity(number))
	    printf("even parity\n");
	else
	   printf("odd parity\n");
	return 0;
}
