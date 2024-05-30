#include <stdio.h>
#include <stdlib.h>
#define MAX_NUMBERS 100

int main() {
    int numSets;
    int matrix[MAX_NUMBERS][MAX_NUMBERS]; //matrix[setNo][sets] ex. matrix[1][3, 21, 17, 14, 8, 1, 9, 34, 5, 11]
    int nopts[MAX_NUMBERS]; // array of top of stacks
    int option[MAX_NUMBERS][MAX_NUMBERS]; // array of stacks of options
    int move, start; 
    int subset[MAX_NUMBERS]; 
    int currentSum = 0; 
    
    //opens the file input.txt for reading
    FILE *file = fopen("input.txt", "r");

    //checks if the file is properly opened
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    //gets the first integer on the first line which is the number of sets
    fscanf(file, "%d", &numSets);
    
    for (int i = 0; i < numSets; i++) {
        int targetSum;
        //gets the next line on the file which is the target sum of the subset sum problem
        fscanf(file, "%d", &targetSum);

        int numIntegers = 0;
        //loops through the same line and gets all of the integers until it meets a new line, 
        //also increments the number of integers when it encounters integers
        while (fscanf(file, "%d", &matrix[i][numIntegers]) == 1) {
            numIntegers++;
            if (fgetc(file) == '\n') {
                break;
            }
        }
        //just prints the set
        printf("S = {");
        for (int j = 0; j < numIntegers; j++) {
            if (j > 0) {
                printf(", ");
            }
            printf("%d", matrix[i][j]);
        }
        printf("}\n");
        //prints the target sum
        printf("k = %d\n", targetSum);
        printf("Subsets:\n");

        move = start = 0;
        nopts[start] = 1;
        int subsetChecker = 0;

        while (nopts[start] > 0) { // while dummy stack is not empty
            if (nopts[move] > 0) {
                move++;
                nopts[move] = 0; // initialize new move

                if (move == 1) {
                    for (int candidate = numIntegers - 1; candidate >= 0; candidate--) {
                        nopts[move]++;
                        option[move][nopts[move]] = candidate;
                    }
                } else {
                    for (int candidate = numIntegers; candidate >= 0; candidate--) {
                        int isValid = 1;
                        for (int k = move - 1; k >= 1; k--) {
                            //checks if the candidate has already been chosen before or if the candidate integer is less than or equal to the current integer
                            //if it satisfies the above condition, it means the candidate is not valid and the loop breaks
                            if (candidate == option[k][nopts[k]] || matrix[i][candidate] <= matrix[i][option[k][nopts[k]]]) {
                                isValid = 0;
                                break;
                            }
                        }
                        //if the candidate has not been chosen before or if it is larger than the integer, it is valid and thus added to the set
                        if (isValid) {
                            option[move][++nopts[move]] = candidate;
                        }
                    }
                }

                currentSum = 0;
                //adds all of the value of the candidates to the currentSum
                for (int k = 1; k < move; k++) {
                    subset[k - 1] = matrix[i][option[k][nopts[k]]];
                    currentSum += subset[k - 1];
                }

                //checks if the currentSum is equal to the target sum, and if it is, it prints the subset
                if (currentSum == targetSum) {
                    subsetChecker++;
                    printf("{");
                    for (int i = 0; i < move-1; i++) {
                        if (i > 0) {
                            printf(", ");
                        }
                        printf("%d", subset[i]);
                    }
                    printf("}\n");
                }
            } else {
                move--;
                nopts[move]--;
            }
        }
        //checks if there have been increments to the subset checker if = 0, it means that there are no subsets available, but if it is > 0, there are subsets available
        if (subsetChecker == 0){
            printf("There are no subsets available! \n");
        }
        printf("\n");
    }

    fclose(file);

    return 0;
}