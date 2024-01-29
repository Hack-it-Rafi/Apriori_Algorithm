#include <iostream>
#include <algorithm>
#include <iterator>
#include <set>

using namespace std;

int main() {
    set<int> set1 = {1, 2};
    set<int> set2 = {3, 4, 5, 6, 7};

    // Check if there is any intersection
    bool hasIntersection = any_of(set1.begin(), set1.end(),
                                  [&set2](int element) {
                                      return set2.find(element) != set2.end();
                                  });

    // If there is an intersection, perform the union
    if (hasIntersection) {
        set<int> unionSet;

        // Use set_union to find the union of the sets
        set_union(set1.begin(), set1.end(),
                  set2.begin(), set2.end(),
                  inserter(unionSet, unionSet.begin()));

        // Print the result
        cout << "Union Set: ";
        for (const auto& element : unionSet) {
            cout << element << " ";
        }
        cout << endl;
    } else {
        cout << "No intersection found. Union not performed." << endl;
    }

    return 0;
}
