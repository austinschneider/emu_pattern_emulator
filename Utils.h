/*
 * Utils.h
 *
 *  Created on: Apr 8, 2015
 *      Author: Austin
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <iomanip>
#include <iostream>

namespace emu {
namespace utils {

/* Macro to format char[] as hex for ostreams */
#define HEX(x)  std::setw(2) << std::setfill('0') << std::hex<<int(x)
#define DEC()   std::dec << std::setfill(' ')

/* Common funtions */

/* Hard limit of pattern size */
#define MAX_PAT_SIZE 1024*1024 // 1 GB

/* Returns the size of a file */
int file_size(FILE *fp);

/* A funtion to read a pattern file into a buffer.
 * filename = name of a file to read
 * *buf = pointer char array that will be allocated and filled (remeber to free)
 * verbose = a verbosity flag
 * return value: >=0 indicated the size of the pattern
 * return value: <0 indicated an error
 */
int get_pattern(char* filename, char **buf, int verbose);

/* Print array of hex numbers */
void dumphex(int n, char* buf, std::ostream* s = &std::cout);

/* Save this block (must have size RAMPAGE_SIZE) to a file */
int save_page_to_file(int pageid, char* block);

/* Fill block (must have size RAMPAGE_SIZE) with contents of file for this pageid
 * return 0 if successful
 */
int get_sequential_block(int pageid, char* block, int start = 2);

/* Fill block (must have size RAMPAGE_SIZE) with contents of file for this pageid
 * return 0 if successful
 */
int get_page_from_file(int pageid, char* block);

/* Little endian conversion of first sizeof(int) bytes in c to an unsigned int */
unsigned int bytes2int(char* c);

/* little endian conversion of first sizeof(short) bytes in c to an unsigned short */
unsigned short bytes2short(char* c);

/* get formated time string */
std::string time_string(bool terse = true);

}
}

#endif /* UTILS_H_ */
