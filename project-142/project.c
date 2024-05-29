#include <stdio.h>
#include <stdlib.h>
#define MAX_NUMBERS 100

int main() {
    int numSets;
    int matrix[MAX_NUMBERS][MAX_NUMBERS];
    int nopts[MAX_NUMBERS]; // array of top of stacks
    int option[MAX_NUMBERS][MAX_NUMBERS]; // array of stacks of options
    int move, start;
    int subset[MAX_NUMBERS];
    int currentSum = 0;
    FILE *file = fopen("input.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fscanf(file, "%d", &numSets);
    
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
        printf("}\n");
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
                    for (int candidate = numIntegers - 1; candidate >= 0; candidate--) {
                        int isValid = 1;
                        for (int k = move - 1; k >= 1; k--) {
                            if (candidate == option[k][nopts[k]] || matrix[i][candidate] <= matrix[i][option[k][nopts[k]]]) {
                                isValid = 0;
                                break;
                            }
                        }
                        if (isValid) {
                            option[move][++nopts[move]] = candidate;
                        }
                    }
                }

                currentSum = 0;
                for (int k = 1; k < move; k++) {
                    subset[k - 1] = matrix[i][option[k][nopts[k]]];
                    currentSum += subset[k - 1];
                }

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
        if (subsetChecker == 0){
            printf("There are no subsets available! \n");
        }
        printf("\n");
    }

    fclose(file);

    return 0;
}