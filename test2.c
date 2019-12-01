#include "xortree.h"
#include <stdio.h>
#include <stdlib.h>

void dump(xortree_node_t *node, int level)
{
	printf("%X\n", node->key);

	for (int n = 0; n < XORTREE_NUM_KIDS; n++)
	{
		if (node->kid[n] != NULL) for (int i = 0; i < level; i++)
		{
			printf("  ");
		}
		if (node->kid[n] != NULL)
		{
			printf("%i:", n);
			dump(node->kid[n], level + 1);
		}
		else
		{
			//printf("-\n");
		}
	}
	if (level==0) printf("______________________________________________\n\n");
}


int main()
{
	uint32_t num;
  
  scanf("%u", &num);
  xortree_node_t *tree = malloc(sizeof(xortree_node_t) * num);
  if (NULL == tree)
  {
    printf("malloc tree fail");
    exit(1234);
  }
  
  for (uint32_t i = 0; i < num; i++)
  {   
    xortree_createNode(&tree[i], i, NULL);
    
    if (i > 0)
    {
      xortree_insert(&tree[0], &tree[i]);
    }
  }
  
  dump(&tree[0], 0);
  
  for (uint32_t i = 0; i < num; i++)
  {
    xortree_node_t *found;
    
    found = xortree_lookup(&tree[0], i);
    
    if (found == NULL)
    {
      printf("Key 0x%X not found\n", i);
      exit(2345);
    }
    
    if (found->key != i)
    {
      printf("Key 0x%X at 0x%X\n", i, found->key);
      exit(3456);
    }
  }
  
}
