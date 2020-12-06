#include "BinarySortTree.c"
#include "BinarySortTree.h"

int main() {

    Record r[] = {{5},{2},{7},{1},{4},{3}};

    BSTNodePtr root1 = CreateBSTbyArray(r, 6);

    printf("最大：%d\n",SearchMaxBST(root1)->rcd.key);
    printf("最小：%d\n",SearchMinBST(root1)->rcd.key);
    
    MiddleOrderBST(root1);

    InsertBST(&root1, (Record) {6});

    MiddleOrderBST(root1);

    DeleteNodeBST(root1, 2);

    MiddleOrderBST(root1);

    DestroyBST(root1);


}
