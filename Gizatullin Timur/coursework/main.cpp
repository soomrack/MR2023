#include <vector>
#include <iostream>
#include <memory>
#include <functional>

using namespace std;

struct BinaryTreeNode
{
    shared_ptr<BinaryTreeNode> left, right;
    int key;
};

class BinaryTree
{
public:
    void insert(int key);
    void remove(int key);
    bool search(int key) const;
    typedef function<void(int key)> Visitor;
    void visit(const Visitor& visitor) const;

private:
    void insert_recursive(const shared_ptr<BinaryTreeNode>& cur_node, const shared_ptr<BinaryTreeNode>& node_to_insert);
    void visit_recursive(const shared_ptr<BinaryTreeNode>& cur_node, const Visitor& visitor) const;
    shared_ptr<BinaryTreeNode> root;
    shared_ptr<BinaryTreeNode> remove_recursive(shared_ptr<BinaryTreeNode> cur_node, int key);
    shared_ptr<BinaryTreeNode> find_min(shared_ptr<BinaryTreeNode> cur_node) const;
    bool search_recursive(const shared_ptr<BinaryTreeNode>& cur_node, int key) const;
};

void BinaryTree::insert(int key)
{
    auto node_to_insert = make_shared<BinaryTreeNode>();// new node
    node_to_insert->key = key;

    if (root == nullptr)
    {
        root = node_to_insert;
    }
    else
    {
        insert_recursive(root, node_to_insert);
    }
}

void BinaryTree::insert_recursive(const shared_ptr<BinaryTreeNode>& cur_node, const shared_ptr<BinaryTreeNode>& node_to_insert)
{
    if (node_to_insert->key < cur_node->key)
    {
        if (cur_node->left == nullptr)
        {
            cur_node->left = node_to_insert;
        }
        else
        {
            insert_recursive(cur_node->left, node_to_insert);
        }
    }
    else
    {
        if (cur_node->right == nullptr)
        {
            cur_node->right = node_to_insert;
        }
        else
        {
            insert_recursive(cur_node->right, node_to_insert);
        }
    }
}

void BinaryTree::visit(const Visitor& visitor) const
{
    if (root != nullptr)
    {
        visit_recursive(root, visitor);
    }
}

void BinaryTree::visit_recursive(const shared_ptr<BinaryTreeNode>& cur_node, const Visitor& visitor) const
{
    if (cur_node->left != nullptr)
    {
        visit_recursive(cur_node->left, visitor);
    }

    visitor(cur_node->key);

    if (cur_node->right != nullptr)
    {
        visit_recursive(cur_node->right, visitor);
    }
}

void BinaryTree::remove(int key)
{
    root = remove_recursive(root, key);
}

shared_ptr<BinaryTreeNode> BinaryTree::remove_recursive(shared_ptr<BinaryTreeNode> cur_node, int key)
{
    if (cur_node == nullptr)
    {
        return cur_node;
    }

    if (key < cur_node->key)
    {
        cur_node->left = remove_recursive(cur_node->left, key);
    }
    else if (key > cur_node->key)
    {
        cur_node->right = remove_recursive(cur_node->right, key);
    }
    else
    {
        //1 or more children
        if (cur_node->left == nullptr)
        {
            return cur_node->right;
        }
        else if (cur_node->right == nullptr)
        {
            return cur_node->left;
        }
        //with 2 children
        shared_ptr<BinaryTreeNode> min_node = find_min(cur_node->right);//in the right subtree
        cur_node->key = min_node->key;
        cur_node->right = remove_recursive(cur_node->right, min_node->key);
    }

    return cur_node;
}

shared_ptr<BinaryTreeNode> BinaryTree::find_min(shared_ptr<BinaryTreeNode> cur_node) const
{
    while (cur_node->left != nullptr)
    {
        cur_node = cur_node->left;
    }
    return cur_node;
}

bool BinaryTree::search(int key) const
{
    return search_recursive(root, key); 
}

bool BinaryTree::search_recursive(const shared_ptr<BinaryTreeNode>& cur_node, int key) const
{
    if (cur_node == nullptr)
    {
        return false;
    }

    if (key < cur_node->key)
    {
        return search_recursive(cur_node->left, key); 
    }
    else if (key > cur_node->key)
    {
        return search_recursive(cur_node->right, key); 
    }
    else
    {
        return true;
    }
}


int main() {
    BinaryTree tree;
    vector<int> data_to_sort = {0, -1, 2, -3, 4, -5, 6, -7, 8, -9};

    for (int value : data_to_sort) {
        tree.insert(value);
    }

    tree.visit([](int visited_key) {
        cout << visited_key << " ";
    });

    cout << endl;

    tree.remove(-3);
    tree.remove(4);

    tree.visit([](int visited_key) {
        cout << visited_key << " ";
    });
    cout << endl;
    
    int key_to_search = -5;
    if (tree.search(key_to_search)) {
        cout << "Key " << key_to_search << " found in the tree." << endl;
    } else {
        cout << "Key " << key_to_search << " not found in the tree." << endl;
    }

    return 0;
}