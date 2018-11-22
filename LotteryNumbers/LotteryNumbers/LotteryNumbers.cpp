/*****************************************************************************************************************************************************
******************************************************************************************************************************************************
**  In this quest you are going to create a BST with 70 random numbers using a uniform int distribution on the range of 1 to 70.					**
**  There may be duplicates, so left should be <= while right be strictly > .																		**
**  You will then calculate the depth of the tree.																									**
**  You then go a random number of lefts and/or rights 0 to Depth of tree number of times, topping if your reach a leaf node.						**
**  What you land on will be added to an array of size 6.																							**
**  That node will be removed from the tree to guarantee it will not be picked again.																**
**  Repeat steps 3 - 5 until you have filled the array with numbers.This is the winning lotto number!!!												**
**																																					**
**  By submitting a solution for this Quest I am acknowledging that all code submitted is my work and my ideas and not taken from any				**
**  other source except the instructor provided code unless otherwise noted by a comment in my code.I also acknowledge that if the					**
**  previous is not true, that I may be reported to the Dean for academic dishonesty.See the following policy :										**
**  http://ualr.edu/policy/home/student/academic-integrity-and-grievance/																			**
**																																					**
**  Bonus 50XP : guarantee no duplicates.																											**
**  Bonus 50XP : the 6th ball is the power ball and should be drawn from a set of 25 balls numbered 1 - 25!											**
**  Bonus 100XP : balance the tree after step 1 above.																								**
**																																					**
**	Random numbers in C++ :																															**
**																																					**
**  #include <random>																																**
**																																					**
**	  random_device seed;																															**
**																																					**
**  default_random_engine e(seed());																												**
**																																					**
**  uniform_int_distribution randomBall(1, 70);																										**	
**																																					**
**  node x.data = randomBall(e);																													**
**																																					**
**  uniform_int_distribution randomDepth(0, treeDepth)																								**
**																																					**
**  int numMoves = randomDepth(e);																													**
**																																					**
**  bernoulli_distribution leftOrRight(.5);																											**
**																																					**
**  bool left = leftOrRight(e);																														**
******************************************************************************************************************************************************
*****************************************************************************************************************************************************/


/*****************************************************************************
******************************************************************************
**	Heidi Clement															**
**	CPSC 2380 - Data Structures & Algorithms								**
**	Quest 3 - Lottery Numbers												**
**	November 25, 2018														**
**	Some code used is from the ZyBook, some from Mr. Orme, and some of my 	**
**	own as well as 'Starting Out With C++ From Control Structure Through	**
**	Objects' eighth edition by Tony Gaddis.									**
******************************************************************************
*****************************************************************************/

#include "IntBinaryTree.h"
#include <iostream>
#include <cstdlib>		// For rand and srand
#include <ctime>		// For time function
#include <random>		// For random

using namespace std;


/*************************************************************************************
**************************************************************************************
** This function creates a new node to hold it's value and passes it to the insert  ** 
** function																			**
**************************************************************************************
*************************************************************************************/
void IntBinaryTree::insertNode(int num)
{
	TreeNode *newNode = nullptr;		// Pointer to a new node

	// Create a new node and store num in it
	newNode = new TreeNode;
	newNode->value = num;
	newNode->left = newNode->right = nullptr;

	// Insert new node
	insert(root, newNode);
}

/*************************************************************************************
**************************************************************************************
** This function recursively accepts a pointer to a node.  It insersts the node to  **
** to the treeby the TreeNode ptr.													**
**************************************************************************************
*************************************************************************************/
void IntBinaryTree::insert(TreeNode *&nodePtr, TreeNode *&newNode)
{
	if (nodePtr == nullptr)
		nodePtr = newNode;						// Insert the node
	else if (newNode->value <= nodePtr->value)
		insert(nodePtr->left, newNode);			//Search left branch
	else
		insert(nodePtr->right, newNode);		//Search the right branch
}


/*************************************************************************************
**************************************************************************************
** This function randomizes the numbers 1 - 70 for the new nodes in the binary tree **
**************************************************************************************
*************************************************************************************/
int random()
{
	int number1;
	const int MIN_VALUE = 1;
	const int MAX_VALUE = 70;

	number1 = (rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE;		// Random number from 1 - 70

	return number1;
}

/*************************************************************************************
**************************************************************************************
**  Searches the tree for a value													**
**************************************************************************************
*************************************************************************************/

bool IntBinaryTree::searchNode(int num)
{
	TreeNode *nodePtr = root;

	while (nodePtr)
	{
		if (nodePtr->value == num)
			return true;
		else if (num < nodePtr->value)
			nodePtr = nodePtr->left;
		else
			nodePtr = nodePtr->right;
	}
	return false;
}

/*************************************************************************************
**************************************************************************************
** This function calls deleteNode to delete the node who matches the value          **
**************************************************************************************
*************************************************************************************/

void IntBinaryTree::remove(int num)
{
	deleteNode(num, root);
}

/*************************************************************************************
**************************************************************************************
** This function removesthe node whose value is the same as thas num				**
**************************************************************************************
*************************************************************************************/

void IntBinaryTree::deleteNode(int num, TreeNode *&nodePtr)
{
	if (num < nodePtr->value)
		deleteNode(num, nodePtr->left);
	else if (num > nodePtr->value)
		deleteNode(num, nodePtr->right);
	else
		makeDeletion(nodePtr);
}

/*****************************************************************************************************************
******************************************************************************************************************
** This function calculates the height of a binary search tree.  This code is modified  from					**
** https://www.includehelp.com/data-structure-tutorial/find-height-maximum-depth-of-a-binary-search-tree.aspx	**
******************************************************************************************************************
******************************************************************************************************************/

int IntBinaryTree::FindHeight(TreeNode* root)
{
	int max;
	if (root == NULL)
		return 0;
	else
	{
		int lb = FindHeight(root->left);
		int rb = FindHeight(root->right);
		if (lb > rb)
			max = lb;
		else
			max = rb;
			return max;
	}
}

/*************************************************************************************
**************************************************************************************
** This function takes the reference to a pointer to the node that is to be		    **
** The node is removed and the branches of the tree below the node are reattached.	**
**************************************************************************************
*************************************************************************************/

void IntBinaryTree::makeDeletion(TreeNode *&nodePtr)
{
	//Define a teporary pointer to use in reattaching the left subtree
	TreeNode *tempNodePtr = nullptr;

	if (nodePtr == nullptr)
		cout << "Cannot delete empty node.\n";
	else if (nodePtr->right == nullptr)
	{
		tempNodePtr = nodePtr;
		nodePtr = nodePtr->left;		//Reattach left child
		delete tempNodePtr;
	}
	else if (nodePtr->left == nullptr)
	{
		tempNodePtr = nodePtr;
		nodePtr = nodePtr->right;		//Reattach right child
		delete tempNodePtr->left;
	}

	// If there are two children
	else
	{
		// Move one node to the right
		tempNodePtr = nodePtr->right;

		// Go to the end left node
		while (tempNodePtr->left)
			tempNodePtr = tempNodePtr->left;

			// Reattach the left subtree
			tempNodePtr->left = nodePtr->left;
		tempNodePtr = nodePtr;

		//Reattach the right subtree
		nodePtr = nodePtr->right;
		delete tempNodePtr;
	}
}

class uniform_int_distribution
{
public:
	random_device seed;
	default_random_engine e(seed)
	int numMoves =randomDepth(e);
	bernoulli_distribution leftOrRight(.5);
	bool left = leftOrRight(e);
};

/*************************************************************************************
**************************************************************************************
** This function is the main function where everything happens					    **
**************************************************************************************
*************************************************************************************/

int main()
{
	IntBinaryTree tree;					// Create a tree class occurrance.  
	int randomNumber1;					// Int holder for randomizer.
	int count = 0;
	int max;

	time_t(seed);
	time(&seed);
	srand(seed);


	cout << "Inserting nodes.\n";

	while (count < 70)
	{
		randomNumber1 = random();
		tree.insertNode(randomNumber1);
		count = count++;
	}
	
	cout << "Done.\n";

	max = tree.FindHeight(tree.root);
	cout << "The max height of the tree is: "<< max + 1 << endl;
	cout << "The depth of the tree is: " << max  << endl;

	if (tree.searchNode(68))
	{
		cout << "68 was found in the tree. \n.";
		tree.remove(68);
		cout << "68 was removed. \n";
	}
	else
		cout << "68 was not found in the tree. \n";

	randomDepth(0, max)

	
	system("pause");
	return 0;
}