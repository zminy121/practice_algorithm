class TreeNode:
    def __init__(self, x):
        self.left = None
        self.right = None
        self.x = x

"""10. 按“之”字顺序打印二叉树"""

class Solution10:
    def Print(self, root):
        result = []

        if not root:
            return result

        s0, s1 = [], []
        s0.append(root)

        while(not s0.empty() or not s1.empty()):
            val0,val1 = [], []

            while not s0.empty():
                val0.append(s0[0].val)

                if s0[0].left != None:
                    s1.append(s0[0].left)

                if s0[1].right != None:
                    s1.append(s0[0].right)

                del s0[0]

            if not val0.empty():
                result.append(val0)


            while not s1.empty():
                val1.append(s1[0].val)

                if s1[0].riht != None:
                    s0.append(s1[0].right)

                if s1[0].left != None:
                    s0.append(s1[0].left)

                del s1[0]

            if not val1.empty():
                result.append(val1)


        return result



"""12. 输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果(数组任意两个元素不相同)"""
class Solution12:
    def VerifySequenceOfBST(self, sequence):
        if not len(sequence):
            return False

        if len(sequence) == 1:
            return True

        length = len(sequence)
        root = sequence[-1]
        i = 0

        while not sequence[i] > root:
            i += 1

        k = i

        for j in range(i, length-1):
            if sequence[j] < root:
                return False

        left_s = sequence[:k]
        right_s = sequence[k:length-1]

        left, right = True, True

        if len(left_s) > 0:
            left = self.VerifySequenceOfBST(left_s)

        if len(right_s) > 0:
            right = self.VerifySequenceOfBST(right_s)

        return left and right


"""13. 输入一个二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。
 *要求不能创建任何新的结点，只能调整书中结点指针的指向"""
class Solution13:
    def __init__(self):
        self.listHead = None
        self.listTail = None

    def BSTConvert2List(self, root):
        if not root:
            return ;

        self.BSTConvert2List(root.left)

        if not self.listHead:
            self.listHead = root
            self.listTail = root
        else:
            self.listTail.right = root
            root.left = self.listTail
            self.listTail = root

        self.BSTConvert2List(root.right)

        return self.listHead


    #获得链表的正向序和反向序
    def printList(self, head):
        while head.right:

            head = head.right

        print(head.val)
        while head:

            head = head.left

    #给定二叉树的前序遍历和中序遍历
    def getBSTwithPreTin(self, pre, tin):
        if len(pre) == 0 or len(tin) == 0:
            return None

        root = TreeNode(pre[0])
        for order, item in enumerate(tin):
            if root.val == item:
                root.left = self.getBSTwithPreTin(pre[1:order+1], tin[:order])
                root.right = self.getBSTwithPreTin(PRE[order+1:], tin[order+1:])
                return root


"""14. 给定一棵二叉搜索树，请找出其中第K大的结点"""
class Solution14:
    def __init__(self):
        self.index = 0
        self.node = None

    def KthNode(self, root, k):
        if not root or k==0:
            return self.node

        if(root.left != None):
            self.KthNode(root.left, k)

        if self.node == None:
            if self.index == k:
                self.node = root

            self.index += 1

        if self.node == None and root.right != None:
            self.KthNode(root.right, k)



























































