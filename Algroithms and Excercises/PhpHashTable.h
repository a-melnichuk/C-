#ifndef PHP_HASH_TABLE
#define PHP_HASH_TABLE

#include <ostream>
#include <list>
#include <vector>
#include <cstring>

template<typename V>
class PhpHashTable
{
public:
	PhpHashTable();
	void put(const char *arKey, V val);
	V get(V val);
	V operator[](const char *arKey);
	inline unsigned long hash(const char *arKey, size_t nKeyLength);
	void show();
private:

	struct Pair { const char *key; V val; };
	inline int getIndex(const char *arKey);

	std::vector< std::list<Pair> > a;
	size_t nTableSize;
    size_t nTableMask;
    size_t nNumOfElements;
};



template<typename V>
PhpHashTable<V>::PhpHashTable(): nNumOfElements(0),nTableSize(64),nTableMask(63)
{	
	a.resize(64);
}

template<typename V>
inline int PhpHashTable<V>::getIndex(const char *arKey)
{   //mask maps hashtable to R[0,mask-1] without %, since x % y = x & (y-1) if y % 2 = 0 
	return hash(arKey, strlen(arKey) ) & nTableMask;
}


template<typename V>
void PhpHashTable<V>::show()
{   
	for(size_t i=0;i<a.size();++i)
	{
		std::cout<< i << ": ";
		for(std::list<Pair>::iterator it = a[i].begin(); it != a[i].end(); ++it)
		{
			std::cout << (*it).key << ' ' << (*it).val << ", ";
		}
		std::cout<<'\n';
	}
}

template<typename V>
V PhpHashTable<V>::operator[](const char *arKey)
{
	int index = getIndex(arKey);

	for(std::list<Pair>::iterator it = a[index].begin(); it != a[index].end(); ++it)
	{
		if(strcmp((*it).key, arKey) == 0)
			return (*it).val;
	}
	return NULL;
}

template<typename V>
void PhpHashTable<V>::put(const char *arKey,V val)
{
	
	++nNumOfElements;
	if(nNumOfElements > nTableSize)
	{
		//table size is always power of 2
		nTableSize = nNumOfElements << 1;
		//mask always satisfies x & (y-1) if y % 2 = 0 
		nTableMask = nTableSize - 1;
		//resize data,recount key hashes;
		std::vector<std::list<Pair>> tmp;
		tmp.resize(nTableSize);
		for(size_t i=0;i<a.size();++i)
		{
			if( !a[i].empty() )
			{
				Pair p = a[i].front();
				std::cout<< p.key << '\n';
				int index = getIndex( p.key );
				tmp[index] = a[i];
			}
		}
		a = tmp;
	}
	int index = getIndex(arKey);
	Pair p = {arKey,val};
	a[index].push_back(p);
}

/* DJBX33A algorithm
 * hash(i) = hash(i-1) * 33 + str[i]
 * where hash(i-1)*33 = hash(i-1)*(1<<5 + 1) = hash(i-1)<<5 + hash(i-1)
 * shamefully stolen from http://lxr.php.net/xref/PHP_5_4/Zend/zend_hash.h#261
 */

template<typename V>
inline unsigned long PhpHashTable<V>::hash(const char *arKey, size_t nKeyLength)
{
/* Magic Constant 5381:
 * odd number
 * prime number
 * deficient number
 */
 
  /*
  (c) practically any good multiplier works. 
  I think you're worrying about the fact that 31c + d doesn't cover any reasonable range of hash values if c and d are between 0 and 255. 
  That's why, when I discovered the 33 hash function and started using it in my compressors, I started with a hash value of 5381. 
  I think you'll find that this does just as well as a 261 multiplier.
  */
 
	register unsigned long hash = 5381; 
	//variant with the hash unrolled eight times
	for (; nKeyLength >= 8; nKeyLength -= 8) 
	{	//loop w/o overhead of setting inner loop?
		hash = ((hash << 5) + hash) + *arKey++;
		hash = ((hash << 5) + hash) + *arKey++;
		hash = ((hash << 5) + hash) + *arKey++;
		hash = ((hash << 5) + hash) + *arKey++;
		hash = ((hash << 5) + hash) + *arKey++;
		hash = ((hash << 5) + hash) + *arKey++;
		hash = ((hash << 5) + hash) + *arKey++;
		hash = ((hash << 5) + hash) + *arKey++;
	}

	switch (nKeyLength) 
	{
		case 7: hash = ((hash << 5) + hash) + *arKey++; // fallthrough...
		case 6: hash = ((hash << 5) + hash) + *arKey++; 
		case 5: hash = ((hash << 5) + hash) + *arKey++; 
		case 4: hash = ((hash << 5) + hash) + *arKey++;
		case 3: hash = ((hash << 5) + hash) + *arKey++; 
		case 2: hash = ((hash << 5) + hash) + *arKey++; // fallthrough... 
		case 1: hash = ((hash << 5) + hash) + *arKey++; break;
		case 0: break;
	}
	return hash;
}

#endif
