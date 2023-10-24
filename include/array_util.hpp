#pragma once

#include <array>
#include <algorithm>

template<typename T, size_t S>
void swapInPlace(std::array<T, S> &arr, size_t beginFirst, size_t endFirst, size_t beginSecond, size_t endSecond)
{
    // check min/max intervals
    if (!(beginFirst < endFirst && beginSecond < endSecond))
    {
        return; // Do nothing as the intervals are incorrect
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

    bool leftWider = endLeft - beginLeft > endRight - beginSecond; // If left interval is wider

    // Find common length and difference between intervals
    size_t comLen = std::min(endLeft - beginLeft, endRight - beginRight);
    size_t excLen = std::max(endLeft - beginLeft, endRight - beginRight) - comLen;
    
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
            std::rotate(itFirst, itFirst + excLen, itEnd);
        }
        else
        {
            // cyclic rotation to the right
            auto rbeg = std::reverse_iterator(itEnd);
            auto rmid = rbeg + excLen;
            auto rend = std::reverse_iterator(itFirst);
            std::rotate(rbeg, rmid, rend);
        }
    }

}