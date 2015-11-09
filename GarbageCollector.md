# Garbage Collection #

Toka makes use of a garbage collector for dynamic memory allocations. This allows fairly liberal use of dynamically allocated memory without worry of memory leaks.

The model is pretty simple. To allocate memory, gc\_alloc() is called. This is passed the number of elements, the size of an element, and a hint regarding whether this is known to be temporary or may be permanent.

The garbage collector maintains two lists of allocations. When either of these is filled, the gc() routine is called to clean them up. Any item that was flagged as temporary using gc\_alloc() is freed by gc(). It also frees up to 32 allocations from the primary list each time it is called. To help prevent temporary items from being corrupted by future allocations, only 64 temporary allocations will be freed per call of gc().

Another routine, gc\_keep() skims down through the list of allocations (most recent to oldest) to find a specific pointer. When found, that (and any allocation that follows, are removed from the list making them permanent allocations. (This assumes that subsequent allocations are referenced by the one you desire to keep. In a normal Toka build this is safe.)

Information regarding the current status of the garbage collection subsystem can be obtained via gc\_info().