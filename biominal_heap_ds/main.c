#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
typedef struct Node{
    int value;
    struct Node*parent;
    struct Node*child;
    struct Node*sibling;
}Node;
typedef struct Binomial_Tree{
    Node*root;
    int num_ele;
    int degree;
    struct Binomial_Tree*next;
}
Binomial_Tree;
typedef struct Binomial_heap{
    int num_ele;
    Binomial_Tree*head;
    int num_tree;
}
Binomial_heap;
Binomial_Tree *merge_tree(Binomial_Tree*tree_1,Binomial_Tree*tree_2){//function to merge 2 binomial tree
    (tree_1->num_ele)*=2;
    (tree_2->num_ele)*=2;
    (tree_1->degree)++;
    (tree_2->degree)++;
    if(tree_2->root->value>tree_1->root->value){//merge tree_2 into tree_1
        tree_2->root->parent=tree_1->root;
        tree_2->root->sibling=tree_1->root->child;
        tree_1->root->child=tree_2->root;
        if(tree_2->next!=tree_1){
            tree_1->next=tree_2->next;
            tree_2->next=NULL;
        }
        free(tree_2);
        tree_2=NULL;
        return tree_1;
    }else{//merge tree 1 in to tree 2
        tree_1->root->parent=tree_2->root;
        tree_1->root->sibling=tree_2->root->child;
        tree_2->root->child=tree_1->root;
        if(tree_1->next!=tree_2){
            tree_2->next=tree_1->next;
            tree_1->next=NULL;
        }
        free(tree_1);
        tree_1=NULL;
        return tree_2;
    }
}
Binomial_heap *merge_heap(Binomial_heap*heap_1,Binomial_heap*heap_2){//function to merge and return pointer to the head
    //of binomial heap
    Binomial_Tree *head_heap_1=heap_1->head;
    Binomial_Tree *head_heap_2=heap_2->head;
    (heap_1->num_ele)+=heap_2->num_ele;
    (heap_1->num_tree)+=heap_2->num_tree;
    while(head_heap_1!=NULL&&head_heap_2!=NULL){
        Binomial_Tree*prev_tree_1=head_heap_1;
        Binomial_Tree *prev_tree_2=head_heap_2;
        head_heap_1=head_heap_1->next;
        head_heap_2=head_heap_2->next;
        prev_tree_1->next=prev_tree_2;
        prev_tree_2->next=head_heap_1;
    }
    heap_2->head=NULL;
    free(heap_2);
    heap_2=NULL;
    Binomial_Tree *cur_tree=(heap_1->head);
    Binomial_Tree **new_tree=&(heap_1->head);
    while((cur_tree)!=NULL&&(cur_tree)->next!=NULL){
        if((cur_tree)->degree==(cur_tree)->next->degree&&((cur_tree)->next->next==NULL||(cur_tree)->next->next->degree!=(cur_tree)->degree)){
            cur_tree= merge_tree(cur_tree,(cur_tree)->next);
        }
        (*new_tree)=cur_tree;
        (new_tree)=&((*new_tree)->next);
        cur_tree=(cur_tree)->next;
    }

    return heap_1;
}
void insert(Binomial_heap **my_bio_heap,int value){
    Node*new_node=(Node*)(malloc(sizeof(Node)));
    Binomial_Tree *new_tree=(Binomial_Tree*)(malloc(sizeof(Binomial_Tree)));
    Binomial_heap *new_heap=(Binomial_heap*)(malloc(sizeof(Binomial_heap)));
    if(new_tree!=NULL&&new_node!=NULL&&new_heap!=NULL){
        new_node->child=NULL;
        new_node->sibling=NULL;
        new_node->parent=NULL;
        new_node->value=value;

        new_tree->next=NULL;
        new_tree->root=new_node;
        new_tree->degree=0;
        new_tree->num_ele=1;

        new_heap->head=new_tree;
        new_heap->num_tree=1;
        new_heap->num_ele=new_tree->num_ele;
        if((*my_bio_heap)==NULL){
            *my_bio_heap=new_heap;
        }else{
            *my_bio_heap=merge_heap(*my_bio_heap,new_heap);
        }
    }
}
void print_tree(Node*root){
    if(root!=NULL){
        printf(" %d, ",root->value);
        print_tree(root->child);
        print_tree(root->sibling);
    }
}
void print_heap(Binomial_heap*my_bio_heap){
    int num=0;
    if(my_bio_heap==NULL){
        return;
    }
    Binomial_Tree *cur=my_bio_heap->head;
    while(cur!=NULL){
        printf("\nTree %d: ",num);
        print_tree(cur->root);
        cur=cur->next;
        num++;
    }
}
void delete_tree(Node*root){
    if(root!=NULL){
        delete_tree(root->child);
        delete_tree(root->sibling);
        free(root);
    }
}
void delete_all(Binomial_heap**my_bio_heap){
    if(my_bio_heap==NULL){
        return;
    }
    Binomial_Tree *cur=(*my_bio_heap)->head;
    Binomial_Tree *prev=NULL;
    while(cur!=NULL){
        prev=cur;
        delete_tree(cur->root);
        cur=cur->next;
        free(prev);
    }
    free(*my_bio_heap);
    *my_bio_heap=NULL;
}
int main() {
    srand(time(NULL));
    Binomial_heap *my_heap=NULL;
    for(int i=0;i<=20;i++){
        int num=rand()%1000;
        insert(&my_heap,num);
        printf("\ntime %d",i);
        print_heap(my_heap);
    }
    delete_all(&my_heap);
    return 0;
}
