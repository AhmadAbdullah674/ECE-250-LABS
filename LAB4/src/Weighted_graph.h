#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include <iostream>
#include <limits>
#include <queue>
#include "Exception.h"
/*****************************************
 * UW User ID:  a42abdul
 * Submitted for ECE 250
 * Semester of Submission:  (Winter) 2019
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/
class Weighted_graph {
	private:
		static const double INF;
		double **weight_matrix;
		int *degrees;		
		int size;
		int Tedges;

	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();
		int degree( int ) const;
		int edge_count() const;
		double adjacent( int, int ) const;
		double minimum_spanning_tree( int )const;
		bool is_connected() const;
		void insert( int, int, double );

	friend std::ostream &operator << ( std::ostream &, Weighted_graph const & );
};
const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

Weighted_graph::Weighted_graph(int m){
	if( m < 0 )
		throw illegal_argument();

	weight_matrix = new double*[m];

	for(int i = 0; i < m; i++ ){
		weight_matrix[i] = new double[m];
		for(int j = 0; j < m; j++)
			weight_matrix[i][j] = 0;
	}

	degrees = new int[m];
	for(int i = 0; i < m; i++ ){
		degrees[i]=0;
	}
	Tedges = 0;
	size = m;
}

Weighted_graph::~Weighted_graph(){
	for(int i=0;i<size;i++)
		delete[] weight_matrix[i];
	delete[] weight_matrix;
	delete[] degrees;
	Tedges = 0;
	size = 0;
}

int Weighted_graph::degree(int vertix ) const{
	if( vertix < 0 || vertix >= size )
		throw illegal_argument();
 
	return degrees[vertix];
}

double Weighted_graph::adjacent( int x_vertix, int y_vertix ) const{
	if( x_vertix < 0 || y_vertix < 0 || x_vertix >= size || y_vertix >= size )
		throw illegal_argument();

	if ( x_vertix == y_vertix )
		return 0;

	if ( !(weight_matrix[x_vertix][y_vertix]) )
		return INF;
	
	return weight_matrix[x_vertix][y_vertix];	
		
}
int Weighted_graph::edge_count() const{
	return Tedges;
}

void Weighted_graph::insert(int x_vertix, int y_vertix, double weight){
	if( x_vertix < 0 || y_vertix < 0 || x_vertix >= size || y_vertix >= size || x_vertix == y_vertix )
		throw illegal_argument();

	if ( weight < 0 || weight == INF )
		throw illegal_argument();

	if( weight > 0 ){
		if(!weight_matrix[x_vertix][y_vertix]){
			degrees[x_vertix]++;
			degrees[y_vertix]++;
			Tedges++;
		}
	}
	
	if( weight == 0 ){
		if(weight_matrix[x_vertix][y_vertix]){
			degrees[x_vertix]--;
			degrees[y_vertix]--;
                        Tedges--;
		}
	}
	weight_matrix[x_vertix][y_vertix] = weight;
	weight_matrix[y_vertix][x_vertix] = weight;
}

bool Weighted_graph::is_connected() const{

	bool *visited = new bool[size];
	for(int i = 0; i < size; i++)
		visited[i] = false;

	int j = 0;
	int counter=0;
	visited[j]=true;
	std::queue<int> q;
	q.push(j);

	while(!q.empty()){
		for(int i=0; i<size;i++){
			if( weight_matrix[j][i] ){
				if( !visited[i] ){
					visited[i] = true;
					q.push(i);
					counter++;
				}
			}
		}
		q.pop();
		j = q.front();
	}

	delete[] visited;

	if( counter >= size-1 )
		return true;
	return false;
}

double Weighted_graph::minimum_spanning_tree( int x ) const{
        if( x < 0 || x >= size )
                throw illegal_argument();
	

	double mst_weight = 0;

	bool *visited = new bool[size];

        for(int i = 0; i < size; i++){
                visited[i] = false;
	}

	int path = x;
	visited[x]=true;
	double min=0;

	while(min != INF){
		min = INF;
		for(int i=0;i<size;i++){
			for(int j=0;j<size;j++){
				if(visited[i] && (weight_matrix[i][j] < min && !visited[j] && weight_matrix[i][j])){
					min = weight_matrix[i][j];
					path = j;
				}
			}
		}

		visited[path] = true;

		if(min!=INF)
			mst_weight += min;
	}
	delete[] visited;
	return mst_weight;
} 

// Enter definitions for all public functions here

std::ostream &operator << ( std::ostream &out, Weighted_graph const &graph ) {
	// Your implementation

	for(int i=0;i<graph.size;i++){
		for(int j=0;j<graph.size;j++){
			out<<graph.weight_matrix[i][j]<<" ";
		}
		out<<std::endl;
	}

	return out;
}



#endif
