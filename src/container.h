#include <limits>
#include <iterator>

template<typename T>
class ListIterator: std::iterator<std::output_iterator_tag, T> {
private:
    T* c_value;

public:
    ListIterator(T* value): c_value(value) {}

    bool operator != (const ListIterator& other) const {
        return c_value != other.c_value;
    }

    bool operator == (const ListIterator& other) const {
        return c_value == other.c_value;
    }

    typename T::value_type operator*() const {
        return c_value->value;
    }

    ListIterator<T>& operator++ () {
        c_value = c_value->next;
        return *this; 
    }
};


template<typename T, typename Allocator = std::allocator<T>>
class List {
private:
    template<typename U>
    struct Node {
        using value_type = U;
        using pointer = U*;
        using const_pointer = const U*;
        using reference = U&;
        using const_reference = const U&;

        U value;
        Node<U>* next = nullptr;
        
        Node(const_reference value): value(value) {}
        ~Node() = default;
    };
    
public:
    using node_type = Node<T>;
    using value_type = typename node_type::value_type;
    using pointer = typename node_type::pointer;
    using const_pointer = typename node_type::const_pointer;
    using reference = typename node_type::reference;
    using const_reference = typename node_type::const_reference;
    using iterator = ListIterator<node_type>;
    using const_iterator = ListIterator<const node_type>;
    using allocator_type = Allocator;
    using size_type = std::size_t;

    List(): _allocator() {}

    List(size_type count) {
        for (size_type i = 0; i < count; ++i) {
            this->push_back(T());
        }
    }

    List(const List<T>& lst) {
        for (auto it = lst.cbegin(); it != lst.cend(); ++it) {
            this->push_back(*it);
        }
    }
    
    template<typename InputIt>
    List(InputIt first, InputIt end) {
        for (auto it = begin; it != end; ++it) {
            this->push_back(*it);
        }
    }

    ~List() {
        while (this->_front != nullptr) {
            this->_allocator.deallocate(&this->_front->value, 1);
            this->_front = this->_front->next;
        }
    }

    reference front() {
        return *(this->_front).value;
    }

    reference back() {
        return *(this->_back).value;
    }
    
    void push_front(const_reference value) {
       pointer p = this->_allocator.allocate(1);
       *p = value;
       node_type* node = new node_type{*p};
       if (this->_front == nullptr) {
           this->_front = node;
           this->_back = node;
       }
       else {
           node->next = this->_front;
           this->_back = this->_front;
           this->_front = node;
       }
       this->_size++;
    }

    void push_back(const_reference value) {
        pointer p = this->_allocator.allocate(1);
        *p = value;
        node_type* node = new node_type{*p};
        if (this->_front == nullptr) {
            this->_front = node;
            this->_back = node;
        }
        else {
            this->_back->next = node;
            this->_back = node;
        }
        this->_size++;
    }

    iterator begin() {
        return iterator(this->_front);
    }

    iterator end() {
        return iterator(nullptr);
    }

    const_iterator cbegin() {
        return const_iterator(this->_front);
    }

    const_iterator cend() {
        return const_iterator(nullptr);
    }

    size_type size() const {
        return this->_size;
    }
    
    bool empty() const {
        return this->_size == 0;
    }

    allocator_type get_allocator() const {
        return this->allocator;
    }

    size_type max_size() const {
        return std::numeric_limits<size_type>::max();
    }

private:
    Node<T>* _front = nullptr;
    Node<T>* _back = nullptr;
    size_type _size = 0;
    allocator_type _allocator;

};
