// Define in separate file
#define max_memory_size (1 << 4)
#define number_of_registers 17

// Create the ARM struct
struct ARM {
   int memory[max_memory_size];
   int registers[number_of_registers];
   int pc;
   int ir;
};

// Reading binary files
void read_binary_file(int* memory, char* path);

// Bit-utils
int extract_bits(int* n, int start, int length);
int extract_bit(int* n, int start);

// Fetch-execute cycle
void fetch_decode_execute(struct ARM proc);
int check_condition_bits(struct ARM proc);
