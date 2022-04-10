#include <stdio.h>
#include <string.h>

#include "mytar.h"


int main(int argc, char **argv) {
    if (argc < 2) { // usage tip
        printf("Usage: %s [OPTION...] [FILE]...\n", argv[0]);
        printf("Try: '%s -h', for a list of possible options.\n\n", argv[0]);
        fail_with_msg("Too few arguments");
    }

    if (strcmp(argv[1], "-h") == 0) { // HELP
        printf("%s stores multiple files into a single archive\nand can restore files from the archive.\n", argv[0]);
        printf("Usage: %s [OPTION] [FILE]...\n", argv[0]);
        printf("\nPossible options:\n '-h' for help\n '-x' for extracting\n '-c' for archiving\n '-p' for printing\n");
        printf("\nExamples:\n %s -x archive.tar # extracts all files from archive.tar\n", argv[0]);
        printf(" %s -c archive.tar file1 file2 file3 # creates archive.tar containing file1, file2 and file3\n", argv[0]);
        printf(" %s -t archive.tar # prints the contents of archive.tar to stdout\n", argv[0]);
    } else if (strcmp(argv[1], "-x") == 0) { // EXTRACT
        if (argc != 3)
            fail_with_msg("Invalid number of arguments for '-x' option");
        mytar_extract(argv[2]);
    } else if (strcmp(argv[1], "-c") == 0) { // ARCHIVE
        if (argc < 4)
            fail_with_msg("Not enough arguments for '-c' option");
        mytar_archive(argv[2], argv + 3, argc - 3);
    } else if (strcmp(argv[1], "-t") == 0) { // PRINT
        if (argc != 3)
            fail_with_msg("Invalid number of arguments for '-t' option");
        mytar_print(argv[2]);
    } else { // provided option is not valid
        fail_with_msg("Invalid option");
    }

    return 0;
}