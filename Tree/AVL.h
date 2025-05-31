#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BIGGER(a, b) ((a > b) ? (a) : (b))

typedef struct Node {
    int data, fb, alt;
    struct Node *left;
    struct Node *right;   
} Node;

typedef struct Node *AVL;

AVL* createAVL() {
    AVL* root = (AVL*) malloc(sizeof(AVL));
    if (root != NULL)
        *root = NULL;
    return root;
}

void destroyRec(Node* node) {
    if (node == NULL) return;
    destroyRec(node->left);
    destroyRec(node->right);
    free(node);
}

void destroyAVL(AVL* root) {
    if (root != NULL) {
        destroyRec(*root);
        free(root);
    }
}

int countNodes(Node* root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int isEmpty(AVL* root) {
    if (root == NULL) return 1;
    return (*root == NULL);
}

int height(Node* root){
    if(root == NULL) return 0;
    if(root->alt > 0)
        return root->alt;
    else{ 
        return BIGGER(height(root->left), height(root->right)) + 1;
    }
}

int FB(Node* root){
    if(root == NULL) return 0;
    return height(root->left) - height(root->right);
}

void rightRot(Node** root){
    Node* aux;
    aux = (*root)->left;
    (*root)->left = aux->right;
    aux->right = *root;

    (*root)->alt = aux->alt = -1;
    aux->alt = height(aux); 
    (*root)->alt = height(*root); 
    aux->fb = FB(aux); 
    (*root)->fb = FB(*root);

   *root = aux;
}

void leftRot(Node** root){
   Node *aux;
   aux = (*root)->right;
   (*root)->right = aux->left;
   aux->left = *root;

    (*root)->alt = aux->alt = -1;
    aux->alt = height(aux); 
    (*root)->alt = height(*root); 
    aux->fb = FB(aux); 
    (*root)->fb = FB(*root);
   
   *root = aux;
}

void leftRightRot(Node** root){
    Node *ls;
    Node *rss;
    
    ls = (*root)->left;
    rss = ls->right;
    
    ls->right = rss->left;
    rss->left = ls;
    
    (*root)->left = rss->right;
    rss->right = *root;

    (*root)->alt = ls->alt = rss->alt = -1;
    ls->alt = height(ls); 
    rss->alt = height(rss);
    (*root)->alt = height(*root); 
    ls->fb = FB(ls); 
    rss->fb = FB(rss);
    (*root)->fb = FB(*root);

    *root = rss;
}

void rightLeftRot(Node** root){
    Node* rs;
    Node* lss;

    rs = (*root)->right;
    lss = rs->left;
    
    rs->left = lss->right;
    lss->right = rs;
    
    (*root)->right = lss->left;
    lss->left = *root;

    (*root)->alt = rs->alt = lss->alt = -1;
    rs->alt = height(rs); 
    lss->alt = height(lss);
    (*root)->alt = height(*root); 
    rs->fb = FB(rs);
    lss->fb = FB(lss);
    (*root)->fb = FB(*root);

    *root = lss;
}

void auxLS(Node **root){
   Node* fe;
   fe = (*root)->left;
   if(fe->fb == +1)
    rightRot(root);
   else 
    leftRightRot(root);
}

void auxRS(Node **root){
   Node* fd;
   fd = (*root)->right;
   if(fd->fb == -1)
     leftRot(root);
   else
     rightLeftRot(root);
}

int recInsert(Node** root, int elem){
    int ok;
    if(*root == NULL){
        Node* newNode = (Node*) malloc(sizeof(Node));
        if(newNode == NULL) return 0;
        newNode->data = elem; newNode->fb = 0, newNode->alt = 1;
        newNode->left = NULL; newNode->right = NULL;
        *root = newNode; return 1;
    }else{
        if((*root)->data == elem){
            printf("element already exists\n"); ok = 0;
        }
        if(elem < (*root)->data){
            ok = recInsert(&(*root)->left, elem);
            if(ok){
                switch((*root)->fb){
                    case -1:
                        (*root)->fb = 0; ok = 0; break;
                    case 0:
                        (*root)->fb = +1; 
                        (*root)->alt++; 
                        break;
                    case +1:
                        auxLS(root); ok = 0; break;
                }
            }
        }
        else if(elem > (*root)->data){
            ok = recInsert(&(*root)->right, elem);
            if(ok){
                switch((*root)->fb){
                    case +1:
                        (*root)->fb = 0; ok = 0; break;
                    case 0:
                        (*root)->fb = -1; (*root)->alt++; break;
                    case -1:
                        auxRS(root); ok = 0; break;
                }
            }
        }
    }
    return ok;
}

int insertElem(AVL* root, int elem){
    if(root == NULL) return 0;
    return recInsert(root, elem);
}

int recSearch(Node** root, int elem){
    if(*root == NULL) return 0;
    if((*root)->data == elem) return 1;
    if(elem < (*root)->data)
        return recSearch(&(*root)->left, elem);
    else 
        return recSearch(&(*root)->right, elem);
}

int search(AVL* root, int elem){
    if(root == NULL) return 0;
    if(isEmpty(root)) return 0;
    return recSearch(root, elem);
}

int recRemove(Node** root, int elem){
    if(*root == NULL) return 0;
    int ok;
    if((*root)->data == elem){
        Node* aux;
        if((*root)->left == NULL && (*root)->right == NULL){
            free(*root);
            *root = NULL;
        }else if((*root)->left == NULL){
            aux = *root;
            *root = (*root)->right;
            free(aux);
        }else if((*root)->right == NULL){
            aux = *root;
            *root = (*root)->left;
            free(aux);
        }else{
            Node* Filho = (*root)->left;
            while(Filho->right != NULL)
                Filho = Filho->right;
            (*root)->data = Filho->data;
            Filho->data = elem;
            return recRemove(&(*root)->left, elem);
        }
        return 1;
    }else if(elem < (*root)->data){
        ok = recRemove(&(*root)->left, elem); 
        if(ok){
            switch((*root)->fb){
                case +1:
                case 0:

                    (*root)->alt = -1;
                    (*root)->alt = height(*root); 
                    (*root)->fb = FB(*root);
                    break;
                case -1:
                    auxRS(root); break;
            }
        }
    }
    else{ 
        ok = recRemove(&(*root)->right, elem);
        if(ok){
            switch((*root)->fb){
                case -1:
                case 0:
                    (*root)->alt = -1;
                    (*root)->alt = height(*root); 
                    (*root)->fb = FB(*root);
                    break;
                case +1:
                    auxLS(root); break;
            }
        }
    }
    return ok;
}

int removeElem(AVL* root, int elem){
    if(search(root, elem) == 0){
        printf("Element does not exist!\n");
        return 0;
    }
    return recRemove(root, elem);
}

void inOrder(Node* root, int nivel){
    if(root != NULL){
        inOrder(root->left, nivel+1);
        printf("[%d, %d, %d, %d] ", root->data, root->fb, nivel, root->alt);
        inOrder(root->right, nivel+1);
    }
}

void imprime(AVL* root){
    if(root == NULL) return;
    if(isEmpty(root)){
        printf("empty tree!\n");
        return;
    } 
    printf("\nIn Order: [DATA, FB, LEVEL, height]\n"); 
    inOrder(*root, 0);
    printf("\n");
}
#endif
