#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

// Memory allocator by Kernighan and Ritchie,
// The C programming Language, 2nd ed.  Section 8.7.

typedef long Align;

union header {
  struct {
    union header *ptr;
    uint size;
  } s;
  Align x;
};

typedef union header Header;

static Header base;
static Header *freep;

void
free(void *ap)
{
  Header *bp, *p;

  bp = (Header *)ap - 1;
  for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
    if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
      break;
  if (bp + bp->s.size == p->s.ptr) {
    bp->s.size += p->s.ptr->s.size;
    bp->s.ptr = p->s.ptr->s.ptr;
  } else
    bp->s.ptr = p->s.ptr;
  if (p + p->s.size == bp) {
    p->s.size += bp->s.size;
    p->s.ptr = bp->s.ptr;
  } else
    p->s.ptr = bp;
  freep = p;
}

static Header *
morecore(uint nu)
{
  char *p;
  Header *hp;

  if (nu < 4096)
    nu = 4096;
  p = sbrk(nu * sizeof(Header));
  if (p == SBRK_ERROR)
    return 0;
  hp = (Header *)p;
  hp->s.size = nu;
  free((void *)(hp + 1));
  return freep;
}

void *
malloc(uint nbytes)
{
  Header *p, *prevp;
  uint nunits;

  nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
  if ((prevp = freep) == 0) {
    base.s.ptr = freep = prevp = &base;
    base.s.size = 0;
  }
  for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr) {
    if (p->s.size >= nunits) {
      if (p->s.size == nunits)
        prevp->s.ptr = p->s.ptr;
      else {
        p->s.size -= nunits;
        p += p->s.size;
        p->s.size = nunits;
      }
      freep = prevp;
      return (void *)(p + 1);
    }
    if (p == freep)
      if ((p = morecore(nunits)) == 0)
        return 0;
  }
}

#define PGSIZE 4096
#define MAXPG 16// 

char *pages[MAXPG];
int pageSize[MAXPG]; // chunk size that the page is used for 
char used[MAXPG][256]; // used [i][j] = 1 if chunk j in page i is taken
int npages = 0; //pages we have


// allocates nbytes from a segragated list
void * 
block_alloc(int nbytes)
{ 
  //nbytes is how much space the caller asked for
  if(nbytes <= 0){
    return 0; // nothing to give
  }
  int size = 16; // starting smallest page size to allocate space from, double from here
  while(size < nbytes){
    size = size * 2;//keep doubling until enough space is found or allocated
  }
  if(size > PGSIZE){
    return 0; // too big
  }

  for(int i = 0; i < npages; i++){
    if(pageSize[i] == size){
      for(int j = 0; j < PGSIZE / size; j++){
        if(used[i][j] == 0){
          used[i][j] = 1; // if it is 0 its free if its free then we mark it as used sicne it will be used
          //pages[i] is the start address, j is chunk number
          // j * size offset
          return pages[i] + j * size; //gives the memory address
        }
      }
    }
  }
  // we have hit the limit of pages to use
  if(npages == MAXPG){
    return 0;
  } 

}

// frees an allocation made from an allocated list
// needs the list that block_alloc returned
void 
block_free(void *ptr)
{
  int memAddress = 0;
  for(int i = 0; i < npages; i++){
    for(int j = 0; j < PGSIZE / pageSize[i]; j++){
      memAddress = pages[i] + j * pageSize[i];
      if(memAddress == ptr){
        used[i][j] = 0; // free up the used block
        return;
      }
    }
  }
}
