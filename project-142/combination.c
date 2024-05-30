#include <stdio.h>
#include <stdlib.h>
#define N 10

int main(){
	int start, move;
	int nopts[100]; //array of top of stacks
	int option[100][100]; //array of stacks of options
	int i, candidate;
	int subset[100] = {3, 21, 17, 14, 8, 1, 9, 34, 5, 11};

	move = start = 0; 
	nopts[start]= 1;
	
	while (nopts[start] >0) //while dummy stack is not empty
	{
		if(nopts[move]>0) 
		{
			move++;
			nopts[move]=0; //initialize new move

			if(move == 1){
				for(candidate = N; candidate >=1; candidate --) 
				{
					nopts[move]++;
					option[move][nopts[move]] = candidate;         
				}
			}
			else{
				for(candidate=N;candidate>=0;candidate--)
				{
					for(i=move-1;i>=0;i--)
						if(candidate==option[i][nopts[i]] || subset[candidate] <=subset[option[i][nopts[i]]] ) break;
					if(i<1)
						option[move][++nopts[move]] = candidate;
				}
			}
			for(i=1;i<move;i++)
					printf("%2i ",subset[option[i][nopts[i]]]);
				printf("\n");
		}
		else 
		{
			
			move--;
			nopts[move]--;
            
		}
	}
}