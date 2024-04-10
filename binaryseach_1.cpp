template <class T>
class Node
{
public:
    Node()
    {
        prev = NULL;
        next = NULL;
    }
    Node(T data)
    {
        prev = NULL;
        next = NULL;
        this->data = data;
    }
    Node(T data, Node<T> *prev, Node<T> *next)
    {
        this->prev = prev;   //access previous 
        this->next = next;  //access next
        this->data = data;  //access data
    }

    Node<T> *prev;
    Node<T> *next;
    T data;
};

template <class T>
class LinkedList
{
public:
    LinkedList()
    {
        head = NULL;
        tail = NULL;      //list is empty
    }
    void addToTail(T data)  //function adds tail
    {
        Node<T> *newNode = new Node<T>(data);
        if (tail == NULL)   //list is empty add new node
        {
            tail = newNode;
            head = newNode;
        }
        else
        {
            newNode->prev = tail;    //add new node to existing list
            tail->next = newNode;  //new node is assigned to next accessed by tail
            tail = tail->next;
        }
    }
    void addToHead(T data)  //function adds to head
    {
        Node<T> *newNode = new Node<T>(data);
        if (head == NULL)    //the list is empty add new node to list
        {
            head = newNode;   //adds to list
            tail = newNode;
        }
        else
        {
            newNode->next = head;         //add to existing list
            head->prev = newNode;
            head = head->prev;
        }
    }
    void deleteData(T data)   //delete data from list
    {
        Node<T> *cur = head;
        while (cur != NULL)  //list is not empty
        {
            if (data == cur->data)
            {
                if (head == tail)
                {
                    head = NULL;   //head is assigned to null, because it is empty
                }
                else if (cur == head)  //data exists
                {
                    head = head->next;   
                    head->prev = NULL;
                }
                else if (cur == tail)  //the list is full
                {
                    tail = tail->prev;
                    tail->next = NULL;
                }
                else
                {
                    cur->prev->next = cur->next;   
                    cur->next->prev = cur->prev;
                }
                break;
            }
            cur = cur->next;
        }
    }
    void deleteData(T data, int n)   //delete data from list
    {
        if (n == 0)   //nothing to delete
            return;
        deleteData(data);    
        deleteData(data, n - 1);  //delete data
    }
    friend std::ostream &operator<<(std::ostream &out, LinkedList *n)      //output list
    {
        Node<T> *cur = n->head;
        out << "(";
        if (cur != NULL)
            out << cur->data;
        cur = cur->next;
        while (cur != NULL)
        {
            out << ", " << cur->data;
            cur = cur->next;
        }
        out << ")" << endl;
        return out;
    }

    Node<T> *head;
    Node<T> *tail;
};

template <class T>
class Queue
{
public:
    Queue()
    {
        list = new LinkedList<T>;
    }

    void enqueue(T data)   //add to queue
    {
        list->addToTail(data);
    }

    T dequeue()    //delete from queue
    {
        T n = front();
        list->deleteData(front());
        return n;
    }

    T front()
    {
        if (list->head == NULL)  //list is empty
            return 0;
        return (list->head->data);  //list accesses data
    }

    bool isEmpty()  //check if it's empty
    {
        if (list->head == NULL)
            return true;  //it's empty
        else
            return false;
    }

    LinkedList<T> *list;
};

template <class T>
class TreeNode
{
public:
    TreeNode()
    {
        left = NULL;
        right = NULL;
    }
    TreeNode(T data)
    {
        this->data = data;
        left = NULL;
        right = NULL;
    }
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;
};

/**
 * A binarySearchTree abstract class for BinarySearchTree class
 */
template <class T>
class binarySearchTree
{
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
    virtual bool search(T target) = 0;

protected:
    TreeNode<T> *root;
};

int flag;

template <class T>
class BinarySearchTree : public binarySearchTree<T>
{
public:
    BinarySearchTree()
    {
        root = NULL;
    }
    BinarySearchTree(T data)
    {
        root = NULL;
        setRoot(data);
    }
    void preorder() override
    {
        flag = 0;
        preorder(root);
        cout << endl;
    }
    void preorder(TreeNode<T> *node)
    {
        if (node == NULL)
            return;
        if (flag != 0)
            cout << ",";
        cout << node->data;
        flag = 1;
        preorder(node->left);
        preorder(node->right);
    }
    void inorder() override
    {
        flag = 0;
        inorder(root);
        cout << endl;
    }
    void inorder(TreeNode<T> *node)
    {
        if (node == NULL)
            return;
        inorder(node->left);
        if (flag != 0)
            cout << ",";
        cout << node->data;
        flag = 1;
        inorder(node->right);
    }
    void postorder() override
    {
        flag = 0;
        postorder(root);
        cout << endl;
    }
    void postorder(TreeNode<T> *node)
    {
        if (node == NULL)
            return;
        postorder(node->left);
        postorder(node->right);
        if (flag != 0)
            cout << ",";
        cout << node->data;
        flag = 1;
    }
    void levelorder() override
    {
        Queue<TreeNode<T> *> *queue = new Queue<TreeNode<T> *>;
        TreeNode<T> *cur;
        flag = 0;
        queue->enqueue(root);
        while (!queue->isEmpty())
        {
            if (flag != 0)
                cout << ",";
            flag = 1;
            cur = queue->front();
            cout << cur->data;
            if (cur->left != NULL)
                queue->enqueue(cur->left);
            if (cur->right != NULL)
                queue->enqueue(cur->right);
            queue->dequeue();
        }
    }
    bool insert(T data) override
    {
        if (root == NULL)
        {
            root = new TreeNode<T>(data);
            return true;
        }
        TreeNode<T> *cur = root;
        while (true)
        {
            if (data < cur->data)
            {
                if (cur->left == NULL)
                {
                    cur->left = new TreeNode<T>(data);
                    return true;
                }
                cur = cur->left;
            }
            if (data > cur->data)
            {
                if (cur->right == NULL)
                {
                    cur->right = new TreeNode<T>(data);
                    return true;
                }
                cur = cur->right;
            }
            if (data == cur->data)
                return false;
        }
    }
    void setRoot(T data) override
    {
        if (root == NULL)
            root = new TreeNode<T>;
        root->data = data;
    }
    bool search(T data) override
    {
        if (root == NULL)
            return false;
        TreeNode<T> *cur = root;
        while (true)
        {
            if (data < cur->data)
            {
                if (cur->left == NULL)
                    return false;
                cur = cur->left;
            }
            else if (data > cur->data)
            {
                if (cur->right == NULL)
                    return false;
                cur = cur->right;
            }
            else if (data == cur->data)
                return true;
        }
    }

    TreeNode<T> *root;
};