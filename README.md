# operation_binary_search_tree
•	Define a binary search tree class called BinTree, and do the relevant operations about BinTree;
•	Multiple-kind constructors, use proper destructor to make sure no memory leak; Use recursive helper methods to realize overload =, ==, !=, getting node height, doing tree operations.

Specific: 
Develop the class:
1. A default constructor (creates an empty tree), a copy constructor (deep copy), and destructor.
2. Overload operators:
(a). The assignment operator (=) to assign one tree to another.
(b). The equality and inequality operators (==, !=). Define two trees to be equal if they have the
same data and same structure. 
3. Accessors:
(a). Overload << to display the tree using inorder traversal. The NodeData class is responsible for
displaying its own data.
(b). retrieve function to get the NodeData* of a given object in the tree (via pass-by-reference
parameter) and to report whether the object is found (true or false).
bool retrieve(const NodeData &, NodeData* &);
The 2nd parameter in the function signature may initially be garbage. Then if the object is found, it
will point to the actual object in the tree.
(c). getHeight function to find the height of a given value in the tree. SPECIAL INSTRUCTION:
For this function only, you do not get to know that the tree is a binary search tree. You must solve
the problem for a general binary tree where data could be stored anywhere (e.g., tree T4 above).
Use this height definition: the height of a node at a leaf is 1, height of a node at the next level is
2, and so on. The height of a value not found is zero.
int getHeight (const NodeData &) const;
4. Others:
(a). bstreeToArray function to fill an array of Nodedata* by using an inorder traversal of the
tree. It leaves the tree empty. (Since this is just for practice, assume a statically allocated array of
100 NULL elements. No size error checking necessary.)
void bstreeToArray(NodeData* []);
After the call to bstreeToArray, the tree in Figure 1 should be empty and the array should be
filled with
and, eee, ff, iii, jj, m, not, ooo, pp, r, sssss, tttt, y, z (in this order)
Figure 2. bstreeToArray result for the example tree
(b). arrayToBSTree function to builds a balanced BinTree from a sorted array of NodeData*
leaving the array filled with NULLs. The root (recursively) is at (low+high)/2 where low is the
lowest subscript of the array range and high is the highest.
void arrayToBSTree(NodeData* []);
