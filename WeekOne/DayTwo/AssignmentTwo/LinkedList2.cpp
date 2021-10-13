#include <iostream>
typedef struct Node {
    int     data;
    struct Node *next;    
}Node_t;

Node_t *findLast(Node_t *LinkedList) {
    if (LinkedList == nullptr) {    
        return LinkedList;
    }
    Node_t *current = LinkedList;
     while (current->next != nullptr) {
        current = current->next;
    }
    return current;

}
Node_t *add(Node_t *LinkedList, int value) {
    // 1) find the last item
    // 2)create a new node
    // 3) assign & link
    if (LinkedList == nullptr) {
        LinkedList = new Node_t;
        LinkedList->data  = value;
        LinkedList->next = nullptr;
              
    } else {
        Node_t  *newNode = new Node_t,
                *lastNode = findLast(LinkedList);
        newNode->next = nullptr;
        newNode->data = value;
        lastNode->next = newNode; 
           
    }
    return LinkedList;
}

Node_t *remove(Node_t *LinkedList) {
    // 1) find the head of next and set is as new head
    // 2) delete head
    if (LinkedList == nullptr) {
        return LinkedList;
    }
    Node_t *secondFirst = LinkedList->next;
    delete LinkedList;
    return secondFirst;

}
void print(Node_t *LinkedList) {
    // 1)loop over the list
    // 2) print things
     
    if (LinkedList == nullptr){
        std::cout << "List is empty" << std::endl;
        return;
    } 

    Node_t *current = LinkedList;    
    while(current->next != nullptr) {
        std::cout << current->data << std::endl; 
        current = current->next;       
    }
    std::cout << current->data << std::endl;
}
int main (int argc, char ** argv) {  
      
    Node_t * MY_LINKED_LIST = nullptr;
    std::cout << "Add 3 elements" << std::endl;    
    MY_LINKED_LIST = add (MY_LINKED_LIST, 12);
    MY_LINKED_LIST = add (MY_LINKED_LIST, 152);
    MY_LINKED_LIST = add (MY_LINKED_LIST, 1232);
    print(MY_LINKED_LIST);
    std::cout << "Remove 1 element" << std::endl;
    MY_LINKED_LIST = remove (MY_LINKED_LIST);
    print(MY_LINKED_LIST);
    std::cout << "Remove 2 element" << std::endl;
    MY_LINKED_LIST = remove (MY_LINKED_LIST);
    MY_LINKED_LIST = remove (MY_LINKED_LIST);
    print(MY_LINKED_LIST);
    std::cout << "Add 1 elements" << std::endl;  
    MY_LINKED_LIST = add (MY_LINKED_LIST, 13);
    print(MY_LINKED_LIST);
    return 0;
}