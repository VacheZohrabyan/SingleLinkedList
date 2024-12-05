#include "SingleLinkedList.tpp"

template <typename Item>
single_linked_list<Item>::single_linked_list(std::initializer_list<Item> items) 
        : m_head{nullptr}, m_tail{nullptr} {
    for(auto &item: items) {
        push_back(item);
    }
}

template <typename Item>
single_linked_list<Item>::~single_linked_list() {
    clear();
}

template <typename Item>
void single_linked_list<Item>::push_front(value_type item) {
    auto newnode = new Node {std::move(item)};

    if (m_head == nullptr) {
        m_head = m_tail = newnode;
    }
    newnode->next = m_head;
    m_head = newnode;
}

template <typename Item>
void single_linked_list<Item>::push_back(value_type item) {
    auto newnode = new Node {std::move(item)};
    if (m_tail) {
        m_tail->next = newnode;
        m_tail = newnode;
        m_tail->next = nullptr;
    } else {
        m_head = m_tail = newnode;
    }
    m_tail->next = nullptr;
}

template <typename Item>
void single_linked_list<Item>::insert_after(const_iterator place, value_type item) {
    auto ptr = const_cast<Node*>(place.Get());
    if (!ptr) {
        push_front(std::move(item));
        return;
    }
    auto newnode = new Node {std::move(item)};
    newnode->next = ptr->next;
    ptr->next = newnode;
}

template <typename Item>
void single_linked_list<Item>::erase_after(const_iterator place) noexcept {
    auto ptr = const_cast<Node*> (place.Get());
    if (ptr) {
        auto nodeDelete = ptr->next;
        if (ptr->next) {
            ptr->next = ptr->next->next;
        }
        delete nodeDelete;
    } else {
        assert(m_head != nullptr);
        delete std::exchange(m_head, m_head->next);
    }
}

template<typename Item>
void single_linked_list<Item>::clear() {
    while (m_head != nullptr) {
        auto head = m_head;
        m_head = m_head->next;
        delete head;
    }
    m_head = m_tail = nullptr;
}

template <typename Item>
typename single_linked_list<Item>::const_iterator single_linked_list<Item>::begin() const noexcept {
    return const_iterator{m_head};
}

template <typename Item>
typename single_linked_list<Item>::const_iterator single_linked_list<Item>::end() const noexcept {
    return const_iterator{nullptr};
}

template <typename Item>
typename single_linked_list<Item>::const_iterator single_linked_list<Item>::cbegin() const noexcept {
    return const_iterator{m_head};
}

template <typename Item>
typename single_linked_list<Item>::const_iterator single_linked_list<Item>::cend() const noexcept {
    return const_iterator{nullptr};
}

template <typename Item>
typename single_linked_list<Item>::iterator single_linked_list<Item>::begin() noexcept {
    return iterator{m_head};
}

template <typename Item>
typename single_linked_list<Item>::iterator single_linked_list<Item>::end() noexcept {
    return iterator{nullptr};
}

template <typename Item>
typename single_linked_list<Item>::const_iterator single_linked_list<Item>::find(const_reference item) const noexcept {
    for (auto it = begin(); it != end(); ++it) {
        if (*it == item) {
            return it;
        }
    }
    return const_iterator{nullptr};
}

template <typename Item>
typename single_linked_list<Item>::iterator single_linked_list<Item>::find(const_reference item) noexcept {
    const auto& const_ref = static_cast<const single_linked_list<Item>&>(*this);
    const_iterator it = const_ref.find(item);
    return iterator{const_cast<Node*>(it.Get())};
}