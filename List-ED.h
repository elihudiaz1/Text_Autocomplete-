#include <iostream>

using namespace std;

template <typename Object>
class List_ED
{
private:
    struct Node
    {
        Object data;
        Node *nextptr;

        Node(const Object & d = Object{}, Node *n = nullptr) : data(d), nextptr(n)
        {}

        friend class List_ED;
    };

public:
    class const_iterator
    {
    public:
        const_iterator() : current(nullptr)
        {}

        const Object & operator* () const
        {
            return retrieve();
        }

        const_iterator & operator++ ()
        {
            current = current->nextptr;
            return *this;
        }

        const_iterator operator++ (int)
        {
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        bool operator== (const const_iterator & rhs) const {
            return current == rhs.current;
        }

        bool operator!= (const const_iterator & rhs) const
        {
            return !(*this == rhs);
        }



    protected:
        Node *current;
        Object & retrieve() const
        {
           return current->data;
        }
        const_iterator(Node *p) : current(p)
        {}

        friend class List_ED<Object>;

    };

    class iterator : public const_iterator
    {
    public:
        iterator()
        {}

        Object & operator* ()
        {
            return const_iterator::retrieve();
        }

        const Object & operator* () const
        {
            return const_iterator::operator*();
        }

        iterator & operator++ ()
        {
            this->current = this->current->nextptr;
            return *this;
        }

        iterator operator++ (int)
        {
            iterator old = *this;
            ++(*this);
            return old;
        }

    protected:
        iterator(Node *p) : const_iterator(p)
        {}

        friend class List_ED<Object>;
    };

public:

    List_ED() : firstptr(0), lastptr(0)
    {

    }

    ~List_ED()
    {
        if(!isEmpty())
        {
            Node *currentptr = firstptr;
            Node *tempptr;

            while(currentptr != 0)
            {
                tempptr = currentptr;
                currentptr = currentptr->nextptr;
                delete tempptr;
            }

        }

    }

    List_ED(const List_ED & rhs)
    {
        List_ED copy;
        for(auto & x : rhs)
            copy.push_back(x);
    }

    void push_back(const Node & value)
    {
        Node *newptr = getNewNode(value);
        if(isEmpty())
        {
            firstptr = lastptr = newptr;
        } else
        {
            lastptr->nextptr = newptr;
            lastptr = newptr;
        }

    }

    iterator begin()
    {
        return firstptr;
    }

    const iterator begin() const {
        return firstptr;
    }

    iterator end()
    {
        return lastptr->nextptr;
    }

    const iterator end() const {
        return lastptr->nextptr;
    }

    bool isEmpty() const
    {
        return (firstptr == 0);
    }

private:

    Node *firstptr;
    Node *lastptr;

    Node *getNewNode(const Node & value ) {
        return new Node(value);
    }

};

