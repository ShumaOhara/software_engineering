#include "bptree.h"
#include <vector>
#include <sys/time.h>

struct timeval
cur_time(void)
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return t;
}

void
print_tree_core(NODE *n)
{
	printf("["); 
	for (int i = 0; i < n->nkey; i++) {
		if (!n->isLeaf) print_tree_core(n->chi[i]); 
		printf("%d", n->key[i]); 
		if (i != n->nkey-1 && n->isLeaf) putchar(' ');
	}
	if (!n->isLeaf) print_tree_core(n->chi[n->nkey]);
	printf("]");
}

void
print_tree(NODE *node)
{
	print_tree_core(node);
	printf("\n"); fflush(stdout);
}

NODE *
find_leaf(NODE *node, int key)
{
	int kid;

	if (node->isLeaf) return node;
	for (kid = 0; kid < node->nkey; kid++) {
		if (key < node->key[kid]) break;
	}

	return find_leaf(node->chi[kid], key);
}

NODE *
alloc_leaf(NODE *parent)
{
	NODE *node;
	if (!(node = (NODE *)calloc(1, sizeof(NODE)))) ERR;
	node->isLeaf = true;
	node->parent = parent;
	node->nkey = 0;

	return node;
}

NODE *
insert_in_leaf(NODE *leaf, int key, DATA *data)
{
	int i;
	if (key < leaf->key[0]) {
		for (i = leaf->nkey; i > 0; i--) {
			leaf->chi[i+1] = leaf->chi[i] ;
			leaf->key[i] = leaf->key[i-1] ;
		}
		leaf->key[0] = key;
		leaf->chi[0] = (NODE *)data;
	}
	else {
		for (i = 0; i < leaf->nkey; i++) {
			if (key < leaf->key[i]) break;
		}
		for (int j = leaf->nkey; j > i; j--) {		
			leaf->chi[j+1] = leaf->chi[j] ;
			leaf->key[j] = leaf->key[j-1] ;
		}
		leaf->key[i] = key;
		leaf->chi[i] = (NODE *)data;
	}
	leaf->nkey += 1;

	return leaf;
}

void
insert_in_parent(NODE *leaf, int key, NODE *new_leaf){
    //Rootだったら新しく作る
    NODE *parent;
    if(Root == leaf){
        parent = alloc_leaf(NULL);
        parent->key[0] = key;
        parent->chi[0] = leaf;
        parent->chi[1] = new_leaf;
        parent->nkey = 1;
        parent->isLeaf = false;
        leaf->parent = parent;
        new_leaf->parent = parent;
        Root = parent;
        return;
    }

    //Rootじゃなかったらinsert_in_leaf関数と同じようなことする
    parent = leaf->parent;
    //まだ元のparentに枠が余ってた場合
    if(parent->nkey < N){
        int i;
        if(key < parent->key[0]){
            for(i = parent->nkey; i > 0; i--){
                parent->chi[i+1] = parent->chi[i];
                parent->key[i] = parent->key[i-1];
            }
            parent->key[0] = key;
            parent->chi[0] = leaf;
            parent->chi[1] = new_leaf;
        }
        else{
            for(i = 0; i < parent->nkey; i++){
                if(key < parent->key[i]) break;
            }
            for(int j = parent->nkey; j > i; j--){
                parent->chi[j+1] = parent->chi[j];
                parent->key[j] = parent->key[j-1];
            }
            leaf->key[i] = key;
            leaf->chi[i+1] = new_leaf;
        }
        parent->nkey += 1;
        return;
    }
    //もう枠がなかった場合
    else{
        TEMP temp;
        
        int i;
        for(i = 0; i < N-1; i++){
            temp.key[i] = parent->key[i];
        }
        for(i = 0; i < N; i++){
            temp.chi[i] = parent->chi[i];
        }
        temp.nkey = N-1;
        temp.isLeaf = parent->isLeaf;

        if(key < temp.key[0]){
            for(i = temp.nkey-1; i > 0; i--){
                temp.chi[i+1] = temp.chi[i];
                temp.key[i] = temp.key[i-1];
            }
            temp.key[0] = key;
            temp.chi[0] = leaf;
            temp.chi[1] = new_leaf;
        }
        else{
            for(i = 0; i < temp.nkey; i++){
                if(key < temp.key[i]) break;
            }
            for(int j = temp.nkey-1; j > i; j--){
                temp.chi[j+1] = temp.chi[j];
                temp.key[j] = temp.key[j-1];
            }
            temp.key[i] = key;
        }
        temp.nkey++;

        NODE *new_parent;
        new_parent = alloc_leaf(parent->parent);

        new_parent->chi[N-1] = parent->chi[N-1];
        for(int i = 0; i < N-1; i++){
            parent->key[i] = 0;
            parent->chi[i] = NULL;
        }
        parent->chi[i+1] = NULL;
        parent->nkey = 0;
        for(int i = 0; i < N/2; i++){
            parent->chi[i] = temp.chi[i];
            parent->key[i] = temp.key[i];
            parent->nkey++;
            new_parent->chi[i] = temp.chi[i+(N/2)];
            new_parent->key[i] = temp.key[i+(N/2)];
            new_parent->nkey++;
        }
        NODE *key_leaf = parent->chi[0];
        while(true){
            if(key_leaf->isLeaf == true) break;
            key_leaf = key_leaf->chi[0];
        }
        int parent_key = key_leaf->key[0];
        insert_in_parent(parent, parent_key, new_parent);
    }
}

void 
insert(int key, DATA *data)
{
	NODE *leaf, *new_leaf;

	if (Root == NULL) {
		leaf = alloc_leaf(NULL);
		Root = leaf;
	}else {
    	leaf = find_leaf(Root, key);
  	}

	if (leaf->nkey < N-1) {
		insert_in_leaf(leaf, key, data);
	}else { // split
        //TEMP型の構造体にリーフをコピー
        TEMP temp;
        int i;
        for(i = 0; i < N-1; i++){
            temp.key[i] = leaf->key[i];
            temp.chi[i] = leaf->chi[i];
        }
        temp.chi[i+1] = temp.chi[i+1];
        temp.nkey = leaf->nkey;
        temp.isLeaf = leaf->isLeaf;
        
        //あたらしいkeyをいれる
        if(key < temp.key[0]){
            for(i = temp.nkey-1; i > 0; i--){
                temp.chi[i+1] = temp.chi[i];
                temp.key[i] = temp.key[i-1];
            }
            if(temp.chi[0]->key[0] > data->key){
                temp.chi[1] = temp.chi[0];
                temp.chi[0] = (NODE *)data;
            }
            else{
                temp.chi[1] = (NODE *)data;
            }
            temp.key[0] = key;
        }
        else{
            for(i = 0; i < temp.nkey; i++){
                if(key < temp.key[i]) break;
            }
            for(int j = temp.nkey-1; j > i; j--){
                temp.chi[j+1] = temp.chi[j];
                temp.key[j] = temp.key[j-1];
            }
            temp.key[i] = key;
            temp.chi[i+1] = (NODE *)data;
        }
        temp.nkey++;
        //2つにリーフを分ける
        new_leaf = alloc_leaf(leaf->parent);
        new_leaf->chi[N-1] = temp.chi[N-1];
        leaf->chi[N-1] = new_leaf;
        for(int i = 0; i < N-1; i++){
            leaf->key[i] = 0;
            leaf->chi[i] = NULL;
        }
        leaf->nkey = 0;
        for(i = 0; i < N/2; i++){
            insert_in_leaf(leaf, temp.key[i], (DATA *)temp.chi[i]);
            insert_in_leaf(new_leaf, temp.key[i+N/2], (DATA *)temp.chi[i+N/2]);
        }
        temp.isLeaf = false;
        temp.nkey = 0;
        for(int i = 0; i < N; i++){
            temp.chi[i] = NULL;
            temp.key[i] = 0;
        }
        temp.chi[N] = NULL;
        int parent_key = new_leaf->key[0];
        insert_in_parent(leaf, parent_key, new_leaf);
    }
}

void
init_root(void)
{
	Root = NULL;
}

int 
interactive()
{
  int key;

  std::cout << "Key: ";
  std::cin >> key;

  return key;
}

int
main(int argc, char *argv[])
{
  struct timeval begin, end;

	init_root();

	printf("-----Insert-----\n");
	begin = cur_time();
  while (true) {
		insert(interactive(), NULL);
    print_tree(Root);
  }
	end = cur_time();

	return 0;
}