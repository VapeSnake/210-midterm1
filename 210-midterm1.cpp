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
        {          // If true, new dynamic node is created and becomes both head AND tail of list.
            head = tail = newNode;
            return; // Exits function after this is done. Position not needed here since list was empty.
        }

        Node *temp = head;                         // If list is not empty, a temporary pointer is needed to traverse and insert node properly.
        for (int i = 0; i < position && temp; ++i) // Loop points temp pointer to each node until it reaches
            temp = temp->next;                     // position or end of list.

        if (!temp)
        { // If desired position is greater than list size, temp will point to nullptr
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode; // Deletes new node since it can't be inserted to prevent memory leak and exits function.
            return;
        }
        // Once position is found, our temp pointer is pointing to node we will insert after.
        newNode->next = temp->next;     // New node's next pointer is set to temp's next pointer to prepare for insertion.
        newNode->prev = temp;           // We do the same for new node's prev pointer, otherwise it would be left as nullptr and break the list.
        if (temp->next)                 // Temp's next pointer points back to temp as prev pointer if temp->next is not nullptr.
            temp->next->prev = newNode; // Ensures node after temp points back to new node as prev pointer.
        else                            // If temp-next = nullptr, then temp is the tail and new node becomes the new tail.
            tail = newNode;
        temp->next = newNode; // Temp's next pointer set to new node to complete insertion.
    }

    void delete_val(int value)
    {              // Deletes first node found with data member = value.
        if (!head) // If list is empty (head = nullptr), exits function since there is nothing to delete.
            return;

        Node *temp = head; // Temp traversal pointer starts at head.

        while (temp && temp->data != value) // As long as temp != nullptr and current node's data != value,
            temp = temp->next;              // temp moves to next node. Repeats until value found or end of list reached.

        if (!temp) // Condition described above^. Exits function if condition is true.
            return;

        if (temp->prev)                    // If temp's prev pointer != nullptr, temp is not head of list.
            temp->prev->next = temp->next; // Sets temp's PREV NODE's next pointer to temp's next pointer to prepare for deletion.
        else                               // If temp's prev pointer = nullptr, temp IS head of list.
            head = temp->next;             // Changes head pointer to next node since current head is being deleted.

        if (temp->next)                    // Same logic as above, but for temp's next pointer. If temp's next pointer != nullptr,
            temp->next->prev = temp->prev; // sets temp's NEXT NODE's prev pointer to temp's prev pointer to prepare deletion.
        else                               // Otherwise, changes tail pointer to temp's prev node since temp is the tail and will be deleted.
            tail = temp->prev;

        delete temp; // Deletes temp node to free memory and complete deletion.
    }

    void delete_pos(int pos)
    { // Deletes node AT chosen position. This time position is indexed starting at 1.
        if (!head)
        { // Displays message and exits function is list is empty. Nothing to delete.
            cout << "List is empty." << endl;
            return;
        }

        if (pos == 1)
        {                // If position is 1, calls pop_front function to delete head of list.
            pop_front(); // Function handles pointer updates and deletion.
            return;
        }

        Node *temp = head; // Temp traversal pointer starting at head.

        for (int i = 1; i < pos; i++) // Starting at 1, temp moves through list until desired position is reached.
        {
            if (!temp)
            { // If temp reaches nullptr, notifies user and exits function since no node exists at position to delete.
                cout << "Position doesn't exist." << endl;
                return;
            }
            else // Moves temp to next node as long as temp != nullptr.
                temp = temp->next;
        }
        if (!temp)
        { // Similar to above
            cout << "Position doesn't exist." << endl;
            return;
        }

        if (!temp->next)
        {               // If temp's next pointer = nullptr, temp is the tail and pop_back function can be called to delete it.
            pop_back(); // Also handles all pointer updates and deletion.
            return;
        }
        // If temp is not head or tail, temp's prev and next nodes need to be linked together to keep list intact after deletion.
        Node *tempPrev = temp->prev; // Otherwise, list will be broken since temp's pointers will dangle after deletion.
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp; // Deletes temp node to free memory and complete deletion.
    }

    void push_back(int v)
    { // Creates new node with value for data member and adds it to end of list.
        Node *newNode = new Node(v);
        if (!tail) // If list is empty (tail = nullptr), new node becomes both head and tail of list.
            head = tail = newNode;
        else
        {                         // If not empty, new node is added after tail and becomes new tail.
            tail->next = newNode; // Old tail's next pointer is set to new node to prepare for insertion.
            newNode->prev = tail;
            tail = newNode; // Tail pointer is updated to new node to complete insertion.
        }
    }

    void push_front(int v)
    { // Similar to push_back, but adds new node to front of list instead. New node becomes new head.
        Node *newNode = new Node(v);
        if (!head) // If list is empty (head = nullptr), new node becomes both head and tail of list.
            head = tail = newNode;
        else
        { // When list is not empty, new node is added before head and becomes new head.
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void pop_front()
    { // Handles deletion of head node.

        if (!head)
        { // Checks if list is empty.
            cout << "List is empty." << endl;
            return;
        }

        Node *temp = head; // Traversal pointer.

        if (head->next)
        { // If head's next pointer != nullptr, head is not the only node in list and head can be updated to next node.
            head = head->next;
            head->prev = nullptr;
        }
        else // Head is only node in list, so head and tail are set to nullptr to show an empty list.
            head = tail = nullptr;
        delete temp; // Deletes temp node to free memory and complete deletion.
    }

    void pop_back()
    { // Handles deletion of tail node.
        if (!tail)
        { // Checks if list is empty.
            cout << "List is empty." << endl;
            return;
        }
        Node *temp = tail; // Traversal pointer.

        if (tail->prev)
        { // If tail->prev != nullptr, tail becomes the previous node and sets next pointer to nullptr.
            tail = tail->prev;
            tail->next = nullptr;
        } // Similar to pop_front.
        else
            head = tail = nullptr;
        delete temp; // Frees memory.
    }

    ~DoublyLinkedList()
    { // Destructor to free memory of all nodes when list is destroyed, otherwise memory leaks!
        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print()
    {                         // Prints list from head to tail.
        Node *current = head; // Traversal pointer.
        if (!current)
        {
            cout << "List is empty." << endl;
            return;
        }
        while (current)
        { // As long as current != nullptr, prints current node's data and moves to next node until end of list reached.
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse()
    { // Prints list from tail to head.
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

    void every_other_element()
    { // Prints every other element in list. i.e: "Head, 3rd node, 5th node"
        Node *current = head;
        if (!current) // Checks if list is empty.
        {
            cout << "List is empty." << endl;
            return;
        }
        int count = 1;  // Counter to keep track of node positions.
        while (current) // Moves through list and prints data of every other node based on count variable.
        {
            if (count % 2 != 0) // If count is odd, current node's data is printed.
                cout << current->data << " ";
            current = current->next; // Moves to next node and increments count until end of list reached.
            count++;
        }
    }
};

    int main()
    {
        // Demo for every_other_element function. Should print odd indexed nodes in list starting with head as index 1.
        cout << "Demo for every_other_element function:" << endl;
        DoublyLinkedList list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        list.push_back(4);
        list.push_back(5);
        cout << "List: ";
        list.every_other_element(); // Should print 1, 3, and 5 since those are the odd indexed nodes in the list.

        list.push_back(6);
        list.push_back(7);
        list.push_back(8);
        cout << "\nUpdated List: ";
        list.every_other_element(); // Should print 1, 3, 5, and 7 since those are the odd indexed nodes in the updated list.

        return 0;
    }