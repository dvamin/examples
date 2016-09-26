#include <iostream>
#include <vector>

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
};

template <typename TYPE>
class List {
    Node<TYPE> *d_head;

  public:
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

    const int count() const
    {
        Node<TYPE> *iter = d_head;
        int counter = 0;
        while (iter) {
            counter++; iter = iter->next();
        }
        return counter;
    }    
};

template <typename TYPE>
class Stack {
    List<TYPE> d_list;

  public:
    Stack()
    : d_list()
    {}

    void push(TYPE val)
    {
        Node<TYPE> *n = new Node<TYPE>(val);
        d_list.prepend(n);
    }

    TYPE pop()
    {
        if (isEmpty()) {
            throw std::runtime_error("Cannot pop from empty stack");
        }
        Node<TYPE> *n = d_list.remove();
        TYPE val = n->value();
        delete n;
        return val;
    }

    bool isEmpty() const
    {
        return 0 == d_list.count();
    }
};

int main()
{
    Stack<int> s;
    std::cout << "Pushing: " << 1 << std::endl;
    s.push(1);
    std::cout << "Pushing: " << 2 << std::endl;
    s.push(2);
    std::cout << "Popped: " << s.pop() << std::endl;
    std::cout << "Pushing: " << 3 << std::endl;
    s.push(3);
    std::cout << "Popped: " << s.pop() << std::endl;
    std::cout << "Popped: " << s.pop() << std::endl;
    std::cout << "Pushing: " << 4 << std::endl;
    s.push(4);
    std::cout << "Popped: " << s.pop() << std::endl;
    std::cout << "Popped: " << s.pop() << std::endl;
    return 0;
}