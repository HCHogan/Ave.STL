#include <iostream>
using namespace std;

// 理解：2-3树,红棍连接同一个节点的几个元素
//		 头顶的棍是啥颜色节点就是啥颜色
//		 根节点为黑色
//
// 1. 红都是左
// 2. 不存在连续两个红
// 3. 黑色平衡
// 4. 叶节点空指针看做黑节点

#define RED 1
#define BLACK 0

struct Node {
	int key, value;
	Node* left;
	Node* right;
	int n;			// 树中节点数(包括节点自身)
	bool color;
};

bool isRed(Node* n) {
	if(n == NULL)
		return false;
	return n->color;
}

void rotateLeft(Node*& n) {
	printf("左旋喽\n");
	Node* x = n->right;
	n->right = x->left;
	x->left = n;
	x->color = n->color;
	n->color = RED;
	x->n = n->n;
	n->n = n->left->n + n->right->n + 1;	
}

void rotateRight(Node*& n) {
	printf("右旋喽\n");
	Node* x = n->left;
	n->left = x->right;
	x->right = n;
	x.
}


