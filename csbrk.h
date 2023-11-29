
#include <stdint.h>
#include <stdlib.h>

#define PAGESIZE 4096

void *csbrk(intptr_t increment);
int check_malloc_output(void *payload_start, size_t payload_length);
