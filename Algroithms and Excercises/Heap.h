#ifndef _ALM_HEAP_H_ 
#define _ALM_HEAP_H_

#include <assert.h>

template <class T>
class Heap 
{
public:
	Heap(int max = 500);
	Heap(const Heap<T> &rhs);
	Heap(T *a, int num, int max);
    ~Heap();
	T *sort();

	bool add(const T &item);
	T remove();
protected:
	T *data;
	int currSize;
	const int MAX_SIZE;

	void shiftUp(int nodeIndex);
	void shiftDown(int nodeIndex);

	inline int parentOf(int nodeIndex);
	inline int leftChildOf(int nodeIndex);
};

template <class T>
Heap<T>::Heap(int max) : MAX_SIZE(max)
{
	data = new T[MAX_SIZE];
	currSize = 0;
}
			 
template <class T>
Heap<T>::Heap(const Heap<T> &rhs) : MAX_SIZE(rhs.MAX_SIZE)
{
	data = new T[MAX_SIZE];
	currSize = rhs.currSize;

	for(int i = 0; i < rhs.currSize; ++i)
	{
		data[i] = rhs.data[i];
	}
    

}

template<class T>
Heap<T>::Heap(T *a, int num, int max): MAX_SIZE(max)
{	
	data = new T[MAX_SIZE];
	currSize = num;

	for(int i = 0; i < num; ++i)
	{
		data[i] = a[i];
	}

    for(int i = parentOf(num - 1); i >= 0; --i)
    {
        shiftDown(i);
    }
}


template<class T>
T *Heap<T>::sort()
{
    T *newArr = new T[currSize];

    for(int i = currSize - 1; i >= 0; --i)
    {
        newArr[i] = remove();
    }
    return newArr;
}


template<class T>
Heap<T>::~Heap()
{
    if(data) 
    {
        delete data;
    }
}



template<class T>
bool Heap<T>::add(const T &item)
{
    if(currSize >= MAX_SIZE) 
    {
        return false;
    }
    data[currSize] = item;
}


template<class T>
T Heap<T>::remove()
{
    assert( currSize > 0);
    
    T tmp = data[0];
    data[0] = data[--currSize];
    shiftDown(0);

    return tmp;
}


template<class T>
void Heap<T>::shiftUp(int nodeIndex)
{
    int currIndex = nodeIndex;
    int parentIndex = parentOf(currIndex);
    T item = data[currIndex];
    
    while(currIndex > 0)
    {
        if(data[parentIndex] > item) break;

        data[currIndex] = data[parentIndex];
        currIndex = parentIndex;
        parentIndex = parentOf(currIndex);
    }
    data[currIndex] = item;
}


template<class T>
void Heap<T>::shiftDown(int nodeIndex)
{
    int currIndex = nodeIndex;
    int childIndex = leftChildOf(currIndex);
    T item = data[currIndex];
    
    while(childIndex < currSize)
    {
        if(childIndex < currSize - 1 && data[childIndex] < data[childIndex+1])
            ++childIndex;
        
        if(item > data[childIndex]) break;
        
        data[currIndex] = data[childIndex];
        currIndex = childIndex;
        childIndex = leftChildOf(currIndex);
    }
    data[currIndex] = item;
}

template<class T>
int Heap<T>::parentOf(int nodeIndex)
{
    assert(nodeIndex > 0);

    return (nodeIndex -1)/2;
}

template<class T>
int Heap<T>::leftChildOf(int nodeIndex)
{
    return nodeIndex * 2 + 1;
}



#endif


