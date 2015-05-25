


namespace graph{
	
	namespace Link {
		struct Link
		{
			Link * next;
			int data; 
		};
		struct Link * create (int data);
		void connect (struct Link * l  ,struct  Link * j);
		void insert(struct Link * l , int new_data);
		void print (Link * l);
	};

	namespace Queue {
		namespace doubleLink {
			struct doubleLink
			{
				doubleLink * right; 
				doubleLink *  left;
				int data;
			};
			struct doubleLink * create(int data);
			void connect(struct doubleLink * doubleLink1 , struct doubleLink * doubleLink2);
		};

		struct Queue {
			doubleLink::doubleLink *  first; 
			doubleLink::doubleLink *  last;
		};
		struct Queue * create(int data);
		bool emptiy(struct Queue *Q);
		void push(struct Queue * Q , int data);
		int pop(struct Queue * Q) ;
	};
	namespace Node {
		struct Node
		{
			Link::Link  *weight ;
			Link::Link  *next ;
			int id;
		};

		struct Node * create(int id);

		void connect(struct Node * G , int j , int weight);
		void connect(struct Node * G , struct Node * G2 , int weight);
		void connect(struct Node * G , struct Node * G2 , int weight , bool flag);
	};
	struct Graph
	{
		struct Node::Node ** nodes;
		int V , E;
	};
	struct Graph* gin(int V , int E);
	void DFS(struct Graph * G , int v , bool * colors);
	void DFS(struct Graph * G);
	void BFS(struct Graph *G , bool * colors);
	void BFS(struct Graph * G);

};