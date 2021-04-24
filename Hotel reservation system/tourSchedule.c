#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definition.h"
#include "Hotel.h"
#include "Reservation.h"

#include<time.h>
typedef enum{ false, true }bool;
/////////////////////////////

typedef struct taxi_info {
	int preprice;
	int price;
	int duration;
}taxi_n;
typedef struct _price
{
	int taxi;
	int pre_taxi;
	int bus;
	int pre_bus;
	int subway;
	int train;
	int pre_train;
}price;
typedef struct _dur
{
	int taxi;
	int bus;
	int train;
	int subway;
	int base;

}duration;
typedef struct train_info {
	int preprice;
	int price;
	int duration;
}train_n;
typedef struct bus_info {
	int preprice;
	int price;
	int duration;
}bus_n;
typedef struct subway_info {
	int price;
	int duration;
}subway_n;
typedef struct {
	train_n *train;
	bool train_flag;
	bus_n *bus;
	bool bus_flag;
	taxi_n *taxi;
	subway_n *subway;
	bool subway_flag;
}transport;

typedef struct _Node
{
	int name;
	int link_cnt;
	transport *link;
	struct _Node* next;
}GNode;
void initGNode(GNode* pnode)
{
	pnode->link_cnt = 0;
	pnode->link = NULL;
	pnode->next = NULL;
}
typedef struct
{
	int num;
	GNode** heads;
}Graph;
typedef struct route
{
	int num;
	int bus;
	int prebus;
	int taxi;
	int pretaxi;
	int train;
	int pretrain;
	int subway;
	int durbus;
	int durtaxi;
	int dursubway;
	int durtrain;
	int base;
	int route[100];
	price pri[100];
}route;
//////////////////////////////
void CreateGraph(Graph *pgraph, int num)
{
	pgraph->num = num;
	pgraph->heads = (GNode**)malloc(sizeof(GNode*)*num);
	int i;
	for (i = 0; i < num; i++)
	{
		pgraph->heads[i] = (GNode*)malloc(sizeof(GNode));
		pgraph->heads[i]->next = NULL;
		pgraph->heads[i]->name = i;
	}
}
void DestroyGraph(Graph* pgraph)
{
	int i;
	for (i = 0; i < pgraph->num; i++)
	{
		GNode* cur = pgraph->heads[i];
		while (cur != NULL)
		{
			GNode* temp = cur;
			cur = cur->next;
			free(temp);
		}
	}
	free(pgraph->heads);
}
bool valid(Graph*pgraph, int src, int dest)
{
	if (src == dest)
	{
		return false;
	}
	GNode*cur;
	///
	cur = pgraph->heads[src];
	while (cur->next != NULL)
	{
		if (cur->name == dest)
		{
			return false;
		}
		cur = cur->next;
	}
	/////


	return true;
}
////////////////////////////////////////////

void swap(route *a, route* b)
{
	route temp = *a;
	*a = *b;
	*b = temp;
}
void sort(route* arr, int num)
{
	int i, j;
	for (i = 0; i < num - 1; i++)
	{
		for (j = 0; j < num - i - 1; j++)
		{
			if (arr[j].pretaxi>arr[j + 1].pretaxi)
			{
				swap(&arr[j], &arr[j + 1]);
			}
		}
	}
}
void swap_1(int *a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
void sort_1(int* arr, int num)
{
	int i, j;
	for (i = 0; i < num - 1; i++)
	{
		for (j = 0; j < num - i - 1; j++)
		{
			if (arr[j]>arr[j + 1])
			{
				swap_1(&arr[j], &arr[j + 1]);
			}
		}
	}
}

///////////////////////////////////////////

int k;
int cnt = 0;
route save[10];

route *confirmed;
int route_count = 0;
void AddEdge(Graph* pgraph, int src, int dest)
{
	GNode* newNode1, *newNode2, *cur;
	newNode1 = (GNode *)malloc(sizeof(GNode));
	initGNode(newNode1);
	newNode1->link = (transport*)malloc(sizeof(transport));
	transport *info = newNode1->link;
	info->bus = (bus_n*)malloc(sizeof(bus_n));
	info->bus->duration = (rand() % 2) + 1;
	info->bus->price = ((int)100 / info->bus->duration) * 100;
	info->bus->preprice = ((int)100 / info->bus->duration) * 150;
	info->subway = (subway_n*)malloc(sizeof(subway_n));
	info->subway->duration = (rand() % 2) + 1;
	info->subway->price = ((int)100 / info->subway->duration) * 100;
	info->taxi = (taxi_n*)malloc(sizeof(taxi_n));
	info->taxi->duration = (rand() % 2) + 1;
	info->taxi->price = ((int)(100 / info->taxi->duration)) * 100;
	info->taxi->preprice = ((int)(100 / info->taxi->duration)) * 150;
	info->train = (train_n*)malloc(sizeof(train_n));
	info->train->duration = (rand() % 2) + 1;
	info->train->price = ((int)100 / info->train->duration) * 100;
	info->train->preprice = ((int)100 / info->train->duration) * 150;

	cnt = cnt + 4;
	newNode1->name = dest;
	newNode1->next = NULL;
	cur = pgraph->heads[src];
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = newNode1;
	pgraph->heads[src]->link_cnt++;

}

//int route[100][100] = { -1};
int r_cnt = 0;
//////////////////////////////////////////////////

int path[100] = { 0, };
bool visited[100] = { false, };
int path_index = 0;
////////////////////////////////////////////////
void printAllPaths(Graph* pgraph, int s, int d)
{
	printf("\n");

	printAllPathsUtil(pgraph, s, d);
}
int printAllPathsUtil(Graph* pgraph, int u, int d)
{
	if (r_cnt == 10)
	{
		return 0;
	}

	price* sum = (price*)malloc(sizeof(price));
	sum->taxi = 0; sum->bus = 0; sum->subway = 0; sum->train = 0; sum->pre_bus = 0;
	sum->pre_taxi = 0; sum->pre_train = 0;
	duration* dur = (duration*)malloc(sizeof(duration));
	dur->bus = 0; dur->taxi = 0; dur->subway = 0; dur->train = 0; dur->base = 0;

	visited[u] = true;

	path[path_index] = u;
	path_index++;
	/*if (path_index > 10)
	{
	return;
	}*/

	if (u == d)
	{


		int i;


		for (i = 0; i < path_index; i++)
		{

			if (!(i == path_index - 1))
			{
				GNode*cur = pgraph->heads[path[i]]->next;
				while (1)
				{
					//printf("媛寃??뷀븯??以?\n");

					if (cur->name == path[i + 1])
					{
						break;
					}
					cur = cur->next;
				}
				sum->bus = sum->bus + cur->link->bus->price;
				sum->pre_bus = sum->pre_bus + cur->link->bus->preprice;
				sum->taxi = sum->taxi + cur->link->taxi->price;
				sum->pre_taxi = sum->pre_taxi + cur->link->taxi->preprice;
				sum->train = sum->train + cur->link->train->price;
				sum->pre_train = sum->pre_train + cur->link->train->preprice;
				sum->subway = sum->subway + cur->link->subway->price;
				dur->bus = dur->bus + cur->link->bus->duration;
				dur->taxi = dur->taxi + cur->link->taxi->duration;
				dur->subway = dur->subway + cur->link->subway->duration;
				dur->train = dur->train + cur->link->train->duration;
				dur->base = dur->base + 8;

			}
			//route[r_cnt][i] = path[i];

			//printf("%d ", path[i]);
		}

		if (dur->bus <50 || dur->taxi <50 || dur->train <50 || dur->subway <50)
		{
			r_cnt++;
			save[route_count].num = path_index;
			for (i = 0; i < path_index; i++)
			{
				save[route_count].route[i] = path[i];
				save[route_count].bus = sum->bus;
				save[route_count].subway = sum->bus;
				save[route_count].taxi = sum->taxi;
				save[route_count].train = sum->train;
				save[route_count].prebus = sum->pre_bus;
				save[route_count].pretaxi = sum->pre_taxi;
				save[route_count].pretrain = sum->pre_train;
				save[route_count].durbus = dur->bus;
				save[route_count].durtaxi = dur->taxi;
				save[route_count].durtrain = dur->train;
				save[route_count].dursubway = dur->subway;
				save[route_count].base = dur->base;
			}
			int j;

			route_count++;




		}
	}

	else
	{
		GNode*cur = pgraph->heads[u]->next;
		while (cur != NULL)
		{
			if (!visited[cur->name])
			{

				printAllPathsUtil(pgraph, cur->name, d);
			}
			cur = cur->next;
		}
	}
	path_index--;
	visited[u] = false;
}

void Showroute(route* save,int start,int end) {
	int j;
	int i;
	for (i = start; i < end; i++)
	{

	printf("<option %d>\n\n", i+1);
	for (j = 0; j < save[i].num; j++)
	{
	char buf[4] = { 0, };
	int t = save[i].route[j] + 100;
	_itoa(t, buf, 10);
	buf[0] = '0';
	if (j == save[i].num - 1)
	printf("SITE_%s. ", buf);
	else
	printf("SITE_%s--> ", buf);
	}
	printf("\n");
	printf("\t <Price>\n\t <site> %d hours\n\n taxi/premium taxi : %d/%d(%dhours) \n bus/premium bus : %d/%d(%dhours) \n train/premium train : %d/%d(%dhours) \n subway : %d(%dhours)\n\n", save[i].base,
	save[i].taxi, save[i].pretaxi, save[i].durtaxi, save[i].bus, save[i].prebus, save[i].durbus, save[i].train, save[i].pretrain, save[i].durtrain, save[i].subway,
	save[i].dursubway);
	}
}
RInfo Choosetransport(RInfo Reserve,route selection) {
	
	printf("===========================================Please Choose the transport===========================================\n");
	printf("(1) Taxi : cost : %d\ttime : %d\n", selection.taxi,selection.durtaxi);
	printf("(2) Premium Taxi cost : %d\ttime : %d\n", selection.pretaxi, selection.durtaxi);
	printf("(3) Bus cost : %d\ttime : %d\n", selection.bus,selection.durbus);
	printf("(4) Premium Bus cost : %d\ttime : %d\n", selection.prebus, selection.durbus);
	printf("(5) Train cost : %d\ttime : %d\n", selection.train,selection.durtrain);
	printf("(6) Premium Train cost : %d\ttime : %d\n", selection.pretrain, selection.durtrain);
	printf("(7) Subway cost : %d\ttime : %d\n", selection.subway,selection.dursubway);
	printf("==================================================================================================================\n");
	printf("Please input 1 to 7 to choose your option : ");

	for (;;) {
		scanf("%d", &option);
		getchar();

		if (option < 1 || option > 7)
			printf("Invalid Option. Please write again : ");
		else
			break;
	}
	
	Reserve.r_num = selection.num;
	Reserve.peroid += selection.base;
	switch (option) {
	case 1:
		strcpy(Reserve.tranport, "Taxi");
		Reserve.remainder -= selection.taxi;
		Reserve.T_cost += selection.taxi;
		Reserve.transport_cost = selection.taxi;
		Reserve.peroid += selection.durtaxi;
		for (int loop = 0; loop < selection.num; loop++) {
			Reserve.route[loop] = selection.route[loop];
		}
		break;
	case 2:
		strcpy(Reserve.tranport,"Premium Taxi");
		Reserve.remainder -= selection.pretaxi;
		Reserve.T_cost += selection.pretaxi;
		Reserve.transport_cost = selection.pretaxi;
		Reserve.peroid += selection.durtaxi;
		for (int loop = 0; loop < selection.num; loop++) {
			Reserve.route[loop] = selection.route[loop];
		}
		break;
	case 3:
		strcpy(Reserve.tranport, "Bus");
		Reserve.remainder -= selection.bus;
		Reserve.T_cost += selection.bus;
		Reserve.transport_cost = selection.bus;
		Reserve.peroid += selection.durbus;
		for (int loop = 0; loop < selection.num; loop++) {
			Reserve.route[loop] = selection.route[loop];
		}
		break;
	case 4:
		strcpy(Reserve.tranport, "Premium Bus");
		Reserve.remainder -= selection.prebus;
		Reserve.T_cost += selection.prebus;
		Reserve.peroid += selection.durbus;
		Reserve.transport_cost = selection.prebus;
		for (int loop = 0; loop < selection.num; loop++) {
			Reserve.route[loop] = selection.route[loop];
		}
		break;
	case 5:
		strcpy(Reserve.tranport, "Train");
		Reserve.remainder -= selection.train;
		Reserve.T_cost += selection.train;
		Reserve.transport_cost = selection.train;
		Reserve.peroid += selection.durtrain;
		for (int loop = 0; loop < selection.num; loop++) {
			Reserve.route[loop] = selection.route[loop];
		}
		break;
	case 6:
		strcpy(Reserve.tranport, "Premium Train");
		Reserve.remainder -= selection.pretrain;
		Reserve.T_cost += selection.pretrain;
		Reserve.transport_cost = selection.pretrain;
		Reserve.peroid += selection.durtrain;
		for (int loop = 0; loop < selection.num; loop++) {
			Reserve.route[loop] = selection.route[loop];
		}
		break;
	case 7:
		strcpy(Reserve.tranport, "Subway");
		Reserve.remainder -= selection.subway;
		Reserve.T_cost += selection.subway;
		Reserve.transport_cost = selection.subway;
		Reserve.peroid += selection.dursubway;
		for (int loop = 0; loop < selection.num; loop++) {
			Reserve.route[loop] = selection.route[loop];
		}
		break;
	}
	
	printf("Transport : %s\nCost : %d\n",Reserve.tranport,Reserve.T_cost);

	return Reserve;
}
void ShowReservation(RNode *data) {
	// 생성된 ID, 출발지, 도착지, 경로(와 그 정보), 호텔(과 그 정보), 설정 예산, 남은 예산을 가지고 트리를 작성해주세요
	printf("ID : %d\nPeriod : %d(Day)\n",data->ID, data->peroid/24);
	
	printf("=========================================Route=========================================\n");
	printf("Departure : %s\t Destination : %s\n", data->Ssite, data->Esite);
	for (int loop = 0; loop < data->r_num; loop++) {
		printf("SITE_%d\t", data->route[loop]);
	}
	printf("\nTransportation : %s\tTransportation cost : %d\n", data->tranport,data->transport_cost);

	printf("===========================================================================================\n\n");
	
	printf("=========================================Hotel=========================================\n");
	for (int loop = 0; loop < data->r_num; loop++) {
		printf("Name : SITE_%d_%s\t Level : %d\t Duration : %d\t Price :%d\n", data->route[loop], data->hotel_name, data->hotel_level, data->hotel_duration, data->hotel_price);
	}
	printf("===========================================================================================\n\n");
	printf("=========================================Cost=========================================\n");
	printf("Total_cost : %d\nRemainder : %d\n",  data->T_cost, data->remainder);
	printf("===========================================================================================\n\n");
}

route copy(route select, route save) {
	select.base = save.base;
	select.num = save.num;

	select.bus = save.bus;
	select.prebus = save.prebus;
	
	select.durbus = save.bus;
	select.subway = save.subway;
	select.dursubway = save.dursubway;
	select.taxi = save.taxi;
	select.pretaxi = save.pretaxi;
	
	select.durtaxi = save.durtaxi;
	select.train = save.train;
	select.pretrain = save.pretrain;
	select.durtrain = save.durtrain;
	
	for (int loop = 0; loop < save.num; loop++) {
		select.route[loop] = save.route[loop];
	}
	return select;
}


////////////////////////////////////////////////////////
void clear();
void hello();
void thankyou();
void printSites();
void getSite(char * printString, char place[MAX]);
void getOption();
int isYes(char * string);
int isNo(char * string);
int checkAns();
int validSite(char * place);




int main() {
    char isConfirmed[5];
	char buffer[2];
    int tmp, flag = 0;
	// Hotel을 위한 변수 추가
	char Hname[110][30] = { 0 , };
	HNode* Hroot = (HNode*)malloc(sizeof(HNode));
	HInfo *table = malloc(sizeof(HInfo) * 10);
	// Reservation을 위한 변수 추가
	RInfo Reservation;
	memset(&Reservation, 0, sizeof(route));
	RNode *Rroot = (RNode*)malloc(sizeof(RNode));
	RNode *temp = (RNode*)malloc(sizeof(RNode));
	//////////////////////////////////
	route selection;
	memset(&selection, 0, sizeof(route));

	Graph map;
	CreateGraph(&map, 100);
	int i;
	int src, dest;
	srand(time(NULL));
	while (!(cnt == 1200))
	{
	check:;
		src = rand() % 100;
		dest = rand() % 100;
		if (!valid(&map, src, dest))
		{
			//printf(" %d %d 중복\n", src, dest);
			goto check;
		}
		AddEdge(&map, src, dest);

	}
	///////////////////////////////////////////////
    hello();

    for(;;) {
        /* ID INPUT */
        printf("Please input your ID number\n(If you are new, write -1): ");
        scanf("%d", &tmp);
        getchar();
        clear();

        /* CHECK RESERVATION INFORMATION */
        if(tmp <= ID && tmp > 0) {
            printf("This is your reservation information:\n\n");
            
            // 여기다가 reservation에서 ID를 이용해 정보를 프린트해주세요!!
			temp = R_Search(Rroot,ID);
			ShowReservation(temp);

            printf("Want to end the program? (yes / no): ");
            flag = checkAns();
            if(flag)
                break;
            if(!flag) {
                clear();
                continue;
            }
        }

        /* CHECK ID */
        if(tmp > ID || tmp == 0) {
            printf("Your ID number is wrong.\n");
            continue;
        }

        /* GIVE ID */
        ID++;
        printf("This is your ID number: %d\n", ID);
		Reservation.ID = ID;

        /* GET BUDGET */
        printf("Please input your budget: ");
        scanf("%d", &totalBudget);
        getchar();
        Reservation.remainder = totalBudget;

        /* CHOOSE START & DESTINATION SITES */
        for(;;) {
			int h;
		again:;
			printSites();
			int start, end;
			char buf[4] = { 0, };
            getSite("Where is your start place? : ", startPlace);
			strcpy(Reservation.Ssite,startPlace);
			for (h = 0; h < 3; h++)
			{
				buf[h] = startPlace[5 + h];
			}
			start = atoi(buf);
			memset(buf, 0x00, sizeof(buf));
            getSite("Where is your destination? : ", destination);
			strcpy(Reservation.Esite,destination);
			for (h = 0; h < 3; h++)
			{
				buf[h] = destination[5 + h];
			}
			end = atoi(buf);
		
            printf("\nYour start place : %s\n", startPlace);
            printf("Your destination: %s\n", destination);
            printf("Confirmed? (yes or no): ");
			
			
            flag = checkAns();
			if (flag)
			{
				printf("Please wait for a few minute.....\n");
				printAllPaths(&map, start, end);
				if (route_count == 0)
				{
					int u;
					printf("there's no route please press any key and press enter \n");
					scanf("%d", &u);
					goto again;
				}
				sort(save, route_count);

				break;
			}
			
			if (!flag)
			{
				clear();

			}
        }
		
        /* CHOOSE ROUTE */
        for(;;) {
            clear();

			Showroute(save,0,10);
			printf("Select travel product\n");
            getOption();

			// selection에 선택한 경로 저장
			
            printf("Confirmed? (yes or no): ");

			selection = copy(selection, save[option]);
			
			printf("\n");


            flag = checkAns();
            if(flag)
                break;
            if(!flag)
                clear();
        }
		/////////////
		confirmed = (route*)malloc(sizeof(route));
		confirmed->num;
		confirmed->base = 0; confirmed->bus = 0; confirmed->durbus=save[option].durbus; confirmed->dursubway=save[option].dursubway; confirmed->durtaxi=save[option].durtaxi;
		confirmed->durtrain = save[option].durtrain; confirmed->prebus = 0; confirmed->pretaxi = 0;
		confirmed->subway = 0; confirmed->taxi = 0; confirmed->train = 0;
		int no[3];
		no[0]=rand()%((save[option].num)-2)+1;
		no[1]= rand() % ((save[option].num) - 2) + 1;
		if (no[0] == no[1])
		{
			while (1)
			{
				no[1]=rand() % ((save[option].num) - 2) + 1;
				if (no[0] != no[1])
				{
					break;
				}
				
			}
		}
		no[2] = rand() % ((save[option].num) - 2) + 1;
		if (no[0]== no[2]||no[1]==no[2])
		{
			if (no[0] == no[2])
			{
				while (1)
				{
					no[2] = rand() % ((save[option].num) - 2) + 1;
					if (no[0] != no[2])
					{
						break;
					}
				}
			}
			else
			{
				while (1)
				{
					no[2] = rand() % ((save[option].num) - 2) + 1;
					if (no[1] != no[2])
					{
						break;
					}
				}
			}
		}
		sort_1(no, 3);
	
		confirmed->num = 5;
		confirmed->route[0] = save[option].route[0];
		
		confirmed->route[1] = save[option].route[no[0]];
		confirmed->pri[1].bus = save[option].pri[no[0]].bus; confirmed->pri[1].pre_bus = save[option].pri[1].pre_bus; confirmed->pri[1].pre_taxi = save[option].pri[no[0]].pre_taxi;
		confirmed->pri[1].subway = save[option].pri[no[0]].subway; confirmed->pri[1].taxi = save[option].pri[no[0]].taxi; confirmed->pri[1].train = save[option].pri[no[0]].train;
		
		confirmed->route[2] = save[option].route[no[1]];
		confirmed->pri[2].bus = save[option].pri[no[1]].bus; confirmed->pri[2].pre_bus = save[option].pri[no[1]].pre_bus; confirmed->pri[2].pre_taxi = save[option].pri[no[1]].pre_taxi;
		confirmed->pri[2].subway = save[option].pri[no[1]].subway; confirmed->pri[2].taxi = save[option].pri[no[1]].taxi; confirmed->pri[2].train = save[option].pri[no[1]].train;
		
		printf("\n%d\n", confirmed->route[2]);
		confirmed->route[3] = save[option].route[no[2]];
		confirmed->pri[3].bus = save[option].pri[no[2]].bus; confirmed->pri[3].pre_bus = save[option].pri[no[2]].pre_bus; confirmed->pri[3].pre_taxi = save[option].pri[no[2]].pre_taxi;
		confirmed->pri[3].subway = save[option].pri[no[2]].subway; confirmed->pri[3].taxi = save[option].pri[no[2]].taxi; confirmed->pri[3].train = save[option].pri[no[2]].train;
		
		confirmed->route[4] = save[option].route[(save[option].num)-1];
		//printf("\n\n%d\n", (save[option].num) - 1);
		confirmed->pri[4].bus = save[option].pri[(save[option].num) - 1].bus; confirmed->pri[4].pre_bus = save[option].pri[(save[option].num) - 1].pre_bus; confirmed->pri[4].pre_taxi = save[option].pri[(save[option].num) - 1].pre_taxi;
		confirmed->pri[4].subway = save[option].pri[(save[option].num) - 1].subway; confirmed->pri[4].taxi = save[option].pri[(save[option].num) - 1].taxi; confirmed->pri[4].train = save[option].pri[(save[option].num) - 1].train;
		
		
		confirmed->bus = save[option].bus; confirmed->prebus = save[option].prebus; confirmed->pretaxi = save[option].pretaxi;
		confirmed->subway = save[option].subway; confirmed->taxi = save[option].taxi; confirmed->train = save[option].train;

		confirmed->base = 40; 
		///////////////////////
		/* CHOOSE TRANSPORT */
		for (;;) {
			clear();
			int j;
			printf("<recommendation sites>\n\n");
			for (j = 0; j < confirmed->num; j++)
			{
				char buf[4] = { 0, };
				int t = confirmed->route[j] + 100;
				_itoa(t, buf, 10);
				buf[0] = '0';
				if (j == confirmed->num - 1)
					printf("SITE_%s. ", buf);
				else
					printf("SITE_%s--> ", buf);
			}
				
			printf("\n");
			
			Reservation = Choosetransport(Reservation,selection);
			//getOption();
			
			printf("Confirmed? (yes or no): ");

			
			flag = checkAns();
			if (flag)
				break;
			if (!flag)
				clear();
		}

        printf("\nYour remain budget: %d\tCumlative cost : %d\n", Reservation.remainder, Reservation.T_cost);
        printf("\n(Please press ENTER to continue)\n");
	    fgets(buffer, 2, stdin);


        // 유저가 선택한 경로와 transportation등의 정보를 option을 참조하여 definition.h에 있는 변수에다가 저장해주시고 remainBudget을 업데이트 해주세요


        /* CHOOSE HOTEL */
        for(;;) {
            clear();


            // 출발지, 도착지, 예산 (필요하다면 경로까지) 을 가지고 선택 가능 호텔을 보여주세요

			Load_Data(Hname);
			Hroot = Make_Hotel_tree(Hname);
			table = Show_list(Hroot, Reservation.remainder/Reservation.r_num);
            getOption();

            printf("Confirmed? (yes or no): ");
			strcpy(Reservation.hotel_name,table[option].name);
			Reservation.hotel_level = table[option].level;
			Reservation.hotel_duration = table[option].duration;
			Reservation.hotel_price = table[option].price;
			Reservation.peroid += table[option].duration*Reservation.r_num;
			Reservation.remainder -= table[option].price*Reservation.r_num;
			Reservation.T_cost += table[option].price*Reservation.r_num;
			free(table);
            flag = checkAns();
            if(flag)
                break;
            if(!flag)
                clear();
        }
        printf("\nYour remain budget : %d\t totla budget : %d\n", Reservation.remainder, Reservation.T_cost);
        printf("\n(Please press ENTER to continue)\n");
	    fgets(buffer, 2, stdin);


        // 유저가 선택한 호텔과 호텔의 정보를 option을 참조하여 definition.h에 있는 변수에다가 저장해주시고 remainBudget을 업데이트 해주세요


        // 생성된 ID, 출발지, 도착지, 경로(와 그 정보), 호텔(과 그 정보), 설정 예산, 남은 예산을 가지고 트리를 작성해주세요
		Rroot = R_Make_R_Tree();
		R_RB_Insert(&Rroot,Reservation);
		
		


        /* END */
        clear();
        
		printf("ID : %d\nPeriod : %d\n", Reservation.ID, Reservation.peroid);
		
		printf("Route\n");
		printf("Departure : %s\t Destination : %s\n", Reservation.Ssite, Reservation.Esite);
		for (int loop = 0; loop < Reservation.r_num; loop++) {
			printf("SITE_%d\t", Reservation.route[loop]);
		}
		printf("\nTransportation : %s\tTransportation cost : %d\n", Reservation.tranport, Reservation.transport_cost);
		
		printf("Hotel\n");
		printf("Name : %s\t Level : %d\t Duration : %d\t Price :%d\n", Reservation.hotel_name, Reservation.hotel_level, Reservation.hotel_duration, Reservation.hotel_price);
		printf("Total_cost : %d\nRemainder : %d\n", Reservation.T_cost, Reservation.remainder);

		printf("Your reservation is end.\n");
        printf("You can check your reservation information if you input your ID : %d\n\n", ID);
        printf("Want to end the program? (yes / no): ");
        flag = checkAns();
        if(flag)
            break;
        if(!flag) {
            clear();
            continue;
        }
    }

    thankyou();

    return 0;
}

void clear() {
	int i;

	for (i = 0; i<70; i++)
		printf("\n");
}

void hello() {
	int num, i;
	char buffer[2];

    clear();

    printf("                            \"'^^', \"\n");
    printf("                    ioEP@/////////8IIXeX/\"\n");
    printf("                ;@E@e%%N/@e////////N.......oe;\n");
    printf("             ~NPEPNNI...Ee/////eEX..........&@»\n");
    printf("          \"%%E@aNe8NE/eX..E@////NX............N//@o\n");
    printf("         %%P8N8@@8NLo@N8%%.@//eLI..L@eNI.....%%N/N@e/N/\n");
    printf("       ~8//////NEEXN88....Ne@.............N//eeNNN///\n");
    printf("      =@/////N&..I8/eN@...............%%8@.%%Na8%%@N////N\"\n");
    printf("     .@///////eNN/e////N%%............oE8@@L8NN@///////N\"\n");
    printf("    /N//////////N@//@NNEe..............oE@/////////////@\n");
    printf("    8///////////////@E@.................ee/eea////N8eN//%%\n");
    printf("   =e/////////////@o..................N//NIXENEaeNNNN@N/8,\n");
    printf("   L////////////Ee....................L8NNNN8@X&@e888///eI\n");
    printf("   e///////////NI....................X@//////NLeNX&%%N////L\n");
    printf("   /EP///eeLL%%8X....................X@/////////////ea///@@\n");
    printf("   /&N@//@..IXEN%%..................e////////////////N@////\n");
    printf("   X..I@@e8eN...XNeI...............e/////////////////@@//&\n");
    printf("   »o......oNN..%%e%%I...............N//////////////////E@E'\n");
    printf("    L........%%eN////e8L&............N///////////////////%%\n");
    printf("    \"e......../e////////@.............I...&@//////////eN\n");
    printf("     ,e......I8///////////NN%%.............I8//////NNeee\"\n");
    printf("      ,e.......e////////////eX.............&N///////@L\n");
    printf("        o&......LN/////////N&..............X@//////N»\n");
    printf("         'eI.....IN////////@...............@/////ee\"\n");
    printf("           ^eI...I8/////@X.................@///@X\"\n");
    printf("              =e&.N///NNX..................//N;\n");
    printf("                 ieNe8o.................IL/»\n");
    printf("                     '.Le/o&&IIII&Xe/o/\"\n\n");

    printf("  ##      ######  ######  ##  ######     ######  ######   ##\n");
    printf("  ##      ##        ##    ##  ##         ##      ##  ##   ##\n");
    printf("  ##      ######    ##        ######     ## ###  ##  ##   ##\n");
    printf("  ##      ##        ##            ##     ##  ##  ##  ##\n");
    printf("  ######  ######    ##        ######     ######  ######   ##\n");
    
	printf("\n(Please press ENTER to set your tour schedule)\n");
	fgets(buffer, 2, stdin);
	clear();
}

void thankyou() {
    clear();

    printf("                                                  **\n");
    printf("                                            #%%%%%%%%%%%%%%\n");
    printf("                                     *%%%%%%%%%%%%%%%%%%%%%%(%%%%\n");
    printf("                               %%%%%%%%%%%%%%%%(   #%%%%%%. %%%%%%\n");
    printf("                        (%%%%%%%%%%%%%%%%       .%%%%%%%%,   %%%%,\n");
    printf("                  %%%%%%%%%%%%%%%%/           %%%%(##*     %%%%\n");
    printf("           #%%%%%%%%%%%%%%%%               %%%%%% %%%%*      (%%%%\n");
    printf("         %%%%%%%%*                  .%%%%  /(*        %%%%%%\n");
    printf("           %%%%%%%%%%              %%%%,  (%%(          %%%%,\n");
    printf("              %%%%%%%%%%        %%%%%%   /##            %%%%\n");
    printf("                 *%%%%%%%%  *%%%%    (%%/             (%%%%\n");
    printf("                    .%%%%%%%%    /%%%%               %%%%%%\n");
    printf("                       %%%%, *%%#                 %%%%(\n");
    printf("                       %%%%%% %%%%%%%%%%.              %%%%\n");
    printf("                        %%%%*%%. %%%%%%%%%%,          #%%%%\n");
    printf("                        #%%%%%% %%%%%%  %%%%%%%%.       %%%%%%\n");
    printf("                         %%%%%%%%%%       %%%%%%%%/    %%%%/\n");
    printf("                         %%%%%%%%           %%%%%%%%, %%%%\n");
    printf("                                           %%%%%%%%%%\n");
    printf("                                              %%.\n\n");

    printf("######  ##  ##   ####   ##  ##  ##  ##    ##  ##  ######  ##  ##  ##\n");
	printf("  ##    ##  ##  ##  ##  ### ##  ## ##     ##  ##  ##  ##  ##  ##  ##\n");
	printf("  ##    ######  ######  ### ##  ####      ######  ##  ##  ##  ##  ##\n");
	printf("  ##    ##  ##  ##  ##  ## ###  ## ##       ##    ##  ##  ##  ##\n");
	printf("  ##    ##  ##  ##  ##  ##  ##  ##  ##      ##    ######  ######  ##\n\n");

}

void printSites() {
    int i;

    clear();
    printf("                                 [SITES]\n");
    printf("========================================================================\n");
    for(i=0;i<=99;i++) {
        printf("SITE_%03d\t", i);
        if(i%5 == 4)
            printf("\n");
    }
    printf("========================================================================\n");
}

void getSite(char * printString, char place[MAX]) {
    int isValid = 0;

    printf("%s", printString);

    while(!isValid) {
        memset(place, '\0', MAX);
        fgets(place, MAX, stdin);
        if(place[strlen(place)-1] == '\n')
            place[strlen(place)-1] = '\0';
        isValid = validSite(place);
        if(!isValid) {
            printf("Invalid Site. Please write again : ");
        }
    }
}

void getOption() {

	/*int j;
	int i;
	for (i = 0; i < route_count; i++)
	{

		printf("<option %d>\n\n", i);
		for (j = 0; j < save[i].num; j++)
		{
			char buf[4] = { 0, };
			int t = save[i].route[j] + 100;
			_itoa(t, buf, 10);
			buf[0] = '0';
			if (j == save[i].num - 1)
				printf("SITE_%s. ", buf);
			else
				printf("SITE_%s--> ", buf);
		}
		printf("\n");
		printf("\t <Price>\n\t <site> %d hours\n\n taxi/premium taxi : %d/%d(%dhours) \n bus/premium bus : %d/%d(%dhours) \n train/premium train : %d/%d(%dhours) \n subway : %d(%dhours)\n\n", save[i].base,
			save[i].taxi, save[i].pretaxi, save[i].durtaxi, save[i].bus, save[i].prebus, save[i].durbus, save[i].train, save[i].pretrain, save[i].durtrain, save[i].subway,
			save[i].dursubway);
	}*/
    printf("Please input 1 to 10 to choose your option : ");

    for(;;) {
        scanf("%d", &option);
        getchar();

        if(option < 1 || option > 10)
            printf("Invalid Option. Please write again : ");
        else
            return;
    }
}

int isYes(char * string) {
    return !strcmp(string, "yes") || !strcmp(string, "Yes") || !strcmp(string, "YES") || !strcmp(string, "Y") || !strcmp(string, "y");
}

int isNo(char * string) {
    return !strcmp(string, "no") || !strcmp(string, "No") || !strcmp(string, "NO") || !strcmp(string, "N") || !strcmp(string, "n");
}

int checkAns() {
    char ans[5];
    int c;

    for(;;) {
        memset(ans, '\0', 5);
        fgets(ans, 5, stdin);
        if(ans[strlen(ans)-1] == '\n')
            ans[strlen(ans)-1] = '\0';
        if(isYes(ans))
            return 1;
        else if(isNo(ans)) {
            return 0;
        }
        else {
            printf("Your answer is invalid. Please write again: ");
            while(c = getchar()) {
                if(c=='\n' || c=='\0')
                    break;
            }
        }
    }

    return 0;
}

int validSite(char * place) {
    char stmp[10] = {0, };
    int tmp;

    if(strlen(place) != 8)
        return 0;
    tmp = atoi(place+5);
    if(tmp < 0 || tmp > 99)
        return 0;
    sprintf(stmp, "SITE_%03d", tmp);
    return !strcmp(stmp, place);
}