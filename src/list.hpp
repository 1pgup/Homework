#pragma once // NOLINT
#include <iterator>
#include <iostream>
namespace task {
template<class T> class list {
 public:
    struct Node {
        T val{ T() };
        Node* next{ nullptr };
        Node* prev{ nullptr };
    };

    class const_iterator {
     public:
        using difference_type = ptrdiff_t;
        using value_type = const T;
        using pointer = const T*;
        using reference = const T&;
        using iterator_category = std::bidirectional_iterator_tag;

        const_iterator(Node* node) : ptr(node) {}
        const_iterator(const const_iterator& other) : ptr(other.ptr) {}

        const_iterator& operator=(const const_iterator& other) { ptr = other.ptr; return *this; }

        const_iterator& operator++() { ptr = ptr->next; return *this; }
        const_iterator operator++(int) { const_iterator temp(*this); ++(*this); return temp; }

        reference operator*() const { return ptr->val; }
        pointer operator->() const { return &ptr->val; }

        const_iterator& operator--() { ptr = ptr->prev; return *this; }
        const_iterator operator--(int) { const_iterator temp(*this); --(*this); return temp; }

        bool operator==(const_iterator other) const { return ptr == other.ptr; }
        bool operator!=(const_iterator other) const { return ptr != other.ptr; }

     private:
        Node* ptr;
    };

    class iterator {
     public:
        using difference_type = ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::bidirectional_iterator_tag;

        iterator(Node* node) : ptr(node) {}
        iterator(const iterator& other) : ptr(other.ptr) {}

        operator const_iterator() const { return const_iterator(ptr); }

        iterator& operator=(const iterator& other) { ptr = other.ptr; return *this; }

        iterator& operator++() { ptr = ptr->next; return *this; }
        iterator operator++(int) { iterator temp(*this); ++(*this); return temp; }

        reference operator*() const { return ptr->val; }
        pointer operator->() const { return &ptr->val; }

        iterator& operator--() { ptr = ptr->prev; return *this; }
        iterator operator--(int) { iterator temp(*this); --(*this); return temp; }

        bool operator==(iterator other) const { return ptr == other.ptr; }
        bool operator!=(iterator other) const { return ptr != other.ptr; }

     private:
        Node* ptr;
    };

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    list() : head(nullptr), tail(nullptr), len(0) {}
    list(size_t count, const T& value) {
        if (!count) {
            return;
        }

        Node* guard = new Node;
        Node* ptr = new Node;

        guard->prev = ptr;
        ptr->next = guard;
        ptr->val = value;
        head = ptr;

        len++;

        while (size() != count) {
            Node* temp = new Node{ value, guard, ptr };

            guard->prev = temp;
            ptr->next = temp;
            ptr = ptr->next;

            len++;
        }

        tail = ptr;
    }
    explicit list(size_t count) {
        if (!count) {
            return;
        }

        Node* guard = new Node;
        Node* ptr = new Node;

        guard->prev = ptr;
        ptr->next = guard;
        head = ptr;

        len++;

        while (size() != count) {
            Node* temp = new Node{ T(), guard, ptr };

            guard->prev = temp;
            ptr->next = temp;
            ptr = ptr->next;

            len++;
        }

        tail = ptr;
    }

    ~list() {
        clear();
    }

    list(const list& other) {
        if (other.empty()) {
            head = tail = nullptr;
            return;
        }

        *this = other;
    }
    list& operator=(const list& other) {
        if (!empty()) {
            clear();
        }

        if (other.empty()) {
            head = tail = nullptr;
            return *this;
        }

        Node* ptr = other.head;

        Node* guard = new Node;
        Node* cur = new Node;

        guard->prev = cur;
        cur->val = ptr->val;
        cur->next = guard;
        head = cur;
        ptr = ptr->next;

        while (ptr != other.tail->next) {
            Node* temp = new Node{ ptr->val, guard, cur };

            guard->prev = temp;
            cur->next = temp;
            cur = temp;
            ptr = ptr->next;
        }

        tail = cur;

        len = other.size();

        return *this;
    }

    T& front() { return *iterator(head); }
    const T& front() const { return *const_iterator(head); }

    T& back() { return *iterator(tail); }
    const T& back() const { return *const_iterator(tail); }

    iterator begin() const { return iterator(head); }
    iterator end() const {
        if (head == nullptr && tail == nullptr) {
            return nullptr;
        }
        return iterator(tail->next);
    }

    const_iterator cbegin() const { return const_iterator(head); }
    const_iterator cend() const {
        if (head == nullptr && tail == nullptr) {
            return nullptr;
        }
        return const_iterator(tail->next);
    }

    reverse_iterator rbegin() const {
        if (head == nullptr && tail == nullptr) {
            return reverse_iterator(tail);
        }
        return reverse_iterator(tail->next);
    }
    reverse_iterator rend() const { return reverse_iterator(head); }

    const_reverse_iterator crbegin() const {
        if (head == nullptr && tail == nullptr) {
            return const_reverse_iterator(tail);
        }
        return const_reverse_iterator(tail->next);
    }
    const_reverse_iterator crend() const { return const_reverse_iterator(head); }

    bool empty() const { return len == 0; }
    size_t size() const { return len; }
    size_t max_size() const {
        iterator it = begin();
        size_t count = 0;

        while (it != end()) {
            it = std::next(it, 1);
            count++;
        }

        return count;
    }
    void clear() {
        if (empty()) {
            return;
        }

        Node* cur = head;

        while (cur) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }

        head = tail = nullptr;

        len = 0;
    }

    iterator insert(const_iterator pos, const T& value) {
        size_t index = std::distance(cbegin(), pos);
        iterator it = std::next(begin(), index);

        Node* cur = head;

        while (index--) {
            cur = cur->next;
        }

        if (cur == tail->next) {
            push_back(value);
            return it;
        }

        if (cur == head) {
            push_front(value);
            return it;
        }

        Node* newNode = new Node{ value, cur, cur->prev };

        cur->prev->next = newNode;
        cur->prev = newNode;

        len++;

        return it;
    }
    iterator insert(const_iterator pos, size_t count, const T& value) {
        size_t index = std::distance(cbegin(), pos);
        iterator it = std::next(begin(), index);

        Node* cur = head;

        while (index--) {
            cur = cur->next;
        }

        if (cur == tail->next) {
            size_t k = 0;
            while (k != count) {
                push_back(value);
                k++;
            }
            return it;
        }

        if (cur == head) {
            size_t k = 0;
            while (k != count) {
                push_front(value);
                k++;
            }
            return it;
        }

        size_t k = 0;
        while (k != count) {
            insert(pos, value);
            k++;
        }
        return it;
    }

    iterator erase(const_iterator pos) {
        if (empty()) {
            return begin();
        }

        size_t index = std::distance(cbegin(), pos);
        Node* cur = head;

        while (index--) {
            cur = cur->next;
        }

        if (cur == tail->next || cur == nullptr) {
            return iterator(nullptr);
        }

        if (cur == tail) {
            pop_back();
            return begin();
        }

        if (cur == head) {
            pop_front();
            return begin();
        }

        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;

        delete cur;

        len--;

        return begin();
    }
    iterator erase(const_iterator first, const_iterator last) {
        if (empty()) {
            return begin();
        }

        if (last == nullptr || first == nullptr) {
            return iterator(nullptr);
        }

        size_t delIndex = std::distance(first, last);
        size_t index = std::distance(cbegin(), first);

        Node* cur = head;

        while (index--) {
            cur = cur->next;
        }

        if (cur == tail) {
            pop_back();
            return begin();
        }

        if (cur == head) {
            size_t k = 0;
            while (k != delIndex) {
                pop_front();
                k++;
            }
            return begin();
        }

        const_iterator it = first;
        while (it != last) {
            const_iterator itt = std::next(it, 1);
            erase(it);
            it = itt;
        }
        return begin();
    }

    void push_back(const T& value) {
        if (empty()) {
            Node* guard = new Node;
            Node* ptr = new Node;

            guard->prev = ptr;
            ptr->val = value;
            head = tail = ptr;
            tail->next = guard;
            guard->prev = tail;

            len++;

            return;
        }
        if (head == tail) {
            delete tail->next;

            Node* ptr = new Node{ value, nullptr, head };

            tail = ptr;
            head->next = tail;

            Node* guard = new Node;

            guard->prev = tail;
            tail->next = guard;

            len++;

            return;
        }

        Node* ptr = new Node{ value, tail->next, tail };

        tail->next = ptr;
        tail = ptr;
        head->prev = nullptr;
        tail->next->prev = tail;

        len++;
    }
    void pop_back() {
        if (empty()) {
            return;
        }

        if (head == tail) {
            clear();
            return;
        }

        Node* newTail = tail->prev;
        tail->next->prev = newTail;
        newTail->next = tail->next;

        delete tail;

        tail = newTail;

        len--;
    }

    void push_front(const T& value) {
        if (empty()) {
            Node* guard = new Node;
            Node* ptr = new Node;

            guard->prev = ptr;
            ptr->val = value;
            ptr->next = guard;
            head = tail = ptr;

            len++;

            return;
        }

        Node* ptr = new Node{ value, head, nullptr };

        head->prev = ptr;
        head = ptr;

        len++;
    }
    void pop_front() {
        if (empty()) {
            return;
        }

        if (head == tail) {
            clear();
            return;
        }

        Node* newHead = head->next;

        delete head;

        newHead->prev = nullptr;
        head = newHead;

        len--;
    }

    void resize(size_t count) {
        if (size() > count) {
            while (size() != count) {
                pop_back();
            }
        }
        if (size() < count) {
            while (size() != count) {
                push_back(T());
            }
        }
    }
    void swap(list& other) {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(tail->next, other.tail->next);
        std::swap(len, other.len);
    }

    void merge(list& other) {
        if (other.empty()) {
            return;
        }

        delete tail->next;

        tail->next = other.head;
        other.head->prev = tail;
        tail = other.tail;
        tail->next = other.tail->next;
        other.tail->next->prev = tail;
        other.head = other.tail = nullptr;

        len += other.size();
        other.len = 0;

        sort();
    }
    void splice(const_iterator pos, list& other) {
        if (other.empty()) {
            return;
        }
        if (pos == cend()) {
            merge(other);
            return;
        }
        if (pos == cbegin()) {
            delete other.tail->next;

            other.tail->next = head;
            head->prev = other.tail;
            head = other.head;
            other.head = other.tail = nullptr;

            len += other.size();
            other.len = 0;

            return;
        }

        size_t index = std::distance(cbegin(), pos);

        Node* cur = head;

        while (index--) {
            cur = cur->next;
        }

        cur->prev->next = other.head;
        cur->prev = other.tail;

        delete other.tail->next;

        other.tail->next = cur;
        other.head->prev = cur->prev;
        other.head = other.tail = nullptr;

        len += other.size();
        other.len = 0;
    }

    void remove(const T& value) {
        if (empty()) {
            return;
        }

        T temp = value;

        for (const_iterator it = cbegin(); it != cend(); ) {
            if (*it == temp) {
                if (it == --cend()) {
                    erase(it);
                    return;
                }

                const_iterator itt = std::next(it, 1);
                erase(it);
                it = itt;
                continue;
            }
            it = std::next(it, 1);
        }
    }
    void reverse() const {
        if (empty()) {
            return;
        }
        iterator it = begin();
        iterator itt = --end();
        for (size_t i = 0, j = size(); i < size() / 2; i++, j--, ++it, --itt) {
            T temp = *it;
            *it = *itt;
            *itt = temp;
        }
    }
    void unique() {
        if (empty()) {
            return;
        }

        for (const_iterator it = cbegin(); it != --cend(); ) {
            const_iterator itt = std::next(it, 1);
            if (*it == *itt) {
                erase(it);
                it = itt;
                continue;
            }
            it = std::next(it, 1);
        }
    }
    void sort() {
        if (empty()) {
            return;
        }

        for (size_t i = 0; i < size(); i++) {
            Node* cur = head;
            Node* nxt = cur->next;
            while (cur != tail) {
                if (cur->val > nxt->val) {
                    swap_for_sort(cur, nxt);
                    nxt = cur->next;
                    continue;
                }
                cur = cur->next;
                nxt = cur->next;
            }
        }
    }

 private:
     void swap_for_sort(Node* first, Node* second) {
         if (first == head) {
             head = second;
         } else if (second == head) {
             head = first;
         }

         if (first == tail) {
             tail = second;
         } else if (second == tail) {
             tail = first;
         }

         Node* temp;

         temp = first->next;
         first->next = second->next;
         second->next = temp;

         first->next->prev = first;
         second->next->prev = second;

         temp = first->prev;
         first->prev = second->prev;
         second->prev = temp;

         if (first->prev != nullptr) {
             first->prev->next = first;
         }

         if (second->prev != nullptr) {
             second->prev->next = second;
         }
     }

 private:
     Node* head{ nullptr };
     Node* tail{ nullptr };
     size_t len{ 0 };
};
}  // namespace task
