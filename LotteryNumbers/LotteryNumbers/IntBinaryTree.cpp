void IntBinaryTree::insertNode(int num)
{
	TreeNode *newNode = nullptr;		// Pointer to a new node

	// Create a new node and store num in it
	newNode = new TreeNode;
	newNode->value = num;
	newNode->left = newNode->right = nullptr;

	// Insert new node
	insert (root, newNode)
}