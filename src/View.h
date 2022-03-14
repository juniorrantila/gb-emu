#pragma once
#include <stdint.h>

template <typename T, typename SizeType = uint32_t>
struct View {
    T* data;
    SizeType size;

    View(T* data, SizeType size)
        : data(data)
        , size(size)
    {
    }

    View(void* data, SizeType size)
        : data(static_cast<T*>(data))
        , size(size)
    {
    }
    
    T* begin() { return data; }
    T* end() { return &data[size]; }

};

