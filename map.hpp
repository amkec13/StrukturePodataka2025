#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>
template <typename K, typename V> class Map {
public:
  Map() : root_(nullptr), size_(0) {}

  Map(const Map &other) { insert_subtree(other.root_); }

  Map(Map &&other) : root_(other.root_), size_(other.size_) {
    other.root_ = nullptr;
    other.size_ = 0;
  }

  Map &operator=(const Map &other) { return *this = Map(other); }
  Map &operator=(Map &&other) {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
    return *this;
  }

  ~Map() { clear(); }

  template <typename F> void insert(const K &k, F &&v) {
    auto new_node = new Node(k, std::forward<F>(v));
    size_++;

    if (root_ == nullptr) {
      root_ = new_node;
      return;
    }

    auto temp = root_;
    while (temp != nullptr) {
      if (new_node->kljuc < temp->kljuc) {
        if (temp->left_ == nullptr) {
          temp->left_ = new_node;
          return;
        }
        temp = temp->left_;
      } else {
        if (temp->right_ == nullptr) {
          temp->right_ = new_node;
          return;
        }
        temp = temp->right_;
      }
    }
  }

  void clear() {
    clear_subtree(root_);
    size_ = 0;
    root_ = nullptr;
  }

  void print() const {
    print_inorder(root_);
    std::cout << std::endl;
  }

  V *find(const K &k) {
    auto temp = root_;
    while (temp != nullptr) {
      if (temp->kljuc == k) {
        return &temp->vrijednost;
      } else if (k < temp->kljuc) {
        temp = temp->left_;
      } else {
        temp = temp->right_;
      }
    }
    return nullptr;
  }

  const V *find(const K &k) const {
    auto temp = root_;
    while (temp != nullptr) {
      if (temp->kljuc == k) {
        return &temp->vrijednost;
      } else if (k < temp->kljuc) {
        temp = temp->left_;
      } else {
        temp = temp->right_;
      }
    }
    return nullptr;
  }

  V &at(const K &k) {
    auto temp = find(k);
    if (temp != nullptr) {
      return *temp;
    } else {
      throw std::out_of_range("Element sa tim kljucem ne postoji!");
    }
  }

  const V &at(const K &k) const {
    auto temp = find(k);
    if (temp != nullptr) {
      return *temp;
    } else {
      throw std::out_of_range("Element sa tim kljucem ne postoji!");
    }
  }

  bool erase(const K &k) {
    Node **current = &root_;

    while (*current != nullptr) {
      if (k < (*current)->kljuc) {
        current = &(*current)->left_;
      } else if (k > (*current)->kljuc) {
        current = &(*current)->right_;
      } else {
        eraseNode(*current); // brišemo čvor
        return true;
      }
    }

    return false; // nije pronađen
  }

  V &operator[](const K &k) {
    auto temp = find(k);
    if (temp != nullptr) {
      return *temp;
    }

    insert(k, V{});
    temp = find(k);
    return *temp;
  }

  bool empty() const { return root_ == nullptr; }
  size_t size() const { return size_; }

private:
  struct Node {

    template <typename T, typename F>
    Node(T &&k, F &&v, Node *l = nullptr, Node *r = nullptr)
        : kljuc(std::forward<T>(k)), vrijednost(std::forward<F>(v)), left_(l),
          right_(r) {}

    K kljuc;
    V vrijednost;
    Node *left_ = nullptr;
    Node *right_ = nullptr;
  };

  void insert_subtree(const Node *other_root) {
    if (!other_root)
      return;
    auto new_node = new Node(other_root->kljuc, other_root->vrijednost);
    insert_subtree(other_root->left_);
    insert_subtree(other_root->right_);
  }

  void clear_subtree(Node *root) {
    if (root == nullptr)
      return;
    clear_subtree(root->left_);
    clear_subtree(root->right_);
    delete root;
  }

  void eraseNode(Node *&e) {
    if (e == nullptr) {
      return;
    } else if (e->left_ == nullptr && e->right_ == nullptr) {
      delete e;
      e = nullptr;
    } else if (e->right_ == nullptr) {
      auto temp = e;
      e = e->left_;
      delete temp;
    } else if (e->left_ == nullptr) {
      auto temp = e;
      e = e->right_;
      delete temp;
    } else {
      Node *previous = nullptr;
      auto current = e->left_;

      while (current->right_ != nullptr) {
        previous = current;
        current = current->right_;
      }

      e->kljuc = current->kljuc;
      e->vrijednost = current->vrijednost;

      if (previous != nullptr)
        previous->right_ = current->left_;
      else
        e->left_ = current->left_;

      delete current;
    }
    size_--;
  }

  static void print_inorder(const Node *root) {
    if (root == nullptr)
      return;
    print_inorder(root->left_);
    std::cout << root->vrijednost << ' ';
    print_inorder(root->right_);
  }

  Node *root_ = nullptr;
  size_t size_ = 0;
};
