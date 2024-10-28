### Sqrt Decomposition with Lazy Propagation for Range Sum Query

```cpp
#include <iostream>
#include <vector>
#include <cmath>

class SqrtDecomposition {
private:
    std::vector<int> arr;
    std::vector<int> blocks;
    std::vector<int> lazy;
    int blockSize;
    int n;

    void applyLazy(int blockIdx) {
        int start = blockIdx * blockSize;
        int end = std::min(start + blockSize, n);
        for (int i = start; i < end; i++) {
            arr[i] += lazy[blockIdx];
        }
        blocks[blockIdx] += lazy[blockIdx] * (end - start);
        lazy[blockIdx] = 0;
    }

public:
    SqrtDecomposition(const std::vector<int>& input) {
        arr = input;
        n = arr.size();
        blockSize = static_cast<int>(std::sqrt(n));
        int numBlocks = (n + blockSize - 1) / blockSize;
        blocks.resize(numBlocks, 0);
        lazy.resize(numBlocks, 0);

        for (int i = 0; i < n; i++) {
            blocks[i / blockSize] += arr[i];
        }
    }

    int rangeSum(int left, int right) {
        int sum = 0;
        int startBlock = left / blockSize;
        int endBlock = right / blockSize;

        if (startBlock == endBlock) {
            applyLazy(startBlock);
            for (int i = left; i <= right; i++) {
                sum += arr[i];
            }
        } else {
            // Sum of the first partial block
            applyLazy(startBlock);
            for (int i = left; i < (startBlock + 1) * blockSize; i++) {
                sum += arr[i];
            }

            // Sum of the whole blocks
            for (int i = startBlock + 1; i < endBlock; i++) {
                sum += blocks[i] + lazy[i] * blockSize;
            }

            // Sum of the last partial block
            applyLazy(endBlock);
            for (int i = endBlock * blockSize; i <= right; i++) {
                sum += arr[i];
            }
        }
        return sum;
    }

    void update(int idx, int val) {
        int blockIdx = idx / blockSize;
        applyLazy(blockIdx);
        blocks[blockIdx] += val - arr[idx];
        arr[idx] = val;
    }

    void rangeUpdate(int left, int right, int val) {
        int startBlock = left / blockSize;
        int endBlock = right / blockSize;

        if (startBlock == endBlock) {
            applyLazy(startBlock);
            for (int i = left; i <= right; i++) {
                arr[i] += val;
                blocks[startBlock] += val;
            }
        } else {
            // Update first partial block
            applyLazy(startBlock);
            for (int i = left; i < (startBlock + 1) * blockSize; i++) {
                arr[i] += val;
                blocks[startBlock] += val;
            }

            // Update whole blocks
            for (int i = startBlock + 1; i < endBlock; i++) {
                lazy[i] += val;
            }

            // Update last partial block
            applyLazy(endBlock);
            for (int i = endBlock * blockSize; i <= right; i++) {
                arr[i] += val;
                blocks[endBlock] += val;
            }
        }
    }
};

int main() {
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    SqrtDecomposition sd(arr);

    std::cout << "Sum of range [2, 7]: " << sd.rangeSum(2, 7) << std::endl;
    
    sd.rangeUpdate(3, 6, 5);  // 인덱스 3부터 6까지 5를 더함
    std::cout << "After range update, sum of range [2, 7]: " << sd.rangeSum(2, 7) << std::endl;

    sd.update(5, 20);  // 인덱스 5의 값을 20으로 변경
    std::cout << "After single update, sum of range [2, 7]: " << sd.rangeSum(2, 7) << std::endl;

    return 0;
}

```


### Sqrt Decomposition with Lazy Propagation for Range Min Query

```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

class SqrtDecomposition {
private:
    std::vector<int> arr;
    std::vector<int> blocks;
    std::vector<int> lazy;
    int blockSize;
    int n;

    void applyLazy(int blockIdx) {
        int start = blockIdx * blockSize;
        int end = std::min(start + blockSize, n);
        for (int i = start; i < end; i++) {
            arr[i] += lazy[blockIdx];
        }
        blocks[blockIdx] += lazy[blockIdx];
        lazy[blockIdx] = 0;
    }

public:
    SqrtDecomposition(const std::vector<int>& input) {
        arr = input;
        n = arr.size();
        blockSize = static_cast<int>(std::sqrt(n));
        int numBlocks = (n + blockSize - 1) / blockSize;
        blocks.resize(numBlocks, std::numeric_limits<int>::max());
        lazy.resize(numBlocks, 0);

        for (int i = 0; i < n; i++) {
            blocks[i / blockSize] = std::min(blocks[i / blockSize], arr[i]);
        }
    }

    int rangeMin(int left, int right) {
        int minVal = std::numeric_limits<int>::max();
        int startBlock = left / blockSize;
        int endBlock = right / blockSize;

        if (startBlock == endBlock) {
            applyLazy(startBlock);
            for (int i = left; i <= right; i++) {
                minVal = std::min(minVal, arr[i]);
            }
        } else {
            // Min of the first partial block
            applyLazy(startBlock);
            for (int i = left; i < (startBlock + 1) * blockSize; i++) {
                minVal = std::min(minVal, arr[i]);
            }

            // Min of the whole blocks
            for (int i = startBlock + 1; i < endBlock; i++) {
                minVal = std::min(minVal, blocks[i] + lazy[i]);
            }

            // Min of the last partial block
            applyLazy(endBlock);
            for (int i = endBlock * blockSize; i <= right; i++) {
                minVal = std::min(minVal, arr[i]);
            }
        }

        return minVal;
    }

    void update(int idx, int val) {
        int blockIdx = idx / blockSize;
        applyLazy(blockIdx);
        arr[idx] = val;
        blocks[blockIdx] = *std::min_element(arr.begin() + blockIdx * blockSize, 
                                             arr.begin() + std::min((blockIdx + 1) * blockSize, n));
    }

    void rangeUpdate(int left, int right, int val) {
        int startBlock = left / blockSize;
        int endBlock = right / blockSize;

        if (startBlock == endBlock) {
            applyLazy(startBlock);
            for (int i = left; i <= right; i++) {
                arr[i] += val;
            }
            blocks[startBlock] = *std::min_element(arr.begin() + startBlock * blockSize, 
                                                   arr.begin() + std::min((startBlock + 1) * blockSize, n));
        } else {
            // Update first partial block
            applyLazy(startBlock);
            for (int i = left; i < (startBlock + 1) * blockSize; i++) {
                arr[i] += val;
            }
            blocks[startBlock] = *std::min_element(arr.begin() + startBlock * blockSize, 
                                                   arr.begin() + (startBlock + 1) * blockSize);

            // Update whole blocks
            for (int i = startBlock + 1; i < endBlock; i++) {
                lazy[i] += val;
                blocks[i] += val;
            }

            // Update last partial block
            applyLazy(endBlock);
            for (int i = endBlock * blockSize; i <= right; i++) {
                arr[i] += val;
            }
            blocks[endBlock] = *std::min_element(arr.begin() + endBlock * blockSize, 
                                                 arr.begin() + std::min((endBlock + 1) * blockSize, n));
        }
    }
};

int main() {
    std::vector<int> arr = {3, 2, 4, 5, 1, 1, 5, 3, 4, 2};
    SqrtDecomposition sd(arr);

    std::cout << "Min of range [2, 7]: " << sd.rangeMin(2, 7) << std::endl;
    
    sd.rangeUpdate(3, 6, 2);  // 인덱스 3부터 6까지 2를 더함
    std::cout << "After range update, min of range [2, 7]: " << sd.rangeMin(2, 7) << std::endl;

    sd.update(5, 0);  // 인덱스 5의 값을 0으로 변경
    std::cout << "After single update, min of range [2, 7]: " << sd.rangeMin(2, 7) << std::endl;

    return 0;
}
```