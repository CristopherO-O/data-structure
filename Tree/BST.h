#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

typedef Node* BST;

BST* createBST() {
    BST* root = (BST*) malloc(sizeof(BST));
    if (root != NULL) {
        *root = NULL;
    }
    return root;
}

void destroyRec(Node* node) {
    if (node == NULL) return;
    destroyRec(node->left);
    destroyRec(node->right);
    free(node);
}

void destroyBST(BST* root) {
    if (root != NULL) {
        destroyRec(*root);
        free(root);
    }
}

int isEmpty(BST* root) {
    if (root == NULL) return 1;
    return (*root == NULL);
}

int countNodes(Node* root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int insertRec(Node** root, int value) {
    if (*root == NULL) {
        Node* newNode = (Node*) malloc(sizeof(Node));
        if (newNode == NULL) return 0;
        newNode->data = value;
        newNode->left = NULL;
        newNode->right = NULL;
        *root = newNode;
        return 1;
    } else {
        if ((*root)->data == value) {
            printf("Element already exists!\n");
            return 0;
        }
        if (value < (*root)->data)
            return insertRec(&(*root)->left, value);
        else
            return insertRec(&(*root)->right, value);
    }
}

int insertElement(BST* root, int value) {
    if (root == NULL) return 0;
    return insertRec(root, value);
}

int searchRec(Node** root, int value) {
    if (*root == NULL) return 0;
    if ((*root)->data == value) return 1;
    if (value < (*root)->data)
        return searchRec(&(*root)->left, value);
    else
        return searchRec(&(*root)->right, value);
}

int searchElement(BST* root, int value) {
    if (root == NULL) return 0;
    if (isEmpty(root)) return 0;
    return searchRec(root, value);
}

Node* removeNode(Node* current) {
    Node *parent, *replacement;

    if (current->left == NULL) {
        Node* rightChild = current->right;
        free(current);
        return rightChild;
    }

    parent = current;
    replacement = current->left;
    while (replacement->right != NULL) {
        parent = replacement;
        replacement = replacement->right;
    }

    if (parent != current) {
        parent->right = replacement->left;
        replacement->left = current->left;
    }
    replacement->right = current->right;
    free(current);
    return replacement;
}

int removeIter(BST* root, int value) {
    if (*root == NULL) return 0;
    Node* current = *root;
    Node* parent = NULL;

    while (current != NULL) {
        if (value == current->data) {
            if (current == *root)
                *root = removeNode(current);
            else if (parent->left == current)
                parent->left = removeNode(current);
            else
                parent->right = removeNode(current);
            return 1;
        }
        parent = current;
        if (value < current->data)
            current = current->left;
        else
            current = current->right;
    }
    return 0;
}

int removeElement(BST* root, int value) {
    if (!searchElement(root, value)) {
        printf("Element not found!\n");
        return 0;
    }
    return removeIter(root, value);
}

void inOrder(Node* root, int level) {
    if (root != NULL) {
        inOrder(root->left, level + 1);
        printf("[%d, %d] ", root->data, level);
        inOrder(root->right, level + 1);
    }
}

void preOrder(Node* root, int level) {
    if (root != NULL) {
        printf("[%d, %d] ", root->data, level);
        preOrder(root->left, level + 1);
        preOrder(root->right, level + 1);
    }
}

void postOrder(Node* root, int level) {
    if (root != NULL) {
        postOrder(root->left, level + 1);
        postOrder(root->right, level + 1);
        printf("[%d, %d] ", root->data, level);
    }
}

void printBST(BST* root) {
    if (root == NULL) return;
    if (isEmpty(root)) {
        printf("Empty Tree!\n");
        return;
    }
    printf("\nIn Order: ");
    inOrder(*root, 0);
    printf("\nPre Order: ");
    preOrder(*root, 0);
    printf("\nPost Order: ");
    postOrder(*root, 0);
    printf("\n");
}

#endif
