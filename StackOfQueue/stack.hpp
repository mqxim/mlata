#pragma once
#include <vector>
#include <iostream>

template<class T> class Stack
{
    public:
        Stack()
        {
            head = nullptr;
            size = 0;
        }

        void push(T data)
        {
            ptr item = new StackItem;
            item->info   = data;
            item->next = head;   
            head = item;
            
            size++;
        }

        T pop()
        {
            if (head == nullptr)
            {
                return {};
            }
            ptr item = head;
            T data = item->info;
            head = item->next;
            
            size--;
            
            return data;
        }

        int getSize()
        {
            return size;
        }

        void destroyStack()
        {
            destroy(head);
        }

        vector<T> getCopiesAsArray()
        {
            std::vector<T> vectorOfCopies;

            ptr explorer = head;
            
            while (explorer != nullptr)
            {
                vectorOfCopies.push_back(explorer->info);
                explorer = explorer->next;
            }
            return vectorOfCopies;
        }

    private:
        struct StackItem;
        typedef StackItem *ptr;
        
        void destroy(ptr &pointer)
        {
            if (pointer != nullptr)
            {
                destroy(pointer->next);
                delete pointer;
                pointer = nullptr;
            }
        }

        ptr head;
        int size;
        struct StackItem
        {
            ptr next;
            T info;
        };
};