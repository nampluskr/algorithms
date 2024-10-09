## 정렬되지 않는 배열

### 선형 탐색: $O(N)$

- 방법:  지정된 점부터 배열의 모든 요소를 순회하며, 각 요소와의 거리를 계산합니다. 가장 작은 거리를 가진 요소를 찾으면 그 요소가 가장 가까운 점입니다.
- 시간 복잡도: O(n), n은 배열의 크기

```cpp
// 정렬되지 않은 배열에서 가장 가까운 점을 찾는 함수
int findNearestNeighbor(const vector<int>& arr, int target) {
  int minDistance = INT_MAX;
  int nearestIndex = 0;

  for (size_t i = 0; i < arr.size(); ++i) {
    int distance = abs(arr[i] - target);
    if (distance < minDistance) {
      minDistance = distance;
      nearestIndex = i;
    }
  }

  return nearestIndex;
}

int countPointsInRange(const int arr[], int size, int lowerBound, int upperBound) {
  int count = 0;

  for (int i = 0; i < size; ++i) {
    if (arr[i] >= lowerBound && arr[i] <= upperBound) {
      count++;
    }
  }
  return count;
}
```

## 정렬된 배열: 정렬하는데 $O(N\log N)$

- 방법:  배열이 정렬되어 있어야 합니다. 중간 요소와 지정된 점의 거리를 계산합니다. 만약 중간 요소가 가장 가까운 점이라면 종료, 아니면 중간 요소보다 작은 값을 가지는 쪽으로 또는 큰 값을 가지는 쪽으로 검색 영역을 반으로 줄입니다.
- 시간 복잡도: $O(\log n)$

### 이진탐색

```cpp
// 이분 검색을 사용하여 정렬되지 않은 배열에서 가장 가까운 점을 찾는 함수
int findClosestPointBinarySearch(const int arr[], int size, int target) {
  std::sort(arr, arr + size); // 배열을 정렬합니다.

  int left = 0;
  int right = size - 1;
  int closestIndex = 0;
  int minDistance = abs(arr[0] - target);

  while (left <= right) {
    int mid = left + (right - left) / 2;
    int distance = abs(arr[mid] - target);

    if (distance < minDistance) {
      minDistance = distance;
      closestIndex = mid;
    }

    if (arr[mid] == target) {
      return mid; // 정확히 일치하는 경우 인덱스 반환
    } else if (arr[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return closestIndex;
}

int countPointsInRange(const int arr[], int size, int lowerBound, int upperBound) {
  // 배열을 정렬합니다 (시간 복잡도 O(n log n))
  std::sort(arr, arr + size); 

  int count = 0;
  int left = 0;
  int right = size - 1;

  while (left <= right) {
    if (arr[left] >= lowerBound && arr[left] <= upperBound) {
      count++;
      left++;
    } else {
      left++;
    }
  }
  return count;
}
```

### K-최근접 이웃 알고리즘

```cpp
// k-최근접 이웃 알고리즘을 사용하여 정렬되지 않은 배열에서 가장 가까운 점을 찾는 함수
int findClosestPointKNN(const int arr[], int size, int target, int k) {
  std::vector<std::pair<int, int>> distances; // 거리와 인덱스를 저장하는 벡터

  for (int i = 0; i < size; ++i) {
    int distance = abs(arr[i] - target);
    distances.push_back(std::make_pair(distance, i));
  }
  // 거리 기준으로 정렬
  std::sort(distances.begin(), distances.end());

  return distances[0].second; // 가장 가까운 점의 인덱스 반환
}
```

## 정렬된 배열: 이진 탐색 (lowerBound, upperBound)

```
// 이진 탐색을 이용한 lower_bound 함수
int lowerBound(const int arr[], int size, int target) {
  int left = 0;
  int right = size - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2;

    if (arr[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return left;
}

// 이진 탐색을 이용한 upper_bound 함수
int upperBound(const int arr[], int size, int target) {
  int left = 0;
  int right = size - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2;

    if (arr[mid] <= target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return left;
}

int lowerIndex = lowerBound(arr, size, lowerBoundValue);
int upperIndex = upperBound(arr, size, upperBoundValue);

std::cout << "범위 [" << lowerBoundValue << ", " << upperBoundValue << "]에 있는 점의 개수: " << (upperIndex - lowerIndex) << std::endl;
std::cout << "범위 [" << lowerBoundValue << ", " << upperBoundValue << "]에 있는 점들의 인덱스: ";
for (int i = lowerIndex; i < upperIndex; ++i) {
  std::cout << i << " ";
}
std::cout << std::endl;
```

## 이진 탐색 트리: 삽입 $O(n\log n)$, 쿼리 $O(n\log n)$

```cpp
struct Node {
    int value;
    Node *left;
    Node *right;

    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Function to insert a new node into the BST
Node* insert(Node* root, int val) {
    if (root == nullptr) {
        return new Node(val);
    }

    if (val < root->value) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }
    return root;
}

// Function to find the nearest neighbor in the BST
int findNearestNeighbor(Node* root, int target) {
    Node* current = root;
    int nearestValue = current->value; 
    int minDistance = abs(target - nearestValue);

    while (current != nullptr) {
        int distance = abs(target - current->value);
        if (distance < minDistance) {
            minDistance = distance;
            nearestValue = current->value;
        }
        if (target < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return nearestValue;
}

// Function to find elements within a given range in the BST
void findInRange(Node* root, int lowerBound, int upperBound, int arr[], int &index) {
    if (root == nullptr) {
        return; 
    }
    if (root->value >= lowerBound && root->value <= upperBound) {
        arr[index++] = root->value;
    }
    if (root->value > lowerBound) {
        findInRange(root->left, lowerBound, upperBound, arr, index);
    }
    if (root->value < upperBound) {
        findInRange(root->right, lowerBound, upperBound, arr, index);
    }
}
```
