 // Linked Binary Tree
#include<iostream>
#include <bits/stdc++.h>
using namespace std;


#define SIZE 50 // Defining Q size

// declaration of structure Node
class Node
{
	public:
	char charVal;
	Node *r,*l;
};

// declaration of Q Node
class que
{
	public:
	int f, r;
	int length;
	Node**CharArray;
};


Node* CreateNewNode(char charVal) //making of new node of binary tree
{
	Node* flag = new Node();
	flag->charVal = charVal;
	flag->l = flag->r = NULL;
	return flag;
}


que* createQueue(int length) //making of new Q of binary tree traversal
{
	que* Q = new que();

	Q->f = Q->r = -1;

	Q->length = length;

	Q->CharArray = new Node*[Q->length * sizeof( Node* )];

	for (int i = 0; i < length; ++i)
		Q->CharArray[i] = NULL;

	return Q;
}

int Checkempty(que* Q)//checker function of empty for queue
{
	return Q->f == -1;
}

int CheckFull(que* Q)  //checker function of full for queue
{ 
	return Q->r == Q->length - 1; 
}

int Hashingofelement(que* Q) //hashing function 
{ 
	return Q->f == Q->r;
	 }

void enqueuingFunc(Node rootNode, que Q)
{
	if (CheckFull(Q))
		{
			return;
		}

	Q->CharArray[++Q->r] = rootNode;

	if (Checkempty(Q))
		{
			++Q->f;
		}
}

Node* dequeuingFunc(que* Q)
{
	if (Checkempty(Q))
		{
			return NULL;
		}

	Node* flag = Q->CharArray[Q->f];

	if (Hashingofelement(Q))
		{
			Q->f = Q->r = -1;
			}
	else
		{
			++Q->f;
		}

	return flag;
}

Node* getFront(que* Q)
{ return Q->CharArray[Q->f]; }


int CheckBothChild(Node* flag) //checking if tree has both child or not
{
	{
		return flag && flag->l && flag->r;
	}
}


void InsertionNode(Node *rootNode, char charVal, que Q) //insertion of node function
{
	Node *flag = CreateNewNode(charVal); //making a new temporary node


	if (!*rootNode) // if the node is empty then make it the root node
		{
			*rootNode = flag;
		}

	else
	{
		Node* f = getFront(Q);

		if (!f->l)
			{
				f->l = flag;
				}

		else if (!f->r)
			{
				f->r = flag;
				}

		
		if (CheckBothChild(f))
			{
				dequeuingFunc(Q);
			}
	}

	enqueuingFunc(flag, Q);
}


void TraverseOrderLevel(Node* rootNode) //traversing the linked binary tree in level order
{
	que* Q = createQueue(SIZE);

	enqueuingFunc(rootNode, Q);

	while (!Checkempty(Q))
	{
		Node* flag = dequeuingFunc(Q);

		cout<<flag->charVal<<" ";

		if (flag->l)
			{
				enqueuingFunc(flag->l, Q);
			}

		if (flag->r)
			{
				enqueuingFunc(flag->r, Q);
			}
	}
}

int main()
{
	Node* rootNode = NULL;
	que* Q = createQueue(SIZE);
	
//insertion of data new node into binary tree
	    InsertionNode(&rootNode, 'R', Q);
		InsertionNode(&rootNode, 'A', Q);
		InsertionNode(&rootNode, 'B', Q);
		InsertionNode(&rootNode, 'C', Q);
		InsertionNode(&rootNode, 'D', Q);
		InsertionNode(&rootNode, 'E', Q);
		InsertionNode(&rootNode, 'F', Q);

	//traversing the linked binary tree
	TraverseOrderLevel(rootNode);

	return 0;
}
