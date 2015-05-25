namespace graph{
	namespace Heap {
		namespace Fibo{
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

			struct FiboRoot * create(int data);

			struct Fibo * _create(int data);
			struct Fibo * _create(int data , int key);

			void exchange(struct Fibo * f1 , struct Fibo * f2);
			void insert(struct FiboRoot * root1 , struct Fibo * f);
			void insert (struct FiboRoot * root1 , int data , int key);
			void Union(struct FiboRoot * root1 , struct FiboRoot * root2);
			void remove(struct Fibo * f);
			struct Fibo * pop(struct FiboRoot * root);
			struct FiboRoot * makeRoot(struct Fibo * r);
			void link(struct Fibo * x , struct Fibo * y);
			void consolidate(struct FiboRoot * root);
			void decresasekey(struct FiboRoot * root ,struct Fibo * f , int newkey);
			void cut(struct FiboRoot * root , struct Fibo *  y , struct Fibo * x);
			void cascadingcut(struct FiboRoot * root , struct Fibo * y);
			bool emptiy(struct FiboRoot * f);
		};
	};

	namespace dijkstra {
		void dijkstra(struct Graph * G);
	};

};