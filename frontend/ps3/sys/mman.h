#ifndef MMAN_H
#define MMAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <sys/memory.h>

#define PROT_READ       0x0b001
#define PROT_WRITE      0x0b010
#define PROT_EXEC       0x0b100
#define MAP_PRIVATE     2
#define MAP_ANONYMOUS   0x20

#define MAP_FAILED      ((void *)-1)

static inline void* mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset)
{
   (void)prot;
   (void)flags;
   (void)fd;
   (void)offset;
   
   sys_addr_t loc_addr = (sys_addr_t) addr;
   
   if( sys_mmapper_allocate_address(len, SYS_MEMORY_ACCESS_RIGHT_ANY | SYS_MEMORY_PAGE_SIZE_1M, 0x10000000, &loc_addr) != 0 )
       return MAP_FAILED;
   
   if(!loc_addr)
		return MAP_FAILED;

   if( sys_mmapper_change_address_access_right(loc_addr, SYS_MEMORY_PROT_READ_WRITE) != 0)
        return MAP_FAILED;

   return (void *) loc_addr;
}

static inline int mprotect(void *addr, size_t len, int prot)
{
   (void)addr;
   (void)len;
   (void)prot;
   return 0;
}

static inline int munmap(void *addr, size_t len)
{
   return sys_mmapper_free_address((sys_addr_t) addr);
}

#ifdef __cplusplus
};
#endif

#endif // MMAN_H
