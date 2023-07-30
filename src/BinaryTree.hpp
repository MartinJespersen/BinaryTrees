typedef struct Node{
    int number;
    Node *right;
    Node *left;
    Node* parent;
    int balancefactor = 0;
} Node;

const int N = 100;
typedef struct Container{
    int arr[N];
    int count;
} Container;


class BinaryTree{
    
    public:

    BinaryTree(int num, bool allowUnbalancedTree = true){
        _root = new Node{num};
        _allowUnbalancedTree = allowUnbalancedTree;
    }

    BinaryTree( bool allowUnbalancedTree = true){
        _allowUnbalancedTree = allowUnbalancedTree;
    };

    ~BinaryTree(){
        //should delete all Nodes in Tree.
    }
    Node* _root;
    bool _allowUnbalancedTree;
    
    void Preorder(Node* curNode, Container& container);

    bool BinaryTree::Insert(int num);

    bool InsertArr(int arr[], int count);

    void PrintContainer(Container& container);

    int* createRandomArr(const int count);

    Node* Find(int num);

    bool Delete(int num);

    void RotationCounterClockwise(Node* node);
    
    void RotationClockwise(Node* node);

    private:
    
    Node* Find(Node* node, int num);
    
    bool Insert(Node* curNode, int num);

    bool Delete(Node* root, int num);

    void UpdateBalanceFactor(Node* insertedNode);

    void RebalanceRightTree(Node* node);

    void RebalanceLeftTree(Node* node);

    void DeleteLeftSubTree(Node* node, Node* root);

    void DeleteRightSubTree(Node* node, Node* root);
};