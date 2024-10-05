#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void transpile(FILE *inputFile, FILE *outputFile) {
    char line[256];

    // Loop through each line in the file
    while (fgets(line, sizeof(line), inputFile)) {
        // Check if the line contains the 'func' statement
        if (strstr(line, "func") != NULL) {
            char *funcText = strstr(line, "func") + strlen("func "); // Get text after "func"
            fprintf(outputFile, "%s", funcText);  // Use fprintf to write to the output file
         
        }
else if (strstr(line, "end") != NULL) {
    fprintf(outputFile, "ret\n"); // Write "ret" to the output file
}       else if (strstr(line, "call") != NULL) {
            fprintf(outputFile, "%s", line); // Write the call line to the output file
        }
       else if (strstr(line, "dw") != NULL) {
            fprintf(outputFile, "%s", line); // Write the dw line to the output file
        }
        else if (strstr(line, "asm") != NULL) {
            char *funcText = strstr(line, "asm") + strlen("asm ");
            fprintf(outputFile, "%s", funcText); // Write the assembly to the output file
        }     
       else if (strstr(line, "jmp") != NULL) {
            fprintf(outputFile, "%s", line); // Write the jmp line to the output file
       }    
        else if(strstr(line, "//") != NULL)
        {
            printf(line);
        }
        else if(strstr(line, "") != NULL)
        {
            int i = 0;
        }
        else if(strstr(line, " ") != NULL)
        {
            int i = 0;
        }
        else {
            printf("%s", line); 
            printf("Error! \n");\
    }
}
}
int main(int argc, char *argv[]) {
    // Check command line arguments
    if (argc != 3) {
        printf("Usage: CST <input.cst> <output.asm>\n");
        return 1;
    }

    // Open the input file
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Open the output file
    FILE *outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile); // Close input file before returning
        return 1;
    }

    // Call the transpile function
    transpile(inputFile, outputFile);

    // Close the files
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
