#include "SingleLinkedList.tpp"
#include "SingleLinkedList.cpp"

int main() {
    std::cout << "Test 1: Constructor with initializer list\n";
    single_linked_list<int> list = {1, 2, 3, 4, 5};

    std::cout << "Elements in list: ";
    for (auto it = list.cbegin(); it != list.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n\n";

    std::cout << "Test 2: push_front\n";
    list.push_front(0);
    std::cout << "List after push_front(0): ";
    for (auto it = list.cbegin(); it != list.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n\n";

    std::cout << "Test 3: push_back\n";
    list.push_back(6);
    std::cout << "List after push_back(6): ";
    for (auto it = list.cbegin(); it != list.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n\n";

    std::cout << "Test 4: insert_after\n";
    auto it = list.find(3);
    if (it != list.end()) {
        list.insert_after(it, 7);
    }

    std::cout << "List after insert_after(3, 7): ";
    for (auto it = list.cbegin(); it != list.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n\n";

    std::cout << "Test 5: erase_after\n";
    it = list.find(3);
    if (it != list.end()) {
        list.erase_after(it);
    }

    std::cout << "List after erase_after(3): ";
    for (auto it = list.cbegin(); it != list.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n\n";

    std::cout << "Test 6: Modify elements using iterator\n";
    for (auto it = list.begin(); it != list.end(); ++it) {
        *it += 10;
    }

    std::cout << "List after modifying with iterator: ";
    for (auto it = list.cbegin(); it != list.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n\n";

    std::cout << "Test 7: Clear the list\n";
    list.clear();
    std::cout << "List after clear(): ";
    if (list.begin() == list.end()) {
        std::cout << "List is empty!";
    } else {
        for (auto it = list.cbegin(); it != list.cend(); ++it) {
            std::cout << *it << " ";
        }
    }
    std::cout << "\n\n";

    std::cout << "Test 8: Push elements after clear\n";
    list.push_back(10);
    list.push_back(20);
    list.push_front(5);

    std::cout << "List after push_back(10), push_back(20), push_front(5): ";
    for (auto it = list.cbegin(); it != list.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    return 0;
}