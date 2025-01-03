/*Assignment: Doubly Linked List
 * (COMP 218- Data Structures) (Assignment Number): 1
 * Author(s):Rylie Seaberg
 * Due Date: Friday, 10/04/2024 11:59:00 PM
 * Description: The objective of this project is to implement the doubly linked list (DLL)
 * and practice testing programs efficiently. The program will be implementing the DLL class in
 * and test each member function.
 * Comments: The insertAtHead() and insertAtTail() functions may cause the list to not be in numerical order
 * depending on the inputted value
 * Honor Pledge: I have abided by the Wheaton Honor Code and
 * all work below was performed by Rylie Seaberg .
*/

#include <iostream>
#include <stdexcept>
using namespace std;
using std::runtime_error;

class DLLNode {
    public:
    int data;
    DLLNode* next;
    DLLNode* prev;
    DLLNode(int val) {
        this->data = val;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

class DLL{
    protected:
    DLLNode* head;
    DLLNode* tail;

    public:
    DLL();
    DLL(DLL& toCopy);
    ~DLL();
    int size() const;
    bool isEmpty() const;
    int peekHead() const;
    int peekTail() const;
    int& at(int i) const;
    int& operator[](const int i);
    void insert(const int val);
    void insertAtHead(const int val);
    void insertAtTail(const int val);
    int remove(int val);
    int removeHead();
    int removeTail();
    void display();
    void displayBackwards();
};

/*
 * Description: this is a constructor for the DLL class, establishes the head and tail variables as nullptr
 * @param: N/A
 * @return: N/A
 * Dependencies: N/A
 * */
DLL :: DLL() {
    head = nullptr;
    tail = nullptr;
}

/*
 * Description: This is a destructor for the DLL class, that will deallocate memory when necessary
 * @param: N/A
 * @return: N/A
 * Dependencies: N/A
 * */
DLL :: ~DLL() {
    DLLNode *temp;
    DLLNode *current;
    current = this->head;

    while (current != nullptr) {
        temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
}

/*
 * Description:
 * @param: toCopy- a variable that initializes an object using another object of the same class
 * @return: N/A
 * Dependencies: N/A
 * */
DLL :: DLL (DLL& toCopy) {
    head = nullptr;
    DLLNode *current = toCopy.head;
    DLLNode *lastNode = nullptr;

    while (current != nullptr) {
        DLLNode *newNode = new DLLNode(current->data);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            lastNode->next = newNode;
            newNode->prev = lastNode;
        }
        lastNode = newNode;
    }
}

void test_copyConstructor(){
    cout << "TESTING copyConstructor() FUNCTION" <<endl;
// 1. empty list
    //DLL emptyList;
    //emptyList.size(); // ERROR: size(), the list is empty
// 2. non-empty list with a single node and multiple nodes
    DLL list;
    list.insert(12);
    list.insert(47);
    list.insert(190);
    list.insert(389);
    list.insert(1210);
    list.display(); //12 <-> 47 <-> 190 <-> 289 <-> 1210
    list.displayBackwards(); // 1210 <-> 289 <-> 190 <-> 47 <-> 12
    DLL list2 = list;
    list2.display(); //12 <-> 47 <-> 190 <-> 289 <-> 1210
    list2.displayBackwards(); // 1210 <-> 289 <-> 190 <-> 47 <-> 12

}


/*
 * Description: this function gets the size of the doubly linked list using a counter variable
 * @param: N/A
 * @return: the size of the doubly linked list
 * Dependencies: N/A
 * */
int DLL :: size() const {
    DLLNode *current = this->head;
    int size = 0;
    while (current != nullptr) {
        size++;
        current = current->next;
    }
    return size;
}
/*
 * Description: this function tests whether or not the size() function in the class DLL returns the size
 * of the doubly linked ist
 * @param: N/A
 * @return:N/A
 * Dependencies: insert(), display(), size()
 * */
void test_size(){
    cout << "TESTING size() FUNCTION" <<endl;
// 1. empty list
    //DLL emptyList;
    //emptyList.size(); // ERROR: size(), the list is empty
// 2. non-empty list with a single node and multiple nodes
    DLL list;
    list.insert(2);
    list.insert(4);
    list.insert(6);
    list.insert(8);
    list.insert(10);
    list.display();
    cout << list.size() << endl; //5


    list.insert(0);
    list.display();
    cout << list.size() << endl; //6

    list.insert(12);
    list.insert(14);
    list.display();
    cout << list.size() << endl; //8
}



/*
 * Description: prints the doubly linked list head to tail
 * @param: N/A
 * @return: N/A
 * Dependencies: N/A
 * */
void DLL :: display(){
    DLLNode* current = head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

/*
 * Description: prints the doubly linked list tail to head
 * @param: N/A
 * @return: N/A
 * Dependencies: N/A
 * */
void DLL :: displayBackwards(){
    DLLNode* current = tail;
    while (current) {
        cout << current->data << " ";
        current = current->prev;
    }
    cout << endl;
}
/*
 * Description: inserts a value in the form of a node in numeric order
 * @param: val, the node being created and then added to the doubly linked list
 * @return: N/A
 * Dependencies: isEmpty(), makes sure the doubly linked list has values in it
 * */
void DLL :: insert(int val) {
    DLLNode *newNode = new DLLNode(val);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        DLLNode* curr = head;
        while (curr != nullptr) {
            if (newNode->data < curr->data) {
                newNode->next = curr;
                newNode->prev = curr->prev;
                if (curr->prev) {
                    curr->prev->next = newNode;
                } else {
                    head = newNode;
                }
                curr->prev = newNode;
                return;
            }
            curr = curr->next;
        }
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}
/*
 * Description: this function tests whether or not the insert() and display() functions in the class DLL adds
 * values in numeric order to the the doubly linked list and the display function then outputs the list
 * @param: N/A
 * @return:N/A
 * Dependencies: insert(), display()
 * */
void test_insert_display(){
    cout << "TESTING insert() FUNCTION" <<endl;

    DLL list;
    list.insert(29);
    list.insert(20);
    list.insert(4849);
    list.insert(840);
    list.insert(108);
    list.display(); //20 <-> 29 <-> 108  <-> 840 <-> 4849
    list.displayBackwards(); // 4849 <-> 840 <-> 108 <-> 29 <-> 20


    list.insert(1);
    list.display(); // 1 <-> 20 <-> 29 <-> 108 <-> 840 <-> 4849
    list.displayBackwards(); // 4849 <-> 840 <-> 108 <-> 29 <-> 20 <-> 1

    list.insert(930);
    list.insert(78);
    list.display(); // 1 <-> 20 <-> 29 <-> 78 <-> 108 <-> 930 <-> 840 <-> 4849
    list.displayBackwards(); // 4849 <-> 840 <-> 930 <-> 108 <-> 78 <-> 29 <-> 20 <-> 1
}

/*
 * Description: inserts a value in the form of a node at the head of the doubly linked list
 * @param: value, the node being created and then added to the head of the doubly linked list
 * @return: N/A
 * Dependencies: isEmpty(), makes sure the doubly linked list has values in it
 * */
void DLL :: insertAtHead(int value) {
    DLLNode* newNode = new DLLNode(value);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}
/*
 * Description: this function tests whether or not the insertAtHead() function in the class DLL adds
 * a value to the head node of the doubly linked list
 * @param: N/A
 * @return:N/A
 * Dependencies: insert(), display(), insertAtHead()
 * */
void test_insertAtHead() {
    cout << "TESTING insertAtHead() FUNCTION" <<endl;
// 1. empty list
    //DLL emtpyList;
    //emtpyList.insertAtHead(); // ERROR: insertAtHead(), the list is empty
// 2. non-empty list with a single node and multiple nodes
    DLL list;
    list.insert(4);
    list.insert(8);
    list.insert(12);
    list.display(); // head: 4 <-> 8 <-> 12 : tail
    list.insertAtHead(36); // head: 36 <-> 4 <-> 8 <-> 12: tail
    list.insertAtHead(88); // head: 88 <-> 36 <-> 4 <-> 8 <-> 12: tail
    list.display();
}

/*
 * Description: inserts a value in the form of a node at the tail of the doubly linked list
 * @param: value, the node being created and then added to the tail of the doubly linked list
 * @return: N/A
 * Dependencies: isEmpty(), makes sure the doubly linked list has values in it
 * */
void DLL :: insertAtTail(int value) {
    DLLNode* newNode = new DLLNode(value);
    if (tail == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}
/*
 * Description: this function tests whether or not the insertAtTail() function in the class DLL adds
 * a value to the tail node of the doubly linked list
 * @param: N/A
 * @return:N/A
 * Dependencies: insert(), display(), insertAtTail()
 * */
void test_insertAtTail() {
    cout << "TESTING insertAtTail() FUNCTION" <<endl;
// 1. empty list
    //DLL emtpyList;
    //emtpyList.insertAtTail(); // ERROR: insertAtTail(), the list is empty
// 2. non-empty list with a single node and multiple nodes
    DLL list;
    list.insert(12);
    list.insert(36);
    list.insert(24);
    list.display(); // head: 12 <-> 24 <-> 36 : tail
    list.insertAtTail(6); // head: 12 <-> 24 <-> 36 <-> 6: tail
    list.display();
}




/*
 * Description: tests whether or not the doubly linked list is only nullptrs
 * @param: N/A
 * @return: a boolean value (TRUE- variable )
 * Dependencies: N/A
 * */
bool DLL :: isEmpty() const {
    return head == nullptr;
}
/*
 * Description: this function tests whether or not the isEmpty() function in the class DLL tests properly
 * if the doubly linked list is strictly nullptrs as nodes of the list
 * @param: N/A
 * @return:N/A
 * Dependencies: insert(), display(), isEmpty()
 * */
void test_isEmpty(){
    cout << "TESTING isEmpty() FUNCTION" <<endl;
// 1. empty list
    DLL emtpyList;
    emtpyList.isEmpty(); // ERROR: isEmpty(), the list is empty
// 2. non-empty list with a single node and multiple nodes
    //DLL list;
    //list.insert(2);
    //list.insert(1);
    //list.insert(3);

    //list.display();
    //list.isEmpty(); // 1<->2<->3
}





/*
 * Description: this function shows the head node of the doubly linked list
 * @param: N/A
 * @return: the head node value
 * Dependencies: N/A
 * */
int DLL :: peekHead() const {
    if (this->head != nullptr) {
        return this->head->data;
    }
    throw std::runtime_error("DLL is empty");
}
/*
 * Description: this function tests whether or not the peekHead() function in the class DLL will return
 * the value of the head node in the doubly linked list
 * @param: N/A
 * @return:N/A
 * Dependencies: insert(), display(), peekHead()
 * */
void test_peekHead() {
    cout << "TESTING peekHead() FUNCTION" <<endl;
// 1. empty list
    //DLL emtpyList;
    //emtpyList.peekHead(); // ERROR: peekHead(), the list is empty
// 2. non-empty list with a single node and multiple nodes
    DLL list;
    list.insert(2);
    list.display(); // head: 2 : tail
    list.peekHead(); // 2
    list.insert(1);
    list.insert(3);
    list.display(); // head: 1 <-> 2 <-> 3 : tail
    cout << list.peekHead() << endl; // 1
}

/*
 * Description: this function shows the tail node of the doubly linked list
 * @param: N/A
 * @return: the tail node value
 * Dependencies: N/A
 * */
int DLL :: peekTail() const {
    if (this->tail != nullptr) {
        return this->tail->data;
    }
    throw std::runtime_error("DLL is empty");
}
/*
 * Description: this function tests whether or not the peekTail() function in the class DLL will return
 * the value of the tail node in the doubly linked list
 * @param: N/A
 * @return:N/A
 * Dependencies: insert(), display(), peekTail()
 * */
void test_peekTail() {
// 1. empty list
    cout << "TESTING peekTail() FUNCTION" <<endl;
    //DLL emtpyList;
    //emtpyList.peekTail(); // ERROR: peekTail(), the list is empty
// 2. non-empty list with a single node and multiple nodes
    DLL list;
    list.insert(4);
    list.display(); // head: 4 : tail
    list.peekTail(); // 4
    list.insert(2);
    list.insert(6);
    list.display(); // head: 2 <-> 4 <-> 6 : tail
    cout << list.peekTail()<< endl; // 6
}





/*
 * Description: access the nodes of doubly linked list and determine the data at a user inputted index
 * @param: i, the index in which the user wants to know the value of the node
 * @return: the value of the specified node
 * Dependencies: isEmpty(), makes sure the doubly linked list has values in it
 * */
int& DLL::operator[](const int i) {
    if (isEmpty()) {
        throw std::out_of_range("Index out of range");
    }
    DLLNode* current = head;
    int index = 0;

    while (current != nullptr) {
        if (index == i) {
            return current->data;
        }
        current = current->next;
        index++;
    }
    throw std::out_of_range("Index out of range");
}
/*
 * Description: this function tests whether or not the operator[] function in the class DLL will return
 * the value of the user inputted index
 * @param: N/A
 * @return:N/A
 * Dependencies: insert(), display(), operator[]
 * */
void test_operator(){
    cout << "TESTING operator[] FUNCTION" <<endl;
// 1. empty list
    //DLL emptyList;
    //cout << emptyList[3] << endl; // 4 // ERROR: operator[], the list is empty
// 2. non-empty list with a single node and multiple nodes
    DLL list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);
    list.insert(6);
    list.display(); // head: 1 <-> 2 <-> 3 <-> 4 <-> 5 <-> 6: tail
    cout << list[3] << endl; // 4
    cout << list[0] << endl; // 1
    cout << list[5] << endl; // 6
}

/*
 * Description: iterates through the doubly linked list in order to find the
 * @param: i, a specific node index
 * @return: the value at the index specified
 * Dependencies: isEmpty(), makes sure the doubly linked list has values in it
 * */
int& DLL ::at(int i) const {
    if (isEmpty()) {
        throw std::out_of_range("Index out of range");
    }
    DLLNode* current = head;
    int index = 0;

    while (current != nullptr) {
        if (index == i) {
            return current->data;
        }
        current = current->next;
        index++;
    }
    throw std::out_of_range("Index out of range");
}
/*
 * Description: this function tests whether or not the at() function in the class DLL will return
 * the value of the user inputted index
 * @param: N/A
 * @return:N/A
 * Dependencies: insert(), display(), at()
 * */
void test_at(){
    cout << "TESTING at() FUNCTION" <<endl;
// 1. empty list
    //DLL emtpyList;
    //emtpyList.at(1); // ERROR: at(), the list is empty
// 2. non-empty list with a single node and multiple nodes
    DLL list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);
    list.insert(6);
    list.display(); // head: 1 <-> 2 <-> 3 <-> 4 <-> 5 <-> 6: tail
    cout << list.at(2) << endl; // 3
    cout << list.at(3) << endl; // 4
}




/*
 * Description: removes a specified value
 * @param: value, the node that is to be removed
 * @return: N/A
 * Dependencies: N/A
 * */
int DLL:: remove(int val)  {
    DLLNode* current = head;

    while (current != nullptr) {
        if (current->data == val) {
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }
            if (current->next != nullptr) {
                current->next->prev = current->prev;
            }
            delete current;
            return val;
        }
        current = current->next;
    }
    cout << "Value " << val << " not found in the list." << endl;
}
/*
 * Description: this function tests whether or not the remove() function in the class DLL will return
 * the value removed from the doubly linked list
 * @param: N/A
 * @return:N/A
 * Dependencies: insert(), display(), remove()
 * */
void test_remove() {
    cout << "TESTING remove() FUNCTION" <<endl;
    // 1. empty list
    //DLL emtpyList;
    //emtpyList.remove(); // ERROR: remove(), the list is empty
    // 2. non-empty list with a single node and multiple nodes
    DLL list;
    list.insert(4);
    list.insert(8);
    list.insert(12);
    list.display(); // head: 4 <-> 8 <-> 12 : tail
    list.remove(8); // head: 4 <-> 12 : tail
    list.display();
}

/*
 * Description: removes the head node of the doubly linked list
 * @param: N/A
 * @return: the removed tail node data value
 * Dependencies: isEmpty(), makes sure the doubly linked list has values in it
 * */
int DLL::removeHead() {
    if (isEmpty()) {
        throw std::runtime_error("List is empty");
    }
    int val = head->data;
    DLLNode* temp = head;
    head = head->next;
    if (head) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    delete temp;
    return val;
}
/*
 * Description: this function tests whether or not the removeHead() function in the class DLL will return
 * the head node removed from the doubly linked list
 * @param: N/A
 * @return:N/A
 * Dependencies: insert(), display(), removeHead()
 * */
void test_removeHead() {
    cout << "TESTING removeHead() FUNCTION" <<endl;
// 1. empty list
    //DLL emtpyList;
    //emtpyList.removeHead(); // ERROR: removeHead(), the list is empty
// 2. non-empty list with a single node and multiple nodes
    DLL list;
    list.insert(2);
    list.insert(4);
    list.insert(6);
    list.display(); // head: 2 <-> 4 <-> 6 : tail
    list.removeHead(); // head: 4 <-> 6 : tail
    list.display();
}

/*
 * Description: removes the value at the tail node
 * @param: N/A
 * @return: the removed tail node data value
 * Dependencies: isEmpty(), makes sure the doubly linked list has values in it
 * */
int DLL::removeTail() {
    if (isEmpty()) {
        throw std::runtime_error("List is empty");
    }
    int val = tail->data;
    DLLNode* temp = tail;
    tail = tail->prev;
    if (tail) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }
    delete temp;
    return val;
}
/*
 * Description: this function tests whether or not the removeTail() function in the class DLL will return
 * the tail node removed from the doubly linked list
 * @param: N/A
 * @return:N/A
 * Dependencies: insert(), display(), removeTail()
 * */
void test_removeTail() {
    cout << "TESTING removeTail() FUNCTION" <<endl;
// 1. empty list
    //DLL emtpyList;
    //emtpyList.removeTail(); // ERROR: removeTail(), the list is empty
// 2. non-empty list with a single node and multiple nodes
    DLL list;
    list.insert(3);
    list.insert(6);
    list.insert(9);
    list.display(); // head: 3 <-> 6 <-> 9 : tail
    list.removeTail(); // head: 3 <-> 6 : tail
    list.display();
}





int main() {
    DLL list;
    test_copyConstructor();
    test_size();

    test_insert_display();
    test_insertAtHead();
    test_insertAtTail();

    test_isEmpty();

    test_peekHead();
    test_peekTail();

    test_operator();
    test_at();

    test_remove();
    test_removeHead();
    test_removeTail();

    return 0;
}

