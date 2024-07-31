//Niklas Helander, I used GPT 4o to guide me, VS Code to build and some help from stackoverflow

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Function to read lines from a file
char** read_lines(FILE *file, int *num_lines) {
    char **lines = NULL; //pointer to hold the lines
    size_t size = 0;
    ssize_t read;
    char *line = NULL;
    *num_lines = 0; //base the number of lines

    //Reading lines line by line
    while ((read = getline(&line, &size, file)) != -1) {
        lines = realloc(lines, (*num_lines + 1) * sizeof(char *));
        if (lines == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        lines[*num_lines] = strdup(line);
        (*num_lines)++; 
    }
    free(line); //Free the buffer
    return lines;
}

//Function to print in reverse order
void print_lines_reversed(FILE *output, char **lines, int num_lines) {
    for (int i = num_lines - 1; i >= 0; i--) {
        fprintf(output, "%s", lines[i]);
        free(lines[i]); 
    }
    free(lines);
}

//Main function
int main(int argc, char *argv[]) {
    FILE *input = stdin; //standard input
    FILE *output = stdout; //standard output
    int num_lines = 0; 
    char **lines; 

    //Check if there is too many arguments
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        return 1;
    }

    //Open input file
    if (argc > 1) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            return 1;
        }
    }

    //Open output file
    if (argc == 3) {
        if (strcmp(argv[1], argv[2]) == 0) {
            fprintf(stderr, "Input and output file must differ\n");
            return 1;
        }
        output = fopen(argv[2], "w");
        if (output == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
            fclose(input);
            return 1;
        }
    }

    //Read lines
    lines = read_lines(input, &num_lines);

    //Print lines in reverse order
    print_lines_reversed(output, lines, num_lines);

    //Close files if opened
    if (input != stdin) fclose(input);
    if (output != stdout) fclose(output);

    return 0;
}
