## Array in-place swapper

There is a method for swapping two arbitrary non-overlapping intervals in an array. All operations are done in-place with O(1) external memory consumption.

The logic of the function is the following:
Let's assume we have an arbitrary array `std::array<unsigned int, 10> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}`
And target intervals `[1, 4)` & `[7, 8)`

The array shall be split into three intervals:
`0 -> 1, 2, 3, -> 4, 5, 6 -> 7 -> 8, 9`

The intervals are swapped:
`0 -> 7 -> 4, 5, 6 -> 1, 2, 3 -> 8, 9`

### Build

```
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### Run
`./interval-swap`
