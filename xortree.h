#ifndef _XORTREE_H_
#define _XORTREE_H_

#include <stdint.h>
#include <stddef.h>

#define XORTREE_NUM_KIDS  3

typedef uint32_t xortree_key_t;

typedef struct xortree_node
{
	xortree_key_t key;
	void *data;
	struct xortree_node *kid[XORTREE_NUM_KIDS];
} xortree_node_t;


_Bool xortree_insert(xortree_node_t *root, xortree_node_t *newNode)
{
	xortree_node_t *node = root;

	xortree_key_t parent_new;
	xortree_key_t new_kid;
	int closeKid;
	xortree_key_t min_diff;

	while (node->key != newNode->key)
	{
		parent_new = node->key ^ newNode->key;
		min_diff = -1;

		for (int i = 0; i < XORTREE_NUM_KIDS; i++)
		{
			if (node->kid[i] != NULL)
			{
				new_kid = newNode->key ^ node->kid[i]->key;

				if (new_kid < min_diff)
				{
					closeKid = i;
					min_diff = new_kid;
				}
			}
			else
			{
				node->kid[i] = newNode;
				return (_Bool)1;
			}
		}
		
		node = node->kid[closeKid];
	}

	return (_Bool)0;
}

xortree_node_t *xortree_lookup(xortree_node_t *root, const xortree_key_t skey)
{
	xortree_node_t *node = root;
	xortree_node_t *next_node;
	xortree_key_t next_diff;
	xortree_key_t diff;

	while (node->key != skey)
	{
		next_node = NULL;

		for (int i = 0; i < XORTREE_NUM_KIDS; i++)
		{
			if (node->kid[i] != NULL)
			{
				diff = node->kid[i]->key ^ skey;
				
				if ( (next_node == NULL) || (diff < next_diff) )
				{
					next_node = node->kid[i];
					next_diff = diff;
				}
			}
		}
		node = next_node;

		if (node == NULL)
		{
			break;
		}
	}

	return node;
}

void xortree_createNode(xortree_node_t *node, xortree_key_t key, void *data)
{
	node->key = key;
	node->data = data;
	for (int i = 0; i < XORTREE_NUM_KIDS; i++)
	{
		node->kid[i] = NULL;
	}
}

#endif
