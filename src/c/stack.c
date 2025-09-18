#include "stack.h"

void CreateEmpty(Stack *S){
    Top(*S) = Nil;
}

boolean IsEmpty(Stack S){
    return (Top(S) == Nil);
}

boolean IsFull(Stack S){
    return (Top(S) == MaxEl-1);
}

void Push(Stack * S, Obat X){
    if (IsEmpty(*S)){
        Top(*S) = 0;
        InfoTop(*S) = X;
    }
    else{
        Top(*S) += 1;
        InfoTop(*S) = X;
    }
}

void Pop(Stack * S, Obat* X){
    if(Top(*S) == 0){
        *X = InfoTop(*S);
        Top(*S) = Nil;
    }
    else{
        *X = InfoTop(*S);
        Top(*S) -= 1;
    }
}
