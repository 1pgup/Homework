#pragma once // NOLINT
#include <iterator>

namespace task {

template <class T> class list {
 public:
        class iterator {
         public:
            using difference_type = ptrdiff_t;
            using value_type = T;
            using pointer = T*;
            using reference = T&;
            using iterator_category = std::bidirectional_iterator_tag;

            // constructors
            iterator() : memberPtr(0) {}
            iterator(pointer ptr) : memberPtr(ptr) {}
            iterator(const iterator& other) { memberPtr = other.memberPtr; }

            // operators
            iterator& operator=(const iterator& other) { memberPtr = other.memberPtr; return *this; }

            iterator& operator++() { memberPtr++; return *this; }
            iterator operator++(int) const { iterator tmp = *this; ++(*this); return tmp; }

            reference operator*() const { return *memberPtr; }
            pointer operator->() const { return memberPtr; }

            iterator& operator--() { memberPtr--; return *this; }
            iterator operator--(int) const { iterator tmp = *this; --(*this); return tmp; }

            bool operator==(iterator other) const { return this->memberPtr == other.memberPtr; }
            bool operator!=(iterator other) const { return this->memberPtr != other.memberPtr; }

         private:
            pointer memberPtr;
        };

        class const_iterator {
         public:
            using difference_type = ptrdiff_t;
            using value_type = const T;
            using pointer = const T*;
            using reference = const T&;
            using iterator_category = std::bidirectional_iterator_tag;

            // constructors
            const_iterator() : memberPtr(0) {}
            const_iterator(pointer ptr) : memberPtr(ptr) {}
            const_iterator(const const_iterator& other) { memberPtr = other.memberPtr; }

            // operators
            const_iterator& operator=(const const_iterator& other) {
               memberPtr = other.memberPtr;
               return *this; }

            const_iterator& operator++() { memberPtr++; return *this; }
            const_iterator operator++(int) const { const_iterator tmp = *this; ++(*this); return tmp; }

            reference operator*() const { return *memberPtr; }
            pointer operator->() const { return memberPtr; }

            const_iterator& operator--() { memberPtr--; return *this; }
            const_iterator operator--(int) const { const_iterator tmp = *this; --(*this); return tmp; }

            bool operator==(const const_iterator other) const { return this->memberPtr == other.memberPtr; }
            bool operator!=(const const_iterator other) const { return this->memberPtr != other.memberPtr; }

         private:
            pointer memberPtr;
        };

        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        list(): element(0), len(0) {}

        list(size_t count, const T& value) {
            this->len = count;
            this->element = new T[this->len];
            for (size_t i = 0; i < this->len; i++) {
                this->element[i] = value;
            }
        }

        explicit list(size_t count) {
            this->len = count;
            this->element = new T[this->len];
        }

        list(const list& other) {
            this->~list();

            this->len = other.len;
            this->element = new T[this->len];
            for (size_t i = 0; i < this->len; i++) {
                this->element[i] = other.element[i];
            }
        }

        ~list() {
            delete[] this->element;
            this->element = nullptr;
            this->len = 0;
        }

        list& operator=(const list& other) {
            if (!this->empty()) {
                this->~list();
            }

            this->len = other.len;
            this->element = new T[this->len];
            for (size_t i = 0; i < this->len; i++) {
                this->element[i] = other.element[i];
            }
            return *this;
        }

        T& front() {
            if (this->empty()) {
                throw this->empty();
            }

            iterator front = this->begin();
            return *front;
        }
        const T& front() const {
            if (this->empty()) {
                throw this->empty();
            }

            const_iterator front = this->cbegin();
            return *front;
        }

        T& back() {
            if (this->empty()) {
                throw this->empty();
            }

            iterator back = this->end();
            return *back;
        }
        const T& back() const {
            if (this->empty()) {
                throw this->empty();
            }

            const_iterator back = this->cend();
            return *back;
        }

        iterator begin() const { return iterator(element); }
        iterator end() const { return iterator(element + len); }

        const_iterator cbegin() const { return const_iterator(element); }
        const_iterator cend() const { return const_iterator(element + len); }

        reverse_iterator rbegin() const { return reverse_iterator(element + len); }
        reverse_iterator rend() const { return reverse_iterator(element); }

        const_reverse_iterator crbegin() const { return const_reverse_iterator(element + len); }
        const_reverse_iterator crend() const { return const_reverse_iterator(element); }


        bool empty() const {
            if (this->element == nullptr) {
                return true;
            }
            return false;
        }

        size_t size() const {
            return this->len;
        }

        size_t max_size() const {
            size_t maxLen = 0;
            for (iterator it = this->begin(); it != this->end(); ++it) {
                maxLen++;
            }
            return maxLen;
        }

        void clear() {
            if (this->empty()) {
                return;
            }
            this->~list();
        }

        iterator insert(const_iterator pos, const T& value) {
            if (std::distance(this->cbegin(), this->cend()) <= std::distance(this->cbegin(), pos)) {
                throw pos;
            }

            int counter = std::distance(this->cbegin(), pos);

            list newList;
            iterator it = this->begin();
            for (; it != std::next(this->begin(), counter); ++it) {
                newList.push_back(*it);
            }
            newList.push_back(value);
            iterator where = it;
            for (; it != this->end(); ++it) {
                newList.push_back(*it);
            }
            *this = newList;
            return where;
        }

        iterator insert(const_iterator pos, size_t count, const T& value) {
            if (std::distance(this->cbegin(), this->cend()) <= std::distance(this->cbegin(), pos)) {
                throw pos;
            }

            int counter = std::distance(this->cbegin(), pos);

            list newList;
            iterator it = this->begin();
            for (; it != std::next(this->begin(), counter); ++it) {
                newList.push_back(*it);
            }

            iterator where = it;
            for (size_t i = 0; i != count; i++) {
                newList.push_back(value);
            }

            for (; it != this->end(); ++it) {
                newList.push_back(*it);
            }

            *this = newList;
            return where;
        }

        iterator erase(const_iterator pos) {
            if (std::distance(this->cbegin(), this->cend()) <= std::distance(this->cbegin(), pos)) {
                return this->end();
            }

            int counter = std::distance(this->cbegin(), pos);

            list newList;
            iterator it = this->begin();
            for (; it != std::next(this->begin(), counter); ++it) {
                newList.push_back(*it);
            }
            it = std::next(it, 1);

            for (; it != this->end(); ++it) {
                newList.push_back(*it);
            }

            *this = newList;
            return this->begin();
        }

        iterator erase(const_iterator first, const_iterator last) {
            if (std::distance(this->cbegin(), first) > std::distance(this->cbegin(), last)) {
                throw;
            }

            if (std::distance(this->cbegin(), this->cend()) <= std::distance(this->cbegin(), last) ||
                std::distance(this->cbegin(), this->cend()) <= std::distance(this->cbegin(), first)) {
                return this->end();
            }

            int counter = std::distance(this->cbegin(), first);

            list newList;
            iterator it = this->begin();
            for (; it != std::next(this->begin(), counter); ++it) {
                newList.push_back(*it);
            }

            counter = std::distance(first, last);

            it = std::next(it, counter);

            for (; it != this->end(); ++it) {
                newList.push_back(*it);
            }

            *this = newList;

            return this->begin();
        }

        void push_back(const T& value) {
            list newList(this->size() + 1);
            reverse_iterator newRBegin = newList.rbegin();
            *newRBegin = value;
            newRBegin = std::next(newRBegin, 1);
            for (reverse_iterator rBegin = this->rbegin(); rBegin != this->rend(); ++rBegin, ++newRBegin) {
                *newRBegin = *rBegin;
            }
            *this = newList;
        }

        void pop_back() {
           if (this->empty()) {
                    throw this->empty();
           }

            list newList;
            for (iterator it = this->begin(); it != --this->end(); ++it) {
                newList.push_back(*it);
            }
            *this = newList;
        }

        void push_front(const T& value) {
            list newList(this->size() + 1);
            iterator newIt = newList.begin();
            *newIt = value;
            newIt = std::next(newIt, 1);
            for (iterator it = this->begin(); it != this->end(); ++it, ++newIt) {
                *newIt = *it;
            }
            *this = newList;
        }

        void pop_front() {
            if (this->empty()) {
                throw this->empty();
            }

            list newList;
            for (iterator it = std::next(this->begin(), 1); it != this->end(); ++it) {
                newList.push_back(*it);
            }
            *this = newList;
        }

        void resize(size_t count) {
            if (this->size() == count) {
                return;
            }
            if (this->size() > count) {
                while (this->size() != count) {
                    this->pop_back();
                }
            }
            if (this->size() < count) {
                while (this->size() != count) {
                    this->push_back(0);
                }
            }
        }

        void swap(list& other) {
            list tempList(*this);
            *this = other;
            other = tempList;
        }

        void merge(list& other) {
            reverse_iterator reverseBegin = this->rbegin();
            size_t i = this->size();
            while (i) {
                other.push_front(*reverseBegin);
                reverseBegin = std::next(reverseBegin, 1);
                i--;
            }
            this->clear();
        }

        void splice(const_iterator pos, list& other) {
            int counter = std::distance(this->cbegin(), pos);
            iterator it = this->begin();
            list newList;
            for (; it != std::next(this->begin(), counter); ++it) {
                newList.push_back(*it);
            }

            iterator newIt = other.begin();
            while (newIt != other.end()) {
                newList.push_back(*newIt);
                newIt = std::next(newIt, 1);
            }
            for (; it != this->end(); ++it) {
                newList.push_back(*it);
            }
            *this = newList;
            other.clear();
        }

        void remove(const T& value) {
            list newList;
            iterator it = this->begin();
            for (; it != this->end(); ++it) {
                if (*it != value) {
                    newList.push_back(*it);
                }
            }
            *this = newList;
        }

        void reverse() {
            iterator beginIt = this->begin();
            iterator endIt = std::prev(this->end(), 1);
            for (size_t i = 0, j = this->size(); i < this->size() / 2; i++, j--, ++beginIt, --endIt) {
                T temp = *beginIt;
                *beginIt = *endIt;
                *endIt = temp;
            }
        }

        void unique() {
            list newList;
            iterator it = this->begin();
            for (; it != this->end();) {
                if (*it != *(std::next(it, 1))) {
                    newList.push_back(*it);
                    it = std::next(it, 1);
                    continue;
                }
                newList.push_back(*it);
                it = std::next(it, 2);
            }
            *this = newList;
        }

        void sort() {
            for (size_t i = 0; i < this->size(); i++) {
                iterator it = this->begin();
                iterator itt = std::next(it, 1);
                for (; it != std::prev(this->end(), 1);) {
                    if (*it > *itt) {
                        T temp = *it;
                        *it = *itt;
                        *itt = temp;
                        it = std::next(it, 1);
                        itt = std::next(itt, 1);
                        continue;
                    }
                    it = std::next(it, 1);
                    itt = std::next(itt, 1);
                }
            }
        }

 private:
      T* element;
      size_t len;
};

}  // namespace task
