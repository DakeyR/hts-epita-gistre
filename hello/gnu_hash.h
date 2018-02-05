/* gnu_hash.h */
#include <elf.h>
#include <link.h>



/* Copyright (C) 1993-2017 Free Software Foundation, Inc.*/
struct gnu_hash_table {
    ElfW(Word) nbuckets;
    ElfW(Word) symoffset;
    ElfW(Word) bloom_size;
    ElfW(Word) bloom_shift;
    ElfW(Xword) *bloom;
    ElfW(Word) *buckets;
    ElfW(Word) *chain;
};

ElfW(Word) gnu_hash(const unsigned char* name);
