#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int rand_num_fun(int r)
{
	 int temp;
	 srand(time(NULL));
	 temp=rand()%5;

	 while(1){
	 	if(r == temp){
	 		temp = rand()%5;
	 	}else{
	 		break;
	 	}
	 }
	 return temp;
}