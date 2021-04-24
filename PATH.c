#include "PATH.h"
#include "RESERVATION.h"

int location[MAX_DIS * 2 + 10][MAX_DIS * 2 + 10] = { 0 };
int number_visiting_city = 0;

int number_visiting_citys(){
	return number_visiting_city;
}

void CreateGraph(Graph* pgraph, int num) {
	pgraph->len = num;
	pgraph->heads = (Node**)malloc(sizeof(Node*) * num);
	for (int i = 0; i<num; i++) {
		// Make a dummy node.
		pgraph->heads[i] = (Node*)malloc(sizeof(Node));
		pgraph->heads[i]->id = i;
		pgraph->heads[i]->next = NULL;
		pgraph->heads[i]->distance = 0;
	}
}

void AddEdge(Graph* pgraph, int** city, int src, int dest) {
	int x_dis = city[src][0] - city[dest][0];
	int y_dis = city[src][1] - city[dest][1];
	int dis = sqrt(x_dis*x_dis + y_dis * y_dis);

	Node* newNode1 = (Node*)malloc(sizeof(Node));
	newNode1->next = NULL;
	newNode1->id = dest;
	newNode1->distance = dis;

	Node* cur = pgraph->heads[src];
	while (cur->next != NULL) cur = cur->next;
	cur->next = newNode1;

	Node* newNode2 = (Node*)malloc(sizeof(Node));
	newNode2->next = NULL;
	newNode2->id = src;
	newNode2->distance = dis;

	cur = pgraph->heads[dest];
	while (cur->next != NULL) cur = cur->next;
	cur->next = newNode2;
}

int IsEdge(Graph* pgraph, int src, int dest) {
	Node* cur = pgraph->heads[src];

	while (cur->next != NULL) {
		cur = cur->next;
		if (cur->id == dest) return 1;
	}

	return 0;
}

void CreateCity(int** arr, int num) {
	srand((unsigned)time(NULL));
	int i = 0;

	while (i < num) {
		int x = rand() % (MAX_DIS * 2 + 1) - MAX_DIS;
		int y = rand() % (MAX_DIS * 2 + 1) - MAX_DIS;
		if (location[x + MAX_DIS][y + MAX_DIS] == 1) continue;

		arr[i][0] = x;
		arr[i][1] = y;
		location[x + MAX_DIS][y + MAX_DIS] = 1;
		i++;
	}
}

float** CreatePathGraph(Graph* pgraph, int src, int dest) {
	float** weight = (float**)malloc(sizeof(float*) * MAX_VERTICES);
	for (int i=0; i<MAX_VERTICES; i++){
		weight[i] = (float*)malloc(sizeof(float) * MAX_VERTICES);
	}

	for (int i=0; i<MAX_VERTICES; i++){
		for(int j=0; j<MAX_VERTICES; j++){
			weight[i][j] = INF;
		}
	}

	for (int i = 0; i < MAX_VERTICES; i++) {
		Node* cur = pgraph->heads[i]->next;
		
		while(cur != NULL){
			weight[i][cur->id] = (float)cur->distance/500;
			cur = cur->next;
		}
		
		/*for (int j = 0; j < MAX_VERTICES; j++) {
			if(cur == NULL) break;

			if (i == j) weight[i][j] = 0;
			else if (j == cur->id) {
				weight[i][j] = (float)cur->distance / 500;
				cur = cur->next;
			}
			else {
				weight[i][j] = INF;
				cur = cur->next;
			}
		}*/
	}
	return weight;
}

int path[MAX_VERTICES];
int min_time[MAX_VERTICES]; 
int found[MAX_VERTICES];  

int choose(int min_time[], int n, int found[]) {


	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;


	for (i = 0; i < n; i++)
	{
		if ( (min_time[i] < min) && (found[i] == FALSE) )
		{
			min = min_time[i];
			
			minpos = i;
		}
		
	}
	return minpos;
}

int shortest_path_time(Graph* pgraph, int*** month, int src, int dest, int date, RNode* T)
{
	//printf("%d %d\n", src, dest);
	float** weight = CreatePathGraph(pgraph, src, dest);
	int i, u, w, date_real;

	for( i=0; i<26; i++){
		path[i] = -1;
	}

	for (i = 0; i < 26; i++)
	{
		min_time[i] = weight[src][i]+month[date][src][i];

		found[i] = FALSE;
	}
	found[src] = TRUE;

	min_time[src] = TRUE;
	u = src;

	for(i=0;i<26;i++)
	{
		//printf("u:%d, min_time[u]:%d\n", u, min_time[u]);
		/*if (u == dest)
			break;*/

		found[u] = TRUE; 

		for (w = 0; w <26; w++)
		{
			if (found[w] == FALSE)
			{
				if (weight[u][w] == INF)
					continue;
				date_real = min_time[u] / 1440;
				int waiting_time = month[date_real][u][w] - min_time[u];
				while (waiting_time<0) {
					date_real++;
					if(date_real > 31) break;
					waiting_time = month[date_real][u][w] - min_time[u];
				}
				//printf("(%d)", date_real);
				//printf("%d:%d ", w, min_time[w]);
				if (min_time[u] + weight[u][w]+waiting_time< min_time[w])
				{
					min_time[w] = min_time[u] + weight[u][w]+ waiting_time;
					path[w] = u;
				}
			}
		}
		u = choose(min_time, 26, found);
		//printf("\n");
	}

	//for(i=0; i<26; i++) printf("%d:%d ", i, path[i]);
	if (min_time[dest]==INF) printf("It has NO path!");
	else SearchPath(src, dest, T);

	for(int i = 0; i < number_visiting_city - 1; i++){
		date = min_time[T->flight_path[i]] / 1440;
		T->departure_time[i] = month[date][T->flight_path[i]][T->flight_path[i+1]];
		T->departure_date[i] = date;
		T->arrival_time[i] = min_time[T->flight_path[i]];
		T->arrival_date[i] = date;
		T->flight_time += weight[T->flight_path[i]][T->flight_path[i+1]];
	}

	/*int second_country=SearchPath(src, dest);
	int departure_time=month[date][src][second_country];
	int arrival_time=min_time[dest];
	printf("departure schedule(date: %d, time: %d:%2d)\n arrival schedule(date:%d, time: %d:%2d)",departure_time%14400)*/
	//return min_time[dest];
}

void SearchPath(int src, int dest, RNode* T){
	int stack[50];
	int top = 0;
	
	
	int vertex = dest;

	stack[top++] = vertex;

	while(1){
		number_visiting_city++;
		vertex = path[vertex];
		stack[top++] = vertex;
		if(vertex == src)
			break;
	}

	int second_country=stack[top-2];

	while(--top >= 0){
		printf("%d", stack[top]);
		T->flight_path[top] = stack[top];
		if(top > 0) printf("->");
	}
	printf("\n");
	//return second_country;
}