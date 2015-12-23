#ifndef SORTING_AND_SEARHING
#define SORTING_AND_SEARHING

#include <iostream>
class Sort
{
public:
	Sort(int *arr,int size);
	void bubble();
	void selection();
	void merge();
	void quick();
	void radix();

	int *a, sz;

private:
	void show();
	void quickSort(int l,int r);
	void mergeSort( int a[], int low, int high );
	void mergeArr(int a[], int low, int mid, int high);

};

class Search
{
public:
	Search(int *arr,int sz,int v);
	int binary();

	int *a, sz, v;
private:
	int binarySearch(int *a,int v, int l, int r);
};


#endif
