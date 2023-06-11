#ifndef MLTCRD_H
#define MLTCRD_H

#include <threads.h>

#if defined(__GNUC__)
  #define packed_stuct struct __attribute__((packed))
  #define unused_function __attribute__((unused))
#else
  #define packed_stuct struct
  #define unused_function
#endif

#if defined(__x86_64) || defined(__x86_64__)
  #define __MLTCRD_PAD_FTR_T (4)
#elif defined(__i386) || defined(i386) || defined(__i386__)
  #define __MLTCRD_PAD_FTR_T (0)
#endif

#define __MLTCRD_SIZEOF_FTR_T (  __SIZEOF_PTHREAD_MUTEX_T                     \
                               + __SIZEOF_PTHREAD_COND_T                      \
                               + __SIZEOF_POINTER__                           \
                               + __SIZEOF_POINTER__                           \
                               + __SIZEOF_INT__                               \
                               + __MLTCRD_PAD_FTR_T)

#define __MLTCRD_SIZEOF_PACK_T (  __SIZEOF_POINTER__                          \
                                + __SIZEOF_POINTER__                          \
                                + __SIZEOF_POINTER__)

/** Future result */
typedef struct ftr_t ftr_t;

/** Packaged task */
typedef struct pack_t pack_t;

/** Deallocator callable type */
typedef void (*dealloc_t) (void *);

/** Asynchronous callable type */
typedef void (*async_t) (void *, ftr_t *);

/** Future result states */
enum { ftr_unready, ftr_ready, ftr_failed, ftr_destroyed };

//-----------------------------------------------------------------------------
// Future result functions
//-----------------------------------------------------------------------------

extern int
ftr_create(ftr_t *future);

extern int
ftr_destroy(ftr_t *future);

extern int
ftr_set(ftr_t *future, void *result, dealloc_t dealloc);

extern int
ftr_fail(ftr_t *future);

extern int
ftr_wait(ftr_t *future);

extern int
ftr_get(ftr_t *future, void **result);

//-----------------------------------------------------------------------------
// Packaged task functions
//-----------------------------------------------------------------------------

extern int
pack_create(pack_t *pack, async_t async, void *arg, ftr_t *future);

extern int
pack_destroy(pack_t *pack)
unused_function;

extern int
pack_execute(pack_t *pack);

//-----------------------------------------------------------------------------
// Async call functions
//-----------------------------------------------------------------------------

extern int
async_call(async_t async, void *arg, ftr_t *future);

#endif
