#include "extension.h"

char** read_file(char* filepath) {
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

  int i;
  // Alocate space for the next line
  words[i] = malloc(max_line_len);

  while (fgets(words[i], max_line_len-1,fp) != NULL) {
    int j;

    /* Have we gone over our line allocation? */
    if (i >= lines_allocated) {
      int new_size;

      /* Double our allocation and re-allocate */
      new_size = lines_allocated*2;
      words = (char **)realloc(words,sizeof(char*)*new_size);
      if (words==NULL) {
        fprintf(stderr,"Out of memory.\n");
        exit(3);
      }
      lines_allocated = new_size;
    }

    /* Allocate space for the next line */
    words[i] = malloc(max_line_len);
    if (words[i]==NULL) {
      fprintf(stderr,"Out of memory (3).\n");
      exit(4);
    }

    /* Get rid of CR or LF at end of line */
    for (j=strlen(words[i])-1; j>=0 && (words[i][j]=='\n' || words[i][j]=='\r'); j--) {
      words[i][j+1]='\0';
    }
    i++;
  /* Close file */
  fclose(fp);
  return words;

  }
}
