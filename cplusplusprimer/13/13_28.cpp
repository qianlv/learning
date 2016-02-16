/*
 * =====================================================================================
 *
 *       Filename:  13_28.cpp
 *
 *    Description:  13.28
 *
 *        Version:  1.0
 *        Created:  2016年01月11日 15时26分52秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "13_28.h"

TreeNode::TreeNode() :
    value(string()), count(new int(1)), left(nullptr), right(nullptr)
{
}

TreeNode::TreeNode(const TreeNode &rhs) :
    value(rhs.value), count(rhs.count), left(rhs.left), right(rhs.right)
{
    ++*count;
}

TreeNode& TreeNode::operator= (const TreeNode &rhs)
{
    ++*rhs.count;
    if (--*count == 0)
    {
        delete count;
        if (left)
            delete left;
        if (right)
            delete right;
    }
    value = rhs.value;
    count = rhs.count;
    left = rhs.left;
    right = rhs.right;
    return *this;
}

TreeNode::~TreeNode()
{
    if (--*count == 0)
    {
        delete count;
        count = nullptr;
        if (left)
        {
            delete left;
            left = nullptr;
        }
        if (right)
        {
            delete right;
            right = nullptr;
        }
    }
}

BinStrTree::BinStrTree() : root(nullptr)
{
}

BinStrTree::BinStrTree(const BinStrTree &rhs) :
    root(new TreeNode(*rhs.root))
{
}

BinStrTree& BinStrTree::operator= (const BinStrTree &rhs)
{
    TreeNode *newroot = new TreeNode(*rhs.root);
    delete root;
    root = newroot;
    return *this;
}

int main()
{
    return 0;
}
