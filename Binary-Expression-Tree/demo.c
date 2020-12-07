#include "BinaryExpressionTree.h"
#include "BinaryExpressionTree.c"

int main() {
    BTNode *s = NULL; 
    char a[] = "+a*2b"; 
    char b[] = "^c2";
    add(&s, "+*15^x2*8x"); 
    PrintExpr_Infix(s);
    BTNodePtr root1 = Prefix2BET(a);
    BTNodePtr root2 = Prefix2BET(b);
    PrintExpr_Infix(root1);
    AssignNodeVar(root1, 'a', 1);
    AssignNodeVar(root1, 'b', 2);
    AssignNodeVar(root2, 'c', 3);
    CalValue(root1);
    CalValue(root2);

    BTNodePtr root3 = CompoundExpr('-', root1, root2);
    PrintExpr_Infix(root3);
    CalValue(root3);

    return 0;
} 