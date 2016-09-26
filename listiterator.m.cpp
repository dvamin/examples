#include <iostream>
#include <cstddef>

template <typename TYPE>
class ListIter;

template <typename TYPE>
class Node {
    TYPE  d_val;
    Node *d_next;

  public:
    Node(const TYPE& val)
    : d_val(val)
    , d_next(0)
    {}

    void next(Node *next)
    {
        d_next = next;;
    }

    Node *next() const
    {
        return d_next;
    }

    const TYPE& value() const
    {
        return d_val;
    }

    TYPE& value()
    {
        return d_val;
    }
};

template <typename TYPE>
class List {
    Node<TYPE> *d_head;

    size_t count() const
    {
        size_t counter = 0;
        Node<TYPE> *t = d_head;
        while (t) {
            counter++; t = t->next();
        }
        return counter;
    }

    TYPE& getNth(size_t n)
    {
        Node<TYPE> *iter = d_head; size_t i = 0;
        while (i < n) {
            i++; iter = iter->next();
        }
        return iter->value();
    }    

  public:
    typedef std::ptrdiff_t difference_type;
    typedef std::size_t size_type;
    typedef TYPE* pointer;
    typedef TYPE& reference;
    typedef TYPE value_type;
    typedef ListIter<TYPE> iterator;

    List()
    : d_head(0)
    {}

    explicit List(Node<TYPE> *head)
    : d_head(head)
    {}

    void prepend(Node<TYPE> *elem)
    {
        if (d_head) {
            Node<TYPE> *nextPtr = d_head;
            d_head = elem;
            elem->next(nextPtr);
        }
        else {
            d_head = elem;
        }
    }

    Node<TYPE> *remove()
    {
        Node<TYPE> *retPtr = 0;
        if (d_head) {
            retPtr = d_head;
            d_head = d_head->next();
        }
        return retPtr;
    }

    void reverseList()
    {
        if (0 == d_head || 0 == d_head->next()) {
            return;
        }

        Node<TYPE> *prev = d_head, *curr = d_head->next(), *next = curr->next();
        while (next) {
            curr->next(prev);
            Node<TYPE> *tmp = next->next();
            next->next(curr);
            prev = curr;
            curr = next;
            next = tmp;
        }
        d_head->next(0);
        d_head = curr;
    }

    void printList() const
    {
        Node<TYPE> *iter = d_head;
        while (iter) {
            std::cout << iter->value() << ", ";
            iter = iter->next();
        }
        std::cout << "DONE!" << std::endl;
    }    

    bool isEmpty() const
    {
        return 0 == d_head;
    }

    ListIter<TYPE> begin()
    {
        return iterator(this, 0);
    }

    ListIter<TYPE> end()
    {
        return iterator(this, count());
    }

    friend class ListIter<TYPE>;
};

template <typename TYPE>
class ListIter {
    List<TYPE> *d_list;
    size_t      d_pos;

    explicit ListIter(List<TYPE> *list, size_t pos)
    : d_list(list)
    , d_pos(pos)
    {
        // assert pos is between 0 and size(list)
    }

  public:
    ListIter<TYPE>& operator++()
    {
        d_pos++; return *this;
    }

    ListIter<TYPE> operator++(int)
    {
        ListIter<TYPE> orig = *this;
        d_pos++;
        return orig;
    }

    TYPE& operator*()
    {
        return d_list->getNth(d_pos);
    }

    TYPE *operator->()
    {
        return &d_list->getNth(d_pos);
    }

    friend class List<TYPE>;

    template <typename T>
    friend bool operator==(const ListIter<T>& lhs, const ListIter<T>& rhs);

    template <typename T>
    friend bool operator!=(const ListIter<T>& lhs, const ListIter<T>& rhs);
};

template <typename TYPE>
bool operator==(const ListIter<TYPE>& lhs, const ListIter<TYPE>& rhs)
{
    return lhs.d_pos == rhs.d_pos;
}

template <typename TYPE>
bool operator!=(const ListIter<TYPE>& lhs, const ListIter<TYPE>& rhs)
{
    return lhs.d_pos != rhs.d_pos;
}

int main()
{
    Node<int> n1(4), n2(13), n3(132), n4(11), n5(53);
    List<int> list;
    list.prepend(&n1);
    list.prepend(&n2);
    list.prepend(&n3);
    list.prepend(&n4);
    list.prepend(&n5);
    for(List<int>::iterator it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << ", ";
    }
    std::cout << "DONE!" << std::endl;
    return 0;
}