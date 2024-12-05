#ifndef HIDDER_SINGLE
#define HIDDER_SINGLE

#include <iostream>
#include <cstddef>
#include <cassert>
#include <utility>
#include <iterator>

template <typename Item>
class single_linked_list
{
public:
    using value_type = Item;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type *;
    using const_pointer = value_type *;
    using reference = value_type &;
    using const_reference = const value_type &;

private:
    struct Node {
        Item data;
        Node* next;

        Node (Item value) noexcept 
            : data{std::move(value)}
        {
        }
    };

public:
    single_linked_list() = default;
    single_linked_list(std::initializer_list<Item> items);
    ~single_linked_list();

public:
    class single_linked_list_const_iterator 
    {
    public:
        friend class single_linked_list;
        explicit single_linked_list_const_iterator(const Node* node) noexcept
                            : m_current{node}
        {}

    public:
        using difference_type = single_linked_list::difference_type;
        using value_type = single_linked_list::value_type;
        using pointer = single_linked_list::pointer;
        using reference = single_linked_list::reference;
        using iterator_category = std::forward_iterator_tag;

        const_reference operator*() const noexcept {
            assert(m_current != nullptr);
            return m_current->data;
        }

        single_linked_list_const_iterator& operator++() {
            assert(m_current != nullptr);
            m_current = m_current->next;
            return *this;
        }

        single_linked_list_const_iterator operator++(int) noexcept {
            assert(m_current != nullptr);
            auto copy = *this;
            
            m_current = m_current->next;
            return copy;
        }

        bool operator== (single_linked_list_const_iterator other) const noexcept {
            return m_current == other.m_current;
        }

        bool operator!= (single_linked_list_const_iterator other) const noexcept {
            return !(*this == other);
        }

    protected:
        const Node* Get() const noexcept {
            return m_current;
        }
    protected:
        const Node* m_current;
    };

    class single_linked_list_iterator : public single_linked_list_const_iterator
    {
    private:
        friend class single_linked_list;
    
    public:
        using difference_type = single_linked_list::difference_type;
        using value_type = single_linked_list::value_type;
        using pointer = single_linked_list::pointer;
        using reference = single_linked_list::reference;
        using iterator_category = std::forward_iterator_tag;

        explicit single_linked_list_iterator(Node* node) noexcept
                            : single_linked_list_const_iterator(node)
        {}

        reference operator*() noexcept {
            auto &&res = single_linked_list_const_iterator::operator*();
            return const_cast<reference>(res);
        }

        single_linked_list_iterator& operator++() noexcept {
            single_linked_list_const_iterator::operator++();
            return *this;
        }

        single_linked_list_iterator operator++(int) noexcept {
            auto res = single_linked_list_const_iterator::operator++(0);
            return single_linked_list_iterator {
                const_cast<Node*>(res.Get())
            };
        }
    };
    using iterator = single_linked_list_iterator;
    using const_iterator = single_linked_list_const_iterator;

public:
    void push_front(value_type item);
    void push_back(value_type item);
    void insert_after(const_iterator place, value_type item);
    void erase_after(const_iterator place) noexcept;
    void clear();

public:
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    iterator begin() noexcept;
    iterator end() noexcept;

public:
    const_iterator find(const_reference item) const noexcept;
    iterator find(const_reference item) noexcept;
private:
    Node* m_head;
    Node* m_tail;
};

#endif