#include "gin.h"
#include "fenwick_tree.h"
#include <iostream>
#include <cmath>
#include "Dijkstra.h"

using namespace std;

int main (){
	int arr[7] = {0 , 5 , 7 ,2 ,4 ,8 , 9};
	int *brr = fenwick::create(arr , 7);
	for (int i = 0 ; i < 7;i++){
		cout << brr[i] << " ";
	
	}

	int y = fenwick::query(brr ,2 , 5);
	cout << endl << "the sum between 1-4 -> " << y << endl;

	cout << "-----------" << endl;

	struct graph::Graph *l = graph::gin(3 , 4);
	DFS(l);
	cout << endl;
	BFS(l);
	cout << endl;
	graph::dijkstra::dijkstra(l);
	cout << endl;
	
	

	int x;
	cin >> x;
	return 0;

}