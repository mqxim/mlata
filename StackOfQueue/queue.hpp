#pragma once
#include <vector>

using namespace std;

template<class T> class Queue
{
    public:
        Queue()
        {
            tale = nullptr;
            size = 0;
        }

        T get()
        {
            ptr explorer = tale;
            if (explorer == nullptr)
            {
                return {};
            }

            ptr lastItem = nullptr;
            ptr lastButOne = nullptr;
            while (explorer != nullptr)
            {
                lastButOne = lastItem;
                lastItem = explorer;
                explorer = explorer->next;
            }

            if (lastButOne != nullptr)
            {
                lastButOne->next = nullptr;
            }
            else
            {
                tale = nullptr;
            }
            
            T info = lastItem->info;
            delete lastItem;
            
            size--; 
            
            return info;
        }

        void put(T value)
        {
            ptr item = new QueueItem;
            item->info = value;
            item->next = this->tale;
            tale = item;
            
            size++;
        }

        int getSize()
        {
            return size;
        }

        vector<T> getCopiesAsArray()
        {
            vector<T> vectorOfCopies;

            ptr explorer = tale;
            
            while (explorer != nullptr)
            {
                vectorOfCopies.push_back(explorer->info);
                explorer = explorer->next;
            }
            return vectorOfCopies;
        }

        void destroyQueue()
        {
            destroy(tale); 
        }

    private:
        struct QueueItem;
        typedef QueueItem *ptr;

        void destroy(ptr &pointer)
        {
            if (pointer != nullptr)
            {
                destroy(pointer->next);
                delete pointer;
                pointer = nullptr;
            }
        }

        struct QueueItem
        {
            ptr next;
            T info;
        };
        int size;
        ptr tale;
};