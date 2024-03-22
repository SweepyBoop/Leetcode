#pragma once
#include "..\Common.h"

struct Node {
    int key;
    int val;
    Node* next;
    Node* prev;
    Node() : key(0), val(0), next(nullptr), prev(nullptr) {}
    Node(int key, int val) : key(key), val(val), next(nullptr), prev(nullptr) {}
};

class LRUCache {
public:
    LRUCache(int capacity) : capacity(capacity) {
        oldest = new Node();
        newest = new Node();
        oldest->next = newest;
        newest->prev = oldest;
    }

    int get(int key) {
        auto find = hash.find(key);
        if (find == hash.end()) {
            return -1;
        }

        // found the element, move it to newest
        Node* node = (*find).second;
        moveToNewest(node);
        return node->val;
    }

    void put(int key, int value) {
        auto find = hash.find(key);
        if (find == hash.end()) {
            // insert a new node, but check if we have capacity yet
            if (hash.size() == capacity) {
                removeOldest();
            }

            // create a new node and make it newest
            Node* node = new Node(key, value);
            hash[key] = node;
            moveToNewest(node);
        }
        else {
            // update existing node
            Node* node = (*find).second;
            node->val = value;
            moveToNewest(node);
        }
    }

private:
    void moveToNewest(Node* node) {
        // if already newest node
        if (node->next == newest) {
            return;
        }

        // remove the node IF it's in the original linked list
        Node* prev = node->prev;
        Node* next = node->next;
        if (prev) {
            prev->next = next;
        }
        if (next) {
            next->prev = prev;
        }

        // re-insert before newest
        prev = newest->prev;
        prev->next = node;
        node->prev = prev;
        node->next = newest;
        newest->prev = node;
    }

    void removeOldest() {
        // oldest <-> node <-> next
        Node* node = oldest->next;

        hash.erase(node->key);
        Node* next = node->next;
        oldest->next = next;
        next->prev = oldest;

        delete node;
    }

    // oldest <-> actual nodes <-> newest
    Node* oldest;
    Node* newest;
    unordered_map<int, Node*> hash;
    int capacity = 0;
};
