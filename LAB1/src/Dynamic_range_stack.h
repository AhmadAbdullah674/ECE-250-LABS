/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  a42abdul@uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2019
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -JSSAHI
 *    -JGATHIES 
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef DYNAMIC_STACK_AS_ARRAY_H
#define DYNAMIC_STACK_AS_ARRAY_H

#ifndef nullptr
#define nullptr 0
#endif

#include <algorithm>
#include "Exception.h"

class Dynamic_range_stack {
	private:
		int entry_count;
		int max_count;
		int min_count;
		int initial_capacity;
		int current_capacity;

		int *stack_array;
		int *maximum_array;
		int *minimum_array;

		// You may wish to include a number of helper functions
		// in order to abstract out some operations


	public:
		Dynamic_range_stack( int = 10 );
		~Dynamic_range_stack();

		int top() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		int maximum() const;
		int minimum() const;

		
		void push( int const & );
		int pop();
		void clear();
		void clean_arrays();


	// Friends

	friend std::ostream &operator<<( std::ostream &, Dynamic_range_stack const & );
};

Dynamic_range_stack::Dynamic_range_stack( int n ):
entry_count( 0 ),
min_count( 0 ),
max_count( 0 ),
initial_capacity( std::max( 1, n ) ),
current_capacity( initial_capacity ),
stack_array( new int[current_capacity] ),
maximum_array( new int[current_capacity] ),
minimum_array( new int[current_capacity] ) {

}

Dynamic_range_stack::~Dynamic_range_stack() {

	clean_arrays();
}

int Dynamic_range_stack::top() const {

	int top_element = stack_array[size()-1];
	
	if( entry_count <= 0 )
		throw underflow();
	
	return top_element;
}

int Dynamic_range_stack::maximum() const {
	
	int maximum_element = maximum_array[size()-1];
	
	if( entry_count == 0 )
		throw underflow();	

	return maximum_element;
}

int Dynamic_range_stack::minimum() const {
	
	int minimum_element = minimum_array[size()-1];
	
	if ( entry_count <= 0 )
		throw underflow();
 
	return minimum_element;
}

int Dynamic_range_stack::size() const {
	
	return entry_count;
}

bool Dynamic_range_stack::empty() const {
	
	if(size() <= 0){
		return true;
	}
	else{
		return false;
	}
	
}

int Dynamic_range_stack::capacity() const {
	
	return current_capacity;
}


void Dynamic_range_stack::clean_arrays(){

        delete[] stack_array;
        delete[] maximum_array;
        delete[] minimum_array;

}


void Dynamic_range_stack::push( int const &obj ) {

	if( (entry_count+1) > current_capacity ){
		current_capacity = 2 * current_capacity;

		int *p_stack_array = new int [/*entry_count*/current_capacity];
		int *p_minimum_array = new int[/*entry_count*/current_capacity];
		int *p_maximum_array = new int[/*entry_count*/current_capacity];

		for( int i=0; i<current_capacity; i++ ){

			p_stack_array[i] = stack_array[i]; 
			p_minimum_array[i] = minimum_array[i];
			p_maximum_array[i] = maximum_array[i];
		}
		
		clean_arrays();

                stack_array = p_stack_array;
               	minimum_array = p_minimum_array;
               	maximum_array = p_maximum_array;
	}
	

	if( entry_count == 0 ){
		maximum_array[entry_count] = obj;
		minimum_array[entry_count] = obj;

		max_count++;
		min_count++;
	}

	else{
		if( maximum_array[entry_count-1] < obj ){
			maximum_array[entry_count] = obj;
			max_count++;
		}
		else{
			maximum_array[entry_count] = maximum_array[entry_count-1];
		}

		if ( minimum_array[entry_count-1] > obj ){ 
			minimum_array[entry_count] = obj;
			min_count++;
		}
		else{
			minimum_array[entry_count] =  minimum_array[entry_count-1];
		}
	}
	stack_array[entry_count] = obj;
        entry_count++;

}

int Dynamic_range_stack::pop() {
	
        if( entry_count <= 0 )
                throw underflow();

	int pop_element = stack_array[size()-1];
	
	entry_count--;	

	return pop_element;
}

void Dynamic_range_stack::clear() {
	
	max_count = 0;
	min_count = 0;
	entry_count = 0;
	
	if( current_capacity != initial_capacity ){
	
		clean_arrays();

		stack_array = new int[initial_capacity];
		minimum_array = new int[initial_capacity];
		maximum_array = new int[initial_capacity];
		current_capacity = initial_capacity;
	}	
}


std::ostream &operator<<( std::ostream &out, Dynamic_range_stack const &stack ) {
	
	for(int i = stack.size()-1; i >= 0; i--)
		out <<"Mincount "<<stack.min_count <<" MAxcount "<<stack.max_count<<" stack value = " <<stack.stack_array[i] <<" max = "<< stack.maximum_array[i] <<" min = "<< stack.minimum_array[i]<< std::endl;
	return out;
}

#endif
