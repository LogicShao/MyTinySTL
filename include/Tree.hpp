#ifndef TINY_TREE_HPP
#define TINY_TREE_HPP

#include "Vector.hpp"
#include <cstddef>
#include <utility>

namespace Tiny {
template <typename T> class binarySearchTree {
private:
  struct Node {
    T data;
    std::size_t count, treeSize;
    Node *left;
    Node *right;
    Node(const T &data)
        : data(data), count(1), treeSize(1), left(nullptr), right(nullptr) {}

    Node(T &&data)
        : data(std::move(data)), count(1), treeSize(1), left(nullptr),
          right(nullptr) {}
  };

  Node *m_root;
  std::size_t m_size;

  void _inorder_impl(Node *node, Vector<T> &vec) const {
    if (node) {
      _inorder_impl(node->left, vec);
      for (std::size_t i = 0; i < node->count; i++) {
        vec.push_back(node->data);
      }
      _inorder_impl(node->right, vec);
    }
  }

  void _preorder_impl(Node *node, Vector<T> &vec) const {
    if (node) {
      vec.push_back(node->data);
      for (std::size_t i = 0; i < node->count; i++) {
        vec.push_back(node->data);
      }
      _preorder_impl(node->right, vec);
    }
  }

  void _postorder_impl(Node *node, Vector<T> &vec) const {
    if (node) {
      _postorder_impl(node->left, vec);
      _postorder_impl(node->right, vec);
      for (std::size_t i = 0; i < node->count; i++) {
        vec.push_back(node->data);
      }
    }
  }

  void _clear_impl(Node *node) {
    if (node) {
      _clear_impl(node->left);
      _clear_impl(node->right);
      delete node;
    }
  }

public:
  binarySearchTree() : m_root(nullptr), m_size(0) {}
  ~binarySearchTree() { clear(); }

  binarySearchTree(const binarySearchTree &) = delete;
  binarySearchTree &operator=(const binarySearchTree &) = delete;

  binarySearchTree(binarySearchTree &&other)
      : m_root(other.m_root), m_size(other.m_size) {
    other.m_root = nullptr;
    other.m_size = 0;
  }

  binarySearchTree &operator=(binarySearchTree &&other) {
    if (this != &other) {
      clear();
      m_root = other.m_root;
      m_size = other.m_size;
      other.m_root = nullptr;
      other.m_size = 0;
    }
    return *this;
  }

  void insert(T &&data) {
    Node *node = m_root;
    Node *parent = nullptr;
    while (node) {
      parent = node;
      node->treeSize++;
      if (data < node->data) {
        node = node->left;
      } else if (node->data < data) {
        node = node->right;
      } else {
        node->count++;
        m_size++;
        return;
      }
    }
    Node *newNode = new Node(data);
    if (!parent) {
      m_root = newNode;
    } else if (data < parent->data) {
      parent->left = newNode;
    } else {
      parent->right = newNode;
    }
    m_size++;
  }

  bool find(const T &data) const {
    Node *node = m_root;
    while (node) {
      if (data < node->data) {
        node = node->left;
      } else if (node->data < data) {
        node = node->right;
      } else {
        return true;
      }
    }
    return false;
  }

  std::size_t count(const T &data) const {
    Node *node = m_root;
    while (node) {
      if (data < node->data) {
        node = node->left;
      } else if (node->data < data) {
        node = node->right;
      } else {
        return node->count;
      }
    }
    return 0;
  }

  std::size_t rank(const T &data) const {
    Node *node = m_root;
    std::size_t r = 0;
    while (node) {
      if (data < node->data) {
        node = node->left;
      } else if (node->data < data) {
        r += node->count + node->left->treeSize;
        node = node->right;
      } else {
        return r + node->left->treeSize;
      }
    }
    return r;
  }

  T queryKth(std::size_t k) const {
    Node *node = m_root;
    while (node) {
      if (k < node->left->treeSize) {
        node = node->left;
      } else if (node->left->treeSize + node->count <= k) {
        k -= node->left->treeSize + node->count;
        node = node->right;
      } else {
        return node->data;
      }
    }
    return T{};
  }

  void clear() {
    _clear_impl(m_root);
    m_root = nullptr;
    m_size = 0;
  }

  std::size_t size() const { return m_size; }

  Vector<T> inorder() const {
    Vector<T> vec;
    _inorder_impl(m_root, vec);
    return vec;
  }

  Vector<T> preorder() const {
    Vector<T> vec;
    _preorder_impl(m_root, vec);
    return vec;
  }

  Vector<T> postorder() const {
    Vector<T> vec;
    _postorder_impl(m_root, vec);
    return vec;
  }

  Vector<T> levelorder() const { return inorder(); }
};

// TODO: Implement Treap
template <typename T> class Treap {};

// TODO: Implement SplayTree
template <typename T> class SplayTree {};

// TODO: Implement AVLTree
template <typename T> class AVLTree {};

// TODO: Implement RedBlackTree
template <typename T> class RedBlackTree {};
} // namespace Tiny

#endif // TINY_TREE_HPP