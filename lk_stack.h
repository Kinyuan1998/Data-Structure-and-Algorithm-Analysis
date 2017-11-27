template <class Type>
class LinkStack {
private:
    int top;
    int maxSize;
    Type *data;
public:
	LinkStack(int s = 20);
    ~LinkStack() {delete []data;}
    int Push(Type x);
    int Pop(Type &x);
    int GetTop(Type &x);
    int IsEmpty() const {return top == -1; } 
    int IsFull() const {return top == maxSize - 1;}
    void Clear() {top = -1;}
};

template <class Type> 
LinkStack<Type>::LinkStack(int s) { 
    top = -1;
	maxSize = s;
    data = new Type[maxSize];
}

template <class Type>
int LinkStack<Type>::Push(Type x) {   
    if (IsFull( ))
		return 0;
    data[++top] = x;
	return 1;
}

template <class Type>
int LinkStack<Type>::Pop(Type &x) {
    if (IsEmpty( ))
		return 0;  
    x = data[top--];
	return 1;
} 

template <class Type> 
int LinkStack<Type>::GetTop(Type &x) {
    if (IsEmpty( ))
		return 0;
    x = data[top];
	return 1;
}

