/*****************************************
 * UW User ID:  y98han
 * Submitted for ECE 250
 * Semester of Submission:  (Winter) 2018
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided  code.
 *****************************************/

#ifndef DYNAMIC_DEQUE_H
#define DYNAMIC_DEQUE_H

#include "Exception.h"

template <typename Type>
class Resizable_deque {
	public:
		Resizable_deque( int = 16 );
		Resizable_deque( Resizable_deque const & );
		Resizable_deque( Resizable_deque && );
		~Resizable_deque();

		Type front() const;
		Type back() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		void swap( Resizable_deque & );
		Resizable_deque &operator=( Resizable_deque const& );
		Resizable_deque &operator=( Resizable_deque && );
		void push_front( Type const & );
		void push_back( Type const & );
		void pop_front();
		void pop_back();
		void clear();

	private:
		// Your member variables
	int ifront;
	int iback;
	int deque_size;
	int initial_array_capacity;
	int array_capacity;
	Type *array;
	
		// Any private member functions
		//   - helper functions for resizing your array?

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Resizable_deque<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                   Constructors and Destructors                      //
/////////////////////////////////////////////////////////////////////////

// Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( int n )
// Your initalization list
{
	// Enter your implementation here
	if (n<=16){
		initial_array_capacity = 16;
	}
	else{
		initial_array_capacity = n;
	}
	array_capacity = initial_array_capacity;
	array = new Type[array_capacity];
	ifront =0;
	iback =0;
	deque_size =0;
	
}

// Copy Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque const &deque )
// Your initalization list
{
	// Enter your implementation here
	//array_capacity = initial_array_capacity;
	//array = new Type[array_capacity];
	//Type *temp = deque.array;
	//ifront =0;
	//iback=0;
	//deque_size =0;
	
	//int index = deque.ifront;
	//for (int i=0; i<deque.deque_size;i++){
	//	array[i] = temp[index];
	//	index++;
	//}
	//delete []array;
	//array = temp;
	
	
	initial_array_capacity = deque.initial_array_capacity;
	ifront = deque.ifront;
	iback = deque.iback;
	deque_size = deque.deque_size;
	array_capacity = deque.array_capacity;
	array = new Type[array_capacity];
	int index = ifront;
	for (int i=0;i<deque_size;i++){
		array[i] = deque.array[index];
		index++;
	}

	
	
	
	
	
	
}

// Move Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque &&deque )
// Your initalization list
{
	// Enter your implementation here
	
	array_capacity = 0;
	initial_array_capacity =0;
	ifront =0;
	iback =0;
	deque_size =0;
	swap(deque);
}

// Destructor
template <typename Type>
Resizable_deque<Type>::~Resizable_deque() {
	// Enter your implementation here
	delete []array;
	
}

/////////////////////////////////////////////////////////////////////////
//                     Public Member Functions                         //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
int Resizable_deque<Type>::size() const {
	// Enter your implementation here
	int counter = 0;
	for (int i=0; i<deque_size; i++){
			counter++;
	}
	return counter;
}

template <typename Type>
int Resizable_deque<Type>::capacity() const {
	// Enter your implementation here
	return array_capacity;
}

template <typename Type>
bool Resizable_deque<Type>::empty() const {
	// Enter your implementation here
	return (deque_size ==0);
}

template <typename  Type>
Type Resizable_deque<Type>::front() const {
	// Enter your implementation here
	if (empty()){
		throw underflow();
	}
	return array[ifront];
}

template <typename  Type>
Type Resizable_deque<Type>::back() const {
	// Enter your implementation here
	if (empty()){
		throw underflow();
	}
	return array[iback];
}

template <typename Type>
void Resizable_deque<Type>::swap( Resizable_deque<Type> &deque ) {
	// Swap the member variables
	//     std::swap( variable, deque.variable );
	// Enter your implementation here
	std::swap( ifront, deque.ifront);
	std::swap( iback, deque.iback );
	std::swap( deque_size, deque.deque_size );
	std::swap( array_capacity, deque.array_capacity);
	std::swap( initial_array_capacity, deque.initial_array_capacity);
	std::swap( array, deque.array);
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=( Resizable_deque<Type> const &rhs ) {
	// This is done for you...
	Resizable_deque<Type> copy( rhs );
	swap( copy );

	return *this;
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=( Resizable_deque<Type> &&rhs ) {
	// This is done for you...
	swap( rhs );

	return *this;
}

template <typename Type>
void Resizable_deque<Type>::push_front( Type const &obj ) {
	// Enter your implementation here
	
	if (empty()){ // if the deque is empty
		ifront =0;
		iback =0;
		array[ifront] = obj;
		++deque_size;
		return;
	}
	
	else if (deque_size == array_capacity -1){ // if the array capacity is reached and need to double it
		int index1 = ifront;
		Type *temp_array = new Type[2*array_capacity];
		for (int i=0; i<deque_size;i++){
			temp_array[i] = array[index1];
			++index1;
		}
		delete []array;
		array = temp_array;
		array_capacity *=2;
		ifront = 0;
		iback = deque_size -1;
	}
		int index = ifront;
		Type *temp_array = new Type[array_capacity];
		for (int i=0;i<deque_size;i++){
			temp_array[i+1] = array[index];
			index++;
		}
		delete []array;
		array = temp_array;
		
		++deque_size;
		iback = deque_size-1;
		array[ifront] = obj;
		
		
		


		
		
	

	
}

template <typename Type>
void Resizable_deque<Type>::push_back( Type const &obj ) {
	// Enter your implementation here
	
	if (empty()){	
		ifront =0;
		iback =0;
		array[iback] = obj;
		++deque_size;
		return;
	}
	
	else if (deque_size == array_capacity -1){
		Type *temp_array = new Type[2*array_capacity];
		int index = ifront;
		for (int itr = 0; itr<deque_size; itr++){
			temp_array[itr] = array[index];
			++index;
		}
		delete []array;
		array = temp_array;
		array_capacity *=2;
		ifront =0;
		iback = deque_size -1;
	}
	++deque_size;
	++iback;
	array[iback] = obj;
}

template <typename Type>
void Resizable_deque<Type>::pop_front() {
	int size1 = size();
	if (empty()){
		throw underflow();
	}
	else if(size1 ==1){
		ifront =0;
		iback=0;
		array[ifront] =0;
		--deque_size;
		return;
	}
	++ifront;
	--deque_size;
	
	if ((deque_size <= (array_capacity*(0.25)) ) && (array_capacity>initial_array_capacity)){
		int new_capacity= 0.5*array_capacity;
		Type *temp_array = new Type[new_capacity];
		int index = ifront;
		for (int itr = 0; itr<deque_size; itr++){
			temp_array[itr] = array[index];
			++index;
		}
		delete []array;
		array = temp_array;
		array_capacity = new_capacity;
		ifront =0;
		iback = deque_size -1;
	}
}

template <typename Type>
void Resizable_deque<Type>::pop_back() {
	// Enter your implementation here
	int size1 = size();
	if (empty()){
		throw underflow();
	}
	else if(size1 ==1){
		ifront =0;
		iback=0;
		array[ifront] =0;
		--deque_size;
		return;
	}
	--iback;
	--deque_size;
	
	if ((deque_size <= (array_capacity*(0.25)) ) && (array_capacity>initial_array_capacity)){
		int new_capacity= 0.5*array_capacity;
		Type *temp_array = new Type[new_capacity];
		int index = ifront;
		for (int itr = 0; itr<deque_size; itr++){
			temp_array[itr] = array[index];
			++index;
		}
		delete []array;
		array = temp_array;
		array_capacity = new_capacity;
		ifront =0;
		iback = deque_size -1;
	}
}

template <typename Type>
void Resizable_deque<Type>::clear() {
	// Enter your implementation here
	ifront =0;
	iback =0;
	deque_size =0;
	array_capacity = initial_array_capacity;
	
}
/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// Enter any private member functios (helper functions) here


/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Resizable_deque<T> const &list ) {
	out << "not yet implemented";

	return out;
}

#endif
