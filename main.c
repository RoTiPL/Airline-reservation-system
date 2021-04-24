/*
    Airline Reservation System
*/
#define _CRT_SECURE_NO_WARNINGS
#include "SCHEDULE.h"
#include "PATH.h"
#include "STRUCT.h"
#include "RESERVATION.h"
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <conio.h> //getch();
#include <math.h>

void welcome();
void earth();
void textcolor(int color_number);
void menu();
int mov(int key);
void drw(void);

#define WID 50
#define HEI 20
int x = WID / 2;
int y = HEI / 2;
int count = 0;
int reservation_num = 0;

int main(){
   srand((unsigned)time(NULL));
   RBT* T = RB_INIT();
   Graph g;
   CreateGraph(&g, 26);

   int** city = (int**)malloc(sizeof(int*) * 26);
   for (int i = 0; i < 26; i++) {
      city[i] = (int*)malloc(sizeof(int) * 2);
   }
   CreateCity(city, 26);

   int cnt = 0;
   while (cnt < 100) {
      int src = rand() % 26;
      int dest = rand() % 26;
      if (src == dest) continue;
      if (IsEdge(&g, src, dest)) continue;
      AddEdge(&g, city, src, dest);
      cnt++;
   }

   char* name = (char*)malloc(sizeof(char) * 100);
   char source, destination, ticket_grade;
   int date;
   int m;
   welcome();

   textcolor(9);
   earth();

   system("cls");

   textcolor(15);

   drw();
   while (1) {
      m = mov(getchar());
      fflush(stdin);
      if (m == 0) {
         RB_INSERT(T, reservation_num);

         reservation_num++;

         printf("Please Write Your Name: ");
         scanf("%s", name);
         getchar();
         printf("Please Write Departure Point: ");
         scanf("%c", &source);
         getchar();

         printf("Please Write Arrival Point: ");
         scanf("%c", &destination);
         getchar();
         printf("Please Write Departure Date: ");
         scanf("%d", &date);
         printf("Please Write your ticket type( economy: e, business: b, first: f): ");
         scanf("%d", &ticket_grade);

         int src = (int)source - ALPHA_TO_NUM;
         int dest = (int)destination - ALPHA_TO_NUM;

         int*** month = CreateMonthSchedule(&g);

         shortest_path_time(&g, month, src, dest, date - 1, SEARCH_NODE(T, reservation_num));

         int number_visiting_city = number_visiting_citys();

         INSERT_INFORMATION(SEARCH_NODE(T, reservation_num), name, source, destination, ticket_grade, number_visiting_city);
         
      }
      else if (m == 1) {
         int key;

         printf("Please Write your reservation number to delete: ");
         scanf("%d", &key);
         RB_DELETE(T, key);
         printf("Delete!!\n");
      }
      else{
         
         int key;
         
         printf("Please Write your reservation number to see: ");
         scanf("%d", &key);
         PRINT_RESERVATION_INFORMATION(T, key);
         printf("\n");
      }
   }
}


void textcolor(int color_number) //콘솔창 출력색상을 나타내는 함수
{
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

void welcome() {
   puts("");
   puts("");
   puts("");
   puts("");
   printf("dMP dMP dMP  dMMMMMP  dMP     aMMMb    aMMMb   dMMMMMMMMb   dMMMMMP     dMMMMMMP   aMMMb        aMMMb   dMP   dMMMMb   dMMMMb   dMP      aMMMb    dMMMMb   dMMMMMP   dMMMMMP    dMP dMP      \n");
   printf("dMP dMP dMP  dMP      dMP    dMP VMP  dMP dMP  dMP dMP dMP  dMP           dMP     dMP dMP      dMP dMP  amr   dMP.dMP  dMP.dMP  dMP     dMP dMP   dMP dMP  dMP              PMP    dMP dMP      \n");
   printf("dMP dMP dMP  dMMMP    dMP    dMP      dMP dMP  dMP dMP dMP  dMMMP         dMP     dMP dMP      dMMMMMP  dMP   dMMMMK   dMMMMP   dMP     dMMMMMP   dMP dMP  dMMMMMP   dMMMMMP    dMP dMP      \n");
   printf("dMP.dMP.dMP  dMP      dMP    dMP.aMP  dMP.aMP  dMP dMP dMP  dMP           dMP     dMP.aMP      dMP dMP  dMP   dMP AMF  dMP      dMP     dMP dMP   dMP dMP  dMP              PMP                \n");
   printf(" VMMMPVMMP   dMMMMMP  dMMMMMP VMMMP    VMMMP   dMP dMP dMP  dMMMMMP       dMP      VMMMP       dMP dMP  dMP   dMP dMP  dMP      dMMMMMP dMP dMP   dMP dMP  dMMMMMP   dMMMMMP    dMP dMP      \n");
}

void earth() {

   puts("");
   puts("");
   puts("");
   puts("");

   textcolor(15);
   printf("                                                               BQQQBQBQQQBQQQBBBBBBB62LLLsrJ1KgBBBQBBBQBMQQBQQQQQQ\n");
   printf("                                                               QBMBQBQBQQQBBBBBBa,");
   textcolor(9);
   printf(";;.    ..  rB");
   textcolor(15);
   printf("    BBBBQBQBQBQBMQQ\n");
   printf("                                                               BMBQQMBQBBBBBQQs");
   textcolor(9);
   printf("  ;Ba7,   :rS;,,  rUg");
   textcolor(15);
   printf("  BBBBQBMBQBQQ\n");
   printf("                                                               MBMBQBQQQBBBLs");
   textcolor(9);
   printf("L::c;;J2D: ;Z2.B2 ,;  :cJr");
   textcolor(15);
   printf("GBBBMQQBMQQ\n");
   printf("                                                               BMQQBQBQBQw,");
   textcolor(9);
   printf("GP :; ar.:65J, ; s71BQM5Dgr ");
   textcolor(15);
   printf(" QBBQQBMNBQ\n");
   printf("                                                               MQQBQBQBB5.");
   textcolor(9);
   printf("7;::;   ,vsXar2aXBQEGQBBO2RRgHDg ");
   textcolor(15);
   printf("BBQQQMQ\n");
   printf("                                                               BMBMBQBBa");
   textcolor(9);
   printf("X;:PHZ7::pBgsSs:sBHPOOEDORgRDQDRMQpD ");
   textcolor(15);
   printf(" BBQB\n");
   printf("                                                               QBQBQBQX");
   textcolor(9);
   printf("i7:77, JLHMB1cPR2JXXKGggGEEgGRDR6EL : ");
   textcolor(15);
   printf(" QBQQ\n");
   printf("                                                               BMQQBBR");
   textcolor(9);
   printf("rrrGs  ;,L7cw:LiRBOEEOa56E2GZgOgggOB7:5B");
   textcolor(15);
   printf(" BBM\n");
   printf("                                                               QQQBBBa:");
   textcolor(9);
   printf("KgXZ;s;P5QgLrr aBBgOGMJDOE6HDDDMDMMgGGRB ");
   textcolor(15);
   printf("BB\n");
   printf("                                                               BMBQBg");
   textcolor(9);
   printf("RpgG  gJL,rB2cJLrr1J27rvJsPgEDREGOg6RM6LpB;");
   textcolor(15);
   printf("BM\n");
   printf("                                                               QBMBB");
   textcolor(9);
   printf(";cZE1rpHU  ;vLX:   Li   sP5U2HOBRRDggMsLHB;");
   textcolor(15);
   printf(" BB\n");
   printf("                                                               BQQQB");
   textcolor(9);
   printf("vKZDBBaPMJ;7OJZL       LJJw5p5r2MQBRMRBgRQ:");
   textcolor(15);
   printf(" BQ\n");
   printf("                                                               QQQBQ");
   textcolor(9);
   printf("5pgpDZDPpXgRRR6OBBQ    iL7LcwUXsL1UpQRQBGOQ:");
   textcolor(15);
   printf("BB\n");
   printf("                                                               BQBBB");
   textcolor(9);
   printf("5XgRO6XOOGHZSJ    J    sJsL2sS1r;wr7KDGRQBQ:");
   textcolor(15);
   printf("BR\n");
   printf("                                                               MQMBB");
   textcolor(9);
   printf("R11JJ2p6GpXwUSUsJ  arvssLr;7sLs;;vSBBGRaXM;");
   textcolor(15);
   printf("BQB\n");
   printf("                                                               BQQMQp");
   textcolor(9);
   printf("DR6P6pXXPGpZRBEGJ.   rsLi;rr77a; 7pBBBMB;");
   textcolor(15);
   printf(" QQB\n");
   printf("                                                               QBQBQBD");
   textcolor(9);
   printf(";JBBBEXwXEOp7wB6Es     Pc77rrrr, ;.:OQQB ");
   textcolor(15);
   printf("QMB\n");
   printf("                                                               BMQQBQB6");
   textcolor(9);
   printf("   LBBOKZZOP:rQSrsL  cKJUEZJSKMBBBXGB;;");
   textcolor(15);
   printf("MBMB\n");
   printf("                                                               MBMBQBQBB1");
   textcolor(9);
   printf("   XBQEZDMU6BQRQBp.JL2, .6QBBBRBBBR");
   textcolor(15);
   printf(" BMBQB\n");
   printf("                                                               BMQMQMBBBBGJ");
   textcolor(9);
   printf(",QBB1HMOgODMBrr1UHBJ    .2XggRRRM");
   textcolor(15);
   printf(" BQBQB\n");
   printf("                                                               QQQBMQQBBBBSX6,");
   textcolor(9);
   printf(" :R;r:;sUKME.:2E2:;; r21BMM ");
   textcolor(15);
   printf("BQBMBQBB\n");
   printf("                                                               BQBQBQQQBBBBQ1Ss");
   textcolor(9);
   printf(" ;:    ,  : HBQ1ii5v2UgQ ");
   textcolor(15);
   printf("QBQBMQQBQB\n");
   printf("                                                               QQMQQBMBQBQBQBBD7");
   textcolor(9);
   printf("      i:;:.,,.::rJ2RB ");
   textcolor(15);
   printf("BBBBMQMQMQMB\n");
   printf("                                                               BMQQBMBQBQBQBQBBBBQJ");
   textcolor(9);
   textcolor(9);
   printf(":, L,     : LZBB ");
   textcolor(15);
   printf("BBBQBQBQQMBMBB\n");
   printf("                                                               QQQBQBMBQQQBMBQBQBBBBBBBBQQBBBBBBBBBBBQBQBQQQBQBQBQ\n");

   puts("");
   puts("");
   puts("");
   puts("");
   puts("");
   puts("");
}

void menu() {
   textcolor(15);
   printf("       dMP dMP dMP  dMP dMP   aMMMb  dMMMMMMP    dMMMMb    aMMMb        dMP dMP   aMMMb    dMP dMP      dMP dMP dMP    aMMMb    MMMb  dMMMMMP\n");
   printf("     dMP dMP dMP  dMPMdMP  dMP dMP   dMP       dMP VMP   dMP dMP      dMP.dMP  dMP dMP   dMP dMP      dMP dMP dMP   dMP dMP  dMP dMP   dMP\n");
   printf("    dMP dMP dMP  dMP dMP  dMMMMMP   dMP       dMP.aMP   dMP.aMP       VMMP    dMP dMP   dMP dMP      dMP dMP dMP   dMMMMMP  dMP dMP   dMP\n");
   printf("    VMMMPVMMP   dMP dMP  dMP dMP   dMP       dMMMP     VMMMP       dA.dMP    dMP.aMP   dMP.aMP      dMP.dMP.dMP   dMP dMP  dMP dMP   dMP\n");

   puts("");
   puts("");
   puts("");
   puts("");
   puts("");
   puts("");

   printf("pleae press W to move upward, S to move downward\n");

   printf("■ 비행기 예약 \n\n\n\n\n\n\n");
   printf("   비행기 예약 취소 \n\n\n\n\n\n\n");
   printf("   예약 정보 확인 \n\n\n\n\n\n\n");


}

int mov(int key) {
   fflush(stdin);
   while (1) {
      if (key == 87 || key == 119) {
         count--;
         drw();
      }
      else if (key == 83 || key == 115) {
         count++;
         drw();
      }
      if (key == 97 || key == 65){break;}

      key = getchar();
      fflush(stdin);
   }
   switch (count) {
      case 0:
         return 0;
         break;

      case 1:
         return 1;
         break;

      case 2:
         return 2;
         break;

      default:
         return -1;
         break;

   }
}

void drw(void) {
   count = abs(count) % 3;
   switch (count) {
   case 0:
      system("cls");
      puts("");
      puts("");
      puts("");
      puts("");
      puts("");
      puts("");
      printf("          dMP dMP dMP  dMP dMP   aMMMb  dMMMMMMP    dMMMMb    aMMMb        dMP dMP   aMMMb    dMP dMP      dMP dMP dMP    aMMMb    MMMb  dMMMMMP\n");
      printf("     dMP dMP dMP  dMPMdMP  dMP dMP   dMP       dMP VMP   dMP dMP      dMP.dMP  dMP dMP   dMP dMP      dMP dMP dMP   dMP dMP  dMP dMP   dMP\n");
      printf("    dMP dMP dMP  dMP dMP  dMMMMMP   dMP       dMP.aMP   dMP.aMP       VMMP    dMP dMP   dMP dMP      dMP dMP dMP   dMMMMMP  dMP dMP   dMP\n");
      printf("    VMMMPVMMP   dMP dMP  dMP dMP   dMP       dMMMP     VMMMP       dA.dMP    dMP.aMP   dMP.aMP      dMP.dMP.dMP   dMP dMP  dMP dMP   dMP\n");
      printf("\n\n\n\n\n\n\n             pleae press W to move upward, S to move downward, A for choose the menu\n\n\n\n\n\n\n");

      printf("          ■ 비행기 예약 \n\n\n\n\n\n\n");
      printf("             비행기 예약 취소 \n\n\n\n\n\n\n");
      printf("             예약 정보 확인 \n\n\n\n\n\n\n");
      break;

   case 1:
      system("cls");
      puts("");
      puts("");
      puts("");
      puts("");
      puts("");
      puts("");
      printf("          dMP dMP dMP  dMP dMP   aMMMb  dMMMMMMP    dMMMMb    aMMMb        dMP dMP   aMMMb    dMP dMP      dMP dMP dMP    aMMMb    MMMb  dMMMMMP\n");
      printf("     dMP dMP dMP  dMPMdMP  dMP dMP   dMP       dMP VMP   dMP dMP      dMP.dMP  dMP dMP   dMP dMP      dMP dMP dMP   dMP dMP  dMP dMP   dMP\n");
      printf("    dMP dMP dMP  dMP dMP  dMMMMMP   dMP       dMP.aMP   dMP.aMP       VMMP    dMP dMP   dMP dMP      dMP dMP dMP   dMMMMMP  dMP dMP   dMP\n");
      printf("    VMMMPVMMP   dMP dMP  dMP dMP   dMP       dMMMP     VMMMP       dA.dMP    dMP.aMP   dMP.aMP      dMP.dMP.dMP   dMP dMP  dMP dMP   dMP\n");
      printf("\n\n\n\n\n\n\n             pleae press W to move upward, S to move downward, A for choose the menu\n\n\n\n\n\n\n");

      printf("             비행기 예약 \n\n\n\n\n\n\n");
      printf("          ■ 비행기 예약 취소 \n\n\n\n\n\n\n");
      printf("             예약 정보 확인 \n\n\n\n\n\n\n");
      break;

   case 2:
      system("cls");
      puts("");
      puts("");
      puts("");
      puts("");
      puts("");
      puts("");
      printf("          dMP dMP dMP  dMP dMP   aMMMb  dMMMMMMP    dMMMMb    aMMMb        dMP dMP   aMMMb    dMP dMP      dMP dMP dMP    aMMMb    MMMb  dMMMMMP\n");
      printf("     dMP dMP dMP  dMPMdMP  dMP dMP   dMP       dMP VMP   dMP dMP      dMP.dMP  dMP dMP   dMP dMP      dMP dMP dMP   dMP dMP  dMP dMP   dMP\n");
      printf("    dMP dMP dMP  dMP dMP  dMMMMMP   dMP       dMP.aMP   dMP.aMP       VMMP    dMP dMP   dMP dMP      dMP dMP dMP   dMMMMMP  dMP dMP   dMP\n");
      printf("    VMMMPVMMP   dMP dMP  dMP dMP   dMP       dMMMP     VMMMP       dA.dMP    dMP.aMP   dMP.aMP      dMP.dMP.dMP   dMP dMP  dMP dMP   dMP\n");
      printf("\n\n\n\n\n\n\n             pleae press W to move upward, S to move downward, A for choose the menu\n\n\n\n\n\n\n");

      printf("             비행기 예약 \n\n\n\n\n\n\n");
      printf("             비행기 예약 취소 \n\n\n\n\n\n\n");
      printf("          ■ 예약 정보 확인 \n\n\n\n\n\n\n");
      break;

   default:
      break;


   }
}