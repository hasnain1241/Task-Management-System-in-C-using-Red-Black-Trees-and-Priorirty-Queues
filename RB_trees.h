#include <iostream>
#include<string>
#include<queue>

using namespace std;


/*

I have implemented the following classes
1) taskNode
2) taskPriority
3) AssigneNode
7) Priority Queue(heap)
4) Node
5) RB tree
6) Task management system


*/


enum COLOR { RED, BLACK };

class taskNode {

public:

    int taskID;
    string description;
    int priority;
    string assignID;
    bool isCompleted;


    taskNode()
    {
        taskID = 0;
        description = "";
        priority = 0;
        assignID = "";
        isCompleted = false;


    }


    taskNode(int t, string d, int p, string a)
    {

        taskID = t;
        description = d;
        priority = p;
        assignID = a;
        isCompleted = false;




    }


    friend bool operator==(const taskNode& lhs, const taskNode& rhs) {
        return lhs.taskID == rhs.taskID;
    }

    friend bool operator<(const taskNode& lhs, const taskNode& rhs) {



        return lhs.taskID < rhs.taskID;
    }

    friend bool operator>(const taskNode& lhs, const taskNode& rhs) {


        return lhs.taskID > rhs.taskID;
    }






    


    friend bool operator!=(const taskNode& lhs, const taskNode& rhs) {
        // Define how two taskNodes are considered not equal
        return !(lhs == rhs);  
    }

    friend std::ostream& operator<<(std::ostream& os, const taskNode& node) {
        // Output the desired fields of taskNode
        os << "Task ID: " << node.taskID << ", Description: " << node.description; // etc.
        return os;
    }




};


class taskPriority {

public:
    int taskID;
    string description;
    int priority;
    string assignID;
    bool isCompleted;
    bool isDeleted;


    taskPriority()
    {
        taskID = 0;
        description = "";
        priority = 0;
        assignID = "";
        isCompleted = false;
        isDeleted = false;


    }


    taskPriority(int t, string d, int p, string a)
    {

        taskID = t;
        description = d;
        priority = p;
        assignID = a;
        isCompleted = false;
        isDeleted = false;




    }


    friend bool operator==(const taskPriority& lhs, const taskPriority& rhs) {
        return lhs.taskID == rhs.taskID;
    }

    friend bool operator<(const taskPriority& lhs, const taskPriority& rhs) {



        return lhs.priority < rhs.priority;
    }

    friend bool operator>(const taskPriority& lhs, const taskPriority& rhs) {


        return lhs.priority > rhs.priority;
    }

    friend bool operator!=(const taskPriority& lhs, const taskPriority& rhs) {
        // Define how two taskNodes are considered not equal
        return !(lhs == rhs);  
    }

    friend std::ostream& operator<<(std::ostream& os, const taskPriority& node) {
        // Output the desired fields of taskNode
        os << "Task ID: " << node.taskID << ", Description: " << node.description; // etc.
        return os;
    }


};



class AssigneeNode {

public:

    string firstName;
    string lastName;
    string Address;
    string DOB;
    string aID;

    AssigneeNode()
    {
        firstName = "";
        lastName = "";
        Address = "";
        DOB = "";
        aID = "";


    }


    AssigneeNode(string f, string l, string a, string d, string i)
    {
        firstName = f;
        lastName = l;
        Address = a;
        DOB = d;
        aID = i;


    }


    string toString() const {
        stringstream ss;
        ss << "Name: " << firstName << " " << lastName;
        ss << ", Address: " << Address;
        ss << ", DOB: " << DOB;
        ss << ", Assignee ID: " << aID << "\n";
        return ss.str();
    }



    friend bool operator==(const AssigneeNode& lhs, const AssigneeNode& rhs) {
        return lhs.aID == rhs.aID;
    }

    friend bool operator<(const AssigneeNode& lhs, const AssigneeNode& rhs) {
        return lhs.aID < rhs.aID;
    }

    friend bool operator>(const AssigneeNode& lhs, const AssigneeNode& rhs) {
        return lhs.aID > rhs.aID;
    }



    friend bool operator!=(const AssigneeNode& lhs, const AssigneeNode& rhs) {
        return lhs.aID != rhs.aID; 
    }

    friend std::ostream& operator<<(std::ostream& os, const AssigneeNode& node) {
        os << "Name: " << node.firstName << " " << node.lastName
            << ", Address: " << node.Address << ", DOB: " << node.DOB
            << ", Assignee ID: " << node.aID;
        return os;
    }


};

//This is a priority Queue class. It is used in a few functions
//It is used for the prirority pritning


struct PQNode {
    taskNode task;
    PQNode* next;

    PQNode(taskNode t) : task(t), next(nullptr) {}
};



class TaskPriorityQueue {
private:
    PQNode* head;

public:
    TaskPriorityQueue() : head(nullptr) {}

    ~TaskPriorityQueue() {
        while (head != nullptr) {
            PQNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push(taskNode t) {
        PQNode* newNode = new PQNode(t);
        if (head == nullptr || t.priority < head->task.priority) {
            newNode->next = head;
            head = newNode;
        }
        else {
            PQNode* current = head;
            while (current->next != nullptr && current->next->task.priority <= t.priority) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    taskNode top() {
        if (head != nullptr) {
            return head->task;
        }
        // Return a default taskNode in case of empty queue
        return taskNode(-1, "", INT_MAX, ""); // Assuming -1 is an invalid taskID
    }

    void pop() {
        if (head != nullptr) {
            PQNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool empty() const {
        return head == nullptr;
    }
};




//This is a node class
//I have templaztized it so I
//I can use it with taskNode and assigneNode
//it is much easier to use this approach


template <typename T>
class Node {
public:
    T val;  // Now val can be of any type
    COLOR color;
    Node* left, * right, * parent;

    Node(T val) : val(val) {
        parent = left = right = NULL;

        // Node is created during insertion
        // Node is red at insertion, as per the rules of RB trees
        color = RED;
    }

    // returns pointer to uncle
    Node* uncle() {
        // If no parent or grandparent, then no uncle
        if (parent == NULL || parent->parent == NULL)
            return NULL;

        if (parent->isOnLeft())
            // uncle on right
            return parent->parent->right;
        else
            // uncle on left
            return parent->parent->left;
    }

    // check if node is left child of parent
    bool isOnLeft() { return this == parent->left; }

    // returns pointer to sibling
    Node* sibling() {
        // sibling null if no parent
        if (parent == NULL)
            return NULL;

        if (isOnLeft())
            return parent->right;

        return parent->left;
    }

    // moves node down and moves given node in its place
    void moveDown(Node* nParent) {
        if (parent != NULL) {
            if (isOnLeft()) {
                parent->left = nParent;
            }
            else {
                parent->right = nParent;
            }
        }
        nParent->parent = parent;
        parent = nParent;
    }
    //checks for right child
    //returns true and false

    bool hasRedChild() {
        return (left != NULL && left->color == RED) ||
            (right != NULL && right->color == RED);
    }
};

template <typename T>
class RBTree {

public:
    Node<T>* root;

    void leftRotate(Node<T>* x) {
        Node<T>* nParent = x->right;
        if (x == root)
            root = nParent;

        x->moveDown(nParent);

        x->right = nParent->left;
        if (nParent->left != NULL)
            nParent->left->parent = x;

        nParent->left = x;
    }

    void rightRotate(Node<T>* x) {
        Node<T>* nParent = x->left;
        if (x == root)
            root = nParent;

        x->moveDown(nParent);

        x->left = nParent->right;
        if (nParent->right != NULL)
            nParent->right->parent = x;

        nParent->right = x;
    }

    //swapping the colors bw nodes
    void swapColors(Node<T>* x1, Node<T>* x2) {
        COLOR temp;
        temp = x1->color;
        x1->color = x2->color;
        x2->color = temp;
    }

    //swapping the values

    void swapValues(Node<T>* u, Node<T>* v) {
        T temp;
        temp = u->val;
        u->val = v->val;
        v->val = temp;
    }



    void fixRedRed_Violation(Node<T>* x) {
        if (x == root) {
            x->color = BLACK;
            return;
        }

        Node<T>* parent = x->parent, * grandparent = parent->parent,
            * uncle = x->uncle();

        if (parent->color != BLACK) {
            if (uncle != NULL && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                fixRedRed_Violation(grandparent);
            }
            else {
                if (parent->isOnLeft()) {
                    if (x->isOnLeft()) {
                        swapColors(parent, grandparent);
                    }
                    else {
                        leftRotate(parent);
                        swapColors(x, grandparent);
                    }
                    rightRotate(grandparent);
                }
                else {
                    if (x->isOnLeft()) {
                        rightRotate(parent);
                        swapColors(x, grandparent);
                    }
                    else {
                        swapColors(parent, grandparent);
                    }
                    leftRotate(grandparent);
                }
            }
        }
    }


    Node<T>* predecessor(Node<T>* x) {
        Node<T>* temp = x;

        // Go to the left subtree and then find the rightmost node

        while (temp->right != NULL)
            temp = temp->right;


        return temp;
    }

    Node<T>* BSTreplace_afterdelete(Node<T>* x) {
        // Find the predecessor (max value in left subtree) if the left subtree exists
        if (x->left != NULL)
            return predecessor(x->left);

        // If the node has no left child, then it has at most one child
        if (x->left == NULL && x->right == NULL)
            return NULL;

        // If the node has a right child, then return it
        if (x->right != NULL)
            return x->right;

        // Otherwise, it must have a left child
        return x->left;
    }
    void deleteNode(Node<T>* v) {
        Node<T>* u = BSTreplace_afterdelete(v);

        bool uvBlack = ((u == NULL || u->color == BLACK) && (v->color == BLACK));
        Node<T>* parent = v->parent;

        if (u == NULL) {
            if (v == root) {
                root = NULL;
            }
            else {
                if (uvBlack) {
                    fixDoubleBlack_violation(v);
                }
                else {
                    if (v->sibling() != NULL)
                        v->sibling()->color = RED;
                }

                if (v->isOnLeft()) {
                    parent->left = NULL;
                }
                else {
                    parent->right = NULL;
                }
            }
            delete v;
            return;
        }

        if (v->left == NULL || v->right == NULL) {
            if (v == root) {
                v->val = u->val;
                v->left = v->right = NULL;
                delete u;
            }
            else {
                if (v->isOnLeft()) {
                    parent->left = u;
                }
                else {
                    parent->right = u;
                }
                delete v;
                u->parent = parent;
                if (uvBlack) {
                    fixDoubleBlack_violation(u);
                }
                else {
                    u->color = BLACK;
                }
            }
            return;
        }

        swapValues(u, v);
        deleteNode(u);
    }

    void fixDoubleBlack_violation(Node<T>* x) {
        if (x == root)
            return;

        Node<T>* sibling = x->sibling(), * parent = x->parent;
        if (sibling == NULL) {
            fixDoubleBlack_violation(parent);
        }
        else {
            if (sibling->color == RED) {
                parent->color = RED;
                sibling->color = BLACK;
                if (sibling->isOnLeft()) {
                    rightRotate(parent);
                }
                else {
                    leftRotate(parent);
                }
                fixDoubleBlack_violation(x);
            }
            else {
                if (sibling->hasRedChild()) {
                    if (sibling->left != NULL && sibling->left->color == RED) {
                        if (sibling->isOnLeft()) {
                            sibling->left->color = sibling->color;
                            sibling->color = parent->color;
                            rightRotate(parent);
                        }
                        else {
                            sibling->left->color = parent->color;
                            rightRotate(sibling);
                            leftRotate(parent);
                        }
                    }
                    else {
                        if (sibling->isOnLeft()) {
                            sibling->right->color = parent->color;
                            leftRotate(sibling);
                            rightRotate(parent);
                        }
                        else {
                            sibling->right->color = sibling->color;
                            sibling->color = parent->color;
                            leftRotate(parent);
                        }
                    }
                    parent->color = BLACK;
                }
                else {
                    sibling->color = RED;
                    if (parent->color == BLACK)
                        fixDoubleBlack_violation(parent);
                    else
                        parent->color = BLACK;
                }
            }
        }
    }

    void levelOrder(Node<T>* x) {
        if (x == NULL)
            return;

        std::queue<Node<T>*> q;
        Node<T>* curr;

        q.push(x);

        while (!q.empty()) {
            curr = q.front();
            q.pop();

            std::cout << curr->val << "(" << (curr->color == RED ? "RED" : "BLACK") << ") ";

            if (curr->left != NULL)
                q.push(curr->left);
            if (curr->right != NULL)
                q.push(curr->right);
        }
    }

    void inorder(Node<T>* x) {
        if (x == NULL)
            return;
        inorder(x->left);
        std::cout << x->val << "(" << (x->color == RED ? "RED" : "BLACK") << ") ";
        inorder(x->right);
    }

public:
    RBTree() { root = NULL; }

    Node<T>* getRoot() { return root; }

    Node<T>* search(T n) {
        Node<T>* temp = root;
        while (temp != NULL) {
            if (n < temp->val) {
                if (temp->left == NULL)
                    break;
                else
                    temp = temp->left;
            }
            else if (n == temp->val) {
                break;
            }
            else {
                if (temp->right == NULL)
                    break;
                else
                    temp = temp->right;
            }
        }

        return temp;
    }

    void insert(T n) {
        Node<T>* newNode = new Node<T>(n);
        if (root == NULL) {
            newNode->color = BLACK;
            root = newNode;
        }
        else {
            Node<T>* temp = search(n);

            if (temp->val == n) {
                return;
            }

            newNode->parent = temp;

            if (n < temp->val)
                temp->left = newNode;
            else
                temp->right = newNode;

            fixRedRed_Violation(newNode);
        }
    }

    void deleteByVal(T n) {
        if (root == NULL)
            return;

        Node<T>* v = search(n), * u;

        if (v->val != n) {
            std::cout << "No node found to delete with value:" << n << std::endl;
            return;
        }

        deleteNode(v);
    }

    void printInOrder() {
        std::cout << "Inorder: " << std::endl;
        if (root == NULL)
            std::cout << "Tree is empty" << std::endl;
        else
            inorder(root);
        std::cout << std::endl;
    }

    void printLevelOrder() {
        std::cout << "Level order: " << std::endl;
        if (root == NULL)
            std::cout << "Tree is empty" << std::endl;
        else
            levelOrder(root);
        std::cout << std::endl;
    }

    bool compare(const AssigneeNode& a, const AssigneeNode& b) {
        return a.aID < b.aID;  // Compare based on aID
    }


    Node<T>* searchForSpecial(T n) {
        Node<T>* temp = root;
        while (temp != NULL) {
            if (T::compare(n, temp->val)) {  // Use the comparison function
                if (temp->left == NULL)
                    break;
                else
                    temp = temp->left;
            }
            else if (n == temp->val) {
                break;
            }
            else {
                if (temp->right == NULL)
                    break;
                else
                    temp = temp->right;
            }
        }
        return temp;
    }

    void displayByName(std::ostream& out, const string& firstName, const string& lastName) {
        displayByNameHelper(root, out, firstName, lastName);
    }


    void displayByNameHelper(Node<T>* node, std::ostream& out, const string& firstName, const string& lastName) {
        if (node == NULL) return;

        displayByNameHelper(node->left, out, firstName, lastName);

        if (typeid(T) == typeid(AssigneeNode)) {
            AssigneeNode& assignee = static_cast<AssigneeNode&>(node->val);
            if (assignee.firstName == firstName && assignee.lastName == lastName) {
                out << assignee.toString();
            }
        }

        displayByNameHelper(node->right, out, firstName, lastName);
    }


};



class taskManagementSystem {
private:
    int assigneeCount = 0;
    RBTree<AssigneeNode> assigneeTree;
    RBTree<taskNode> taskTree;
    RBTree<taskPriority> taskPtree;


public:
    void addAssignee(const string& firstName, const string& lastName, const string& address, const string& dob) {
        
        string assigneeID = "A00" + to_string(++assigneeCount);  // Generate a unique ID
        AssigneeNode newAssignee(firstName, lastName, address, dob, assigneeID);
        assigneeTree.insert(newAssignee);  // Insert into the tree
    }

    void addTask(int tasD, const string& description, int priority, const string& assigneeID) {
        taskNode newTask(tasD, description, priority, assigneeID);
        taskPriority newTask1(tasD, description, priority, assigneeID);

        taskTree.insert(newTask);  // Insert into the tree
        taskPtree.insert(newTask1);  // Insert into the tree

    }

    

    void displaybyID(std::ostream& out, const string& assigneeID) {
        AssigneeNode searchNode;  // Create a node with the ID to search for
        searchNode.aID = assigneeID;
        Node<AssigneeNode>* foundNode = assigneeTree.search(searchNode);  // Search in the tree

        if (foundNode != NULL && foundNode->val.aID == assigneeID) {
            out << foundNode->val.toString();  // Print the details of the assignee
        }
        else {
            out << "Assignee with ID " << assigneeID << " not found.\n";
        }
    }


    void displaybyname(std::ostream& out, const string& firstName, const string& lastName) {
        assigneeTree.displayByName(out, firstName, lastName);
    }

    void AssigneeWithNoTask(std::ostream& out) {
        checkAssigneeForTasks(assigneeTree.getRoot(), out);
    }

    void checkAssigneeForTasks(Node<AssigneeNode>* node, std::ostream& out) {
        if (node == NULL) return;

        // Check left subtree
        checkAssigneeForTasks(node->left, out);

        // Check if this assignee has a task
        if (!hasTask(node->val.aID)) {
            out << node->val.toString();
        }

        // Check right subtree
        checkAssigneeForTasks(node->right, out);
    }

    bool hasTask(const string& assigneeID) {
        // Start searching from the root of the taskTree
        return findTask(taskTree.getRoot(), assigneeID);
    }

    bool findTask(Node<taskNode>* node, const string& assigneeID) {
        if (node == NULL) return false;

        if (node->val.assignID == assigneeID) return true;

        // Recursively search in left and right subtrees
        return findTask(node->left, assigneeID) || findTask(node->right, assigneeID);
    }

    void ShiftTask(const string& fromAssigneeID, const string& toAssigneeID) {
        shiftTaskHelper(taskTree.getRoot(), fromAssigneeID, toAssigneeID);
    }

    void shiftTaskHelper(Node<taskNode>* node, const string& fromAssigneeID, const string& toAssigneeID) {
        if (node == NULL) return;

        // Recursively call for left and right children
        shiftTaskHelper(node->left, fromAssigneeID, toAssigneeID);
        shiftTaskHelper(node->right, fromAssigneeID, toAssigneeID);

        // Check if the current node's assignID matches fromAssigneeID
        if (node->val.assignID == fromAssigneeID) {
            taskNode updatedTask = node->val;
            updatedTask.assignID = toAssigneeID; // Update assignee ID
            taskTree.deleteNode(node); // Delete the current node
            taskTree.insert(updatedTask); // Re-insert with updated assignee ID
        }
    }




    void printTaskQueue(std::ostream& out) {
        TaskPriorityQueue pq;  // Assuming TaskPriorityQueue is your custom priority queue
        fillPriorityQueue(taskTree.getRoot(), pq); // Assuming this method populates the priority queue

        while (!pq.empty()) {
            taskNode currentTask = pq.top();
            pq.pop();
            string assigneeName = getAssigneeName(currentTask.assignID);
            out << "Task ID: " << currentTask.taskID << ", Description: " << currentTask.description
                << ", Priority: " << currentTask.priority << ", Assignee: " << assigneeName << "\n";
        }
    }


    void fillPriorityQueue(Node<taskNode>* node, TaskPriorityQueue& pq) {
        if (node == NULL) return;

        // Only add tasks that are not completed
        if (!node->val.isCompleted) {
            pq.push(node->val);
        }
        fillPriorityQueue(node->left, pq);
        fillPriorityQueue(node->right, pq);
    }


    string getAssigneeName(const string& assigneeID) {
        Node<AssigneeNode>* assigneeNode = assigneeTree.search(AssigneeNode("", "", "", "", assigneeID));
        if (assigneeNode != nullptr && assigneeNode->val.aID == assigneeID) {
            return assigneeNode->val.firstName + " (" + assigneeID + ")";
        }
        else {
            return "Unknown Assignee (" + assigneeID + ")";  // or return just assigneeID if you prefer
        }
    }


    void DeleteAssignee(const string& assigneeID) {
        if (hasAssignedTasks(assigneeID)) {
            std::cout << "Cannot delete assignee with ID " << assigneeID << " as they have assigned tasks.\n";
            return;
        }

        AssigneeNode toDelete("", "", "", "", assigneeID);
        assigneeTree.deleteByVal(toDelete);
    }




    void DisplayAssignee(std::ostream& out) {
        displayAssigneeHelper(assigneeTree.getRoot(), out);
    }

    void displayAssigneeHelper(Node<AssigneeNode>* node, std::ostream& out) {
        if (node == nullptr) return;

        displayAssigneeHelper(node->left, out);
        out << "Name: " << node->val.firstName << " " << node->val.lastName
            << ", Address: " << node->val.Address << ", DOB: " << node->val.DOB
            << ", Assignee ID: " << node->val.aID << "\n";
        displayAssigneeHelper(node->right, out);
    }



    bool hasAssignedTasks(const string& assigneeID) {
        return hasAssignedTasksHelper(taskTree.getRoot(), assigneeID);
    }

    bool hasAssignedTasksHelper(Node<taskNode>* node, const string& assigneeID) {
        if (node == nullptr) {
            return false;
        }
        if (node->val.assignID == assigneeID) {
            return true;
        }
        return hasAssignedTasksHelper(node->left, assigneeID) || hasAssignedTasksHelper(node->right, assigneeID);
    }


    void AssigneeInOrder(std::ostream& out) {
        assigneeInOrderHelper(assigneeTree.getRoot(), out);
    }


    void assigneeInOrderHelper(Node<AssigneeNode>* node, std::ostream& out) {
        if (node == nullptr) return;

        assigneeInOrderHelper(node->left, out); // Traverse left subtree

        // Output assignee ID and color
        out << node->val.aID << " (" << (node->color == RED ? "red" : "black") << ")\n";

        assigneeInOrderHelper(node->right, out); // Traverse right subtree
    }



    void completeTask(int taskID) {

        taskNode searchNode(taskID, "", 0, "");
        Node<taskNode>* foundNode = taskTree.search(searchNode);

        if (foundNode != nullptr && foundNode->val.taskID == taskID) {
            foundNode->val.isCompleted = true;  // Mark the task as completed
        }
    }

    void updateTaskPriority(int taskID, int newPriority) {
        // Search for the task in taskTree to get the current priority
        taskNode searchNode(taskID, "", 0, "");
        Node<taskNode>* foundNode = taskTree.search(searchNode);

        // Search for the task in taskPtree
        if (foundNode != nullptr && foundNode->val.taskID == taskID) {
            int currentPriority = foundNode->val.priority; // Get current priority from foundNode
            taskPriority searchNode1(taskID, "", currentPriority, "");

            Node<taskPriority>* foundNode1 = taskPtree.search(searchNode1);

            // Check if the task is found in taskPtree and has the same priority
            if (foundNode1 != nullptr && foundNode1->val.priority == currentPriority) {
                // Update the priority in both trees
                foundNode->val.priority = newPriority;
                taskPriority updatedTask = foundNode1->val;
                updatedTask.priority = newPriority;

                taskPtree.deleteByVal(foundNode1->val); // Delete the old node
                taskPtree.insert(updatedTask); // Insert the updated node
            }
        }
    }


    void findHighestPriorityTask(std::ostream& out) {
        // Check if there are any tasks
        if (taskTree.getRoot() == nullptr) {
            out << "No tasks available.\n";
            return;
        }

        // Use TaskPriorityQueue to find the highest priority tasks
        TaskPriorityQueue pq;
        fillPriorityQueue(taskTree.getRoot(), pq);

        if (!pq.empty()) {
            int currentPriority = pq.top().priority;  // Get the priority of the top task

            while (!pq.empty() && pq.top().priority == currentPriority) {
                // Process all tasks with the current highest priority
                taskNode highestPriorityTask = pq.top();
                pq.pop();

                string assigneeName = getAssigneeName(highestPriorityTask.assignID);
                out << "Highest Priority Task: Task ID: " << highestPriorityTask.taskID
                    << ", Description: " << highestPriorityTask.description
                    << ", Priority: " << highestPriorityTask.priority
                    << ", Assignee: " << assigneeName << "\n";
            }
        }
        else {
            out << "No tasks available.\n";
        }
    }




    void findTasksByAssignee(const string& assigneeID, std::ostream& out) {
        // Check if there are any tasks
        if (taskTree.getRoot() == nullptr) {
            out << "No tasks available for Assignee ID " << assigneeID << ".\n";
            return;
        }

        // Retrieve assignee name
        string assigneeName = getAssigneeName(assigneeID);

        // Priority queue to sort tasks by priority
        TaskPriorityQueue pq;

        // Start searching for tasks assigned to the given assigneeID
        findTasksByAssigneeHelper(taskTree.getRoot(), assigneeID, pq);

        if (pq.empty()) {
            out << "No tasks available for Assignee ID " << assigneeID << ".\n";
            return;
        }

        out << "Tasks Assigned to \"" << assigneeName << "\":\n";
        while (!pq.empty()) {
            taskNode task = pq.top();
            pq.pop();
            out << "Task ID: " << task.taskID << ", Description: " << task.description
                << ", Priority: " << task.priority << ", Assignee: " << assigneeName << "\n";
        }
    }

    void findTasksByAssigneeHelper(Node<taskNode>* node, const string& assigneeID, TaskPriorityQueue& pq) {
        if (node == nullptr) return;

        // Traverse the left subtree
        findTasksByAssigneeHelper(node->left, assigneeID, pq);

        // Check if the current node's assignee ID matches the given assignee ID
        if (node->val.assignID == assigneeID) {
            pq.push(node->val);
        }

        // Traverse the right subtree
        findTasksByAssigneeHelper(node->right, assigneeID, pq);
    }


    void countTotalTasks(std::ostream& out) {
        int count = countTasksHelper(taskTree.getRoot());
        out << "Total Tasks in the System: " << count << "\n";
    }

    int countTasksHelper(Node<taskNode>* node) {
        if (node == nullptr) {
            return 0;
        }
        // Count the current node, then add the counts from the left and right subtrees
        return 1 + countTasksHelper(node->left) + countTasksHelper(node->right);
    }


    void searchTasksByPriorityRange(int low, int high, std::ostream& out) {
        TaskPriorityQueue pq;
        searchTasksByPriorityRangeHelper(taskTree.getRoot(), low, high, pq);

        if (pq.empty()) {
            out << "No tasks found within Priority Range (" << low << " to " << high << ").\n";
            return;
        }

        out << "Tasks within Priority Range (" << low << " to " << high << "):\n";
        while (!pq.empty()) {
            taskNode task = pq.top();
            pq.pop();
            string assigneeName = getAssigneeName(task.assignID);
            out << "Task ID: " << task.taskID << ", Description: " << task.description
                << ", Priority: " << task.priority << ", Assignee: " << assigneeName << "\n";
        }
    }

    void searchTasksByPriorityRangeHelper(Node<taskNode>* node, int low, int high, TaskPriorityQueue& pq) {
        if (node == nullptr) return;

        searchTasksByPriorityRangeHelper(node->left, low, high, pq);

        if (node->val.priority >= low && node->val.priority <= high) {
            pq.push(node->val);
        }

        searchTasksByPriorityRangeHelper(node->right, low, high, pq);
    }


    void displayCompletedTasks(std::ostream& out) {
        out << "Completed Tasks:\n";
        displayCompletedTasksHelper(taskTree.getRoot(), out);
    }

    void displayCompletedTasksHelper(Node<taskNode>* node, std::ostream& out) {
        if (node == nullptr) return;

        displayCompletedTasksHelper(node->left, out);

        if (node->val.isCompleted) {
            string assigneeName = getAssigneeName(node->val.assignID);
            out << "Task ID: " << node->val.taskID << ", Description: " << node->val.description
                << ", Priority: " << node->val.priority << ", Assignee: " << assigneeName << "\n";
        }

        displayCompletedTasksHelper(node->right, out);
    }

    void PrintTreeInorder(std::ostream& out) {

        PrintTreeInorderHelper(taskPtree.getRoot(), out);

    }

    void PrintTreeInorderHelper(Node<taskPriority>* node, std::ostream& out) {
        if (node == nullptr) return;

        // Left subtree
        PrintTreeInorderHelper(node->left, out);

        if (!node->val.isDeleted) {  // Check if the task is not deleted
            out << node->val.taskID << " (" << (node->color == RED ? "red" : "black") << ")\n";
        }
        // Right subtree
        PrintTreeInorderHelper(node->right, out);
    }

    void deleteTask(int taskID) {
        // Search for the task in taskTree to get the current priority
        taskNode searchNode(taskID, "", 0, "");
        Node<taskNode>* foundNode = taskTree.search(searchNode);

        if (foundNode != nullptr && foundNode->val.taskID == taskID) {
            int currentPriority = foundNode->val.priority; // Get the current priority from foundNode
            taskPriority searchNode1(taskID, "", currentPriority, "");

            Node<taskPriority>* foundNode1 = taskPtree.search(searchNode1);

            // Check if the task is found in taskPtree and has the same priority
            if (foundNode1 != nullptr && foundNode1->val.priority == currentPriority) {
                foundNode1->val.isDeleted = true;  // Mark the task as deleted
                taskPtree.deleteByVal(foundNode1->val); // Delete from taskPtree

                taskTree.deleteByVal(foundNode->val); // Also delete from taskTree
            }
        }
    }

};