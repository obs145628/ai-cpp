#pragma once

#include "real-chunk.hh"

#include <iostream>

inline RealChunk* RealChunk::alloc(std::size_t size)
{
    std::size_t alloc_size = sizeof(RealChunk) + size * sizeof(num_t);
    char* data = new char[alloc_size];
    RealChunk* chunk = reinterpret_cast<RealChunk*>(data);
    chunk->size = size;
    chunk->refs = 0;
    return chunk;
}

inline void RealChunk::free(RealChunk* chunk)
{
    delete[] chunk;
}

inline void RealChunk::ref()
{
    ++refs;
}

inline void RealChunk::unref()
{
    if (!--refs)
	free(this);
}
