#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mytar.h"

static struct posix_header
{                              /* byte offset */
  char name[100];               /*   0 */
  char mode[8];                 /* 100 */
  char uid[8];                  /* 108 */
  char gid[8];                  /* 116 */
  char size[12];                /* 124 */
  char mtime[12];               /* 136 */
  char chksum[8];               /* 148 */
  char typeflag;                /* 156 */
  char linkname[100];           /* 157 */
  char magic[6];                /* 257 */
  char version[2];              /* 263 */
  char uname[32];               /* 265 */
  char gname[32];               /* 297 */
  char devmajor[8];             /* 329 */
  char devminor[8];             /* 337 */
  char prefix[155];             /* 345 */
                                /* 500 */
} header;

// store BLOCK_SIZE bytes of data
static char block[BLOCK_SIZE] = { 0 };

/** TODO: - fread and fwrite error checking 
 *        - issue a warning if the archive does not have an end marker
 *        - set all fields for each file (not just name, size and chksum)
 *        - created archives should be compatible with GNU Tar
*/
static void read_block(FILE *ar); // read a block of BLOCK_SIZE bytes
static void write_block(FILE *ar); // write a block of BLOCK_SIZE bytes
static char is_block_null(); // check if last read block contains only null bytes

static void init_header(); // init header with some default values
static void print_header(); // print all fields 
static void create_header(const char *file_name, long size); // create header for file
static void read_header(); // read header from block
static void write_header(FILE *ar); // write header with padding

static void read_file(FILE *ar, long size); // extract a file from the archive
static void write_file(FILE *ar, FILE *f, long size); // write a file to the archive with appropriate padding

static long read_file_size(); // read the file size from header
static long get_size_of_file(FILE *f); // returns the size (in bytes) of f
static long calculate_chksum(); // calculate chksum for current header
static void write_octal_to_str(long dec, char *s, long len); // converts dec to octal and writes it to string with leading zeros

static long dec_to_octal(long dec); // converts number to its octal representation

void fail_with_msg(const char *msg) {
    printf("Error: %s\n", msg);
    exit(EXIT_FAILURE);
}

void mytar_extract(const char *ar_name) {
    FILE *ar = fopen(ar_name, "rb");
    long file_size;
    if (!ar)
        fail_with_msg("Could not open archive");
    while (!feof(ar)) {
        read_block(ar);
        if (is_block_null()) // end of archive marker
            break;
        memcpy(&header, block, sizeof(header)); // copy header from read block
        file_size = read_file_size();
        read_file(ar, file_size);
    }
    fclose(ar);
}

void mytar_archive(const char *ar_name, char **files, int n) {
    FILE *ar = fopen(ar_name, "wb");
    if (!ar)
        fail_with_msg("Could not create archive");
    long file_size;
    for (int i = 0; i < n; ++i) {
        FILE *f = fopen(files[i], "rb");
        if (!f) {
            printf("Could not open %s\n", files[i]);
            continue;
        }
        file_size = get_size_of_file(f);
        create_header(files[i], file_size);
        write_header(ar);
        write_file(ar, f, file_size);
        fclose(f);
    }
    // write end of archive marker
    memset(block, 0, BLOCK_SIZE);
    write_block(ar);
    write_block(ar);
    fclose(ar);
}

void mytar_print(const char *ar_name) {
    FILE *ar = fopen(ar_name, "rb");
    if (!ar)
        fail_with_msg("Could not open archive");
    long file_size = 0;
    while (!feof(ar)) {
        read_block(ar);
        if (is_block_null()) // end of archive marker
            break;
        memcpy(&header, block, sizeof(header)); // copy header from read block
        print_header();
        file_size = read_file_size();
        // find the next header and ignore file data
        if (file_size == 0) // empty file
            continue;
        fseek(ar, (file_size / BLOCK_SIZE) * BLOCK_SIZE, SEEK_CUR);
        if (file_size % BLOCK_SIZE)
            fseek(ar, BLOCK_SIZE, SEEK_CUR); // need to skip one more block
    }
    fclose(ar);
}

void read_block(FILE *ar) {
    fread(block, 1, BLOCK_SIZE, ar);
}

void write_block(FILE *ar) {
    fwrite(block, 1, BLOCK_SIZE, ar);
}

char is_block_null() {
    for (size_t i = 0; i < BLOCK_SIZE; ++i)
        if (block[i] != 0)
            return 0;
    return 1;
}

void init_header() {
    memset(&header, 0, sizeof(header)); // set header to zeros
    strcpy(header.mode, "0000664");
    strcpy(header.uid, "0001750");
    strcpy(header.gid, "0001750");
    strcpy(header.mtime, "14223654316");
    header.typeflag = '0';
    strcpy(header.magic, "ustar");
    memcpy(header.version, "00", sizeof(header.version));
}

void print_header() {
    printf("\n---HEADER BEGIN---\n");
    printf("name: %s\n", header.name);
    printf("mode: %s\n", header.mode);
    printf("uid: %s\n", header.uid);
    printf("gid: %s\n", header.gid);
    printf("size: %s\n", header.size);
    printf("mtime: %s\n", header.mtime);
    printf("chksum: %s\n", header.chksum);
    printf("typeflag: %c\n", header.typeflag);
    printf("linkname: %s\n", header.linkname);
    printf("magic: %s\n", header.magic);
    printf("version: %s\n", header.version);
    printf("uname: %s\n", header.uname);
    printf("gname: %s\n", header.gname);
    printf("devmajor: %s\n", header.devmajor);
    printf("devminor: %s\n", header.devminor);
    printf("prefix: %s\n", header.prefix);
    printf("---HEADER END---\n");
}

void create_header(const char *file_name, long size) {
    init_header(); // set all fields to default values or zeros
    strncpy(header.name, file_name, sizeof(header.name)); // copy name
    write_octal_to_str(size, header.size, sizeof(header.size) - 2); // copy size
    // write checksum (must be done last)
    write_octal_to_str(calculate_chksum(), header.chksum, sizeof(header.chksum) - 2); 
}

void read_header() {

}

void write_header(FILE *ar) {
    memset(block, 0, BLOCK_SIZE); // reset block
    memcpy(block, &header, sizeof(header)); // copy header to block
    write_block(ar);
}

void read_file(FILE *ar, long size) {

}

void write_file(FILE *ar, FILE *f, long size) {
    if (size == 0) // nothing to write
        return;
    int num_full_blocks = size / BLOCK_SIZE;
    for (int i = 0; i < num_full_blocks; ++i) {
        fread(block, 1, BLOCK_SIZE, f);
        write_block(ar);
    }
    int remainder = size % BLOCK_SIZE;
    if (remainder) { // block which requires padding
        memset(block, 0, BLOCK_SIZE);
        fread(block, 1, remainder, f);
        write_block(ar);
    }
}

long read_file_size() {
    static const long START_INDEX = sizeof(header.size) - 2;
    long size = 0;
    long p = 1;
    for (long i = START_INDEX; i >= 0; --i) { // convert from octal to decimal
        size += (long) (header.size[i] - '0') * p;
        p *= 8;
    }
    return size;
}

long get_size_of_file(FILE *f) {
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    return size;
}

void write_octal_to_str(long dec, char *s, long len) {
    long oct = dec_to_octal(dec);
    for (long i = len; i >= 0; --i) {
        s[i] = (oct % 10) + '0';
        oct /= 10;
    }
}

long calculate_chksum() {
    long sum = 0;
    unsigned char *header_byte = (unsigned char *) &header;
    for (size_t i = 0; i < sizeof(header); ++i)
        sum += header_byte[i];
    return sum;
}

long dec_to_octal(long dec) {
    long octal = 0, p = 1, remainder = 0;
    while (dec) {
        remainder = dec % 8;
        dec /= 8;
        octal += remainder * p;
        p *= 10;
    }
    return octal;
}