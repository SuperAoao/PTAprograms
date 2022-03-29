#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node* PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read()
{
    List c = (List)malloc(sizeof(Node));
    c->Data = 3;
    c->Next = NULL;
    List b = (List)malloc(sizeof(Node));
    b->Data = 2;
    b->Next = c;
    //List a = (List)malloc(sizeof(Node));
    //a->Data = 1;
    //a->Next = b;
    return b;
}; 
void Print(List L)
{
    while (L)
    {
        printf_s("%d", L->Data);
        L = L->Next;
    }
};

// 这个写法会超时，浪费空间和时间，不要做冗余判断，寻找通用解决方案
List ReverseOverTime(List L)
{
    List visitor = L;
    List slow_ptr = NULL;
    List fast_ptr = NULL;
    List front_node = L;
    List last_reversed_node = NULL;
    while (visitor)
    {
        slow_ptr = visitor->Next;
        if (slow_ptr)
        {
            fast_ptr = slow_ptr->Next;
            slow_ptr->Next = visitor;
            if (!fast_ptr)
            {
                front_node = slow_ptr;
                front_node->Next = visitor;
                visitor = NULL;
            }
            last_reversed_node = slow_ptr;
        }
        else
        {
            front_node = visitor;
            front_node->Next = last_reversed_node;
            visitor = NULL;
        }
   
    }
    if (L)
    {
        L->Next = NULL;
    }
    return front_node;
};
List Reverse(List L)
{
    List Prev = NULL;
    List Curr = L;
    List Next = NULL;
    while (Curr)
    {
        Next = Curr->Next;
        Curr->Next = Prev;
        Prev = Curr;
        Curr = Next;
    }
    return Prev;
}
int main()
{
    List L1, L2;
    L1 = Read();
    L2 = Reverse(L1);
    Print(L1);
    Print(L2);
    return 0;
}

/* 你的代码将被嵌在这里 */
