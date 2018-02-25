#pragma once

#include <cstddef>
#include "fwd.hh"

struct __attribute__ ((packed))  RealChunk
{
    std::size_t size;
    int refs;
    num_t data[0];


    static RealChunk* alloc(std::size_t size);
    static void free(RealChunk* chunk);

    void ref();
    void unref();

    RealChunk(const RealChunk&) = delete;
    RealChunk(RealChunk&&) = delete;
    RealChunk& operator=(const RealChunk&) = delete;
    RealChunk& operator=(RealChunk&&) = delete;

private:
    RealChunk() = default;
};

#include "real-chunk.hxx"
