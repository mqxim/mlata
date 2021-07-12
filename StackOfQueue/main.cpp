#include <iostream>
#include <string>
#include "stackOfQueue.hpp"

using namespace std;

StackOfQueue<string> queueStack;

void printHelp()
{
    cout << "   -newq           create a queue" << endl;
    cout << "   -stksize        create a queue" << endl;
    cout << "   -popq           pop the queue and print it" << endl;
    cout << "   -prntstack      print the whole stack" << endl;
    cout << "   -getheadq        work with the last queue" << endl;
    cout << "   -exit           stop the programm" << endl;
}

void readQ()
{
    string input;
    bool state = false;
    int items = queueStack.getQueueSize() + 1;

    cout << "   To stop adding items and push the queue into stack write -push" << endl;
    cout << "   New items: " << endl;
    while (!state)
    {
        cout << "   Item " << items << " >   ";
        getline(cin, input);
        
        state = input == "-push";
        if (!state)
        {
            items++;
            queueStack.add(input);
        }
    }

    if (!queueStack.pushQueue())
    {
        cout << "   Attempt to push an empty Queue" << endl;
    }
}

void popQueueAndPrint()
{
    if (queueStack.getStackSize() != 0)
    {
        queueStack.popQueue();
        int size = queueStack.getQueueSize();
        cout << "   [Queue size: " << size << "]: "; 
        while (size != 0)
        { 
            cout << queueStack.get();
            size = queueStack.getQueueSize();
            if (size != 0)
            {
                cout << ", ";
            }
        }
        cout << endl;
    }
    else
    {
        cout << "   Stack is empty" << endl;
    }
}

void getLastQ()
{
    if (queueStack.getStackSize() != 0)
    {
        queueStack.popQueue();
        readQ();   
    }
    else
    {
        cout << "   Stack is empty" << endl;
    }
}

void printStack()
{
    int stackSize = queueStack.getStackSize();
    if (stackSize == 0)
    {
        cout << "   Stack is empty" << endl;
    }
    else 
    {
        for (int i = 0; i < stackSize; i++)
        {
            popQueueAndPrint();   
        }
    }
}

void printStackSize()
{
    cout << "   Stack size is: " << queueStack.getStackSize() << endl;
}


void printCopy()
{
    vector<vector<string>> data = queueStack.getCopies();
    for (auto queue = data.begin(); queue != data.end(); ++queue)
    {
        cout << "Size: " << data.size() << " ";
        for (auto element = queue->begin(); element != queue->end(); ++element)
        {
            cout << *element;
        }
        cout << endl;
    }
}

int main()
{
    string input;
    while (input != "-exit")
    {
        cout << ">> ";
        getline(cin, input);
        if (input == "-help")
            printHelp();
        else
        if (input == "-popq")
            popQueueAndPrint();
        else
        if (input == "-prntstack")
            printStack();
        else
        if (input == "-newq")
            readQ();
        else
        if (input == "-exit")
            break;
        else
        if (input == "-stksize")
            printStackSize();
        else
        if (input == "-getheadq")
            getLastQ();
        else
        if (input == "-prntcopy")
            printCopy();
        else
            cout << "   Expected command, got: " << input << ", type -help for help" << endl;
    }
    cout << "Bye" << endl;
    return 0;
}