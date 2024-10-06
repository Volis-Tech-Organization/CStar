#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int forcount = 0;


void transpile(FILE *inputFile, FILE *outputFile) {
    char line[256];
    // Loop through each line in the file
    while (fgets(line, sizeof(line), inputFile)) {
       if (strstr(line, "include") != NULL) {
            // Get the filename from the include line
            char *file = strstr(line, "include") + strlen("include "); // Get text after "include "
            file[strcspn(file, "\n")] = 0; // Remove newline character
            
            // Open the included file
            FILE *includedFile = fopen(file, "r");
            if (includedFile == NULL) { 
                printf("Error: Could not open file: %s\n");
            }

            // Recursively call transpile to process the included file
            transpile(includedFile, outputFile);

            // Close the included file
            fclose(includedFile);
            continue; // Skip the rest of the loop for the current line
        }
        // Check if the line contains the 'func' statement
     else   if (strstr(line, "func") != NULL) {
            char *funcText = strstr(line, "func") + strlen("func "); // Get text after "func"
            fprintf(outputFile, "%s", funcText);  // Use fprintf to write to the output file
            printf("Initializing Function");
         
        }
else if (strstr(line, "end") != NULL) {
    fprintf(outputFile, "ret\n"); // Write "ret" to the output file
}       else if (strstr(line, "call") != NULL) {
            fprintf(outputFile, "%s", line); // Write the call line to the output file
        }
        else if (strstr(line, "asm") != NULL) {
            char *funcText = strstr(line, "asm") + strlen("asm ");
            fprintf(outputFile, "%s", funcText); // Write the assembly to the output file
        }     
       else if (strstr(line, "jmp") != NULL) {
            fprintf(outputFile, "%s", line); // Write the jmp line to the output file
       }  
else if (strstr(line, "je") != NULL) {
            fprintf(outputFile, "%s", line); // Write the jmp line to the output file
       }  

else if (strstr(line, "cmp") != NULL) {
            fprintf(outputFile, "%s", line); // Write the jmp line to the output file
       }         
       else if (strstr(line, "var") != NULL) {
    // Get the text after "var "
    char *val = strstr(line, "var") + strlen("var ");
    
    // Split the text based on the colon to separate the variable name from its value
    char varName[128];
    char varValue[256]; // To handle longer values like strings

    char *colonPos = strchr(val, ':');
    if (colonPos != NULL) {
        // Extract variable name
        size_t varNameLength = colonPos - val;
        strncpy(varName, val, varNameLength);
        varName[varNameLength] = '\0';  // Null-terminate the string

        // Extract variable value after the colon
        strcpy(varValue, colonPos + 1);

        // Remove leading and trailing whitespace from the value if necessary
        char *start = varValue;
        while (*start == ' ' || *start == '\t') start++;  // Remove leading spaces

        char *end = start + strlen(start) - 1;
        while (end > start && (*end == ' ' || *end == '\t' || *end == '\n')) *end-- = '\0';  // Remove trailing spaces

        // Output in the format: varName db varValue
        fprintf(outputFile, "%s db %s\n", strcat(varName,":"), start);
        printf("Writing variable: %s db %s\n", varName, start); // Debug
    } else {
        printf("Error: Invalid 'var' syntax in line: %s\n", line); // Debug
    }
}
else if (strstr(line, "char") != NULL) {
    // Get the text after "var "
    char *val = strstr(line, "char") + strlen("char ");
    
    // Split the text based on the colon to separate the variable name from its value
    char varName[128];
    char varValue[256]; // To handle longer values like strings

    char *colonPos = strchr(val, ':');
    if (colonPos != NULL) {
        // Extract variable name
        size_t varNameLength = colonPos - val;
        strncpy(varName, val, varNameLength);
        varName[varNameLength] = '\0';  // Null-terminate the string
        char charval = strcat(varValue,", 0");
        // Extract variable value after the colon
        strcpy(varValue, colonPos + 1);

        // Remove leading and trailing whitespace from the value if necessary
        char *start = charval;
        while (*start == ' ' || *start == '\t') start++;  // Remove leading spaces

        char *end = start + strlen(start) - 1;
        while (end > start && (*end == ' ' || *end == '\t' || *end == '\n')) *end-- = '\0';  // Remove trailing spaces

        // Output in the format: varName db varValue
        fprintf(outputFile, "%s db %s\n", strcat(varName,":"), start);
        printf("Writing variable: %s db %s\n", varName, start); // Debug
    } else {
        printf("Error: Invalid 'var' syntax in line: %s\n", line); // Debug
    }
}
        else if (strstr(line, "for") != NULL) {
            
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
