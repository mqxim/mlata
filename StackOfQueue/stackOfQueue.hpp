#pragma once
#include "queue.hpp"
#include "stack.hpp"

using namespace std;

template<class T> class StackOfQueue
{
    public:
        StackOfQueue()
        {
            currentQueue = {};
        }
        
        int getQueueSize()
        {
            return currentQueue.getSize();
        }

        int getStackSize()
        {
            return stack.getSize();
        }

        bool pushQueue()
        {
            if (currentQueue.getSize() == 0)
            {
                return false;
            }

            stack.push(currentQueue);
            currentQueue = {};
            return true;
        }

        void popQueue()
        {
            currentQueue.destroyQueue();
            currentQueue = stack.pop();
        }

        void add(T info)
        {
            currentQueue.put(info);
        }

        T get()
        {
            return currentQueue.get();
        }

        vector<vector<T>> getCopies()
        {
            vector<vector<T>> data;
            vector<Queue<T>> vectorOfQueues = stack.getCopiesAsArray();
            for (auto element = vectorOfQueues.begin(); element != vectorOfQueues.end(); ++element)
            {
                data.push_back(element->getCopiesAsArray());
            }
        }

    private:
        Stack<Queue<T>> stack;
        Queue<T> currentQueue;
};