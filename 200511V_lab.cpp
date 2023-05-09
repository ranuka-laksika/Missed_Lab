#include <iostream>
using namespace std;

struct node {
  int key;
  struct node *left, *right;
};

// Inorder traversal
void traverseInOrder(struct node *root) {
  if (root != NULL) {
    traverseInOrder(root->left);
    cout << root->key << " ";
    traverseInOrder(root->right);
  }
}

// Insert a node
struct node *insertNode(struct node *root, int key) {
  // Create a new node
  struct node *newNode = new node;
  newNode->key = key;
  newNode->left = newNode->right = NULL;

  // If the tree is empty, return the new node
  if (root == NULL) {
    return newNode;
  }

  // Otherwise, recur down the tree
  if (key < root->key) {
    root->left = insertNode(root->left, key);
  } else if (key > root->key) {
    root->right = insertNode(root->right, key);
  }

  // Return the (unchanged) root node
  return root;
}

// Deleting a node
struct node *deleteNode(struct node *root, int key) {
  // Base case
  if (root == NULL) {
    return root;
  }

  // Recur down the tree
  if (key < root->key) {
    root->left = deleteNode(root->left, key);
  } else if (key > root->key) {
    root->right = deleteNode(root->right, key);
  } else {
    // Case 1: Node has no children
    if (root->left == NULL && root->right == NULL) {
      delete root;
      root = NULL;
    }
    // Case 2: Node has one child
    else if (root->left == NULL) {
      struct node *temp = root;
      root = root->right;
      delete temp;
    } else if (root->right == NULL) {
      struct node *temp = root;
      root = root->left;
      delete temp;
    }
    // Case 3: Node has two children
    else {
      struct node *temp = root->right;
      while (temp->left != NULL) {
        temp = temp->left;
      }
      root->key = temp->key;
      root->right = deleteNode(root->right, temp->key);
    }
  }

  return root;
}


int main() {
  struct node *root = NULL;

  int operation;
  int operand;
  cin >> operation;

  while (operation != -1) {
    switch(operation) {
      case 1: // insert
        cin >> operand;
        root = insertNode(root, operand);
        cin >> operation;
        break;
      case 2: // delete
        cin >> operand;
        root = deleteNode(root, operand);
        cin >> operation;
        break;
      default:
        cout << "Invalid Operator!\n";
        return 0;
    }
  }
 
  traverseInOrder(root);
}