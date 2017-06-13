#include "ctap.h"

char** read_file(char *filepath) {

  int lines_allocated = 128;
  int max_line_len = 100;

  /* Allocate lines of text */
  char** words = malloc(sizeof(char*)*lines_allocated);
  if (words==NULL) {
    fprintf(stderr,"Out of memory (1).\n");
    exit(1);
  }

  FILE *fp = fopen(filepath, "r");
  if (fp == NULL) {
    fprintf(stderr,"Error opening file.\n");
    exit(2);
  }

  int i = 0;
  // Alocate space for the next line
  words[i] = malloc(max_line_len);

  while (fgets(words[i], max_line_len-1,fp) != NULL) {
    words[i] = trim_whitespace(words[i]);
    i++;
  }

  /* Close file */
  fclose(fp);
  return words;

}
