// Programmer: Adrian Borrego COP4530 DYNAMICARRY PROJECT
// Last modification date: 01/30/17
#include <cassert>
#include <iostream>
#include <string>

/*Description: Description: Implement a generic dynamic array
  class which will be a template class providing basic 
  features of an array.*/

class RuntimeException // generic run-time exception
{
 protected:
  std::string errorMsg;
 public:
  RuntimeException(const std::string& err) { errorMsg = err; }
  std::string getMessage() const { return errorMsg; }
};

class InvalidIndex : public RuntimeException
{
 public:
 InvalidIndex(const std::string& err): RuntimeException(err) {};
};

template <class dynElem>
class dynarr {
  private:
    int capacity;
    dynElem* A;
  public:
    dynarr() : capacity(0), A(NULL){}
    dynarr(int N): capacity(N), A(new dynElem[N]){}
    dynarr(const dynarr<dynElem> &other);
    ~dynarr();
    dynarr<dynElem> & operator=( const dynarr<dynElem> &other);
    dynElem & operator[](int ndx) throw(InvalidIndex);
    int getCapacity();
    void reserve(int newcap);
};

template <class dynElem>
dynarr<dynElem>::dynarr(const dynarr<dynElem> &other)
{
	//Allocating memory for new array.
	A = new dynElem[other.capacity];
	//Copy contents of &other into new array.
	for(int i = 0; i < other.capacity; i++)
		A[i] = other.A[i];
	//Set capacity of new array.
	capacity = other.capacity;
}
template <class dynElem>
dynarr<dynElem>::~dynarr()
{
	//Free allocated memory.
	delete [] A;
}

template <class dynElem>
dynarr<dynElem> & dynarr<dynElem>::operator=( const dynarr<dynElem> &other)
{
	//Check if assignment is not between same array.
	if(this != &other){
		//Delete array and copy contents into new allocated array.
		delete [] A;
		A = new dynElem[other.capacity];
		for(int i = 0; i < other.capacity; i++)
			A[i] = other.A[i];
		capacity = other.capacity;
	}
	//Return created array.
	return (*this);
}
  
template <class dynElem>
dynElem & dynarr<dynElem>::operator[](int ndx) throw(InvalidIndex)
{
	//Test if ndx is greater than capacity of array.
	if(ndx > capacity){
		throw InvalidIndex("Array index is too large");
	}
	//Test if ndx is negative.
	else if(ndx < 0){
		throw InvalidIndex("Array index is negative");
	}
	//Otherwise return value at ndx.
	return A[ndx];

}

template <class dynElem>
int dynarr<dynElem>::getCapacity()
{
  return capacity;
}
  
template <class dynElem>
void dynarr<dynElem>::reserve(int newcap)
{
	// If newcap <= capacity, does nothing; 
	if(newcap <= capacity){
	}
	//If capacity is 0, allocates a dynamic array of
	//capacity newcap and makes A point to that array
	else if(capacity == 0){
		A = new dynElem[newcap];
	}
	//Otherwise allocates a new dynamic array newA of capacity 
    //Newcap, copies values in A to newA, deletes A and sets
    //A equal to newA
	else{
		dynElem* newA = new dynElem[newcap];
		capacity = newcap;
		for(int i = 0; i < newcap; i++)
			newA[i] = A[i];
		delete [] A;
		A = newA;
	}
}


