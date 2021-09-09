#include <iostream>
#include <fstream>
using namespace std;

// A doubly linked list node
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};


class linkedlist {


public:


    //insert a new node at the end of the list
    void insert_end(struct Node** head, int new_data)
    {
        //allocate memory for node
        struct Node* newNode = new Node;

        struct Node* last = *head; //set last node value to head

        //set data for new node
        newNode->data = new_data;

        //new node is the last node , so set next of new node to null
        newNode->next = NULL;

        //check if list is empty, if yes make new node the head of list
        if (*head == NULL) {
            newNode->prev = NULL;
            *head = newNode;
            return;
        }

        //otherwise traverse the list to go to last node
        while (last->next != NULL)
            last = last->next;

        //set next of last to new node
        last->next = newNode;

        //set last to prev of new node
        newNode->prev = last;
        return;
    }

    void del(Node** head, int position)
    {

        // If linked list is empty
        if (*head == NULL)
            return;

        // Store head node
        Node* temp = *head;

        // If head needs to be removed
        if (position == 0)
        {

            // Change head
            *head = temp->next;

            // Free old head
            free(temp);
            return;
        }

        // Find previous node of the node to be deleted
        for (int i = 0; temp != NULL && i < position - 1; i++)
            temp = temp->next;

        // If position is more than number of nodes
        if (temp == NULL || temp->next == NULL)
            return;

        // Node temp->next is the node to be deleted
        // Store pointer to the next of node to be deleted
        Node* next = temp->next->next;

        // Unlink the node from linked list
        free(temp->next); // Free memory

        // Unlink the deleted node from list
        temp->next = next;
    }

    int find(struct Node** head, int x) {


        //Get head node address
        Node* temp = *head;

        //place hold for index of int in linked list
        int pos = 0;

        //traverses doubly linked list
        while (temp->data != x && temp->next != NULL) {

            //pos counter updates position
            pos++;

            //updates temp object address
            temp = temp->next;
        }

        if (temp->data != x)
            return -1;

        return (pos + 1);

    }

    // This function prints contents of linked list starting from the given node
    void displayList(struct Node* node) {
        struct Node* last;

        while (node != NULL) {
            cout << node->data << " | ";
            last = node;
            node = node->next;
        }
        if (node == NULL)
            cout << "NULL";
    }

    /*Function to swap the nodes */
    struct Node* swap(struct Node* ptr1, struct Node* ptr2)
    {
        struct Node* tmp = ptr2->next;
        ptr2->next = ptr1;
        ptr1->next = tmp;
        return ptr2;
    }
    
    /* Function to sort the list */
    void bubbleSort(struct Node** head, int count)
    {
        struct Node** h;
        int i, j, swapped;
    
        for (i = 0; i <= count; i++)
        {
    
            h = head;
            swapped = 0;
    
            for (j = 0; j < count - i - 1; j++) 
            {
    
                struct Node* p1 = *h;
                struct Node* p2 = p1->next;
    
                if (p1->data > p2->data)
                {
    
                    /* update the link after swapping */
                    *h = swap(p1, p2);
                    swapped = 1;
                }
    
                h = &(*h)->next;
            }
    
            /* break if the loop ended without any swap */
            if (swapped == 0)
                break;
        }
    }
  
    /* Function to print the list */
    void printList(struct Node* n)
    {
        while (n != NULL)
        {
            cout << n->data << " -> ";
            n = n->next;
        }
        cout << endl;
    }




};
//main program
int main() {
    
    struct Node* head = NULL;
    
    linkedlist ll;
    int targetDeletion, loc, choice, value, count, temp;
    fstream file_injest;
    string v, path;
  

    do {

        printf("\n1. Insert Tail\n2. Find \n3. Delete \n4. Inject node list \n5. Bubble sort nodes \n6. Display nodes \n7. Exit \nSelect Operation: ");
        cin >> choice;
        

        switch (choice)
        {
            case 1:

                printf("\nEnter value for new item: \n");
                cin >> value;
                ll.insert_end(&head, value);
                cout << "List updated." << endl;
                ll.displayList(head);

                break;
            case 2:
            
                printf("\nEnter value for desired search: \n");
                cin >> value;
                loc = ll.find(&head, value);
                if (loc == -1) {
                    cout << "Query not found!" << endl;

                }
                else {
                    cout << "Query: " << value << " found at position " << loc << endl;
                }
                break;
            case 3:

                printf("\nEnter value for desired deletion: \n");
                cin >> value;
                loc = ll.find(&head, value);
                if (loc == -1) {
                    cout << "Query not found!" << endl;
                    exit(0);
                }
                ll.del(&head, (loc - 1));
                cout << "Node deleted at position " << loc << endl;
                count--;
                cout << "List updated." << endl;
                ll.displayList(head);
                break;
            case 4:
                
                cout << "Enter file path to injest: \n";
                cin >> path;
              
                file_injest.open(path,ios::in); //open a file to perform read operation using file object
                if (file_injest.is_open()){   //checking whether the file is open
                    string tp;
                    while(getline(file_injest, v)){ //read data from file object and put it into string.
                       temp = stoi(v);
                       ll.insert_end(&head, temp);
                       cout << v;
                       count++;
                    }
                    file_injest.close(); //close the file object.
                }
                cout << "Nodes injected successfully.\n";

                break;
            case 5:
                
                ll.bubbleSort(&head, count);
                ll.printList(head);
                break;
            case 6:
                ll.printList(head);
                break;
            case 7:
                exit(0);
                break;
                
            default:
                cout << "Please enter a valid option!" << endl;
        }
    } while (choice != 4);

   

    return 0;
}

