//Lecture 19 – Trees, Part III

//PREVIOUS LECTURE(S) REVIEW
/*
- Overview of the ds set implementation
- begin, find, destroy_tree, insert
- In-order, pre-order, and post-order traversal; breadth-first + depth-first tree search
- Iterator implementation: Finding in-order successor to node: add parent pointers / add list/vector/stack of pointers to iterator
- Ropes overview
*/


//OVERVIEW
/*
- Last piece of ds_set: removing an item, erase
- Breadth-first and depth-first tree search
- Tree height, longest-shortest paths, breadth-first search
- Erase with parent pointers, increment operation on iterators
- Limitations of our ds set implementation
*/


//19.1 ds set Warmup/Review Exercises
/*
- Draw diagram of possible memory layout for ds_set containing 16, 2, 8, 11, and 5; is there only one valid memory layout for this data as
   ds_set? Why? (NOTE: This is different from drawing the tree, the structure behind it - Just)
|int|
|---|
|2  |
|5  |
|8  |
|11 |
|16 |

- In what order should forward iterator visit data? Draw abstract table representation of this data; omit TreeNode memory layout details
*/


//19.2 Erase
/*
- First we need to find the node to remove; once it is found, actual removal is easy if node has no children / only one child
(Draw picture of each case!)
- It is harder if there are two children:
   - Find node with greatest value in left subtree / node with smallest value in right subtree
   - Value in this node may be safely moved into current node because of tree ordering
   - Then, recursively apply erase to remove that node, which is guaranteed to have at most one child

- Exercise: Write a recursive version of erase:*/

/*
- Exercise: How does the order nodes are deleted in affect tree structure? Starting with mostly balanced tree, give erase ordering that
   yields an unbalanced tree:
ANSWER: 15, 14, 13, 12, 11, 10, 9 - root would be pointing to different nodes almost every time
*/


//19.3 Depth-first vs. Breadth-first Search
/*
- We should also discuss two other important tree traversal terms related to problem solving + searching:
   - In DEPTH-FIRST search, we greedily follow links down into the tree + don’t backtrack until we reach leaf
      - When leaf hit, we step back out, but only to LAST DECISION POINT, then proceed to next leaf
      - This search method quickly investigates leaf nodes, but if it has made an “incorrect” branch decision early in searching, it will
         take long time to work back to that point + go down “correct” branch
   
   - In BREADTH-FIRST search, nodes are visited with priority based on distance from root, with nodes closer to root visited first
      - In other words, we visit nodes by level: first root (level 0), then all children of root (level 1), then all children of those
         nodes (level 2), etc. - essentially reading all nodes form left ot right, from top to bottom
      - If multiple solution nodes, search method will find solution node with shortest path to root node
      - However, breadth-first search method memory-intensive since implementation must store all nodes at current level –  worst case,
      number of nodes on each level doubles as we progress down the tree

- Both depth-first + breadth-first will eventually visit all elements in tree
- Note: Ordering of elements visited by depth-first + breadth-first not fully specified
   - In-order, pre-order, and post-order are all examples of depth-first tree traversals
   - Note: Simple recursive tree function usually depth-first traversal
   - What is breadth-first traversal of elements in our sample binary search trees above?
*/


//19.4 General-Purpose Breadth-First Search/Tree Traversal
/*
- Write an algorithm to print nodes in tree one tier at a time, that is, in breadth-first manner:*/
template <class T>
void breadth_first(TreeNode<T>* p) {
   std::vector<TreeNode<T>*> current;
   std::vector<TreeNode<T>*> next;

   // handle empty tree by leaving current empty
   if (p!=NULL) {current.push_back(p);}

   // loop over all levels of the tree
   while (curent.size() > 0) {
      // loop over all elemetns in the level
      for (in x=0 ; x<current.size() ; ++x) {
         std::cout<<" "<<current[x]->value; // "do something part of traversal"
         if (current[x]->left!=NULL) {next.push_back(current[x]->left);}
         if (current[x]->right!=NULL) {next.push_back(current[x]->right);}
      }

      // switch to next level, empty next vector to receive following level
      current = next;
      next.clear();
   }
}

/*
- What is best/average/worst-case running time of this algorithm? What is best/average/worst-case memory usage of this algorithm? Give
   specific example tree that illustrates each case:
ANSWER: 
*/


//19.5 Height and Height Calculation Algorithm
/*
- Height of node in tree = length of longest path down tree from that node to leaf node; Leaf height = 1
   - We will think of height of null pointer as 0
- Height of tree = height of root node; therefore, if tree is empty, height = 0

- Exercise: Write a simple recursive algorithm to calculate the height of a tree:*/
int get_height(TreeNode<T>* root, int height) {
   if (!root) {return 0;}

   if (!root-> && !root->right) {return height;}

   //option 1
   return (std::max(get_height(root->left, height+1), get_height(root->right, height+1)));
   //option 2
   int left_height = get_height(root->left, height+1);
   int right_height = get_height(root->right, height+1);
   return std::max(left_height, rihgt_height);
   // both do the same thing
}

// driver function
int get height(TreeNode<T>* root) {
   return get_height(root, 0);
}

/*
- What is best/average/worst-case running time of this algorithm? What is best/average/worst-case memory usage of this algorithm? Give
   specific example tree that illustrates each case
ANSWER: 
*/


//19.6 Shortest Paths to Leaf Node
/*
- Exercise: Write function to instead calculate shortest path to NULL child pointer:*/
int shortest(TreeNode<T>* root, int height) {
   if (!root) {return 0;}

   if (!root-> && !root->right) {return height;}

   //option 1
   return (std::min(shortest(root->left, height+1), shortest(root->right, height+1)));
   //option 2
   int left_height = shortest(root->left, height+1);
   int right_height = shortest(root->right, height+1);
   return std::min(left_height, rihgt_height);
   // both do the same thing
}

// driver function
int get height(TreeNode<T>* root) {
   return shortest(root, 0);
}

/*
- What is running time of this algorithm? Can we do better? Hint: How does breadth-first vs. depth-first algo. for this problem compare?
ANSWER: 
*/


//19.7 Erase (now with parent pointers)
/*
- If we choose to use parent pointers, we need to add to Node representation, and re-implement several ds_set member functions

- Exercise: Study the new version of insert, with parent pointers
- Exercise: Rewrite erase, now with parent pointers:*/




// -------------------------------------------------------------------
// TREE NODE CLASS
template <class T>
class TreeNode {
   public:
      TreeNode() : left(NULL), right(NULL), parent(NULL) {}
      TreeNode(const T& init) : value(init), left(NULL), right(NULL), parent(NULL) {}
      
      T value;
      TreeNode* left;
      TreeNode* right;
      TreeNode* parent; // to allow implementation of iterator increment & decrement
};

template <class T> class ds_set;


// -------------------------------------------------------------------
// TREE NODE ITERATOR CLASS
template <class T>
class tree_iterator {
   public:
      tree_iterator() : ptr_(NULL), set_(NULL) {}
      tree_iterator(TreeNode<T>* p, const ds_set<T> * s) : ptr_(p), set_(s) {}
      
      // operator* gives constant access to the value at the pointer
      const T& operator*() const { return ptr_->value; }
      // comparions operators are straightforward
      bool operator== (const tree_iterator& rgt) { return ptr_ == rgt.ptr_; }
      bool operator!= (const tree_iterator& rgt) { return ptr_ != rgt.ptr_; }
      
      // increment & decrement operators
      tree_iterator<T> & operator++() {
         if (ptr_->right != NULL) { // find the leftmost child of the right node
            ptr_ = ptr_->right;
            while (ptr_->left != NULL) { ptr_ = ptr_->left; }
         }
         else { // go upwards along right branches... stop after the first left
            while (ptr_->parent != NULL && ptr_->parent->right == ptr_) { ptr_ = ptr_->parent; }
            ptr_ = ptr_->parent;
         }
         return *this;
      }
      tree_iterator<T> operator++(int) { tree_iterator<T> temp(*this); ++(*this); return temp; }
      tree_iterator<T> & operator--() {
         if (ptr_ == NULL) { // so that it works for end()
            assert (set_ != NULL);
            ptr_ = set_->root_;
            while (ptr_->right != NULL) { ptr_ = ptr_->right; }
         }
         else if (ptr_->left != NULL) { // find the rightmost child of the left node
            ptr_ = ptr_->left;
            while (ptr_->right != NULL) { ptr_ = ptr_->right; }
         }
         else { // go upwards along left brances... stop after the first right
            while (ptr_->parent != NULL && ptr_->parent->left == ptr_) { ptr_ = ptr_->parent; }
            ptr_ = ptr_->parent;
         }
         return *this;
      }
      tree_iterator<T> operator--(int) { tree_iterator<T> temp(*this); --(*this); return temp; }
   
   private:
      // representation
      TreeNode<T>* ptr_;
      const ds_set<T>* set_;
};


// -------------------------------------------------------------------
// DS_ SET CLASS
template <class T>
class ds_set {
   public:
      ds_set() : root_(NULL), size_(0) {}
      ds_set(const ds_set<T>& old) : size_(old.size_) { root_ = this->copy_tree(old.root_,NULL); }
      ~ds_set() { this->destroy_tree(root_); root_ = NULL; }
      
      ds_set& operator=(const ds_set<T>& old) {
         if (&old != this) {
            this->destroy_tree(root_);
            root_ = this->copy_tree(old.root_,NULL);
            size_ = old.size_;
         }
         return *this;
      }

      typedef tree_iterator<T> iterator;
      friend class tree_iterator<T>;
      
      int size() const { return size_; }
      bool operator==(const ds_set<T>& old) const { return (old.root_ == this->root_); }
      
      // FIND, INSERT & ERASE
      iterator find(const T& key_value) { return find(key_value, root_); }
      std::pair< iterator, bool > insert(T const& key_value) { return insert(key_value, root_, NULL); }
      int erase(T const& key_value) { return erase(key_value, root_); }
      
      // ITERATORS
      iterator begin() const {
         if (!root_) {return iterator(NULL,this);}
         
         TreeNode<T>* p = root_;
         while (p->left) {p = p->left;}
         return iterator(p,this);
      }
      iterator end() const { return iterator(NULL,this); }

   private:
      // REPRESENTATION
      TreeNode<T>* root_;
      int size_;

      // PRIVATE HELPER FUNCTIONS
      TreeNode<T>* copy_tree(TreeNode<T>* old_root, TreeNode<T>* the_parent) {
         if (old_root == NULL) {return NULL;}
         TreeNode<T> *answer = new TreeNode<T>();
         answer->value = old_root->value;
         answer->left = copy_tree(old_root->left,answer);
         answer->right = copy_tree(old_root->right,answer);
         answer->parent = the_parent;
         return answer;
      }
      void destroy_tree(TreeNode<T>* p) {
         if (!p) {return;}
         
         destroy_tree(p->right);
         destroy_tree(p->left);
         delete p;
      }
      iterator find(const T& key_value, TreeNode<T>* p) {
         if (!p) {return end();}
         
         if (p->value > key_value) {return find(key_value, p->left);}
         else if (p->value < key_value) {return find(key_value, p->right);}
         else {return iterator(p,this);}
      }
      std::pair<iterator,bool> insert(const T& key_value, TreeNode<T>*& p, TreeNode<T>* the_parent) {
         if (!p) {
            p = new TreeNode<T>(key_value);
            p->parent = the_parent;
            this->size_++;
            return std::pair<iterator,bool>(iterator(p,this), true);
         }
         else if (key_value < p->value) {return insert(key_value, p->left, p);}
         else if (key_value > p->value) {return insert(key_value, p->right, p);}
         else {return std::pair<iterator,bool>(iterator(p,this), false);}
      }
      int erase(T const& key_value, TreeNode<T>* &p) {
         if (!p) {return 0;}

         // look left+right
         if (p->value < key_value) {
            return erase(key_value, p->right);
         }
         else if (p->value > key_value) {
            return erase(key_value, p->left);
         }

         // found node - let's delete it
         assert(p->value == key_value);
         if (!p->left && !p->right) { // is leaf
            delete p;
            p=NULL;
            this->size_--;
         }
         else if (!p->left) { // no right child
            TreeNode<T>* q = p;
            p = p->right;
            assert(p->parent == q);
            p->parent = q->parent;
            delete q;
            this->size_--;
         }
         else if (!p->right) { // no left child
            TreeNode<T>* q = p;
            p = p->left;
            assert(p->parent == q);
            p->parent = q->parent;
            delete q;
            this->size_--;
         }
         else {
            TreeNode<T>* q = p->left;
            while (q->right) {q = q->right;}
            p->value = q->value;
            // recursively remove the value from left subtree
            int check = erase(q->value, p->left);
            assert(check==1);
         }
         return 1;
      }
};