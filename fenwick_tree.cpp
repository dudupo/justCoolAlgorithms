#include <iostream>
#include <cmath>
#include "gin.h"

using namespace std;




namespace fenwick {
	int * create(int*arr , int n){
		int *brr = new int[n];
		for (int j = 0 ; j < n ;j++)
			brr[j] = 0;
		for (int j = 1 ; j < n ; j++)
			for (int i = j ; i < n ; i += (i & (-i)))
				brr[i] += arr[j];
		return brr;
	}
	int query(int *arr , int i){
		int sum = 0;
		for(int j = i ; j > 0 ; j -= j & (-j))
			sum += arr[j];
	
		return sum;
	}
	int query(int *arr , int i , int j){
		return query(arr , j) - query(arr ,i);
	}
	void update(int * arr , int n  , int value , int i ){
		for(int j = i ; j < n ; j += j & (-j))
			arr[j] += value;
	}
};


