//
// Created by shh03 on 2020/12/5.
//

#ifndef BINARYSORTTREE_H
#define BINARYSORTTREE_H

#include <stdlib.h>
#include <stdio.h>



typedef int KeyType; //键类型定义
//typedef char DataType; //数据类型定义

//记录类型定义
typedef struct Record {
    KeyType key; //键
    // DataType data;
} Record;

typedef Record RcdType;

//BST结点定义
typedef struct BSTNode {
    RcdType rcd;
    struct BSTNode *lchild,  *rchild;
} BSTNode, *BSTNodePtr;




/*
 * InitBST: 初始化BST
 * @return: 返回一颗空的BST根节点指针
 * */
BSTNodePtr InitBST();

/*
 * CreateBSTbyArray: 根据Record数组创建BST
 * @param r: 记录数组名
 * @param len: 数组长度
 */
BSTNodePtr CreateBSTbyArray(Record *r, int len);

/*
 * DestroyBST: 递归销毁参数BST
 * @param: BSTNodePtr nodep: 外部调用时，此参数应为根节点指针
 */
void DestroyBST(BSTNodePtr nodep);

/*
 * SearchBST: 在树中递归查找一个键
 * @param BSTNodePtr nodep: 外部调用时，此参数应为根节点指针
 * @param KeyType key: 要查找的键
 * @return BSTNodePtr: 返回记录指针
 */
BSTNodePtr SearchBST(BSTNodePtr nodep, KeyType key);

/*
 * InsertBST: 递归插入一个元素
 * @param BSTNodePtr * nodep: 外部调用时，此参数应为根节点指针的地址
 * @param RcdType rcd: 要插入的记录
 * @return int: 成功返回1，重复返回0，错误返回-1;
 */
int InsertBST(BSTNodePtr *nodepp, RcdType rcd);

/*
 * DeleteBSTNode: 根据键删除BST结点
 * @param BSTNodePtr nodep: 外部调用时，此参数应为根节点指针
 */
void DeleteNodeBST(BSTNodePtr nodep, KeyType key);

/*
 * MiddleOrderBST: 中序遍历
 * @param BSTNodePtr nodep: 外部调用时，此参数应为根节点指针
 * */
void MiddleOrderBST(BSTNodePtr nodep);

/* 
 * _MiddleOrderBST: 仅供MiddleOrderBST函数调用
 * @param BSTNodePtr nodep: 结点指针
 */
void _MiddleOrderBST(BSTNodePtr nodep);

/*
 * SearchMaxBST: 找到BST中记录中键最大的结点
 * @param BSTNodePtr nodep: 外部调用时，此参数应为根节点指针
 * @return BSTNodePtr: 返回查找到的结点
 */
BSTNodePtr SearchMaxBST(BSTNodePtr nodep);

/*
 * SearchMaxBST: 找到BST中记录中键最小的结点
 * @param BSTNodePtr nodep: 外部调用时，此参数应为根节点指针
 * @return BSTNodePtr: 返回查找到的结点
 */
BSTNodePtr SearchMinBST(BSTNodePtr nodep);

#endif //BINARYSORTTREE_H
