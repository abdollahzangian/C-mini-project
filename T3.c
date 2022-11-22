#include <stdlib.h>
#include <stdio.h>

int main()
{
	int number;
  	printf("Enter the number :\n");
 	scanf("%d",&number);
		if(10<= number && number<=99){
			if(number%2 == 0){
			printf(" %d is even",number);
			}	
			else{
			printf("%d is odd",number);
			}
	    }
	    else{
			printf("%d is not two digit!", number);
	    }

 	return 0;
}
