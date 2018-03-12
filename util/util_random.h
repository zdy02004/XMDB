#ifndef _UTIL_RANDOM_H_
#define _UTIL_RANDOM_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct mem_random_t{
uint32_t seed_;
};

void mem_random_init(struct mem_random_t* mem_random ,uint32_t s)   
{
		mem_random->seed_ = s;
		if ( mem_random->seed_ == 0 || mem_random->seed_ == 2147483647L) {
      mem_random->seed_ = 1;
    }
    return;
    mem_random->seed_ = s & 0x7fffffffu;
    // Avoid bad seeds.
    if (mem_random->seed_ == 0 || mem_random->seed_ == 2147483647L) {
      mem_random->seed_ = 1;
    }
}
  
   uint32_t mem_random_next(struct mem_random_t* mem_random) {
    static const uint32_t M = 2147483647L;   // 2^31-1
    static const uint64_t A = 16807;  // bits 14, 8, 7, 5, 2, 1, 0
    // We are computing
    //       seed_ = (seed_ * A) % M,    where M = 2^31-1
    //
    // seed_ must not be zero or M, or else all subsequent computed values
    // will be zero or M respectively.  For all other values, seed_ will end
    // up cycling through every number in [1,M-1]
    uint64_t product = mem_random->seed_ * A;

    // Compute (product % M) using the fact that ((x << 31) % M) == x.
    mem_random->seed_ = (uint32_t)((product >> 31) + (product & M));
    // The first reduction may overflow by 1 bit, so we may need to
    // repeat.  mod == M is not possible; using > allows the faster
    // sign-bit-based test.
    if (mem_random->seed_ > M) {
      mem_random->seed_ -= M;
    }
    return  mem_random->seed_;
  }
  
  
    uint32_t mem_random_uniform(struct mem_random_t* mem_random,int n)
     { 
     	return mem_random_next(mem_random) % n;
     }

  // Randomly returns true ~"1/n" of the time, and false otherwise.
  // REQUIRES: n > 0
  int mem_random_onein(struct mem_random_t* mem_random,int n)
  { 
  	return ( mem_random_next(mem_random ) % n ) == 0; 
  }

  // Skewed: pick "base" uniformly from range [0,max_log] and then
  // return "base" random bits.  The effect is to pick a number in the
  // range [0,2^max_log-1] with exponential bias towards smaller numbers.
  uint32_t mem_random_skewed(struct mem_random_t* mem_random,int max_log) {
    return mem_random_uniform(mem_random,1 << mem_random_uniform(mem_random,max_log + 1));
  }
  

#ifdef __cplusplus
}
#endif  
  
#endif  // STORAGE_LEVELDB_UTIL_RANDOM_H_
