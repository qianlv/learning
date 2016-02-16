/*
 * =====================================================================================
 *
 *       Filename:  13_28.h
 *
 *    Description:  13.28
 *
 *        Version:  1.0
 *        Created:  2016年01月11日 15时17分16秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef M_13_28_H_
#define M_13_28_H_

#include <string>
using std::string;

class TreeNode
{
public:
    TreeNode();
    TreeNode(const TreeNode &rhs);
    TreeNode& operator= (const TreeNode &rhs);
    ~TreeNode();
private:
    string   value;
    int      *count;
    TreeNode *left;
    TreeNode *right;
};

class BinStrTree
{
public:
    BinStrTree();
    BinStrTree(const BinStrTree &rhs);
    BinStrTree& operator= (const BinStrTree &rhs);
    ~BinStrTree();
private:
    TreeNode *root;
};
#endif // M_13_28_H_
