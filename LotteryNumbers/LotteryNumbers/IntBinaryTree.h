//Specification file for the IntBinaryTree class
#ifndef INTBINARYTREE_H
#define INTBINARYTREE_H

class IntBinaryTree
{
public:
	struct TreeNode
	{
		int value;			// The value in the node
		TreeNode *left;		// Pointer to left child node
		TreeNode *right;	// Pointer to right child node
	};

	TreeNode *root;			// Pointer to the root node

	// Private member functions
	void insert(TreeNode *&, TreeNode *&);
	void destroySubTree(TreeNode *);
	void deleteNode(int, TreeNode *&);
	void makeDeletion(TreeNode *&);
	void displayInOrder(TreeNode *)	const;
	void displayPreOrder(TreeNode *) const;
	void displayPostOrder(TreeNode *) const;

	// Constructor
	IntBinaryTree()
	{
		root = nullptr;
	}

	//Binary tree operations
	void insertNode(int);
	bool searchNode(int);
	void remove(int);
	int FindHeight(TreeNode* root);

	void displayInOrder() const
	{
		displayInOrder(root);
	}

	void displayPreOrder() const
	{
		displayPreOrder(root);
	}

	void displayPostOrder() const
	{
		displayPostOrder(root);
	}

	int FindHeight()
	{
		FindHeight(root);
	}

};
#endif
