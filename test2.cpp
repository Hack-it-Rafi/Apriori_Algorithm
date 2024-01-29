#include <iostream>
#include <set>

int main() {
    std::set<int> mySet = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    int n = 3; // Number of items to delete from the end

    // Use reverse iterators to iterate from the end
    auto it = mySet.rbegin();
    for (int i = 0; i < n && it != mySet.rend(); ++i) {
        // Erase the element using the reverse iterator
        mySet.erase(std::next(it).base());
    }

    // Print the modified set
    std::cout << "Set after deleting the last " << n << " items: ";
    for (const auto& element : mySet) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}
