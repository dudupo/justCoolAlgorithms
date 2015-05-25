#include "gin.h"
#include <iostream>


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
	namespace Heap {
		namespace Fibo{

			#define ITEARTION_OVER_CHILDREN(f)\
				struct Fibo * c = f->child->root; \
				while (c->right != c)

			#define ITEARTION_ROOT_LIST(f)\
				struct Fibo * c = f; \
				while (c->right != c)

			#define STEP(c)\
				c = c->right;

			#define DN() 100000

			struct FiboRoot {
				struct Fibo * root;
				struct Fibo * last;
				struct Fibo * first;
				int Hn; 
			};


			struct Fibo {
				struct Fibo * perent; 
				struct FiboRoot * child;
				struct Fibo * left;
				struct Fibo * right;
				int data;
				int key;
				int degree;
				bool mark;
			};
			struct Fibo * _create(int data){
				struct Fibo * ret = new struct Fibo;
				ret->perent = 0; 
				ret->child  = 0;
				ret->right = ret;
				ret->left  = ret;
				ret->data = data;
				ret->key = 0;
				ret->degree = 1;
				ret->mark = false;
				return ret;
			}
			struct Fibo * _create(int data , int key){
				struct Fibo * ret = _create(data);
				ret->key = key;
				return ret;
			}
			struct FiboRoot * create(int data){
				struct FiboRoot * root = new struct FiboRoot;
				root->root = _create(data);
				root->Hn = 1;
				root->last = root->root;
				root->first = root->root;
				return root;
			}

			void exchange(struct Fibo * f1 , struct Fibo * f2){
				struct Fibo * temp = f1;
				f1 = f2;
				f2 = temp;
			}

			void insert(struct FiboRoot * root1 , struct Fibo * f){
				
				if (root1->root == 0){
					root1->root = f;
					f->left = f;
					f->right = f;
					root1->last  = root1->root;
					root1->first = root1->root;
					root1->Hn = 1;
				}
				else{
					// note , that this function doesn't 
					// enlarge the numer of the ndes in the tree.
					f->left = root1->root->left;
					root1->root->left = f;
					f->right = root1->root;
					
					// the case of root list with one node...
					if (root1->root->right == root1->root){
						root1->root->right = f;
						root1->last = f;
					}

					if (root1->root->key > f->key){
						root1->root = f;
					}
				}
			}
			void insert (struct FiboRoot * root1 , int data , int key){
				struct Fibo * f = _create(data , key);
				insert(root1 , f);
				root1->Hn++;
			}
			void Union(struct FiboRoot * root1 , struct FiboRoot * root2){
				

				if (root1->root->key > root2->root->key){
					exchange(root1->root , root2->root);
				}

				root1->Hn += root2->Hn;
				// A->B , C->D ---> A->B->C->D
				root2->first->right = root1->last;
				root1->last->left = root2->first;
				// A->B->C->D ----> D->A->B->C->D
				root2->last->left = root1->first;
				root1->first->right = root2->last;

				root1->last = root2->last;
				root2 = root1;
			}
			void remove(struct Fibo * f){
				f->left->right = f->right;
				f->right->left = f->left;
			}
			
			struct FiboRoot * makeRoot(struct Fibo * r){
				struct FiboRoot * ret = new struct FiboRoot;
				ret->root  = r;
				ret->last  = r;
				ret->first = r;
				ret->Hn = 1;
				return ret;
			}
			void link(struct Fibo * x , struct Fibo * y){
				if (x->child == 0){
					x->child = makeRoot(y);
				}
				else{
					insert(x->child , y);
				}
				y->mark = false;
				x->degree++;
			}
			void consolidate(struct FiboRoot * root){

				//the beutiy of the C
				struct Fibo ** Dn = new struct Fibo * [DN()];
				struct Fibo * y; 
				struct Fibo * x;
				ITEARTION_ROOT_LIST(root->root){
					
					if (root->root->key > c->key){
						root->root = c;
					}

					while (Dn[c->degree] != 0){
						x = c;
						y = Dn[x->degree];
						if (x->key > y->key){
							exchange(x , y);
						}
						remove(y);
						link(x , y);
						Dn[x->degree] = 0;
						x->degree++;
					}
					Dn[c->degree] = c;
					STEP(c)	
				}
			}
			struct Fibo * pop(struct FiboRoot * root){
				struct Fibo * min = root->root;
				if (root->root->child != 0){
					ITEARTION_OVER_CHILDREN(root->root){
						insert(root , c);
						STEP(c)
					}
				}
				remove(root->root);
				if (root->root != root->root->right){
					root->root = root->root->right;
					consolidate(root);
				}
				else{
					//to do: take care about- 
					//-spicel cases ...  
					if (root->root->child != 0){
						root->root = root->root->child->root;
					}
					else{
						root->root = 0;
					}
				}
				root->Hn--;
				return min;
			}
			void cut(struct FiboRoot * root , struct Fibo *  y , struct Fibo * x){
				remove(x);
				y->child = 0;
				x->perent =0;
				y->degree--;
				insert(root , x);
				x->mark = false;

			}
			void cascadingcut(struct FiboRoot * root , struct Fibo * y){
				if (y->perent != 0){
					if (!y->mark){
						y->mark = true;
					}
					else{
						cut(root , y->perent , y);
						cascadingcut(root , y->perent);
					}
				}
			}
			void decresasekey(struct FiboRoot * root ,struct Fibo * f , int newkey){
				if (newkey > f->key){
					std::cout << "sorry... newkey must be grater" <<std::endl;
				}
				f->key = newkey;
				if (f->perent != 0){
					if (f->key < f->perent->key){
						cut(root , f->perent , f);
						cascadingcut(root , f->perent);
					}
				}
			}
			bool emptiy(struct FiboRoot * f){
				return (f == 0 ) || (f->root == 0) || (f->Hn == 0);
			}
		};
	};

	#define PUSH_TO_HEAP() \
			if (colors[p->data]){ \
				if (vlist[p->data] == 0){ \
					struct Heap::Fibo::Fibo * t = Heap::Fibo::_create(p->data , w->data + v->key); \
					Heap::Fibo::insert(fheap ,t); \
					fheap->Hn++; \
				} \
				else{ \
					if (vlist[p->data]->key > w->data + v->key){ \
						Heap::Fibo::decresasekey(fheap , vlist[p->data] , w->data + v->key); \
					} \
				}\
			}



	namespace dijkstra {
		void dijkstra(struct Graph * G){
			
			bool * colors = new bool[G->V];
			struct Heap::Fibo::Fibo ** vlist = new struct Heap::Fibo::Fibo * [G->V];

			for (int i =0 ; i < G->V ; i++){
				colors[i] = true;
				vlist[i] = 0;
			}

			struct Heap::Fibo::FiboRoot * fheap = Heap::Fibo::create(G->nodes[0]->id);
			struct Node::Node * N ;
			struct Heap::Fibo::Fibo * v;
			
			while(!Heap::Fibo::emptiy(fheap)){
				v = Heap::Fibo::pop(fheap);
				if (colors[v->data]){
					colors[v->data] = false;
					N = G->nodes[v->data];
					std::cout << N->id << " ";
					if (N->next != 0){
						OPENNODE(N) {
							PUSH_TO_HEAP()
							STEPNODE(p ,w)
						}
						PUSH_TO_HEAP()
					}
				}
			}

		}
	};

};