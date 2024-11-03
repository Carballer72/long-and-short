#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 255

void to_uppercase(char *line) {
    for (int i = 0; line[i]; i++) {
        line[i] = toupper(line[i]);
    }
}

void to_lowercase(char *line) {
    for (int i = 0; line[i]; i++) {
        line[i] = tolower(line[i]);
    }
}

int main(int argc, char *argv[]) {
    // Check for the correct number of arguments
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <source_file> <short_file> <long_file>\n", argv[0]);
        return 1;
    }

    char *source_filename = argv[1];
    char *short_filename = argv[2];
    char *long_filename = argv[3];

    FILE *source_file = fopen(source_filename, "r");
    FILE *short_file = fopen(short_filename, "w");
    FILE *long_file = fopen(long_filename, "w");

    // Check if the files were opened successfully
    if (!source_file || !short_file || !long_file) {
        perror("Error opening files");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int short_lines_count = 0;
    int long_lines_count = 0;

    // Read from the source file line by line
    while (fgets(line, sizeof(line), source_file)) {
        // Remove newline character if present
        line[strcspn(line, "\n")] = 0;

        if (strlen(line) < 20) {
            to_uppercase(line);
            fprintf(short_file, "%s\n", line);
            short_lines_count++;
        } else {
            to_lowercase(line);
            fprintf(long_file, "%s\n", line);
            long_lines_count++;
        }
    }

    // Close all files
    fclose(source_file);
    fclose(short_file);
    fclose(long_file);

    // Display the number of lines written to each file
    printf("%d lines written to %s\n", short_lines_count, short_filename);
    printf("%d lines written to %s\n", long_lines_count, long_filename);

    return 0;
}