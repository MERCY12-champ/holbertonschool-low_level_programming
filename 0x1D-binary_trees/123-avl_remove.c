#include "binary_trees.h"

/**
 * balance_left - balances left side
 * @node: pointer to temp node
 * Return: root of tree
 */
avl_t *balance_left(avl_t *node)
{
	avl_t *z, *x, *y, *ret;

	z = node;
	y = z->left;
	if (!y)
		return (NULL);
	x = binary_tree_balance(y) < 0 ? y->right : y->left;
	if (!x)
		return (NULL);
	if (x == y->left)
	{
		ret = binary_tree_rotate_right(z);
		return (ret);
	}
	binary_tree_rotate_left(y);
	ret = binary_tree_rotate_right(z);
	return (ret);
}

/**
 * rebalance - rebalance AVL tree
 * @node: pointer to node to rebalance
 * @tree: double pointer to root of tree
 * Return: pointer to input node
 */
avl_t *rebalance(avl_t *node, avl_t **tree)
{
	avl_t *tmp, *root, *z, *x, *y, *ret;
	int bal;

	tmp = node;
	while (tmp)
	{
		bal = binary_tree_balance(tmp);
		if (bal > 1)
		{
			root = balance_left(tmp);
			if (root)
				*tree = root;
		}
		else if (bal < -1)
		{
			z = tmp;
			y = z->right;
			if (!y)
				return (NULL);
			x = binary_tree_balance(y) < 0 ? y->right : y->left;
			if (!x)
				return (NULL);
			if (x == y->right)
			{
				ret = binary_tree_rotate_left(z);
				return (ret);
			}
			binary_tree_rotate_right(y);
			root = binary_tree_rotate_left(z);
			if (root)
				*tree = root;
		}
		tmp = tmp->parent;
	}
	return (node);
}

/**
 * bst_search - searches for a value in a Binary Search Tree
 * @tree: pointer to root of tree
 * @value: input value
 * Return: pointer to the node containing a value equals to value
 */
bst_t *bst_search(const bst_t *tree, int value)
{
	if (!tree)
		return (NULL);
	while (tree)
	{
		if (value == tree->n)
			return ((bst_t *)tree);
		tree = value < tree->n ? tree->left
			: tree->right;
	}
	return ((bst_t *)tree);
}

/**
 * swap - swaps two nodes in binary tree
 * @node: first node
 * @new: second node
 * Return: pointer to root
 */
bst_t *swap(bst_t *node, bst_t *new)
{
	bst_t *temp = NULL, *parent = NULL;
	_Bool left_child = false;

	if (node->parent)
	{
		parent = node->parent;
		left_child = node->parent->left == node;
	}
	if (new->parent && new->parent != node)
		new->parent->left = NULL;
	new->parent = node->parent;
	if (node->parent)
	{
		if (left_child)
			node->parent->left = new;
		else
			node->parent->right = new;
	}
	if (node->left != new)
	{
		new->left = node->left;
		node->left->parent = new;
	}
	if (node->right && node->right != new)
	{
		new->right = node->right;
		node->right->parent = new;
	}
	temp = new;
	while (temp->parent)
		temp = temp->parent;
	if (parent)
		rebalance(parent, &temp);
	free(node);
	return (temp);
}

/**
 * avl_remove - removes a node from an AVL tree
 * @root: pointer to root of tree
 * @value: value to be removed
 * Return: pointer to the new root node of the tree after removing the desired
 * value, and after rebalancing
 */
avl_t *avl_remove(avl_t *root, int value)
{
	avl_t *node, *temp;
	_Bool left_child = false;

	if (!root)
		return (NULL);
	node = bst_search(root, value);
	if (!node)
		return (NULL);
	if (node->parent)
		left_child = node->parent->left == node;
	if (!node->right && !node->left)
	{
		if (!node->parent)
		{
			free(node);
			return (NULL);
		}
		if (left_child)
			node->parent->left = NULL;
		else
			node->parent->right = NULL;
		root = temp = node->parent;
		while (root->parent)
			root = root->parent;
		free(node);
		rebalance(temp, &root);
		return (root);

	}
	if (!node->right)
		return (swap(node, node->left));
	temp = node->right;
	while (temp->left)
		temp = temp->left;
	return (swap(node, temp));
}