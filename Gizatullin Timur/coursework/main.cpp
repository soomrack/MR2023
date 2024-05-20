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
    typedef function<void(int key)> Visitor;
    void visit(const Visitor& visitor) const;

private:
    void insert_recursive(const shared_ptr<BinaryTreeNode>& cur_node, const shared_ptr<BinaryTreeNode>& node_to_insert);
    void visit_recursive(const shared_ptr<BinaryTreeNode>& cur_node, const Visitor& visitor) const;
    shared_ptr<BinaryTreeNode> root;
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

    return 0;
}