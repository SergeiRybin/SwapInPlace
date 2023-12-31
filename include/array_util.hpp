#pragma once

#include <algorithm>
#include <array>

template<typename It>
void myRotate(It first, It middle, It last)
{
    // Rotation is not needed, first is already in desired position
    if (first == middle) 
    {
        return;
    }

    It nextPart = middle;

    while (middle != last)
    {
        std::iter_swap(first, middle);
        ++first;
        ++middle;

        if (nextPart == first) 
        {
            // Left part is rotated
            nextPart = middle;
        }
        else if (last == middle) 
        {
            // Rotate remaining sequence
            middle = nextPart;
        }
    }
}

template <typename T, size_t S>
void swapInPlace(std::array<T, S> &arr, size_t beginFirst, size_t endFirst, size_t beginSecond, size_t endSecond)
{
    // check min/max intervals
    if (!(beginFirst < endFirst && beginSecond < endSecond && endFirst < S && endSecond < S))
    {
        // Do nothing as the intervals are incorrect
        return; 
    }

    size_t beginLeft, endLeft, beginRight, endRight;
    if (beginFirst < beginSecond)
    {
        beginLeft = beginFirst;
        endLeft = endFirst;
        beginRight = beginSecond;
        endRight = endSecond;
    }
    else
    {
        beginLeft = beginSecond;
        endLeft = endSecond;
        beginRight = beginFirst;
        endRight = endFirst;
    }

    // Find if left interval is wider
    const bool leftWider = (endLeft - beginLeft) > (endRight - beginSecond);

    // Find common length and difference between intervals
    const size_t comLen = std::min(endLeft - beginLeft, endRight - beginRight);
    const size_t excLen = std::max(endLeft - beginLeft, endRight - beginRight) - comLen;

    auto itFirst = std::next(arr.begin(), beginLeft);
    auto itSecond = std::next(arr.begin(), beginRight);
    auto itEnd = std::next(arr.begin(), endRight);

    // Swap items in common part
    for (size_t i = 0; i < comLen; ++i)
    {
        std::iter_swap(itFirst, itSecond);
        ++itFirst;
        ++itSecond;
    }

    // If intervals have different length
    if (excLen)
    {
        // If left interval was wider, cyclic rotation to the left
        if (leftWider)
        {
            myRotate(itFirst, itFirst + excLen, itEnd);
        }
        else
        {
            // cyclic rotation to the right
            const auto rbeg = std::reverse_iterator(itEnd);
            const auto rmid = rbeg + excLen;
            const auto rend = std::reverse_iterator(itFirst);
            myRotate(rbeg, rmid, rend);
        }
    }
}