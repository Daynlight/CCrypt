//////////////////////////
/////////// BST //////////
//////////////////////////
//// IDEA ////

//// How it works: ////

//// TL;TR ////


#ifndef BST_TREE_H
#define BST_TREE_H


#ifdef __cplusplus
extern "C" {
#endif



typedef char (*bst_compare)(const char* value, const char* left, const char* right);

struct BST_TREE{
  char* value;
  unsigned int size_of_el;
  bst_compare compare;

  struct BST_TREE* parent;
  struct BST_TREE* left;
  struct BST_TREE* right;
};


void bst_tree_init(struct BST_TREE* bst_tree, unsigned int size_of_el);
void bst_tree_destroy(struct BST_TREE* bst_tree);

void bst_tree_add(struct BST_TREE* root, char* node);
void bst_tree_delete(struct BST_TREE* node);

struct BST_TREE* bst_tree_search(struct BST_TREE* bst_tree, char* value);

struct BST_TREE* bst_tree_inorder(struct BST_TREE* bst_tree);



#ifdef __cplusplus
}
#endif

#endif