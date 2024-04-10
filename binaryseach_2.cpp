#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template<class T>
class binarySearchTree;

template<class T>
class BinarySearchTree;

template<class T>
class LinkedList;

template<class T>
class Queue;

template<class T>
class Stack;

template<class T>
class TreeNode;


/**
 * A Node class of Doublely Linked List class
 */
template<class T>
class Node {
public:

    /**
     * Construct a new Node object with no parameter
     */
    Node() {
    }

    /**
     * Construct a new Node object with parameter
     * @param data: data to put in
     */
    Node(T data) {
        this->data = data;
    }

    /**
     * Construct a new Node object with parameters
     * @param data: data to put in
     * @param prev: pointer to the previous node
     * @param next: pointer to the next node
     */
    Node(T data, Node<T>* prev, Node<T>* next) {
        this->data = data;
        this->next = next;
        this->prev = prev;
    }

    /**
    * Getter for the data parameter
    */
    T getData() {
        return this->data;
    }

    /**
    * Getter for the next parameter
    */
    Node<T>* getNext() {
        return next;
    }


    /**
    * Getter for the prev parameter
    */
    Node<T>* getPrev() {
        return prev;
    }

private:
    friend class LinkedList<T>;
    friend class Queue<T>;
    friend class Stack<T>;
    friend class TreeNode<T>;
    Node<T>* prev;
    Node<T>* next;
    T data;
};

/**
 * A Doublely Linked List class
 */
template<class T>
class LinkedList {
public:

    /**
     * Construct a new LinkedList object with no parameter
     */
    LinkedList() {
        n = 0;
        head = nullptr;
        tail = nullptr;
    }


    /**
     * Destroy a LinkedList object and free memory
     */
    ~LinkedList() {
        Node<T>* dummy = head;
        Node<T>* after;
        while (dummy != nullptr) {
            after = dummy->next;
            delete dummy;
            dummy = after;
        }
        head = tail = nullptr;
    }

    /**
     * Add a node to the tail of the linked list
     * @param data: data to put in
     */
    void addToTail(T data) {
        Node<T>* newTail = new Node<T>(data, tail, nullptr);
        if (tail != nullptr) {
            this->tail->next = newTail;
            this->tail = newTail;
        }
        else {
            this->tail = newTail;
            this->head = newTail;
        }
        n += 1;
    }

    /**
     * Add a node to the head of the linked list
     * @param data: data to put in
     */
    void addToHead(T data) {
        Node<T>* newHead = new Node<T>(data, nullptr, head);
        if (head != nullptr) {
            this->head->prev = newHead;
            this->head = newHead;
        }
        else {
            this->tail = newHead;
            this->head = newHead;
        }
        n += 1;
    }

    /**
     * Delete a node from the linked list with the given data from the head
     * If there are no data to be deleted, then do nothing
     * @param data: data to delete
     */
    void deleteData(T data) {
        if (head != nullptr) {
            Node<T>* dummy = head;

            while (dummy != nullptr) {
                if (dummy->data == data) {
                    deleteNode(dummy);
                    break;
                }
                dummy = dummy->next;
            }
        }
    }

    /**
     * Delete a node from the linked list with the given data from the tail
     * If there are no data to be deleted, then do nothing
     * @param data: data to delete
     */
    void deleteDataTail(T data) {
        if (tail != nullptr) {
            Node<T>* dummy = tail;

            while (dummy != nullptr) {
                if (dummy->data == data) {
                    deleteNode(dummy);
                    break;
                }
                dummy = dummy->prev;
            }
        }
    }

    /**
     * Delete valid n nodes from the linked list with the given data from the head
     * If there are no more data to be deleted, then just skip
     * @param data: data to delete
     * @param amount: max number of nodes to delete
     */
    void deleteData(T data, int amount) {
        if (head != nullptr) {
            Node<T>* dummy = head;
            Node<T>* after;
            int i = 0;
            while (dummy != nullptr) {
                after = dummy->next;
                if (i == amount) break;
                if (dummy->data == data) {
                    deleteNode(dummy);
                    i += 1;
                }

                dummy = after;
            }
        }
    }

    /**
     * Overload the operator << to print out all the data in the linked list from the head
     * There is a \n in the end of each print
     *
     * Output example:
     * If your linked list data is 5, 4, 3, 2, 1
     * then you should print out "(5, 4, 3, 2, 1)" with the content in quotes but without the quotes
     */
    friend std::ostream& operator<<(std::ostream& out, LinkedList* n) {
        out << "(";

        Node<T>* dummy = n->head;

        while (dummy != nullptr) {
            out << dummy->getData();
            if (dummy->getNext() != nullptr) {
                out << ", ";
            }
            dummy = dummy->getNext();
        }
        out << ")\n";
        return out;
    }

private:
    int n;
    Node<T>* head;
    Node<T>* tail;
    friend class Queue<T>;
    friend class Stack<T>;

    /**
     * Delete a node (multiple case csenarios)
     */
    void deleteNode(Node<T>* a) {
        if (a == head && a == tail) {
            head = nullptr;
            tail = nullptr;
        }
        else if (a == head) {
            head = a->next;
            a->next->prev = nullptr;
        }
        else if (a == tail) {
            tail = a->prev;
            a->prev->next = nullptr;
        }
        else {
            a->prev->next = a->next;
            a->next->prev = a->prev;
        }
        delete a;
        n -= 1;
    }
};


/**
* A Queue class
*/
template<class T>
class Queue
{
public:

    /**
     * Construct a new Queue object with no parameter
     */
    Queue() {
        this->list = new LinkedList<T>();
    }

    /**
     * Add a data to queue
     * @param data: data to be added to queue
     */
    void enqueue(T data) {
        this->list->addToTail(data);
    }

    /**
     * Remove a data from queue and return it
     * @return the data removed from queue
     */
    T dequeue() {
        T headdata = this->list->head->getData();
        this->list->deleteData(headdata);
        return headdata;
    }

    /**
     * @return the first element in the queue
     */
    T front() {
        T headdata = this->list->head->getData();
        return headdata;
    }

    /**
     * @return true if queue is empty, false otherwise
     */
    bool isEmpty() {
        if (this->list->head == nullptr) return true;
        else return false;
    }

private:
    LinkedList<T>* list;
};

/**
 * A Stack class
 */
template<class T>
class Stack
{
public:

    /**
     * Construct a new Stack object with no parameter
     */
    Stack() {
        this->list = new LinkedList<T>();
    }

    /**
     * Add a data to stack
     * @param data: data to be added to stack
     */
    void push(T data) {
        this->list->addToHead(data);
    }

    /**
     * Remove a data from stack and return it
     * @return the data removed from stack
     */
    T pop() {
        T headdata = this->list->head->getData();
        this->list->deleteData(headdata);
        return headdata;
    }

    /**
     * @return the last element in the stack
     */
    T top() {
        T headdata = this->list->head->getData();
        return headdata;
    }

    /**
     * @return true if stack is empty, false otherwise
     */
    bool isEmpty() {
        if (this->list->head == nullptr) return true;
        else return false;
    }

    /**
     * @return the size of the stack
     */
    int size() {
        return this->list->n;
    }

    void sortStack()
    {
        Stack<int>* tmpStack = new Stack<int>;

        while (!this->isEmpty())
        {
            // pop out the first element
            int tmp = this->top();
            this->pop();

            // while temporary stack is not empty and top of stack is greater than temp
            while (!tmpStack->isEmpty() && tmpStack->top() > tmp)
            {
                // pop from temporary stack and push it to the input stack
                this->push(tmpStack->top());
                tmpStack->pop();
            }

            // push temp in temporary of stack
            tmpStack->push(tmp);
        } //sorted elements in ascending order in tmpStack

        while (!tmpStack->isEmpty()) {
            this->push(tmpStack->pop());
        }
    }

    void output() {
        cout << this->list;
        return;
    }

private:
    LinkedList<T>* list;
};


/**
 * A TreeNode class of binarySearchTree class
 */
template<class T>
class TreeNode {
public:
    TreeNode() {

    }
    TreeNode(T data) {
        this->left = nullptr;
        this->right = nullptr;
        this->data = data;
    }
private:
    friend class binarySearchTree<T>;
    friend class BinarySearchTree<T>;
    friend class Queue<T>;
    T data;
    TreeNode<T>* left;
    TreeNode<T>* right;
};

/**
 * A binarySearchTree abstract class for BinarySearchTree class
 */
template<class T>
class binarySearchTree {
public:
    /**
     * Print preorder traversal of the tree
     * Format: "4,5,6,7". Data seperate by "," with no spaces between and without quotes
     */
    virtual void preorder() = 0;

    /**
     * Print inorder traversal of the tree
     * Format: "4,5,6,7". Data seperate by "," with no spaces between and without quotes
     */
    virtual void inorder() = 0;

    /**
     * Print postorder traversal of the tree
     * Format: "4,5,6,7". Data seperate by "," with no spaces between and without quotes
     */
    virtual void postorder() = 0;

    /**
     * Print levelorder traversal of the tree
     * Format: "4,5,6,7". Data seperate by "," with no spaces between and without quotes
     */
    virtual void levelorder() = 0;

    /**
     * Insert data into the tree if the value is not present
     * @param data data to insert
     * @return true if insert successfully, false if the value is already present
     */
    virtual bool insert(T data) = 0;

    /**
     * Set the value of the root
     * @param data to set to root
     */
    virtual void setRoot(T data) = 0;

    /**
     * Search the tree for the given value
     * @param target target to find
     * @return true if found, false if not found
     */
    virtual bool serach(T target) = 0;
protected:
    TreeNode<T>* root = nullptr;
};

template<class T>
class BinarySearchTree : public binarySearchTree<T> {
public:
    BinarySearchTree() {
        this->root = NULL;
    }
    /**
     * Print preorder traversal of the tree, VLR
     * Format: "4,5,6,7". Data seperate by "," with no spaces between and without quotes
     */
    virtual void preorder() {
        string a = "";
        if (this->root != nullptr) {
            preorderTrav(root, a);
        }
        a.erase(a.begin() + a.size() - 1);
        cout << a << '\n';
        return;
    }

    /**
     * Print inorder traversal of the tree, LVR
     * Format: "4,5,6,7". Data seperate by "," with no spaces between and without quotes
     */
    virtual void inorder() {
        string a = "";
        if (this->root != nullptr) {
            inorderTrav(root, a);
        }
        a.erase(a.begin() + a.size() - 1);
        cout << a << '\n';
        return;
    }

    /**
     * Print postorder traversal of the tree, LRV
     * Format: "4,5,6,7". Data seperate by "," with no spaces between and without quotes
     */
    virtual void postorder() {
        string a = "";
        if (this->root != nullptr) {
            postorderTrav(root, a);
        }
        a.erase(a.begin() + a.size() - 1);
        cout << a << '\n';
        return;
    }

    /**
     * Print levelorder traversal of the tree
     * Format: "4,5,6,7". Data seperate by "," with no spaces between and without quotes
     */
    virtual void levelorder() {
        if (this->root == nullptr) return;

        stringstream ss;

        // empty node 
        Queue<TreeNode<T>*> q;

        // print root
        ss << this->root->data;

        // enquee roots children        
        q.enqueue(this->root->left);
        q.enqueue(this->root->right);

        TreeNode<T>* tnode = nullptr;

        int nullcounter = 0;

        while (!q.isEmpty()) {
            // dequeue node
            tnode = q.dequeue();

            if (tnode == nullptr) {
                nullcounter++;
                continue;
            }

            while (nullcounter > 0) {
                ss << ",NULL";
                nullcounter--;
            }

            // print info
            ss << ',' << tnode->data;

            // enquee node's children        
            q.enqueue(tnode->left);
            q.enqueue(tnode->right);
        }

        string result = ss.str();
        cout << result << endl;
    }

    /**
     * Insert data into the tree if the value is not present
     * @param data data to insert
     * @return true if insert successfully, false if the value is already present
     */
    virtual bool insert(T data) {
        if (this->root == nullptr) {
            // insert as root
            this->root = new TreeNode<T>(data);
            return true;
        }

        serach(data);

        if (searched->data == data) {
            return false;
        }

        TreeNode<T>* newnode = new TreeNode<T>(data);
        if (data > searched->data)
            searched->right = newnode;
        else
            searched->left = newnode;
        return true;
    }



    /**
     * Set the value of the root
     * @param data to set to root
     */
    virtual void setRoot(T data) {
        if (this->root != nullptr) {
            postorderClear(this->root->left);
            postorderClear(this->root->right);
            delete this->root;
        }
        TreeNode<T>* newroot = new TreeNode<T>;
        newroot->data = data;
        this->root = newroot;
        return;
    }

    /**
     * Search the tree for the given value
     * @param target target to find
     * @return true if found, false if not found
     */
    virtual bool serach(T target) {
        if (this->root == nullptr) return false;
        // TreeNode<T> *node = root;
        searched = this->root;

        while (searched->data != target) {
            if (target > searched->data) {
                if (searched->right == nullptr)
                    break;
                searched = searched->right;
            }
            else {
                if (searched->left == nullptr)
                    break;
                searched = searched->left;
            }
        }
        return searched->data == target;
    }
protected:
    TreeNode<T>* searched = nullptr;
    /**
     * preorder tree traversal, VLR
     * @param current received node
     */
    void preorderTrav(TreeNode<T>* current, string& a) {
        if (current != nullptr) {
            a = a + to_string(current->data);
            a = a + ',';
            preorderTrav(current->left, a);
            preorderTrav(current->right, a);
        }
        return;
    }

    ///**
    // * preorder tree traversal, VLR
    // * @param current received node
    // */
    //TreeNode<T>* search(TreeNode<T>* root, int data) {
    //    // Traverse until root reaches to dead end
    //    while (root != nullptr) {
    //        // pass right subtree as new tree
    //        if (data > root->data)
    //            root = root->right;

    //        // pass left subtree as new tree
    //        else if (data < root->data)
    //            root = root->left;
    //        else
    //            return root; // if the key is found return 1
    //    }
    //    return nullptr;
    //}

    //TreeNode<T>* newNode(T data)
    //{
    //    TreeNode<T>* temp = new TreeNode<T>;
    //    temp->data = data;
    //    temp->left = temp->right = nullptr;
    //    return temp;
    //}

    /**
     * inorder tree traversal, LVR
     * @param current received node
     */
    void inorderTrav(TreeNode<T>* current, string& a) {
        if (current != nullptr) {
            inorderTrav(current->left, a);
            a = a + to_string(current->data);
            a = a + ',';
            inorderTrav(current->right, a);
        }
        return;
    }

    /**
     * postorder tree traversal, LRV
     * @param current received node
     */
    void postorderTrav(TreeNode<T>* current, string& a) {
        if (current != nullptr) {
            postorderTrav(current->left, a);
            postorderTrav(current->right, a);
            a = a + to_string(current->data);
            a = a + ',';
        }
        return;
    }

    /**
     * postorder tree traversal, LRV
     * @param current received node
     */
    void postorderClear(TreeNode<T>* current) {
        if (current != nullptr) {
            postorderClear(current->left);
            postorderClear(current->right);
            delete current;
        }
        return;
    }

    TreeNode<T>* root;
};

void removeSubstrs(string& s, string& p) {
    string::size_type n = p.length();
    for (string::size_type i = s.find(p); i != string::npos; i = s.find(p)) s.erase(i, n);
    return;
}

void replacecommas(string& s) {
    for (string::size_type i = s.find(","); i != string::npos; i = s.find(",")) {
        s.replace(i, 1, " ");
    }
}


int main()
{
    string a;
    while (getline(cin, a)) {
        stringstream ss;
        BinarySearchTree<int> tree;
        string pattern = ",NULL";
        removeSubstrs(a, pattern);
        replacecommas(a);
        ss << a;
        int n;
        while (ss >> n) {
            tree.insert(n);
        }
        tree.levelorder();

    }
    
    return 0;
}
