#ifndef BINARYEXPRESSIONTREE_H
#define BINARYEXPRESSIONTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define NOT_SET 0
#define OPERATOR 1
#define NUMBER 2
#define VARIABLE 3

#define STR_MAX_LEN 64

typedef struct BTNode {
    char ch;
    int data;
    int type; 
    struct BTNode * lchild, * rchild;
} BTNode, *BTNodePtr;

typedef struct Stack {
    BTNodePtr nodeArr[STR_MAX_LEN];
    int top;
} Stack, *StackPtr;


/********************外部调用的操作表达式函数********************/

/* 
 * add:             根据前缀表达式构建表达式二叉树
 * @param nodepp:   外部调用时, 此参数应为根结点指针的指针
 * @param prefix:   外部调用时, 此参数应为前缀表达式字符串
 * @return :        递归内部判断递归已结束, 外部不需要此返回值
 */
char* add(BTNodePtr* nodepp, char* pf);

/* 
 * DetermineCharType:
 *                  判断字符类型
 * @aaram c:        字符
 * @return          字符类型, 在#define中已定义, 有OPERATOR, 
 *                  NUMBER, VARIABLE 三种类型
 */
int DetermineCharType(char c);

/* 
 * Prefix2BET:      根据前缀表达式构建表达式二叉树, 构建完成或错误
 *                  会提示用户
 * @param pf:       前缀表达式字符串
 * @return:         构建好的表达式二叉树的根结点指针
 */
BTNodePtr Prefix2BET(char * pf);


/* 
 * AssignNodeVar:   给表达式一个元素赋值, 供外部调用
 * @param root:     表达式根结点指针
 * @param v:        变量名
 * @param data:     赋给变量的值
 */
void AssignNodeVar(BTNodePtr root, char v, int data);


/* 
 * CompoundExpr:    构建复合表达式
 * @param c:        新操作符
 * @param root1:    左边的子表达式二叉树根结点
 * @param root2:    右边的子表达式二叉树根结点
 */
BTNodePtr CompoundExpr(char c, BTNodePtr root1, BTNodePtr root2);

/* 
 * CalValue:        计算表达式的值并打印, 供外部调用
 * @param root:     表达式二叉树根结点指针
 * @return:         计算的值
 */
float CalValue(BTNodePtr root);

/* 
 * PrintNode:       打印结点元素
 * @param root:     表达式二叉树根结点指针
 */
void PrintNode(BTNodePtr nodep);

/* 
 * PrintExpr_Infix: 用带括弧的中缀表示式输出表达式, 供外部调用
 * @param nodep:    根结点指针
 */
void PrintExpr_Infix(BTNodePtr nodep);

/**********************函数中调用的函数**********************/

/* 
 * InitStack:       创建并初始化栈, 栈的元素为[表达式二叉树结点指针]
 * @return:         返回构建好的栈
 */
StackPtr InitStack();

/* 
 * _AssignNodeVar:  递归给表达式赋值, 供函数AssignNodeVar(...)调用,
 *                  成功与没有找到变量会提示用户
 * @param root:     结点指针
 * @param v:        变量名
 * @param data:     赋给变量的值
 * @param tag:      判断是否赋值成功的标签的指针
 */
void _AssignNodeVar(BTNodePtr nodep, char v, int data, int* tag);

/* 
 * _CalValue:       递归计算表达式的值并打印, 供CalValue(...)调用
 * @param nodep:    表达式二叉树结点指针
 * @return:         计算的值
 */
float _CalValue(BTNodePtr nodep);

/* 
 * _PrintExpr_Infix:利用递归, 用带括弧的中缀表示式输出表达式, 以
 *                  正常书写习惯添加括号
 * @param nodep:    结点指针
 * @param parentp:  结点的双亲结点, PrintExpr_Infix语句中调用时, 
 *                  此参数应为NULL
 */
void _PrintExpr_Infix(BTNodePtr nodep, BTNodePtr parentp);

#endif //BINARYEXPRESSIONTREE_H