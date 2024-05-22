#include <stdio.h>
#include <stdlib.h>
#define N 3

int main(){
	int start, move;
	int nopts[N+2]; //array of top of stacks
	int option[N+2][N+2]; //array of stacks of options
	int i, candidate;
    int numSets;
    int targetSum;
    int matrix[100][100];
    int subset[100];
    FILE *file = fopen("input.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fscanf(file, "%d", &numSets); // Read the number of sets
    
    for (int i = 0; i < numSets; i++) {
        int targetSum;
        fscanf(file, "%d", &targetSum);

        int numIntegers = 0;
        while (fscanf(file, "%d", &matrix[i][numIntegers]) == 1) {
            numIntegers++;
            if (fgetc(file) == '\n') {
                break;
            }
        }
        
        printf("S = {");
        for (int j = 0; j < numIntegers; j++) {
            if (j > 0) {
                printf(", ");
            }
            printf("%d", matrix[i][j]);
        }
        printf("}");
        printf("\n");
        printf("k = %d\n", targetSum);
        printf("\n");
    }

    fclose(file);

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
				for(candidate=N;candidate>=1;candidate--)
				{
					for(i=move-1;i>=1;i--)
						if(candidate==option[i][nopts[i]] || candidate >=option[i][nopts[i]]) break;
					if(!(i>=1))
						option[move][++nopts[move]] = candidate;
				}
			}
		}
		else 
		{
            for(i=1;i<move;i++)
                printf("%2i",option[i][nopts[i]]);
            printf("\n");
			move--;
			nopts[move]--;
            
		}
	}
}