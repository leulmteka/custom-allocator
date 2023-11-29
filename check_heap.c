
#include "umalloc.h"

//Place any variables needed here from umalloc.c as an extern.
extern memory_block_t *free_head;

int check_heap() {

   memory_block_t* curr = free_head;
   memory_block_t* prev = NULL;
//   assert(curr != NULL);


   while (curr)
   {
       if (is_allocated(curr))
       {
           return -1;
       }
       
       //printf(curr);
       ;
       //check order
       if (prev != NULL && curr <= prev)
       {
           return -1;
       }
       
       //check overlap
       size_t size = curr->block_size_alloc;
       if(prev != NULL && (char*) prev + prev->block_size_alloc > (char*)curr){
        return -1;
       }

       //check align
       if (size != ALIGN(size)){
            return -1;
       }
   }

   return 0;
   }
