#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

/****************************************
 * UW User ID:  a42abdul
 * Submitted for ECE 250
 * Semester of Submission:  (Winter) 2019
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
	private:
		int count;
		int power;
		int array_size;
		T *array;
		state *array_state;

		int h1( T const & ) const; 
		int h2( T const & ) const; 
		//void Search( T const &, int & );

	public:
		DoubleHashTable( int = 5 );
		~DoubleHashTable();
		int size() const;
		int capacity() const;		
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;

		void print() const;

		void insert( T const & );
		bool remove( T const & );
		void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state [array_size] ) {	
	
	for ( int i = 0; i < array_size; ++i ) {
		array_state[i] = EMPTY;
	}
}

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
	
	delete [] array;
	delete [] array_state;
}

template<typename T >
int DoubleHashTable<T >::size() const {
     
	return count;
}

template<typename T >
int DoubleHashTable<T >::capacity() const {

	return array_size;
}

template<typename T >
bool DoubleHashTable<T >::empty() const {
    
	if ( count ) 
		return false;
	return true;
}

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {

	int x = static_cast<int> (obj);
	x = x % array_size; 

	return ( x < 0 ) ? ( x + array_size ) : x;
}

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {

	int x = static_cast<int> (obj); 
	x = (x / array_size) % array_size; 
 
	if( x < 0 )
		x += array_size;
	
	return ( !( x % 2 ) ) ? ++x : x;
}

template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {


	int index = h1( obj );
	int offset = h2( obj );

	if(array_state[index] == OCCUPIED && array[index] == obj)
		return true;

	int p_index = index;
	index = ( index + offset ) % array_size;

	while ( array_state[index] != EMPTY && index != p_index ) {

		if( array[index] == obj && array_state[index] == OCCUPIED ){
		
			return true;
		}

		index = ( index + offset ) % array_size;	
	}

	return false;
}

/*template<typename T >
void DoubleHashTable<T >::Search( T const &obj, int &type){
}*/

template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
    
	if ( array_state[n] == OCCUPIED )  	                      
		return array[n];

	throw illegal_argument();
}

template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
	
	if ( count == array_size ){
		throw overflow();
	}

	int index = h1( obj );
	int offset  = h2( obj );	

	while (array_state[index] == OCCUPIED){

		index = ( index + offset ) % array_size;
	}

	array[index] = obj;
	array_state[index] = OCCUPIED; 
	count++; 
}

template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
	
	int index = h1( obj );
	int offset = h2( obj );

	if(array_state[index] == OCCUPIED && array[index] == obj){
		count--;
		array_state[index] = DELETED;
		return true;
	}

	int p_index = index;
	index = ( index + offset ) % array_size;
	
	while ( array_state[index] != EMPTY && index != p_index ) {

		if( array[index] == obj && array_state[index] == OCCUPIED ){
			count--;
			array_state[index] = DELETED;
			return true;
		}

		index = ( index + offset ) % array_size;	
	}

	return false;
}

template<typename T >
void DoubleHashTable<T >::clear() {

	for(int i = 0; i < array_size; i++){
		array[i] = 0;
		array_state[i] = EMPTY;
	}
	count = 0;
}


template<typename T >
void DoubleHashTable<T >::print() const {
     
	std::cout << "The capacity " << capacity() << " Current number " << size() << std::endl;
	
	for( int i = 0; i < array_size; i++ ){
		std::cout << "The value of = " << array[i] << " Status is = " << array_state[i] << std::endl;
	}
	return;
}

#endif
