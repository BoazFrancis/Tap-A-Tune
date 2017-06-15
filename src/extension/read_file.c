#include "ctap.h"

char** read_file(char *filepath) {
  int lines_allocated = 128;

  /* Allocate lines of text */
  char **words = malloc(sizeof(char*)*lines_allocated);
  if (words == NULL) {
    fprintf(stderr,"Out of memory (1).\n");
    exit(1);
  }

  FILE *fp = fopen(filepath, "r");

  if (fp == NULL) {
    fprintf(stderr,"Error opening file.\n");
    exit(2);
  }


  int i = 0;
  words[i] = malloc(MAX_LINE_LENGTH);
  while (fgets(words[i], MAX_LINE_LENGTH-1,fp) != NULL) {
    words[i] = trim_whitespace(words[i]);
    i++;
    words[i] = malloc(MAX_LINE_LENGTH);
  }

  fclose(fp);
  return words;
}

int count_lines(char *filepath) {
  FILE *fp = fopen(filepath, "r");
  if (fp == NULL) {
    fprintf(stderr,"Error opening file.\n");
    exit(2);
  }
  char buff[MAX_LINE_LENGTH];
  int count = 0;
  while(fgets(buff, MAX_LINE_LENGTH, fp) != NULL) {
    count++;
  }
  return count;
}
