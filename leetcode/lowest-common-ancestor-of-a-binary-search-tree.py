# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

""" BST定义是左子树的值小于根节点的值,右子树的值大于根节点的值,
    且没有键值相等的节点.
    思路: p, q的val都比root的val大, 则公共祖先在右子树上,
          p, q的val都比root的val小, 则公共祖先在左子树上,
          递归求解, 知道p, q其中的val等于root的val,
          则此节点就是公共祖先.
"""


class Solution:
    # @param {TreeNode} root
    # @param {TreeNode} p
    # @param {TreeNode} q
    # @return {TreeNode}
    def lowestCommonAncestor(self, root, p, q):
        if root.val > p.val and root.val > q.val:
            return self.lowestCommonAncestor(root.left, p, q)
        elif root.val < p.val and root.val < q.val:
            return self.lowestCommonAncestor(root.right, p, q)
        return root
