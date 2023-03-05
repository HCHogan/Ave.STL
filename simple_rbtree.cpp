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
	int cnt;
	bool color;
};

bool isRed(Node*& n) {
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
	n->n = n->left->n + n->right->n + n->cnt;
	n = x;
}

void rotateRight(Node*& n) {
	printf("右旋喽\n");
	Node* x = n->left;
	n->left = x->right;
	x->right = n;
	x->color = n->color;
	n->color = RED;
	x->n = n->n;
	n->n = n->left->n + n->right->n + n->cnt;
	n = x;
}

void flipColors(Node*& n) {
	if(n) {
		n->left->color = BLACK;
		n->right->color = BLACK;
		n->color = RED;
	}
}

void insert(int x, Node*& h) {
	if(h == NULL) h = new Node{x, x, NULL, NULL, 1, 1, RED};
	if(x < h->key) insert(x, h->left);
	else if(x > h->key) insert(x, h->right);
	else h->cnt++;
	if(isRed(h->right) && !isRed(h->left)) rotateLeft(h);
	if(isRed(h->left) && isRed(h->left->left)) rotateRight(h);
	if(isRed(h->left) && isRed(h->right)) flipColors(h);
	h->n = h->left->n + h->right->n + h->cnt;
}

void balance(Node*& h) {
	if(isRed(h->right)) rotateLeft(h);
	if(isRed(h->right) && !isRed(h->left)) rotateLeft(h);
	if(isRed(h->left) && isRed(h->left->left)) rotateRight(h);
	if(isRed(h->left) && isRed(h->right)) flipColors(h);
	h->n = h->left->n + h->right->n + h->cnt;
}

void moveRedLeft(Node*& h) {	// 把右孩子吸上来扩充自己的容量
	flipColors(h);				// 目标 把左下孩子变红
	if(isRed(h->right->left)) {
		rotateRight(h->right);
		rotateLeft(h);
	}
}

void moveRedRight(Node*& h) {
	flipColors(h);
	if(!isRed(h->left->left))
		rotateRight(h);
}

Node* minnode(Node*& h) {
	if(h->left)
		return minnode(h->left);
	return h;
}

void delMin(Node*& h) {
	if(h->left == NULL) {
		h = NULL;
		return;
	}
	if(!isRed(h->left) && !isRed(h->left->left))
		moveRedLeft(h);			// 合并到一条上
	delMin(h->left);		// 继续搜左边的	
	balance(h);				// 向上提,保持平衡崩回去
}
// 其实就是吧除了最左边的所有节点全部合并到一条上，然后删除最左边的那个，重新崩回去

void del(Node*& h, const int& n) {
	if(n < h->key) {
		if(!isRed(h->left) && !isRed(h->left->left)) {		// 当前节点的左孩子 容量只有1
			moveRedLeft(h);									// 右边孩子吸上来扩充自己容量
		}
		del(h->left, n);
	} else {
		if(isRed(h->left))
			rotateRight(h);

		if(n == h->key && !isRed(h->right->left)) {
			moveRedRight(h);
		}
	
		if(n == h->key) {
			// if(h->cnt > 1) h->cnt--;
			h->key = minnode(h->right)->key;
			delMin(h->right);
			// 吧现在这个值变成最小的比他大的那个值,然后删除r->right,可以删除多余的那个最小的比他大的那个节点(二叉树性质)
		} else del(h->right, n);
	}
	balance(h);
}

Node root = {0, 0, NULL, NULL, 1, 1, BLACK};
Node* rootp = &root;

int main() {
	for(int i = 1; i <= 100; i++) {
		insert(i, rootp);
	}
}
