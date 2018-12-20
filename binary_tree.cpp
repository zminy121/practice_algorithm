#include <stdio.h>
#include <vector>
#include <iterator>
#include <string>
#include <stack>
#include <queue>

using namespace std;

struct TreeNode{
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
	TreeNode(int x):val(x), left(NULL), right(NULL){
	
	}
};

/*10. 按行从做到右打印二叉树*/
class Solution10{
public:
	vector<vector<int>> PrintOnRow(TreeNode* pRoot)
	{
		vector<vector<int>> result;
		if(pRoot == NULL){
			return result;
		}

		queue<TreeNode*> que[2];
		que[0].push(pRoot);

		while(!que[0].empty() || !que[1].empty()){
			vector<int> val[2];

			while(!que[0].empty()){
				val[0].push_back(que[0].front()->val);
				
				if(que[0].front()->left != NULL){
					que[1].push(que[0].front()->left);
				}

				if(que[0].front()->right != NULL){
					que[1].push(que[0].front()->right);
				}

				que[0].pop();
			}

			if(!val[0].empty()){
				result.push_back(val[0]);
			}

			while(!que[1].empty()){
				val[1].push_back(que[1].front()->val);

				if(que[1].front()->left != NULL){
					que[0].push(que[1].front()->left);
				}

				if(que[1].front()->right != NULL){
					que[0].push(que[0].front()->right);
				}

				que[1].pop();
			}

			if(!val[1].empty()){
				result.push_back(val[1]);
			}
		}
		return result;
	}
};


/*11. 按“之”字顺序打印二叉树*/
class Solution11{
public:
	vector<vector<int>> Print(TreeNode* pRoot)
	{
		vector<vector<int>> result;
		if(pRoot == NULL){
			return result;
		}

		stack<TreeNode*> s[2];
		s[0].push(pRoot);
		while(!s[0].empty() || !s[0].empty()){
			vector<int> v[2];
			while(!s[0].empty()){
				v[0].push_back(s[0].top()->val);
				if(s[0].top()->left != NULL){
					s[1].push(s[0].top()->left);
				}

				if(s[0].top()->right != NULL){
					s[1].push(s[0].top()->right);
				}
				s[0].pop();
			}
			if(!v[0].empty()){
				result.push_back(v[0]);
			}

			while(!s[1].empty()){
				v[1].push_back(s[1].top()->val);

				if(s[1].top()->right != NULL){
					s[0].push(s[1].top()->right);
				}

				if(s[1].top()->left != NULL){
					s[1].push(s[1].top()->left);
				}
				s[1].pop();
			}

			if(!v[1].empty()){
				result.push_back(v[1]);
			}
		}
		return result;
	}
};

/*12. 输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果(数组任意两个元素不相同)*/
class Solution12{
public:
	bool VerifySequenceOfBST(vector<int> sequence)
	{
		return BST(sequence, 0, sequence.size()-1);
	}

private:
	bool BST(vector<int> seq, int begin, int end)
	{
		if(seq.empty() || begin > end){
			return false;
		}

		// 后序遍历，最后一个节点是根节点
		int root = seq[end];

		// 二叉搜索树左子树节点小于根节点
		int i = begin;
		for(;i<end; ++i){
			if(seq[i] > root){
				break;
			}
		}

		// 二叉搜索树右子树节点大于根节点
		for(int j = i; j<end; ++j){
			if(seq[j] < root){
				return false;
			}
		}
		// 递归查验左子树是否是二叉搜索树
		bool left = true;
		left = BST(seq, begin, i-1);

		// 递归查验右子树是否是二叉搜索树
		bool right = true;
		right = BST(seq, i, end);

		return left && right;
	}
};

/*13. 输入一个二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。
 *要求不能创建任何新的结点，只能调整书中结点指针的指向*/

class Solution13{
public:
	TreeNode* BSTConvert2DulList(TreeNode* pRoot)
	{
		TreeNode* pLastNodeInList = NULL;

		ConvertNode(pRoot, &pLastNodeInList);

		TreeNode* pHead = pLastNodeInInit;

		while(pHead != NULL && pHead->left != NULL){
			pHead = pHead->left;
		}
	}

private:
	void ConvertNode(TreeNode* pNode, TreeNode** pLastNodeInList)
	{
		if(pNode == NULL){
			return;
		}

		TreeNode* pCurNode = pNode;

		// 递归遍历左子树
		if(pCurNode->left != NULL){
			ConvertNode(pCurNode->left, pLastNodeInList);
		}

		// 左指针指向上次循环后左后一个结点
		pCurNode->left = (*pLastNodeInList);

		//右指针指向当前结点
		if((*pLastNodeInList) != NULL){
			(*pLastNodeInList)->right = pCurNode;
		}

		// 更新双向链表中最后一个结点的位置
		(*pLastNodeInList) = pCurNode;


		// 递归遍历右子树
		if(pCurNode->right != NULL){
			ConvertNode(pCurNode->right, pLastNodeInList);
		}
	}

};


/*14. ����һ���������������ҳ����е�K��Ľڵ�*/
class Solution14{
public:
	TreeNode* KthNode(TreeNode * pRoot, int k)
	{
		if(pRoot == NULL || k == 0){
			return NULL;
		}
		KthNodeCore(pRoot, &k);
	}
private:
	TreeNode* KthNodeCore(TreeNode* pRoot, int* k)
	{
		TreeNode target = NULL;
		// �ȱ�����ڵ�
		if(pRoot->left != NULL){
			target = KthNodeCore(pRoot->left, k);
		}

		if(target == NULL){
			if(k == 1){
				target = pRoot;
			}
			(*k)--;
		}

		if(pRoot->right != NULL && target == NULL){
			target = KthNodeCore(pRoot->right, k);
		}
		return target;
	}
};
