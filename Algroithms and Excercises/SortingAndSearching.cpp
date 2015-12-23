#include "SortingAndSearching.h"

 /*
	* Sort class
	*/



Sort::Sort(int *arr,int size): a(arr),sz(size)
{
}

void Sort::bubble()
{
	bool swapped = true;
	int j = 0;		

	while(swapped)
	{
		swapped = false;
		++j;
		for(int i=0;i<sz-j;++i)
		{
			if(a[i] > a[i+1])
			{
				int tmp = a[i];
				a[i] = a[i+1];
				a[i+1]=tmp;
				swapped = true;
			}
			show();
		}
	}
}

void Sort::selection() 
{  
    for (int i = 0; i < sz - 1; ++i) 
	{
        int min = i;
        for (int j = i + 1; j < sz; ++j)
                if (a[j] < a[min])
                    min = j;

        if (min != i) 
		{
                int tmp = a[i];
                a[i] = a[min];
                a[min] = tmp;
        }
		show();
    }  
}

void Sort::quick() 
{
	quickSort(0,sz-1);     
}


void Sort::quickSort(int left,int right)
{
	int i = left, j = right;
	int mid = a[(left + right) / 2];

    while (i <= j) 
	{
        while (a[i] < mid)
			i++;
        while (a[j] > mid)
			j--;

        if (i <= j) 
		{
            int tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;

            i++;
            j--;
        }
    }
	show();

    if (left < j)
        quickSort(left, j);
    if (i < right)
        quickSort(i, right);
}



void Sort::merge()
{
	mergeSort(a,0,sz-1);
}


void Sort::mergeArr(int a[], int low, int mid, int high)
{
	int j = low, k = mid + 1 ,end = high-low+1;
	int *tmp = new int[end];

	for(int i=0;i<end;++i)
	{
		if (j == mid + 1) 
		{ 
			tmp[i] = a[k++];
			continue;
		}
		if (k == high + 1) 
		{ 
			tmp[i] = a[j++]; 
			continue; 
		}
		tmp[i] = (a[j] < a[k]) ? a[j++] : a[k++];
	}
	for(int i=0;i<end;++i)
	{
		a[i+low] = tmp[i];
		std::cout<<a[i+low]<< ' ';
	}
	std::cout<<std::endl;
	delete[] tmp;
}

void Sort::mergeSort( int a[], int low, int high )
{
	if( low < high )
	{
		int mid = ( low + high ) / 2;
		mergeSort( a, low, mid );
		mergeSort( a, mid + 1, high );
		mergeArr( a, low, mid, high );
		show();
	}
}

void Sort::show()
{
	for(int i=0;i<sz;++i)
	{
		std::cout<<a[i]<<' ';
	}
	std::cout<<std::endl;
}



 /*
	* Search class
	*/


Search::Search(int *arr,int size,int val) : a(arr),sz(size),v(val)
{
}

int Search::binary()
{
	return binarySearch(a,v,0,sz-1);
}

int Search::binarySearch(int *a,int v, int l, int r)
{
	if(l>r) return -1;

	int m = (l + r)/2;
	return a[m] == v ? m :  a[m] > v ? binarySearch(a,v,l,m-1) : binarySearch(a,v,m+1,r);
}
