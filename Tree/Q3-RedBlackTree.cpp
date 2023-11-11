#include <iostream>
using namespace std;

#define R 1
#define B 0

struct Node
{
	Node(int data, Node *parentt, int colorr)
	{
		this->data = data;
		this->parent = parentt;
		this->color = colorr;
		left = NULL;
		right = NULL;
	}

	int data;
	int color;
	Node *left, *right, *parent;

};

void BST_insert(Node *&root, Node *&node)
{
	if (root->data < node->data)
	{
		if (root->right == NULL)
		{
			node->parent = root;
			root->right = node;
			return;
		}
		BST_insert(root->right, node);
	}
	else
	{
		if (root->left == NULL)
		{
			node->parent = root;
			root->left = node;
			return;
		}
		BST_insert(root->left, node);
	}
}

void right_rotate(Node *&root, Node *&node)
{
	Node* left_child = node->left;
	node->left = left_child->right;
	if (node->left != NULL)
		node->left->parent = node;
	left_child->parent = node->parent;
	if (node->parent == NULL)
		root = left_child;
	else if (node == node->parent->left)
		node->parent->left = left_child;
	else
		node->parent->right = left_child;
	left_child->right = node;
	node->parent = left_child;
}

void left_rotate(Node *&root, Node *& node)
{
	Node* right_child = node->right;
	node->right = right_child->left;
	if (node->right != NULL)
		node->right->parent = node;
	right_child->parent = node->parent;
	if (node->parent == NULL)
		root = right_child;
	else if (node == node->parent->left)
		node->parent->left = right_child;
	else
		node->parent->right = right_child;
	right_child->left = node;
	node->parent = right_child;
}

Node* fix_tree(Node *&root, Node *&node)
{
	Node *p, *gp, *uncle;
	while(node->color != B && node != root)
	{
		p = node->parent;
		gp = p->parent;
		if (p->color == B)
			break;
		if (p == gp->left)
		{
			uncle = gp->right;
			if (uncle != NULL && uncle->color == R)
			{
				gp->color = R;
				p->color = B;
				uncle->color = B;
				node = gp;
			}
			else
			{
				if (node == p->right)
				{
					left_rotate(root, p);
					node = p;
					p = node->parent;
				}
				right_rotate(root, gp);
				if (p->color == R)
				{
					p->color = B;
					gp->color = R;
				}
				else
				{
					p->color = R;
					gp->color = B;
				}
				node = p;
			}
		}
		else
		{
			uncle = gp->left;
			if (uncle != NULL && uncle->color == R)
			{
				gp->color = R;
				p->color = B;
				uncle->color = B;
				node = gp;
			}
			else
			{
				if (node == p->left)
				{
					right_rotate(root, p);
					node = p;
					p = node->parent;
				}
				left_rotate(root, gp);
				if (p->color == R)
				{
					p->color = B;
					gp->color = R;
				}
				else
				{
					p->color = R;
					gp->color = B;
				}
				node = p;
			}
		}
	}
	root->color = B;
	return root;
}

Node* insert(Node *&root, int data)
{
	Node *node = new Node(data, NULL, R);
	BST_insert(root, node);
	return fix_tree(root, node);
}

Node *search_tree(Node *root, int key)
{
	if (root == NULL || root->data == key)
		return root;
	if (root->data > key)
		return search_tree(root->left, key);
	return search_tree(root->right, key);
}

int main()
{
	int q, n, t, flag = 0;
	Node *root;
	cin >> q;
	for (int i = 0; i < q; i++)
	{
		cin >> t >> n;
		if (t == 1)
		{
			if (flag == 0)
			{
				root = new Node(n, NULL, B);
				flag ++;
			}
			root = insert(root, n);
		}
		else
		{
			if (search_tree(root, n) == NULL)
				cout << "NO" << endl;
			else
				cout << "YES" << endl;
		}
	}
}