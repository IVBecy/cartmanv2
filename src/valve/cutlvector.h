#pragma once

template <typename T>
class CUtlVector {
public:
    constexpr T& operator[](int i) noexcept { return memory[i]; };

    T* memory;
    int allocationCount;
    int growSize;
    int size;
    T* elements;
};
