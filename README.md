# Cache_Simulator
## How to get started?
Run the makefile in the same directory a c-sim.c

After you can run ./c-sim with the following arguments.

c-sim takes in 6 arguments (cache size) (associativity) (block size) (replacement_policy) (write_policy) (trace file)

###**(Cache Size)**

This is the total size of the cache. This should be a power of 2.

Also it should always be true that cachesize = number of sets * setsize * blocksize.

______________________________________

###**(Associativity)**

This can be one of three

direct - simulate a direct mapped cache.

assoc - simulate a fully associative cache.

assoc:n - simulate an n − way associative cache. n should be a power of 2.

###**(Blocksize)**

This is a power of 2 int that specifies the size of the cache block.

______________________________________



###**(Replacement_policy)**

There are two choices for replacement policy

LRU - Least recently used

FIFO - first in first out

______________________________________


###**(Write Policy)**

There are two choices.

wt - write through

wb - write back

______________________________________


###**(Tracefile)**


This is the name of the file that contains all of the memory accesses with the format of -

instruction_pointer": " (R or W for read or write) memory address

an example of a tracefile is the following

0x804ae1c: R 0x0000000c

0x804ae19: R 0x00000004

0x804ae19: W 0x00000004

0x804ae1c: W 0x0000000c

0x804ae1c: W 0x00000014

0x804ae19: R 0x00000004


_____________________________


### Example Input / Output

/c-sim 4 direct 1 FIFO wt mytrace.txt

Memory reads: 5

Memory writes: 3

Cache hits: 1

Cache misses: 5 




