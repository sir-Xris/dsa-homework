class bintree:
    def __init__(self):
        self.data = ''
        self.lchild = None
        self.rchild = None

    def preorder(self):
        t = '' + self.data
        if self.lchild: t += self.lchild.preorder()
        if self.rchild: t += self.rchild.preorder()
        return t

    def inorder(self):
        t = ''
        if self.lchild: t += self.lchild.inorder()
        t += self.data
        if self.rchild: t += self.rchild.inorder()
        return t

    def postorder(self):
        t = ''
        if self.lchild: t += self.lchild.postorder()
        if self.rchild: t += self.rchild.postorder()
        return t + self.data


def pre_in_dfs(preorder, inorder):
    if len(preorder) != len(inorder):
        exit('Impossible to build a tree.')
    if not preorder and not inorder: return None
    if inorder.count(preorder[0]) != 1:
        exit('Impossible to build a tree.')
    v = inorder.find(preorder[0])
    tree = bintree()
    tree.data = preorder[0]
    tree.lchild = pre_in_dfs(preorder[1:v + 1], inorder[:v])
    tree.rchild = pre_in_dfs(preorder[v + 1:], inorder[v + 1:])
    return tree

if __name__ == '__main__':
    a1, a2 = input('Pre-order Traversal: '), input('In-order Traversal:  ')
    print('#' * 80)
    root = pre_in_dfs(a1, a2)
    print('Pre-order Traversal: ', root.preorder())
    print('In-order Traversal:  ', root.inorder())
    print('Post-order Traversal:', root.postorder())

