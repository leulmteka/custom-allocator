#include "umalloc.h"
#include "csbrk.h"
#include <stdio.h>
#include <assert.h>
#include "ansicolors.h"

const char author[] = ANSI_BOLD ANSI_COLOR_RED "" ANSI_RESET;

/*
 * The following helpers can be used to interact with the memory_block_t
 * struct, they can be adjusted as necessary.
 */

// A sample pointer to the start of the free list.
memory_block_t *free_head;

/*
 * is_allocated - returns true if a block is marked as allocated.
 */
bool is_allocated(memory_block_t *block) {
    assert(block != NULL);
    return block->block_size_alloc & 0x1;
}

/*
 * allocate - marks a block as allocated.
 */
void allocate(memory_block_t *block) {
    assert(block != NULL);
    block->block_size_alloc |= 0x1;
}


/*
 * deallocate - marks a block as unallocated.
 */
void deallocate(memory_block_t *block) {
    assert(block != NULL);
    block->block_size_alloc &= ~0x1;
}

/*
 * get_size - gets the size of the block.
 */
size_t get_size(memory_block_t *block) {
    assert(block != NULL);
    return block->block_size_alloc & ~(ALIGNMENT-1);
}

/*
 * get_next - gets the next block.
 */
memory_block_t *get_next(memory_block_t *block) {
    assert(block != NULL);
    return block->next;
}

/*
 * put_block - puts a block struct into memory at the specified address.
 * Initializes the size and allocated fields, along with NUlling out the next 
 * field.
 */
void put_block(memory_block_t *block, size_t size, bool alloc) {
    assert(block != NULL);
    assert(size % ALIGNMENT == 0);
    assert(alloc >> 1 == 0);
    block->block_size_alloc = size | alloc;
    block->next = NULL;
}

/*
 * get_payload - gets the payload of the block.
 */
void *get_payload(memory_block_t *block) {
    assert(block != NULL);
    return (void*)(block + 1);
}

/*
 * get_block - given a payload, returns the block.
 */
memory_block_t *get_block(void *payload) {
    assert(payload != NULL);
    return ((memory_block_t *)payload) - 1;
}

/*
 * The following are helper functions that can be implemented to assist in your
 * design, but they are not required. 
 */

/*
 * find - finds a free block that can satisfy the umalloc request.
 */
memory_block_t *find(size_t size) {
    //* STUDENT TODO
    memory_block_t* curr = free_head;
    while(curr){
        if(!is_allocated(curr) && get_size(curr) >= size){
            return curr;
        }
        curr = get_next(curr);
    }
    return NULL;
}

/*
 * extend - extends the heap if more memory is required.
 */
memory_block_t *extend(size_t size) {
    //* STUDENT TODO
    size_t extendSize = ALIGN(size);
    memory_block_t* extendBlock = csbrk(extendSize);
    if(extendBlock){
        put_block(extendBlock, extendSize, false);
        return extendBlock;
    }else{
        return NULL;
    }
}

memory_block_t *split(memory_block_t *block, size_t size)
{
    //* STUDENT TODO

    if (sizeof(memory_block_t) <= get_size(block) - size)
    {
        memory_block_t *new_block = (memory_block_t *)(block + size);
        put_block(new_block, get_size(block) - size, false);
        return block;
    }
    else
    {
        return NULL;
    }
}


    /*
     * coalesce - coalesces a free memory block with neighbors.
     */
    memory_block_t *coalesce(memory_block_t * block)
    {
        //* STUDENT TODO
        return NULL;

    }

/*
 * uinit - Used initialize metadata required to manage the heap
 * along with allocating initial memory.
 */
int uinit() {
    //* STUDENT TODO
    free_head = csbrk(PAGESIZE);
    if(!free_head){
        return -1;
    }
    put_block(free_head, PAGESIZE, false);
    return 0;
}

/*
 * umalloc -  allocates size bytes and returns a pointer to the allocated memory.
 */
void *umalloc(size_t size) {
    //* STUDENT TODO
   if(size == 0){
    return NULL;
   }
   memory_block_t* new = find(size);
   ;
   if(!new){
        new = extend(sizeof(memory_block_t) + size);
   }else if(ALIGNMENT > get_size(new) - size){
        new = split(new, size);
   }
   allocate(new);
   void* p_payload = get_payload(new);
   return p_payload;

}

/*
 * ufree -  frees the memory space pointed to by ptr, which must have been called
 * by a previous call to malloc.
 */
void ufree(void *ptr) {
    //* STUDENT TODO
    if (ptr == NULL)
    {
        return;
    }
    memory_block_t *block = get_block(ptr);
    deallocate(block);
}
