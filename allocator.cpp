const int MAX_MEM = 500 * 1024 * 1024;
char MEM[MAX_MEM];
size_t memptr = 0;

inline void* operator new (size_t x) {
    assert((memptr += x) < MAX_MEM);
    return MEM + memptr - x;
}
