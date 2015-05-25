#include <iostream>
using namespace std;

#define ITERLINK(l) \
		struct Link *p = l; \
		while(p->next != 0){
#define OPENNODE(G) \
			struct Link::Link *p = G->next; \
			struct Link::Link *w = G->weight; \
			while (p->next != 0)
#define STEPNODE(p , w)\
			p = p->next;\
			w = w->next;

namespace graph{
	
	namespace Link {
		struct Link
		{
			Link * next;
			int data; 
		};
		struct Link * create (int data){
			struct Link l;
			struct Link *r = new struct Link;
			l.data = data;
			l.next = 0;
			*r = l;
			return r; 
		}
		void connect (struct Link * l  ,struct  Link * j){
			l->next = j;
		}
		void insert(struct Link * l , int new_data){
			struct Link * p = l;
			while (p->next != 0){
				p = p->next;
			}
			p->next = create(new_data);
		}
		void print (Link * l){
			if (l != 0){
				ITERLINK(l)
					cout << p->data<<" ";
					p = p->next;
				}
				cout << p->data<<endl;
			}
		} 
	};

	namespace Queue {
		namespace doubleLink {
			struct doubleLink
			{
				doubleLink * right; 
				doubleLink *  left;
				int data;
			};
			struct doubleLink * create(int data){
				struct doubleLink * dl = new struct doubleLink;
				dl->right = 0;
				dl->left  = 0;
				dl->data = data;
				return dl;
			}
			void connect(struct doubleLink * doubleLink1 , struct doubleLink * doubleLink2){
				doubleLink1->right = doubleLink2;
				doubleLink2->left  = doubleLink1;
			}
		};

		struct Queue {
			doubleLink::doubleLink *  first; 
			doubleLink::doubleLink *  last;
		};
		struct Queue * create(int data) {
			struct Queue * Q = new struct Queue;
			Q->last  = doubleLink::create(-1);
			Q->first = doubleLink::create(data);
			doubleLink::connect(Q->last , Q->first);
			return Q;
		}
		bool emptiy(struct Queue *Q){
			return (Q->first->data == -1);
		}
		void push(struct Queue * Q , int data){
			struct doubleLink::doubleLink * left = doubleLink::create(data);
			if (!emptiy(Q)){
				doubleLink::connect( left , Q->last->right);
				doubleLink::connect( Q->last , left); 
			}
			else{
				Q->first = left;
				doubleLink::connect(Q->last , Q->first);
			}
		}
		int pop(struct Queue * Q) {
			int ret  = Q->first->data;
			Q->first = Q->first->left;
			Q->first->right = 0;
			return ret;
		}	
	};
	namespace Node {
		struct Node
		{
			Link::Link  *weight ;
			Link::Link  *next ;
			int id;
		};

		struct Node * create(int id){
			struct Node n;
			
			n.next = 0;
			n.weight =0;
			n.id = id;

			struct Node * r = new struct Node;
			*r = n;
			return r;
		}

		void connect(struct Node * G , int j , int weight){
			if (G->next != 0){
				OPENNODE(G){
					STEPNODE(p , w)
				}
				p->next = Link::create(j);
				w->next = Link::create(weight);
			}
			else{
				G->next   = Link::create(j);
				G->weight = Link::create(weight);
			}
		}
		void connect(struct Node * G , struct Node * G2 , int weight){
			if (G->next != 0){
				OPENNODE(G){
					STEPNODE(p , w)
				}
				p->next = Link::create(G2->id);
				w->next = Link::create(weight);
			}
			else{
				G->next   = Link::create(G2->id);
				G->weight = Link::create(weight);
			}
		}
		void connect(struct Node * G , struct Node * G2 , int weight , bool flag){
			connect(G , G2 , weight);
			connect(G , G2 , weight);
		}
	};
	struct Graph
	{
		struct Node::Node ** nodes;
		int V , E;
	};
	struct Graph* gin(int V , int E){
		struct Node::Node ** nodes = new struct Node::Node * [V];
		for (int i = 0 ; i < V ; i++){
			nodes[i] = Node::create(i);
		}
		int k , j , weight;
		for (int i = 0 ; i < E ; i++){
			cin >> k >> j >> weight;
			Node::connect(nodes[k] , j , weight);
		}

		struct Graph *G = new struct Graph;
		G->V = V;
		G->E = E;
		G->nodes = nodes;
		return G;
	}
	void DFS(struct Graph * G , int v , bool * colors){
		struct Node::Node * N = G->nodes[v];
		colors[v] = false;
		if (N->next != 0){
			OPENNODE(N) {
				if (colors[p->data]){
					DFS(G , p->data , colors);
				}
				STEPNODE(p ,w)
			}
			if (colors[p->data]){
				DFS(G , p->data , colors);
			}
		}
		cout << N->id << " ";
	}
	void DFS(struct Graph * G){
		bool * colors = new bool[G->V];
		for (int i =0 ; i < G->V ; i++){
			colors[i] = true;
		}
		DFS(G , 0 , colors);
	}
	void BFS(struct Graph *G , bool * colors){
		struct Queue::Queue * Q = Queue::create(0);
		struct Node::Node * N ;
		int v;
		
		while(!Queue::emptiy(Q)){
			v = Queue::pop(Q);
			if (colors[v]){
				colors[v] = false;
				N = G->nodes[v];
				cout << N->id << " ";
				if (N->next != 0){
					OPENNODE(N) {
						if (colors[p->data]){
							Queue::push(Q ,p->data);
						}
						STEPNODE(p ,w)
					}
					if (colors[p->data]){
						Queue::push(Q , p->data);
					}
				}
			}
		}
	}
	void BFS(struct Graph * G){
		bool * colors = new bool[G->V];
		for (int i =0 ; i < G->V ; i++){
			colors[i] = true;
		}
		BFS(G , colors);
	}

};