#include <stdio.h>
#include <stdlib.h>

// Definitions - need to go in .h file
void read_binary_file(int* m, char* path);
void fetch_decode_execute(int* m);
int extractBits(int* n, int start, int length);

int main(int argc, char** argv) {

  // Check for correct number of arguments
  if (argc != 2) {
    printf("No file provided\n");
    return EXIT_FAILURE;
  }

  // Memory store
  int max_memory_size = (1 << 4);
  int memory[max_memory_size];

  // Initialise size of memory
  for (int i = 0; i < max_memory_size; i++) {
    memory[i] = 0;
  }

  read_binary_file(memory, argv[1]);

  // Print out memory (for testing only)
  for (int i=0; i<sizeof(memory)/sizeof(int); i++) {
    printf("%x\n", memory[i]);
  }

  fetch_decode_execute(memory);

  return 0;

}

void read_binary_file(int* m, char* path) {
  
  // Open the input file
  FILE* input = fopen(path, "rb");

  // Reading the input file
  int pos = 0;
  int read_success = -1;

  // Keep reading bytes into memory until nothing left to read
  while (read_success != 0) {
    read_success = fread(&m[pos], sizeof(int), 1, input);
    pos++;
  }

  // Close the file
  fclose(input);

}

void fetch_decode_execute(int* m) {
  
  int pc = 0;
  int ir = 0;

  do {
    
    // Get the next instruction and increment PC
    ir = m[pc];
    pc++;

    // Get the 4 most significant bits which is the "Cond"
    int cond = extractBits(&ir, 28, 4);

    switch (cond) {
      
      // Z set
      case 0:
      break;

      // Z clear
      case 1:
      break;

      // N equals V
      case 10:
      break;

      // N not equal to V
      case 11:
      break;

      // Z clear AND (N equals V)
      case 12:
      break;

      // Z set OR (N not equals to V)
      case 13:
      break;

      // Al flag
      case 14:
      break;

      default:
      break;

    }

    /*
      switch (get_instruction_type(&ir)) {
        
        case DATA_PROCESSING:
        data_processing(&ir);
        break;

        case BRANCH:
        branch(&ir);
        break;

        case MULTIPLY:
        multiply(&ir);
        break;

        case SINGLE_DATA_TRANSFER:
        single_data_transfer(&ir);
        break;
      }

    */

  }
  while (ir != 0);

}

int extractBits(int* n, int start, int length) {

  // Set up an empty mask
	int mask = 0;

  // Fill the mask with 1s from start to length
	for (int i = 0; i < length; i++) {
		mask |= (1 << (start + i));
	}

  // Find the common bits in n
  int common = *n & mask;

  // Return just those bits i.e. ignore any zeros to the right by shifting
	return (unsigned int) common >> start;

}