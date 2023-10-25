#define BOOST_TEST_MODULE static library test // Defines the name of the program which is used in the messages
#include <array_util.hpp>
#include <boost/test/unit_test.hpp>
#include <time.h>
#include <vector>

using namespace std;

BOOST_AUTO_TEST_SUITE(MainSuite)

BOOST_AUTO_TEST_CASE(MyRotateLeft)
{
    array<unsigned int, 10> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    myRotate(arr.begin(), arr.begin() + 4, arr.end());
    const array<unsigned int, 10> targetArr = {4, 5, 6, 7, 8, 9, 0, 1, 2, 3};
    BOOST_TEST(arr == targetArr);
}

BOOST_AUTO_TEST_CASE(MyRotateRight)
{
    array<unsigned int, 10> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    myRotate(arr.rbegin(), arr.rbegin() + 3, arr.rend());
    const array<unsigned int, 10> targetArr = {7, 8, 9, 0, 1, 2, 3, 4, 5, 6};
    BOOST_TEST(arr == targetArr);
}

BOOST_AUTO_TEST_CASE(WideLeftAdjacent) // Left wider adjacent intervals
{
    array<unsigned int, 10> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    swapInPlace(arr, 1, 5, 5, 6);
    const array<unsigned int, 10> targetArr = {0, 5, 1, 2, 3, 4, 6, 7, 8, 9};
    BOOST_TEST(arr == targetArr);
}

BOOST_AUTO_TEST_CASE(WideLeftBasic) // Left wider than right
{
    array<unsigned int, 10> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    swapInPlace(arr, 1, 4, 7, 8);
    const array<unsigned int, 10> targetArr = {0, 7, 4, 5, 6, 1, 2, 3, 8, 9};
    BOOST_TEST(arr == targetArr);
}

BOOST_AUTO_TEST_CASE(WideLeftBasic2) // Left wider than right
{
    array<unsigned int, 10> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    swapInPlace(arr, 1, 4, 6, 8);
    const array<unsigned int, 10> targetArr = {0, 6, 7, 4, 5, 1, 2, 3, 8, 9};
    BOOST_TEST(arr == targetArr);
}

BOOST_AUTO_TEST_CASE(SingleElementIntervals) //Equal 1 range
{
    array<unsigned int, 10> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    swapInPlace(arr, 1, 2, 6, 7);
    const array<unsigned int, 10> targetArr = {0, 6, 2, 3, 4, 5, 1, 7, 8, 9};
    BOOST_TEST(arr == targetArr);
}

BOOST_AUTO_TEST_CASE(WideRightInterval) //Right wider than left
{
    array<unsigned int, 10> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    swapInPlace(arr, 1, 2, 5, 7);
    const array<unsigned int, 10> targetArr = {0, 5, 6, 2, 3, 4, 1, 7, 8, 9};
    BOOST_TEST(arr == targetArr);
}

BOOST_AUTO_TEST_CASE(WideRightAdjacent) //Right wider adjacent
{
    array<unsigned int, 10> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    swapInPlace(arr, 1, 2, 2, 7);
    const array<unsigned int, 10> targetArr = {0, 2, 3, 4, 5, 6, 1, 7, 8, 9};
    BOOST_TEST(arr == targetArr);
}


BOOST_AUTO_TEST_CASE(RandomizedTest)
{
    for (unsigned int i = 0; i < 100; ++i)
    {
        srand(time(NULL));
        const size_t width = 20;
        array<unsigned int, width> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
        size_t leftBeg = rand() % 5;
        size_t leftEnd = leftBeg + rand() % 4 + 1;
        size_t rightBeg = leftEnd + rand() % 4;
        size_t rightEnd = rightBeg + rand() % 4 + 1;

        std::vector<unsigned int> vec;
        vec.reserve(width); // preallocate memory

        // Assemble vector with swapped intervals
        vec.insert(vec.end(), arr.begin(), next(arr.begin(), leftBeg));
        vec.insert(vec.end(), next(arr.begin(), rightBeg), next(arr.begin(), rightEnd));
        vec.insert(vec.end(), next(arr.begin(), leftEnd), next(arr.begin(), rightBeg));
        vec.insert(vec.end(), next(arr.begin(), leftBeg), next(arr.begin(), leftEnd));
        vec.insert(vec.end(), next(arr.begin(), rightEnd), arr.end());

        std::array<unsigned int, width> targetArray;
        std::copy_n(vec.begin(), width, targetArray.begin());

        swapInPlace(arr, leftBeg, leftEnd, rightBeg, rightEnd);
        BOOST_TEST(arr == targetArray);
    }
}

BOOST_AUTO_TEST_SUITE_END()