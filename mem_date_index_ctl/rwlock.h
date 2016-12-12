#ifndef _RWLOCK_H_
#define _RWLOCK_H_
#define EEBUSY 1

#define atomic_xadd(P, V) __sync_fetch_and_add((P), (V))
#define cmpxchg(P, O, N) __sync_val_compare_and_swap((P), (O), (N))
#define atomic_inc(P) __sync_add_and_fetch((P), 1)
#define atomic_dec(P) __sync_add_and_fetch((P), -1) 
#define atomic_add(P, V) __sync_add_and_fetch((P), (V))
#define atomic_set_bit(P, V) __sync_or_and_fetch((P), 1<<(V))
#define atomic_clear_bit(P, V) __sync_and_and_fetch((P), ~(1<<(V)))

typedef struct rwlock {
    int write;
    int read;
}rwlock_t;

static inline void
rwlock_init(struct rwlock *lock) {
    lock->write = 0;
    lock->read = 0;
}
static inline void
rwlock_rlock(struct rwlock *lock) {
    for (;;) {
        while(lock->write) {
            __sync_synchronize();
        }
        __sync_add_and_fetch(&lock->read,1);
        if (lock->write) {
            __sync_sub_and_fetch(&lock->read,1);
        } else {
            break;
        }
    }
}
static inline void
rwlock_wlock(struct rwlock *lock) {
    while (__sync_lock_test_and_set(&lock->write,1)) {}
    while(lock->read) {
        __sync_synchronize();
    }
}
static inline void
rwlock_wunlock(struct rwlock *lock) {
    __sync_lock_release(&lock->write);
}
static inline void
rwlock_runlock(struct rwlock *lock) {
    __sync_sub_and_fetch(&lock->read,1);
}

//________________________________________________________________________
/* Compile read-write barrier */
#define barrier() asm volatile("": : :"memory")

/* Pause instruction to prevent excess processor bus usage */ 
#define cpu_relax() asm volatile("pause\n": : :"memory")

/* Atomic exchange (of various sizes) */
static inline void *xchg_64(void *ptr, void *x)
{
    __asm__ __volatile__("xchgq %0,%1"
                :"=r" ((unsigned long long) x)
                :"m" (*(volatile long long *)ptr), "0" ((unsigned long long) x)
                :"memory");

    return x;
}

static inline unsigned xchg_32(void *ptr, unsigned x)
{
    __asm__ __volatile__("xchgl %0,%1"
                :"=r" ((unsigned) x)
                :"m" (*(volatile unsigned *)ptr), "0" (x)
                :"memory");

    return x;
}

static inline unsigned short xchg_16(void *ptr, unsigned short x)
{
    __asm__ __volatile__("xchgw %0,%1"
                :"=r" ((unsigned short) x)
                :"m" (*(volatile unsigned short *)ptr), "0" (x)
                :"memory");

    return x;
}

/* Test and set a bit */
static inline char atomic_bitsetandtest(void *ptr, int x)
{
    char out;
    __asm__ __volatile__("lock; bts %2,%1\n"
                        "sbb %0,%0\n"
                :"=r" (out), "=m" (*(volatile long long *)ptr)
                :"Ir" (x)
                :"memory");

    return out;
}
//________________________________________________________________________
// ×ÔÐýËø ÓÃÓÚÌæ»» spinlock
typedef union ticketlock ticketlock;

typedef union ticketlock
{
    unsigned u;
    struct
    {
        unsigned short ticket;
        unsigned short users;
    } s;
}ticketlock_t;

static void ticket_lock(ticketlock *t)
{
    unsigned short me = atomic_xadd(&t->s.users, 1);
    
    while (t->s.ticket != me) cpu_relax();
}

static void ticket_unlock(ticketlock *t)
{
    barrier();
    t->s.ticket++;
}

static int ticket_trylock(ticketlock *t)
{
    unsigned short me = t->s.users;
    unsigned short menew = me + 1;
    unsigned cmp = ((unsigned) me << 16) + me;
    unsigned cmpnew = ((unsigned) menew << 16) + me;

    if (cmpxchg(&t->u, cmp, cmpnew) == cmp) return 0;
    
    return EEBUSY;
}

static int ticket_lockable(ticketlock *t)
{
    ticketlock u = *t;
    barrier();
    return (u.s.ticket == u.s.users);
}

//________________________________________________________________________
//
#endif