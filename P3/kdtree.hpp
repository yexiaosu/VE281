#include <tuple>
#include <vector>
#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <queue>

/**
 * An abstract template base of the KDTree class
 */
template<typename...>
class KDTree;

/**
 * A partial template specialization of the KDTree class
 * The time complexity of functions are based on n and k
 * n is the size of the KDTree
 * k is the number of dimensions
 * @typedef Key         key type
 * @typedef Value       value type
 * @typedef Data        key-value pair
 * @static  KeySize     k (number of dimensions)
 */
template<typename ValueType, typename... KeyTypes>
class KDTree<std::tuple<KeyTypes...>, ValueType> {
public:
    typedef std::tuple<KeyTypes...> Key;
    typedef ValueType Value;
    typedef std::pair<const Key, Value> Data;
    static inline constexpr size_t KeySize = std::tuple_size<Key>::value;
    static_assert(KeySize > 0, "Can not construct KDTree with zero dimension");
protected:
    struct Node {
        Data data;
        Node *parent;
        Node *left = nullptr;
        Node *right = nullptr;

        Node(const Key &key, const Value &value, Node *parent) : data(key, value), parent(parent) {}

        const Key &key() { return data.first; }

        Value &value() { return data.second; }
    };

public:
    /**
     * A bi-directional iterator for the KDTree
     * ! ONLY NEED TO MODIFY increment and decrement !
     */
    class Iterator {
    private:
        KDTree *tree;
        Node *node;

        Iterator(KDTree *tree, Node *node) : tree(tree), node(node) {}

        /**
         * Increment the iterator
         * Time complexity: O(log n)
         */
        Node *findLeftLeaf(Node *cur_node) {
            if (cur_node->left == nullptr) {
                return cur_node;
            } else {
                return findLeftLeaf(cur_node->left);
            }
        }

        Node *findRightAst(Node *cur_node) {
            Node *par = cur_node->parent;
            if (par == nullptr) {
                return nullptr;
            }
            if (par->left == cur_node) {
                return par;
            } else {
                return findRightAst(par);
            }
        }

        void increment() {
            // TODO: implement this function
            if (*this == tree->end()) {
                throw std::range_error("Increment end()");
            }
            if (node->right != nullptr) {
                // find left most leaf in right sub tree
                this->node = findLeftLeaf(node->right);
                return;
            } else {
                // find first ancestor that turns to right
                this->node = findRightAst(node);
                return;
            }
        }

        /**
         * Decrement the iterator
         * Time complexity: O(log n)
         */
        Node *findRightLeaf(Node *cur_node) {
            if (cur_node->right == nullptr) {
                return cur_node;
            } else {
                return findRightLeaf(cur_node->right);
            }
        }

        Node *findLeftAst(Node *cur_node) {
            Node *par = cur_node->parent;
            if (par == nullptr) {
                return nullptr;
            }
            if (par->right == cur_node) {
                return par;
            } else {
                return findLeftAst(par);
            }
        }

        void decrement() {
            // TODO: implement this function
            if (*this == tree->begin()) {
                throw std::range_error("Decrement begin()");
            }
            if (*this == tree->end()) {
                // return the right most leaf node
                Node *new_node = tree->root;
                while (new_node->right != nullptr) new_node = new_node->right;
                this->node = new_node;
                return;
            }
            if (node->left != nullptr) {
                // find right most leaf in left sub tree
                this->node = findRightLeaf(node->left);
                return;
            } else {
                // find first ancestor that turns to left
                this->node = findLeftAst(node);
                return;
            }
        }

    public:
        friend class KDTree;

        Iterator() = delete;

        Iterator(const Iterator &) = default;

        Iterator &operator=(const Iterator &) = default;

        Iterator &operator++() {
            increment();
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            increment();
            return temp;
        }

        Iterator &operator--() {
            decrement();
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            decrement();
            return temp;
        }

        bool operator==(const Iterator &that) const {
            return node == that.node;
        }

        bool operator!=(const Iterator &that) const {
            return node != that.node;
        }

        Data *operator->() {
            return &(node->data);
        }

        Data &operator*() {
            return node->data;
        }
    };

protected:                      // DO NOT USE private HERE!
    Node *root = nullptr;       // root of the tree
    size_t treeSize = 0;        // size of the tree

    /**
     * Find the node with key
     * Time Complexity: O(k log n)
     * @tparam DIM current dimension of node
     * @param key
     * @param node
     * @return the node with key, or nullptr if not found
     */
    template<size_t DIM>
    Node *find(const Key &key, Node *node) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        // TODO: implement this function
        if (node == nullptr) {
            return nullptr;
        }
        if (key == node->data.first) {
            return node;
        }
        if (compareKey<DIM, std::less<>>(key, node->data.first)) {
            return find<DIM_NEXT>(key, node->left);
        } else {
            return find<DIM_NEXT>(key, node->right);
        }
    }

    /**
     * Insert the key-value pair, if the key already exists, replace the value only
     * Time Complexity: O(k log n)
     * @tparam DIM current dimension of node
     * @param key
     * @param value
     * @param node
     * @param parent
     * @return whether insertion took place (return false if the key already exists)
     */
    template<size_t DIM>
    bool insert(const Key &key, const Value &value, Node *&node, Node *parent) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        // TODO: implement this function
        if (node == nullptr) {
            node = new Node(key, value, parent);
            this->treeSize++;
            return true;
        }
        if (key == node->data.first) {
            node->data.second = value;
            return false;
        }
        if (compareKey<DIM, std::less<>>(key, node->data.first)) {
            return insert<DIM_NEXT>(key, value, node->left, node);
        } else {
            return insert<DIM_NEXT>(key, value, node->right, node);
        }
    }

    /**
     * Compare two keys on a dimension
     * Time Complexity: O(1)
     * @tparam DIM comparison dimension
     * @tparam Compare
     * @param a
     * @param b
     * @param compare
     * @return relationship of two keys on a dimension with the compare function
     */
    template<size_t DIM, typename Compare>
    static bool compareKey(const Key &a, const Key &b, Compare compare = Compare()) {
        if (std::get<DIM>(a) != std::get<DIM>(b)) {
            return compare(std::get<DIM>(a), std::get<DIM>(b));
        }
        return compare(a, b);
    }

    /**
     * Compare two nodes on a dimension
     * Time Complexity: O(1)
     * @tparam DIM comparison dimension
     * @tparam Compare
     * @param a
     * @param b
     * @param compare
     * @return the minimum / maximum of two nodes
     */
    template<size_t DIM, typename Compare>
    static Node *compareNode(Node *a, Node *b, Compare compare = Compare()) {
        if (!a) return b;
        if (!b) return a;
        return compareKey<DIM, Compare>(a->key(), b->key(), compare) ? a : b;
    }

    /**
     * Find the minimum node on a dimension
     * Time Complexity: ?
     * @tparam DIM_CMP comparison dimension
     * @tparam DIM current dimension of node
     * @param node
     * @return the minimum node on a dimension
     */
    template<size_t DIM_CMP, size_t DIM>
    Node *findMin(Node *node) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        // TODO: implement this function
        if (node == nullptr) {
            return nullptr;
        }
        Node *min = findMin<DIM_CMP, DIM_NEXT>(node->left);
        if (DIM_CMP != DIM) {
            Node *rightMin = findMin<DIM_CMP, DIM_NEXT>(node->right);
            min = compareNode<DIM_CMP, std::less<>>(min, rightMin);
        }
        return compareNode<DIM_CMP, std::less<>>(min, node);
    }

    /**
     * Find the maximum node on a dimension
     * Time Complexity: ?
     * @tparam DIM_CMP comparison dimension
     * @tparam DIM current dimension of node
     * @param node
     * @return the maximum node on a dimension
     */
    template<size_t DIM_CMP, size_t DIM>
    Node *findMax(Node *node) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        // TODO: implement this function
        if (node == nullptr) {
            return nullptr;
        }
        Node *max = findMax<DIM_CMP, DIM_NEXT>(node->right);
        if (DIM_CMP != DIM) {
            Node *leftMax = findMax<DIM_CMP, DIM_NEXT>(node->left);
            max = compareNode<DIM_CMP, std::greater<>>(max, leftMax);
        }
        return compareNode<DIM_CMP, std::greater<>>(max, node);
    }

    template<size_t DIM>
    Node *findMinDynamic(size_t dim) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        if (dim >= KeySize) {
            dim %= KeySize;
        }
        if (dim == DIM) return findMin<DIM, 0>(root);
        return findMinDynamic<DIM_NEXT>(dim);
    }

    template<size_t DIM>
    Node *findMaxDynamic(size_t dim) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        if (dim >= KeySize) {
            dim %= KeySize;
        }
        if (dim == DIM) return findMax<DIM, 0>(root);
        return findMaxDynamic<DIM_NEXT>(dim);
    }

    /**
     * Erase a node with key (check the pseudocode in project description)
     * Time Complexity: max{O(k log n), O(findMin)}
     * @tparam DIM current dimension of node
     * @param node
     * @param key
     * @return nullptr if node is erased, else the (probably) replaced node
     */
    template<size_t DIM>
    Node *erase(Node *node, const Key &key) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        // TODO: implement this function
        if (node == nullptr) {
            return nullptr;
        }
        if (key == node->data.first) {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                this->treeSize--;
                return nullptr;
            } else if (node->right != nullptr) { // root not change
                Node *minNode = findMin<DIM, DIM_NEXT>(node->right);
                Key *tmp = const_cast<Key *> (&(node->key()));
                *tmp = *(const_cast<Key *> (&(minNode->key())));
                node->data.second = minNode->value();
                node->right = erase<DIM_NEXT>(node->right, minNode->data.first);
            } else {
                Node *maxNode = findMax<DIM, DIM_NEXT>(node->left);
                Key *tmp = const_cast<Key *> (&(node->key()));
                *tmp = *(const_cast<Key *> (&(maxNode->key())));
                node->data.second = maxNode->value();
                node->left = erase<DIM_NEXT>(node->left, maxNode->data.first);
            }
        } else {
            if (compareKey<DIM, std::less<>>(key, node->data.first)) {
                node->left = erase<DIM_NEXT>(node->left, key);
            } else {
                node->right = erase<DIM_NEXT>(node->right, key);
            }
        }
        return node;
    }

    template<size_t DIM>
    Node *eraseDynamic(Node *node, size_t dim) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        if (dim >= KeySize) {
            dim %= KeySize;
        }
        if (dim == DIM) return erase<DIM>(node, node->key());
        return eraseDynamic<DIM_NEXT>(node, dim);
    }

    // TODO: define your helper functions here if necessary
    template<size_t DIM>
    static bool cmp(const std::pair<Key, Value> &s1, const std::pair<Key, Value> &s2) {
        return compareKey<DIM, std::less<>>(s1.first, s2.first);  // only sort on Key
    }

    static bool uniqueRule(const std::pair<Key, Value> &s1, const std::pair<Key, Value> &s2) {
        return s1.first == s2.first;
    }

    template<size_t DIM>
    void removeDuplicated(std::vector<std::pair<Key, Value>> &v) {
        stable_sort(v.begin(), v.end(), cmp<DIM>);
        auto last = unique(v.rbegin(), v.rend(), uniqueRule);
        v.erase(v.begin(), last.base());
    }

    template<size_t DIM>
    Node *initKDTree(std::vector<std::pair<Key, Value>> v, Node *parent) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        // TODO: implement this function
        if (v.empty()) {
            return nullptr;
        }
        auto m = v.begin() + (v.size()) / 2;
        std::nth_element(v.begin(), m, v.end(), cmp<DIM>);
        Data newData = v.at((v.size()) / 2);
        Node *node;
        node = new Node(newData.first, newData.second, parent);
        node->parent = parent;
        std::vector<std::pair<Key, Value>> left(v.begin(), m);
        std::vector<std::pair<Key, Value>> right(m + 1, v.end());
        node->left = initKDTree<DIM_NEXT>(left, node);
        node->right = initKDTree<DIM_NEXT>(right, node);
        return node;
    }

public:
    KDTree() = default;

    /**
     * Time complexity: O(kn log n)
     * @param v we pass by value here because v need to be modified
     */
    explicit KDTree(std::vector<std::pair<Key, Value>> v) {
        // TODO: implement this function
        if (!v.empty()) {
            removeDuplicated<0>(v);
            root = initKDTree<0>(v, nullptr);
            treeSize = v.size();
        }
    }

    /**
     * Time complexity: O(n)
     */
    KDTree(const KDTree &that) {
        // TODO: implement this function
        if (this->treeSize != 0) {
            std::queue<Node *> all;
            for (auto it = this->begin(); it != this->end(); ++it) {
                all.push(it.node);
            }
            while (!all.empty()) {
                Node *visit = all.front();
                all.pop();
                visit->right = nullptr;
                visit->left = nullptr;
                visit->parent = nullptr;
                delete visit;
                this->treeSize--;
            }
            this->root= nullptr;
        }
        std::queue<Node *> bf;
        bf.push(that.root);
        while (!bf.empty()) {
            Node *visit = bf.front();
            bf.pop();
            this->insert<0>(visit->key(), visit->value(), this->root, nullptr);
            if (visit->left != nullptr) {
                bf.push(visit->left);
            }
            if (visit->right != nullptr) {
                bf.push(visit->right);
            }
        }
        treeSize = that.treeSize;
    }

    /**
     * Time complexity: O(n)
     */
    KDTree &operator=(const KDTree &that) {
        // TODO: implement this function
        if (this->treeSize != 0) {
            std::queue<Node *> all;
            for (auto it = this->begin(); it != this->end(); ++it) {
                all.push(it.node);
            }
            while (!all.empty()) {
                Node *visit = all.front();
                all.pop();
                visit->right = nullptr;
                visit->left = nullptr;
                visit->parent = nullptr;
                delete visit;
                this->treeSize--;
            }
            this->root= nullptr;
        }
        std::queue<Node *> bf;
        bf.push(that.root);
        while (!bf.empty()) {
            Node *visit = bf.front();
            bf.pop();
            this->insert<0>(visit->key(), visit->value(), this->root, nullptr);
            if (visit->left != nullptr) {
                bf.push(visit->left);
            }
            if (visit->right != nullptr) {
                bf.push(visit->right);
            }
        }
        treeSize = that.treeSize;
        return *this;
    }

    /**
     * Time complexity: O(n)
     */
    ~KDTree() {
        // TODO: implement this function
        std::queue<Node *> bf;
        bf.push(this->root);
        while (!bf.empty()) {
            Node *visit = bf.front();
            bf.pop();
            if (visit->left != nullptr) {
                bf.push(visit->left);
            }
            if (visit->right != nullptr) {
                bf.push(visit->right);
            }
            delete visit;
        }
    }

    Iterator begin() {
        if (!root) return end();
        auto node = root;
        while (node->left) node = node->left;
        return Iterator(this, node);
    }

    Iterator end() {
        return Iterator(this, nullptr);
    }

    Iterator find(const Key &key) {
        return Iterator(this, find<0>(key, root));
    }

    void insert(const Key &key, const Value &value) {
        insert<0>(key, value, root, nullptr);
    }

    template<size_t DIM>
    Iterator findMin() {
        return Iterator(this, findMin<DIM, 0>(root));
    }

    Iterator findMin(size_t dim) {
        return Iterator(this, findMinDynamic<0>(dim));
    }

    template<size_t DIM>
    Iterator findMax() {
        return Iterator(this, findMax<DIM, 0>(root));
    }

    Iterator findMax(size_t dim) {
        return Iterator(this, findMaxDynamic<0>(dim));
    }

    bool erase(const Key &key) {
        auto prevSize = treeSize;
        erase<0>(root, key);
        return prevSize > treeSize;
    }

    Iterator erase(Iterator it) {
        if (it == end()) return it;
        auto node = it.node;
        if (!it.node->left && !it.node->right) {
            it.node = it.node->parent;
        }
        size_t depth = 0;
        auto temp = node->parent;
        while (temp) {
            temp = temp->parent;
            ++depth;
        }
        eraseDynamic<0>(node, depth % KeySize);
        return it;
    }

    size_t size() const { return treeSize; }
};
