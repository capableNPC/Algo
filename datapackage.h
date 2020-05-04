#ifndef DATAPACKAGE_H
#define DATAPACKAGE_H

#include <QStringList>
#include <QObject>
#include <QVector>
#include <QEasingCurve>

namespace data {
Q_NAMESPACE
enum AlgoType {
        None = 0,
        List,
        Array,
        LinearChainTable,
        Two_wayChainTable,
        CircularChainTable,
        Stack,
        LinearQueue,
        CircularQueue,
        HashTable,
        BinaryTree = 10,
        BinarySearchTree,
        BalancedBinaryTree,
        RedAndBlackTree,
        HuffmanTree,
        Muitl_waySearchTree,
        BTree,
        B_Tree,//B-Tree
        B__Tree,//B_Tree
        BStarTree,
        BPlusTree = 20,
        BPlusPlusTree,
        RTree,
        Heap,
        String,
        ArrayRepresentationGraph,
        Neighbor_joiningMethodGraph,
        OrthogonalListGraph,
        AdjacencyMultilistGraph,
        //InternalSorting,
        //RadixSort,
        SortingOfMultipleKeywords,
        ChainRadixSort = 30,
        //MergeSort,
        Two_wayMergeSort,
        //SelectionSort,
        SimpleSelectionSort,
        TreeSelectionSort,
        HeapSort,
        QuickSort,
        //InsertionSort,
        DirectSnsertionSort,
        SplitInsertionSort,
        Two_wayInsertionSort,
        TableInsertionSort,
        ShellSort = 40,
        //ExternalSorting,
        Permutation_SelectionSort,
        OptimalMergeTree,
        //GraphSearch,
        //ArraySearch,
        OutOfOrderSearch,
        BinarySearch,
        OutOfOrderChainTableSearch,
        OrderChainTableSearch,
        //BinaryTree,
        DLRSearch,
        LDRSearch,
        LRDSearch,
        //Graph,
        BFS = 50,
        DFS,
        TopologicalSort,
        CriticalPath,
        ShortestPath,
        AStarSearchAlgorithm,
        StringMatch,
        TowerOfHanoi,
        DivisionAlgorithm,
        PrimalityTesting,
        FibonacciSequence = 60,
        //DataCompression,
        Run_LengthCoding,
        HuffmanCode,
        //Security,
        HashFunction,
        PublicKeyEncryption,
        MixedEncryption,
        Diffi_HermannKeyExchange,
        MessageAuthenticationCode,
        DigitalSignature,
        DigitalCertificate,
        K_MeansAlgorithm_Cluster = 70,
        PageRank_Network
    };
Q_ENUM_NS(AlgoType);
Q_DECLARE_FLAGS(AlgoTypes, AlgoType)
Q_FLAG_NS(AlgoTypes)
Q_DECLARE_OPERATORS_FOR_FLAGS(AlgoTypes)
enum OrderType{
    chaos = 0,
    acs,
    des
};

struct Config{
    QStringList data;
    OrderType order;
    bool fill = false;
    bool normalView = true;
    bool configState = false;
    bool hasArrow = false;
};

struct CommandType{
    bool Nop;
    bool Auto;
    bool Stop;
    bool Abort;
    bool Debug;
    bool StopDebug;
    bool Next;
    bool Jump;
    bool StepEnter;
    bool JumpFunction;
    bool NextStatement;
    bool EnterStatement;
};
/*
enum CommandType{
    Nop = 0,
    Auto,
    Stop,
    Abort,
    Debug,
    StopDebug,
    Next,
    Jump,
    StepEnter,
    JumpFunction,
    NextStatement,
    EnterStatement
};
*/

enum ShapeType {
    Circle,
    CircleColumn,
    Rectangle,
    RectangleColumn,
    Square,
    ChainTableRight,
    ChainTableLeft,
    ChainTableDouble,
};

struct DataOfLinear{
    ShapeType type;
    QString value;
    int id;
    int ImmediatePrecursor;
    int ImmediateSuccessors;
};

struct DataOfTree{
    ShapeType type;
};

struct DataOfAnimation{
    int firstItem;
    int secondItem;
    QEasingCurve::Type CurveType;
};

}
















#endif // DATAPACKAGE_H
