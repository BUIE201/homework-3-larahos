#include <iostream>
#include <vector>
#include <algorithm>
#include <vector>



using namespace std;

struct Node
{
	int i;
	Node* pLeft;
	Node* pRight;
	Node(int iIn) : i(iIn), pLeft(nullptr), pRight(nullptr) {}
};


void InsertToTree(Node*& pRoot, Node* pNew)
{
	if (!pRoot)
	{
		pRoot = pNew;

		return;
	}

	if (pNew->i <= pRoot->i)
		InsertToTree(pRoot->pLeft, pNew);
	else
		InsertToTree(pRoot->pRight, pNew);
}

void DeleteNodeFromTree(Node*& pRoot, int i)
{
	if (!pRoot)
		return;

	if (pRoot->i < i)
	{
		DeleteNodeFromTree(pRoot->pRight, i);
		return;
	}

	if (pRoot->i > i)
	{
		DeleteNodeFromTree(pRoot->pLeft, i);
		return;
	}

	Node* q = pRoot;
	if (!q->pRight)
		pRoot = q->pLeft;
	else if (!q->pLeft)
		pRoot = q->pRight;
	else
		DeleteNodeWithTwoChildren(q, q->pLeft);

	delete q;
}
void DeleteNodeWithTwoChildren(Node*& q, Node*& p)
{
	if (p->pRight)
	{
		DeleteNodeWithTwoChildren(q, p->pRight);
		return;
	}

	p->i = q->i;
	q = p;
	p = p->pLeft;
}



void PrintTree(Node* pRoot, int Level)
{
	if (!pRoot)
		return;

	PrintTree(pRoot->pRight, Level + 1);

	for (int i = 0; i < Level; i++)
		cout << "  ";
	cout << pRoot->i << endl;

	PrintTree(pRoot->pLeft, Level + 1);
}

void Insert(Node*& pRoot, Node* pNewNode)
{
	if (!pRoot)
		pRoot = pNewNode;
	else
	{
		if (pNewNode->i < pRoot->i)
			Insert(pRoot->pLeft, pNewNode);
		else
			Insert(pRoot->pRight, pNewNode);
	}
}

int ValueoftheMax(Node* root, vector<Node*>& nodes) {
	if (root == 0)
		return 0;
	int sum = root->i;
	nodes.push_back(root);
	
	if (root->pLeft || root->pRight != NULL) {
		int left = ValueoftheMax(root->pLeft,nodes);
		int right = ValueoftheMax(root->pRight,nodes);
		sum=std::max(left, right);
	}
	else {
		if (root->pLeft != NULL)
			ValueoftheMax(root->pLeft, nodes);
		if (root->pRight != NULL)
			ValueoftheMax(root->pRight, nodes);
	}
}

void PrintSumandBranch(Node* root) {

	vector<Node*> nodes;
	int MaxSum = ValueoftheMax(root, nodes);

	cout << "Branch with the largest sum is: ";

	for (vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		cout << " " << *it;

	cout << "-> SUM= " << MaxSum;


}

void main()
{

	int i;

	Node* pRoot = nullptr;
	while (true)
	{
		cin >> i;
		if (i == 99)
			break;

		Node* p = new Node(i);
		InsertToTree(pRoot, p);
	}

	PrintTree(pRoot, 1);

	PrintSumandBranch(pRoot);
}