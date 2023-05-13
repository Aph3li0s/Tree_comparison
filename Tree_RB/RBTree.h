#ifndef RED_BLACK_TREE_RBTREE_H
#define RED_BLACK_TREE_RBTREE_H

using namespace std;

enum Color {RED, BLACK, DOUBLE_BLACK};


template <typename T>
class Node
{
    public:
        T data;
        int color;
        Node<T> *left, *right, *parent;
        explicit Node(T);
};

template <typename T>
class RBTree
{
    private:
        Node<T> *root;
    protected:
        void rotateLeft(Node<T> *&);
        void rotateRight(Node<T> *&);
        void fixInsertRBTree(Node<T> *&);
        void fixDeleteRBTree(Node<T> *&);
        void inorderBST(Node<T> *&);
        void preorderBST(Node<T> *&);
        int getColor(Node<T> *&);
        void setColor(Node<T> *&, int);
        Node<T> *minValueNode(Node<T> *&);
        Node<T> *maxValueNode(Node<T> *&);
        Node<T> *insertBST(Node<T> *&, Node<T> *&);
        Node<T> *deleteBST(Node<T> *&, T);
        int getBlackHeight(Node<T> *);
        int maxDepthUtil(Node<T> *);
    public:
        RBTree();
        void insertValue(T);
        void deleteValue(T);
        void merge(RBTree);
        void inorder();
        void preorder();
        int maxDepth();
};

template <typename T>
Node<T>::Node(T data) {
    this->data = data;
    color = RED;
    left = right = parent = nullptr;
}

template <typename T>
RBTree<T>::RBTree() {
    root = nullptr;
}

template <typename T>
int RBTree<T>::getColor(Node<T> *&node) {
    if (node == nullptr)
        return BLACK;

    return node->color;
}

template <typename T>
void RBTree<T>::setColor(Node<T> *& node, int color) {
    if (node == nullptr)
        return;

    node->color = color;
}

template <typename T>
Node<T>* RBTree<T>::insertBST(Node<T> *& root, Node<T> *&ptr) {
    if (root == nullptr)
        return ptr;
    if (ptr->data < root->data) {
        root->left = insertBST(root->left, ptr);
        root->left->parent = root;
    } else if (ptr->data > root->data) {
        root->right = insertBST(root->right, ptr);
        root->right->parent = root;
    }
    return root;
}

template <typename T>
void RBTree<T>::insertValue(T n) {
    Node<T> *node = new Node<T>(n);
    root = insertBST(root, node);
    fixInsertRBTree(node);
}

template <typename T>
void RBTree<T>::rotateLeft(Node<T> *&ptr) {
    Node<T> *right_child = ptr->right;
    ptr->right = right_child->left;

    if (ptr->right != nullptr)
        ptr->right->parent = ptr;

    right_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = right_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = right_child;
    else
        ptr->parent->right = right_child;

    right_child->left = ptr;
    ptr->parent = right_child;
}

template <typename T>
void RBTree<T>::rotateRight(Node<T> *&ptr) {
    Node<T> *left_child = ptr->left;
    ptr->left = left_child->right;

    if (ptr->left != nullptr)
        ptr->left->parent = ptr;

    left_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = left_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = left_child;
    else
        ptr->parent->right = left_child;

    left_child->right = ptr;
    ptr->parent = left_child;
}

template <typename T>
void RBTree<T>::fixInsertRBTree(Node<T> *&ptr) {
    Node<T> *parent = nullptr;
    Node<T> *grandparent = nullptr;
    while (ptr != root && getColor(ptr) == RED && getColor(ptr->parent) == RED) {
        parent = ptr->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {
            Node<T> *uncle = grandparent->right;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            } else {
                if (ptr == parent->right) {
                    rotateLeft(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateRight(grandparent);
                swap(parent->color, grandparent->color);
                ptr = parent;
            }
        } else {
            Node<T> *uncle = grandparent->left;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            } else {
                if (ptr == parent->left) {
                    rotateRight(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateLeft(grandparent);
                swap(parent->color, grandparent->color);
                ptr = parent;
            }
        }
    }
    setColor(root, BLACK);
}

template <typename T>
void RBTree<T>::fixDeleteRBTree(Node<T> *&node) {
    if (node == nullptr)
        return;

    if (node == root) {
        root = nullptr;
        return;
    }

    if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED) {
        Node<T> *child = node->left != nullptr ? node->left : node->right;

        if (node == node->parent->left) {
            node->parent->left = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete (node);
        } else {
            node->parent->right = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete (node);
        }
    } else {
        Node<T> *sibling = nullptr;
        Node<T> *parent = nullptr;
        Node<T> *ptr = node;
        setColor(ptr, DOUBLE_BLACK);
        while (ptr != root && getColor(ptr) == DOUBLE_BLACK) {
            parent = ptr->parent;
            if (ptr == parent->left) {
                sibling = parent->right;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateLeft(parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if(getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->right) == BLACK) {
                            setColor(sibling->left, BLACK);
                            setColor(sibling, RED);
                            rotateRight(sibling);
                            sibling = parent->right;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->right, BLACK);
                        rotateLeft(parent);
                        break;
                    }
                }
            } else {
                sibling = parent->left;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateRight(parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if (getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->left) == BLACK) {
                            setColor(sibling->right, BLACK);
                            setColor(sibling, RED);
                            rotateLeft(sibling);
                            sibling = parent->left;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->left, BLACK);
                        rotateRight(parent);
                        break;
                    }
                }
            }
        }
        if (node == node->parent->left)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
        delete(node);
        setColor(root, BLACK);
    }
}

template <typename T>
Node<T>* RBTree<T>::deleteBST(Node<T> *&root, T data) {
    if (root == nullptr)
        return root;

    if (data < root->data)
        return deleteBST(root->left, data);

    if (data > root->data)
        return deleteBST(root->right, data);

    if (root->left == nullptr || root->right == nullptr)
        return root;

    Node<T> *temp = minValueNode(root->right);
    root->data = temp->data;
    return deleteBST(root->right, temp->data);
}

template <typename T>
void RBTree<T>::deleteValue(T data) {
    Node<T> *node = deleteBST(root, data);
    fixDeleteRBTree(node);
}

template <typename T>
void RBTree<T>::inorderBST(Node<T> *&ptr) {
    if (ptr == nullptr)
        return;

    inorderBST(ptr->left);
    cout << ptr->data << " " << ptr->color << endl;
    inorderBST(ptr->right);
}

template <typename T>
void RBTree<T>::inorder(){
    inorderBST(root);
}

template <typename T>
void RBTree<T>::preorderBST(Node<T> *&ptr) {
    if (ptr == nullptr)
        return;

    cout << ptr->data << " " << ptr->color << endl;
    preorderBST(ptr->left);
    preorderBST(ptr->right);
}

template <typename T>
void RBTree<T>::preorder() {
    preorderBST(root);
    cout << "-------" << endl;
}

template <typename T>
Node<T> *RBTree<T>::minValueNode(Node<T> *&node) {

    Node<T> *ptr = node;

    while (ptr->left != nullptr)
        ptr = ptr->left;
    return ptr;
}

template <typename T>
Node<T>* RBTree<T>::maxValueNode(Node<T> *&node){
    Node<T> *ptr = node;
    while (ptr->right != nullptr)
        ptr = ptr->right;
    return ptr;
}

template <typename T>
int RBTree<T>::getBlackHeight(Node<T> *node) {
    int blackheight = 0;
    while (node != nullptr) {
        if (getColor(node) == BLACK)
            blackheight++;
        node = node->left;
    }
    return blackheight;
}

template <typename T>
void RBTree<T>::merge(RBTree<T> rbTree2) {
    int temp;
    Node<T> *c, *temp_ptr;
    Node<T> *root1 = root;
    Node<T> *root2 = rbTree2.root;
    int initialblackheight1 = getBlackHeight(root1);
    int initialblackheight2 = getBlackHeight(root2);
    if (initialblackheight1 > initialblackheight2) {
        c = maxValueNode(root1);
        temp = c->data;
        deleteValue(c->data);
        root1 = root;
    }
    else if (initialblackheight2 > initialblackheight1) {
        c = minValueNode(root2);
        temp = c->data;
        rbTree2.deleteValue(c->data);
        root2 = rbTree2.root;
    }
    else {
        c = minValueNode(root2);
        temp = c->data;
        rbTree2.deleteValue(c->data);
        root2 = rbTree2.root;
        if (initialblackheight1 != getBlackHeight(root2)) {
            rbTree2.insertValue(c->data);
            root2 = rbTree2.root;
            c = maxValueNode(root1);
            temp = c->data;
            deleteValue(c->data);
            root1 = root;
        }
    }
    setColor(c,RED);
    int finalblackheight1 = getBlackHeight(root1);
    int finalblackheight2 = getBlackHeight(root2);
    if (finalblackheight1 == finalblackheight2) {
        c->left = root1;
        root1->parent = c;
        c->right = root2;
        root2->parent = c;
        setColor(c,BLACK);
        c->data = temp;
        root = c;
    }
    else if (finalblackheight2 > finalblackheight1) {
        Node<T> *ptr = root2;
        while (finalblackheight1 != getBlackHeight(ptr)) {
            temp_ptr = ptr;
            ptr = ptr->left;
        }
        Node<T> *ptr_parent;
        if (ptr == nullptr)
            ptr_parent = temp_ptr;
        else
            ptr_parent = ptr->parent;
        c->left = root1;
        if (root1 != nullptr)
            root1->parent = c;
        c->right = ptr;
        if (ptr != nullptr)
            ptr->parent = c;
        ptr_parent->left = c;
        c->parent = ptr_parent;
        if (getColor(ptr_parent) == RED) {
            fixInsertRBTree(c);
        }
        else if (getColor(ptr) == RED){
            fixInsertRBTree(ptr);
        }
        c->data = temp;
        root = root2;
    }
    else {
        Node<T> *ptr = root1;
        while (finalblackheight2 != getBlackHeight(ptr)) {
            ptr = ptr->right;
        }
        Node<T> *ptr_parent = ptr->parent;
        c->right = root2;
        root2->parent = c;
        c->left = ptr;
        ptr->parent = c;
        ptr_parent->right = c;
        c->parent = ptr_parent;
        if (getColor(ptr_parent) == RED) {
            fixInsertRBTree(c);
        }
        else if (getColor(ptr) == RED) {
            fixInsertRBTree(ptr);
        }
        c->data = temp;
        root = root1;
    }
    return;
}

template <typename T>
int RBTree<T>::maxDepthUtil(Node<T> *node){
    if (node == NULL)
        return 0;
    else {
        int lDepth = maxDepthUtil(node->left);
        int rDepth = maxDepthUtil(node->right);
        if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}

template <typename T>
int RBTree<T>::maxDepth(){
    return maxDepthUtil(root);
}

#endif //RED_BLACK_TREE_RBTREE_H