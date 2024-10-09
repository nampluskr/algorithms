#if 0
#include <iostream>
#include <set>

int findClosest(const std::set<int>& s, int target) {
    auto it = s.lower_bound(target);

    if (it == s.end()) {
        return *(--it); // target보다 큰 값이 없으면 가장 큰 값을 반환
    } else if (it == s.begin()) {
        return *it; // target보다 작은 값이 없으면 가장 작은 값을 반환
    } else {
        int left = *(--it);
        int right = *it;
        return std::abs(left - target) < std::abs(right - target) ? left : right;
    }
}

int main() {
    std::set<int> s = {10, 5, 15, 3, 7, 12, 18};

    int target = 8;
    std::cout << "Closest value to " << target << " is: " << findClosest(s, target) << std::endl;

    return 0;
}
#endif
