//
// Created by shh03 on 2020/12/5.
//

#include "BinarySortTree.h"


BSTNodePtr InitBST() {
    BSTNodePtr * rootPtr = (BSTNodePtr *)malloc(sizeof(BSTNode));
    *rootPtr = NULL;

    return *rootPtr;
}

void DestroyBST(BSTNodePtr nodep) {
    
    if (!nodep) return;
    else {
        DestroyBST(nodep->lchild);
        DestroyBST(nodep->rchild);
        free(nodep);
    }
}

BSTNodePtr CreateBSTbyArray(Record *r, int len) {

    // if (len == 0) return NULL;
    // BSTNodePtr root = NULL;
    // root = InsertBST(root, r[0]);
    
    // for (int i=1; i<len; i++) {
    //     InsertBST(root, r[i]);
    // }
    
    // return root;

    BSTNodePtr * rootPtr = (BSTNodePtr *)malloc(sizeof(BSTNode));
    *rootPtr = NULL;

    for (int i=0; i<len; i++) {
        InsertBST(rootPtr, r[i]);
    }

    return *rootPtr;
}

/* Record * SearchBST(BSTNodePtr nodep, KeyType key) {

    if(!nodep) {
        puts("Key not found!");
        return NULL;
    }

    else if (key == nodep->rcd.key) {
        Record r = nodep->rcd;
        return r;
    }
    else if (key > nodep->rcd.key)
        SearchBST(nodep->rchild, key);
    else
        SearchBST(nodep->lchild, key);
} */

BSTNodePtr SearchBST(BSTNodePtr nodep, KeyType key) {

    if(!nodep) {
        puts("Key not found!");
        return NULL;
    }

    else if (key == nodep->rcd.key) {
        return nodep;
    }
    else if (key > nodep->rcd.key)
        SearchBST(nodep->rchild, key);
    else
        SearchBST(nodep->lchild, key);
}

int InsertBST(BSTNodePtr *nodepp, RcdType rcd) {

    if (*nodepp==NULL) {
        BSTNodePtr newNodep = (BSTNodePtr)malloc(sizeof(BSTNode));
        if(!newNodep) {
            puts("[InsertBST]Fail to malloc!");
            return -1;
        }
        newNodep->rcd = rcd;
        newNodep->lchild = NULL; newNodep->rchild = NULL;
        *nodepp = newNodep;
        return 1;
    }

    if (rcd.key == (*nodepp)->rcd.key) {
        printf("[InsertBST]Key(%d) found already existed in BST!\n",(*nodepp)->rcd.key);
        return 0;
    }
    else if (rcd.key > (*nodepp)->rcd.key)
        InsertBST(&((*nodepp)->rchild), rcd);
    else
        InsertBST(&((*nodepp)->lchild), rcd);
}

void DeleteNodeBST(BSTNodePtr root, KeyType key) {
    
    BSTNodePtr nodep = root; //待删除结点
    BSTNodePtr nodepParent = NULL; //结点的父结点

    // 循环查找结点
    while (nodep != NULL && nodep->rcd.key != key) {
        nodepParent = nodep;
        if(key > nodep->rcd.key) nodep = nodep->rchild;
        else nodep = nodep->lchild;
    }

    //没有找到
    if(nodep == NULL) return;

    //情况1，要删除的结点有两个子结点
    if (nodep->lchild != NULL && nodep->rchild != NULL) {
        BSTNodePtr rMinNodep = nodep->rchild; // 要删除结点的右子树上的最小结点
        nodepParent = nodep; // 要删除结点的右子树上的最小结点的父结点
        //循环查找要删除结点的右子树上的最小结点
        while (rMinNodep->lchild != NULL) {
            nodepParent = rMinNodep;
            rMinNodep = rMinNodep->lchild;
        }
        // 替换待删除结点的记录
        nodep->rcd = rMinNodep->rcd;
        //此时要删除[要删除结点的右子树上的最小结点(rMinNodep)]，此节点必定没有左结点，进入情况2
        nodep = rMinNodep;
    }

    //情况2，待删除结点是叶子结点或只有一个子结点
    BSTNodePtr childp = NULL;
    if (nodep->lchild) childp = nodep->lchild;
    else if (nodep->rchild) childp = nodep->rchild;
    
    if (!nodepParent) {
        nodepParent = root;
        root = childp;
        free(nodepParent);
        return;
    }
    else if (nodepParent->lchild == nodep)  {
        nodepParent->lchild = childp;
    }
    else if (nodepParent->rchild == nodep) {
        nodepParent->rchild = childp;
    }
    free(nodep);
    //情况2结束
}

void MiddleOrderBST(BSTNodePtr nodep) {
    _MiddleOrderBST(nodep);
    printf("\n");
}

void _MiddleOrderBST(BSTNodePtr nodep) {

    if(!nodep) return;
    _MiddleOrderBST(nodep->lchild);
    printf("%d ", nodep->rcd.key);
    _MiddleOrderBST(nodep->rchild);
}

BSTNodePtr SearchMaxBST(BSTNodePtr nodep) {
    if (!nodep) return NULL;
    while((nodep->rchild) != NULL) {
        nodep = nodep->rchild;
    }
    return nodep;
}

BSTNodePtr SearchMinBST(BSTNodePtr nodep) {
    if (!nodep) return NULL;
    while((nodep->lchild) != NULL) {
        nodep = nodep->lchild;
    }
    return nodep;
}