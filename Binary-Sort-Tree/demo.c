//
//测试文件
//

#include "BinarySortTree.c"
#include "BinarySortTree.h"

int main() {

    //生成记录数组
    Record r[] = {{5},{2},{7},{1},{4},{3}};

    //CreateBSTbyArray测试，根据数组创建二叉查找树
    BSTNodePtr root1 = CreateBSTbyArray(r, 6);

    //SearchMaxBST和SearchMinBST测试
    printf("最大：%d\n",SearchMaxBST(root1)->rcd.key);
    printf("最小：%d\n",SearchMinBST(root1)->rcd.key);
    
    //MiddleOrderBST中序遍历测试
    MiddleOrderBST(root1);

    //InsertBST插入测试
    InsertBST(&root1, (Record) {6});

    //查看插入后结果
    MiddleOrderBST(root1);

    //DeleteNodeBST删除结点测试
    DeleteNodeBST(root1, 2);

    //查看删除后结果
    MiddleOrderBST(root1);

    //销毁二叉查找树
    DestroyBST(root1);


}
