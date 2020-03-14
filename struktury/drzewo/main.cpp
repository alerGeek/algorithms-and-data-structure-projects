#include <iostream>
#include <time.h>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

struct node {
    int key;
    node *left;
    node *right;
    node *up;
};

bool czyPusty(node *node) {
    return node == nullptr;
}

node *make_leaf(int new_data) {
    node *nn = new node;
    nn->key = new_data;
    nn->left = nullptr;
    nn->right = nullptr;
    nn->up = nullptr;
    return nn;
}

void add_leaf(int new_data, node *&root) {
    if (root == nullptr) {
        root = make_leaf(new_data);
        return;
    }

    node *temp = root;
    while (true) {
        if (new_data >= temp->key) {
            if (temp->right == nullptr) {
                temp->right = make_leaf(new_data);
                temp->right->up = temp;
                return;
            } else {
                temp = temp->right;
            }
        } else {
            if (temp->left == nullptr) {
                temp->left = make_leaf(new_data);
                temp->left->up = temp;
                return;
            } else {
                temp = temp->left;
            }
        }

    }
}

node *find_node(node *root, int value) {
    while (root != nullptr) {
        if (root->key == value) {
            return root;
        }
        if (value > root->key) {
            root = root->right;
        } else {
            root = root->left;
        }
    }
    return root;
}

void preorder(node *root) {
    if (root != nullptr) {
        cout << root->key << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(node *root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

void postorder(node *root) {
    if (root != nullptr) {
        postorder(root->left);
        postorder(root->right);
        cout << root->key << " ";
    }
}

int main() {
    node *node = nullptr;
    int value;

    int menu = -1;
    cout << "Menu:" << endl;
    cout << "1 - Sprawdzenie czy drzewo jest pusta" << endl;
    cout << "2 - Dodanie nowego wêz³a do drzewa."
         << " Wartoœæ klucza powinna zostaæ wczytana przez u¿ytkownika wêz³a na koniec listy"
         << endl;
    cout << "3 - sprawdzenie czy klucza podanej wartoœci wêz³a przez u¿ytkownika znajduje siê w drzewie." << endl;
    cout << "4 - wyœwietlenie drzewa - preorder " << endl;
    cout << "5 - wyœwietlenie drzewa - inorder" << endl;
    cout << "6 - wyœwietlenie drzewa - postorder" << endl;
    cout << "7 - Wyjscie z programu" << endl;

    while (menu != 7) {
        cin >> menu;
        value = rand() % 100 + 0;
        switch (menu) {
            case 1: {
                string wynik = czyPusty(node) ? "Pusty" : "Niepusty";
                cout << wynik << endl;
            }
                break;
            case 2:
                cout << "Dodano " << value << endl;
                add_leaf(value, node);
                break;
            case 3:
                find_node(node, value);
                break;
            case 4:
                preorder(node);
                break;
            case 5:
                inorder(node);
                break;
            case 6:
                postorder(node);
                break;
        }
    }
    return 0;
}

