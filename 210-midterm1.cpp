#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20; // Constants for max/min random numbers and list size.

class DoublyLinkedList
{
private:
    struct Node // A node for a doubly linked list that stores an integer.
    {
        int data;
        Node *prev;
        Node *next; // Next and previous pointers for doubly linked list to allow traversal in both directions.
        Node(int val, Node *p = nullptr, Node *n = nullptr)
        { // Constructor to initialize node with a value for data. Default for prev and next pointer is nullptr.
            data = val;
            prev = p;
            next = n;
        }
    };
    // Pointers to head and tail of doubly linked list. Vital for all functions to manipulate list.
    Node *head;
    Node *tail;

public:
    DoublyLinkedList() // Constructor to initialize an empty list with no head or tail. Great for making a new list with no nodes yet.
    {
        head = nullptr;
        tail = nullptr;
    }

    void insert_after(int value, int position)
    { // Inserts a new node with value for data member AFTER the node at chosen position.
        if (position < 0)
        {
            cout << "Position must be >= 0." << endl;
            return; // Validation to ensure position is non-negative. Exits function this is true.
        }

        Node *newNode = new Node(value);
        if (!head) // The list traverses and sees if head = nullptr.
        { // If true, new dynamic node is created and becomes both head AND tail of list.
            head = tail = newNode;
            return; // Exits function after this is done. Position not needed here since list was empty.
        }

        Node *temp = head; // If list is not empty, a temporary pointer is needed to traverse and insert node properly.
        for (int i = 0; i < position && temp; ++i) // Loop points temp pointer to each node until it reaches 
            temp = temp->next; // position or end of list.

        if (!temp)
        { // If desired position is greater than list size, temp will point to nullptr
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode; // Deletes new node since it can't be inserted to prevent memory leak and exits function.
            return;
        }
// Once position is found, our temp pointer is pointing to node we will insert after.
        newNode->next = temp->next;// New node's next pointer is set to temp's next pointer to prepare for insertion.
        newNode->prev = temp; // We do the same for new node's prev pointer, otherwise it would be left as nullptr and break the list.
        if (temp->next) // Updates
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(int value)
    {
        if (!head)
            return;

        Node *temp = head;

        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp)
            return;

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next;

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;

        delete temp;
    }

    void delete_pos(int pos)
    {
        if (!head)
        {
            cout << "List is empty." << endl;
            return;
        }

        if (pos == 1)
        {
            pop_front();
            return;
        }

        Node *temp = head;

        for (int i = 1; i < pos; i++)
        {
            if (!temp)
            {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp)
        {
            cout << "Position doesn't exist." << endl;
            return;
        }

        if (!temp->next)
        {
            pop_back();
            return;
        }

        Node *tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v)
    {
        Node *newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int v)
    {
        Node *newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void pop_front()
    {

        if (!head)
        {
            cout << "List is empty." << endl;
            return;
        }

        Node *temp = head;

        if (head->next)
        {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back()
    {
        if (!tail)
        {
            cout << "List is empty." << endl;
            return;
        }
        Node *temp = tail;

        if (tail->prev)
        {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList()
    {
        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print()
    {
        Node *current = head;
        if (!current)
        {
            cout << "List is empty." << endl;
            return;
        }
        while (current)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse()
    {
        Node *current = tail;
        if (!current)
        {
            cout << "List is empty." << endl;
            return;
        }
        while (current)
        {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main()
{
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS; // dummy statement to avoid compiler warning

    return 0;
}