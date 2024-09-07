#if 0
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Segment Tree 구조체 정의
struct Node {
    int val;
    int idx; // 원래 배열에서의 인덱스
};

vector<Node> tree;

// Segment Tree 노드 업데이트 함수
void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
        tree[node].val = val; 
        tree[node].idx = idx;
    } else {
        int mid = (start + end) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
    }
}

// // Segment Tree에서 특정 값과 가장 가까운 점 찾기
// int query(int node, int start, int end, int target) {
//     if (start == end) {
//         return abs(tree[node].val - target); 
//     } else {
//         int mid = (start + end) / 2;
//         int leftDist = query(2 * node, start, mid, target);
//         int rightDist = query(2 * node + 1, mid + 1, end, target);

//         // 가장 가까운 점 반환
//         return min(leftDist, rightDist); 
//     }
// }

pair<int, int> query(int node, int start, int end, int target) {
    if (start == end) {
        return {tree[node].val, tree[node].idx}; 
    } else {
        int mid = (start + end) / 2;
        auto left = query(2 * node, start, mid, target);
        auto right = query(2 * node + 1, mid + 1, end, target);

        if (abs(left.first - target) <= abs(right.first - target)) {
            return left;
        } else {
            return right;
        }
    }
}


int main() {
    vector<int> arr = {10, 5, 8, 15, 20}; 
    tree.resize(4 * arr.size()); 
    for (int i = 0; i < arr.size(); ++i) {
        update(1, 0, arr.size() - 1, i, arr[i]); 
    }

    int target = 7;
    auto nearestPoint = query(1, 0, arr.size() - 1, target); 

    cout << "Target: " << target << ", Nearest Point Value: " << nearestPoint.first << endl;
    cout << "Nearest Point Index: " << nearestPoint.second << endl; 


    return 0;
}
#endif