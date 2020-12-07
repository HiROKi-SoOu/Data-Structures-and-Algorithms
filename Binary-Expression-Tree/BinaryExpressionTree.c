#include "BinaryExpressionTree.h"


/* 
 * @aaram char c: char
 * @return  operand:1, operator:2, other: -1
 */
int DetermineCharType(char c) {
    if (c >= 'a' && c <= 'z')
        return VARIABLE;
    else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        return OPERATOR;
    else if (c >= '0' && c <='9')
        return NUMBER;
    else
        return -1;
}

int CharToNum(char c) {
    return c-48;
}

StackPtr InitStack() {
    StackPtr st = (StackPtr)malloc(sizeof(Stack));
    st->top = -1;
    return st;
}

BTNodePtr StackPop(StackPtr st) {
    if(st->top == -1) {
        puts("Stack EMPTY!");
        return NULL;
    }
    return st->nodeArr[st->top--];
}

void StackPush(StackPtr st, BTNodePtr nodep) {
    st->nodeArr[++st->top] = nodep;
}

BTNodePtr CreateNewNode(char c, int type) {
    BTNodePtr nodep = (BTNodePtr)malloc(sizeof(BTNode));
    nodep->type = type;
    nodep->ch = '\0';
    nodep->data = 0;
    nodep->lchild = NULL; nodep->rchild = NULL;
    if(type==NUMBER) {
        nodep->data = CharToNum(c);
    } else {
        nodep->ch = c;
    }
    return nodep;
}

// 栈
BTNodePtr Prefix2BET(char * prefix) {
    StackPtr st = InitStack();
    BTNodePtr nodep = NULL;
    int type;

    printf("[Prefix2BET] 从前缀表达式 %s 构建表达式二叉树...\n", prefix);

    for (int i=strlen(prefix)-1; i>=0; i--) {
        type = DetermineCharType(prefix[i]);
        //If operand, push into stack
        if (type == VARIABLE) {
            nodep = CreateNewNode(prefix[i], VARIABLE);
            StackPush(st, nodep);
        }
        else if (type == NUMBER) {
            nodep = CreateNewNode(prefix[i], NUMBER);
            StackPush(st, nodep);
        }
        //if operator, 从栈弹出2个作为此结点子结点，再把此节点压入栈
        else if (type == OPERATOR) {
            nodep = CreateNewNode(prefix[i], OPERATOR);
            nodep->lchild = StackPop(st);
            nodep->rchild = StackPop(st);
            StackPush(st, nodep);
        }
        else {
            puts("[Prefix2BET] *ERROR* 输入错误!");
            exit(1);
        }
    }

    printf("[Prefix2BET] 表达式二叉树构建完成.\n");
    return StackPop(st);
}

void AssignNodeVar(BTNodePtr root, char v, int data) {
    int tag = 0;
    printf("[AssignNodeVar] 给 %c 赋值 %d...\n", v, data);
    _AssignNodeVar(root, v, data, &tag);
    if (tag)
        puts("[AssignNodeVar] 赋值成功.");
    else {
        printf("[AssignNodeVar] *ERROR* 赋值失败，未找到变量 %c!\n", v);
    }
}

void _AssignNodeVar(BTNodePtr nodep, char v, int data, int * tag) {
    if (!nodep) return;

    if (nodep->type == VARIABLE && nodep->ch == v) {
        nodep->data = data;
        *tag = 1;
    }
    _AssignNodeVar(nodep->lchild, v, data, tag);
    _AssignNodeVar(nodep->rchild, v, data, tag);
    
}

BTNodePtr CompoundExpr(char c, BTNodePtr root1, BTNodePtr root2) {
    puts("[CompoundExpr] 构建复合表达式...");
    if(DetermineCharType(c) != OPERATOR) {
        puts("[CompoundExpr] 符号错误!");
        exit(1);
    }
    BTNodePtr newRoot = CreateNewNode(c, OPERATOR);
    newRoot->lchild = root1;
    newRoot->rchild = root2;
    puts("[CompoundExpr] 复合表达式构建成功.");
    return newRoot;
}

float CalValue(BTNodePtr root) {
    float res = _CalValue(root);
    puts("[CalValue] 计算表达式...");
    printf("[CalValue] 计算完成. Value = %f\n", res);
    return res;    
}

float _CalValue(BTNodePtr nodep) {
    // 如果结点是叶子，则它是变量或数字，直接返回值
    if (!(nodep->lchild) && !(nodep->rchild))
        return nodep->data;
    else {
        switch (nodep->ch) {
        case '+':
            return (_CalValue(nodep->lchild) + _CalValue(nodep->rchild));
        case '-':
            return (_CalValue(nodep->lchild) - _CalValue(nodep->rchild));
        case '*':
            return (_CalValue(nodep->lchild) * _CalValue(nodep->rchild));
        case '/':
            return (_CalValue(nodep->lchild) / _CalValue(nodep->rchild));
        case '^':
            return pow(_CalValue(nodep->lchild), _CalValue(nodep->rchild));
        default:
            puts("[CalValue] *ERROR* 操作符错误!\n");
            exit(1);
        }
    }
}


void PrintNode(BTNodePtr nodep) {
    if (nodep->type == NUMBER)
        printf("%d", nodep->data);
    else
        printf("%c", nodep->ch);
}

void PrintExpr_Infix(BTNodePtr root) {
    printf("[PrintExpr_Infix] ");
    _PrintExpr_Infix(root, NULL);
    printf("\n");
    return;
}

void _PrintExpr_Infix(BTNodePtr nodep, BTNodePtr praentp) {
    if(!nodep) return;
    int tag = 0; //决定是否添加括号
    // +和—不需要括号当【父结点是+或-，或+、-在最外层】
    if (nodep->type == OPERATOR) {
        if ((nodep->ch == '+' || nodep->ch == '-') &&
            (praentp != NULL) &&
            !(praentp->ch == '+' || praentp->ch == '-')) {
            tag = 1;
        }
    }
    if (tag) printf("(");
    _PrintExpr_Infix(nodep->lchild, nodep);
    PrintNode(nodep);
    _PrintExpr_Infix(nodep->rchild, nodep);
    if (tag) printf(")");
}



// 递归
char* add(BTNodePtr* nodepp, char* prefix) {
  
    // 字符串结束
    if (*prefix == '\0') 
        return '\0'; 
  
    while (1) { 
        char* q; 
        if (*nodepp == NULL) { 
            BTNodePtr newNode = (BTNode*)malloc(sizeof(BTNode)); 
            newNode->data = *prefix; 
            newNode->lchild = NULL; 
            newNode->rchild = NULL; 
            *nodepp = newNode; 
        } 
        else { 
            // 如果字符是字母或数字
            if ((*prefix >= 'a' && *prefix <= 'z') || (*prefix >= '0' && *prefix <='9')) { 
                return prefix; 
            } 
            q = add(&(*nodepp)->lchild, prefix + 1); // 构建左子树 
            q = add(&(*nodepp)->rchild, q + 1); // 构建右子树
  
            return q; 
        } 
    } 
} 
  
