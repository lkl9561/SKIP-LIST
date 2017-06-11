# include <stdio.h>
# include <limits.h>
# include <stdlib.h>


# define MAX_LEVEL 6
# define p 0.5 //we want to keep same proportion as in ideal skiplist(fast searching one)


typedef struct node
{
	int key;
	int value;
	struct node ** forward;//pointer to a pack of pointers
}node;

typedef struct skiplist
{
	int level;//current max level
	int size;
	node * header;
}skiplist;


skiplist * initialise(skiplist * list)
{
	node * x=(node *)malloc(sizeof(node));
	x->key=INT_MAX;
	list->header=x;
	x->forward=(node **)malloc(sizeof(node *)*(MAX_LEVEL+1));
	for(int i=0;i<=MAX_LEVEL;i++)
		x->forward[i]=x;
	list->level=1;
	list->size=0;
	return list;
}


node * search(skiplist * list,int s_key)
{
	node * x=list->header;
	for(int i=list->level;i>=1;i--)
		while(x->forward[i]->key < s_key)
			x=x->forward[i];
	x=x->forward[1];
	if(x->key==s_key)
		return x;
	else
		return NULL;
}


int random_level()
{
	int new_level=1;
	while(rand()<p && new_level < MAX_LEVEL)
		new_level++;
	return new_level;
}


int insert(skiplist * list,int s_key,int new_value)
{
	int new_level;
	node * x=list->header;
	node * update[MAX_LEVEL+1];
	
	for(int i=list->level;i>=1;i--)
	{
		while(x->forward[i]->key < s_key)
			x=x->forward[i];
		update[i]=x;
	}

	x=x->forward[1];

	if(x->key==s_key)
		x->value=new_value;
	else
	{
		new_level=random_level();
		if(new_level > list->level)
		{
			for(int i=list->level+1;i<=new_level;i++)
				update[i]=list->header;
			list->level=new_level;
		}	
		
		x=(node *)malloc(sizeof(node));
		x->key=s_key;
		x->value=new_value;
		x->forward=(node **)malloc(sizeof(node *)*(new_level+1));
		//list->level can be greater then new_level thats why in below for loop use new_level
		for(int i=1;i<=new_level;i++)
		{
			x->forward[i]=update[i]->forward[i];
			update[i]->forward[i]=x;
		}
	}
	return 0;
}


int delete(skiplist * list,int s_key)
{
	node * x=list->header;
	node * update[MAX_LEVEL+1];
	
	for(int i=list->level;i>=1;i--)
	{
		while(x->forward[i]->key < s_key)
			x=x->forward[i];
		update[i]=x;
	}

	x=x->forward[1];
	
	if(x->key==s_key)
	{
		for(int i=1;i<=list->level;i++)
		{
			if(update[i]->forward[i]!=x)
				break;//bcoz it wont be true for above levels also
			else
			update[i]->forward[i]=x->forward[i];
		}

		free(x);
		free(x->forward);

		while(list->level>1)
		{
			if(list->header->forward[list->level]==list->header)
				list->level=list->level-1;
		}
	}
	return 0;
}

static void dump(skiplist *list) {
    node *x = list->header;
    while (x && x->forward[1] != list->header) {
        printf("%d[%d]->", x->forward[1]->key, x->forward[1]->value);
        x = x->forward[1];
    }
    printf("NIL\n");
}
 

int main() {
    int arr[] = { 3, 6, 9, 2, 11, 1, 4 }, i;
    skiplist list;
    initialise(&list);
 
    printf("Insert:--------------------\n");
    for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        insert(&list, arr[i], arr[i]);
    }
    dump(&list);
 
    printf("Search:--------------------\n");
    int keys[] = { 3, 4, 7, 10, 111 };
 
    for (i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) {
        node *x = search(&list, keys[i]);
        if (x) {
            printf("key = %d, value = %d\n", keys[i], x->value);
        } else {
            printf("key = %d, not fuound\n", keys[i]);
        }
    }

    printf("Search:--------------------\n");
    delete(&list, 3);
    delete(&list, 9);
    dump(&list);
 
    return 0;
}














