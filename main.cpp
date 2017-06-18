/************************************
*DE TAI:QUAN LY DIEM SINH VIEN      *
*GVHD  :LUU NGUYEN KI THU           *
*SVTH  :-TA HONG TRUNG   N13DCCN213 *
*	    -TRAN CAM TRUONG N13DCCN216 *
************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "alg.cpp"

int main(){
	SetConsoleTitle("QUAN LI DIEM SINH VIEN");
	SetConsolePos(350,100);
	int out=0,pos=0;
	ReadFile();
	MENU:
	ShowCur(false);
	TextColor(23);
	ck = Menu(9,out,pos);
	TextColor(31);
	if (out == 1) {
		Clear();
		if (m == 1) MessageBeep(0x00000010L);
		char a[] = " THONG BAO ";
		TextBox(a,20,5,40,7);
		TextColor(31);
		GotoXY(31,7);printf("THOAT CHUONG TRINH?");
		GotoXY(26,8);printf("PHIEN LAM VIEC SE DUOC LUU LAI");
		TextColor(23);
		GotoXY(48,10);printf("ENTER:THOAT");
		GotoXY(22,10);printf("ESC:QUAY LAI");

		int c = getch();
		if (c == 13){//ENTER TO EXIT
			WriteFile();
			return 1;
		}
		else{
			out=0;
			goto MENU;
		}
	}
	ShowCur(true);
	Clear();
	switch(ck){
		case 0: {
			str hnhap[3]={"MA LOP       :[            ]",
						  "TEN LOP      :[            ]",
					 	  "NAM NHAP HOC :[            ]"};
			char s[]=" NHAP LOP ";
			GotoXY(0,0);
			InputCheck(3,s,hnhap,ck);
			goto MENU;
		}
		case 1: {
			strcpy(ol,"");
			str t[1]={"NIEN KHOA    :[            ]"};
			char s[]=" DS LOP THEO KHOA ";

			InputCheck(1,s,t,ck);
			if(dung==-2) goto MENU;
			Clear();
			int tab=3;
			str header[3]={"MA LOP","TEN LOP","NAM NH"};
			char ti[]="DANH SACH LOP";
			ShowCur(false);
			int sp=(70-10+3)/tab;
			if(dung == -2) goto MENU;
			int dc=0;
			GridView(ti,tab,header,ck);
			for(int i = 0;i < dsl.n;i++) {
				if(dsl.nodes[i].NAMNH == atoi(ol)){
					GotoXY(10,dc+6); printf("%d",dc+1);		
					GotoXY(sp+2,dc+6); printf("%s",strupr(dsl.nodes[i].MALOP));
					GotoXY(sp+sp,dc+6); printf("%s",strupr(dsl.nodes[i].TENLOP));
					GotoXY(sp+sp+sp,dc+6); printf("%d",dsl.nodes[i].NAMNH);
					dc++;
				}
			}
			getch();
			goto MENU;
		}
		case 2:{
			str fnhap[5]={"MA SINH VIEN :[            ]",
						  "HO SINH VIEN :[            ]",
					 	  "TEN SINH VIEN:[            ]",
						  "GIOI TINH    :[            ]",
						  "SO DIEN THOAI:[            ]"};
			strcpy(lp,"");
			char s[]=" NHAP SINH VIEN CHO LOP ";
			str t[1]={"MA LOP       :[            ]"};
			InputCheck(1,s,t,ck);
			if( dung == -2) goto MENU;
			ck=-2;
			char c[]=" NHAP SINH VIEN ";
			InputCheck(5,s,fnhap,ck);
			if( dung == -2) goto MENU;
			ck=2;
			goto MENU;
		}
		case 3:{
			strcpy(lp,"");
			char s[]=" DS SINH VIEN CUA LOP ";
			str t[1]={"MA LOP       :[            ]"};		
			InputCheck(1,s,t,ck);
			if( dung == -2) goto MENU;
			Clear();
			int tab=5;
			str header[5]={"MASV","HO","TEN","PHAI","SDT"};
			char ti[]="DANH SACH SINH VIEN LOP ";
			char *nameClass=strcat(ti,lp);	
		
			NODEPTR p = dsl.nodes[checkMalop(lp)].ptrdssv;	
			ShowCur(false);
			int i=0;
			Clear();
			dssv.n=0;
			Preorder(p,i,dssv);
			OrderSV(dssv);
			int sp=(70-10+3)/tab;
			GridView(nameClass,tab,header,ck);
			getch();
			goto MENU;
		}
		case 4:{
			str gnhap[4]={"MA MON HOC   :[            ]",
						  "TEN MON HOC  :[            ]",
					 	  "STC LY THUYET:[            ]",	
						  "STC THUC HANH:[            ]"};
			int n=4;
			char s[]=" NHAP MON HOC ";
			InputCheck(n,s,gnhap,ck);
			goto MENU;
		}
		case 5:{
			int tab=4;
			str header[4]={"MAMH","TENMH","STCLT","STCTH"};
			char s[]="DANH SACH MON HOC";
			GridView(s,tab,header,ck);
			int sp=(70-10+3)/tab;
			if(dsmh.n==0){
				GotoXY(26,6);
				printf("%s","Khong co mon hoc de in");
			}
			else{
				for(int i=0;i<dsmh.n;i++){	
					GotoXY(10,i+6);printf("%d",i+1);		
					GotoXY(sp,i+6); printf("%s",dsmh.nodes[i].MAMH);
					GotoXY(sp+sp,i+6); printf("%s",dsmh.nodes[i].TENMH);
					GotoXY(sp+sp+sp,i+6); printf("%d",dsmh.nodes[i].STCLT);
					GotoXY(sp+sp+sp+sp,i+6); printf("%d",dsmh.nodes[i].STCTH);		
				}
			}
			GotoXY(0,0);
			ShowCur(false);
			getch();
			goto MENU;
		}
		case 6:{
			str enhap[3]={"MA MON HOC   :[            ]",
						  "LAN THI      :[            ]",
					 	  "DIEM         :[            ]"};
			strcpy(osv,"");
			char sv[]="NHAP DIEM CHO SINH VIEN";
			str tit[1]={"MA SINH VIEN :[            ]"};
			InputCheck(1,sv,tit,ck);
			ck=-6;
			if(dung == -2) goto MENU;
			char s[]=" NHAP DIEM ";
			InputCheck(3,s,enhap,ck);
			ck=6;
			goto MENU;
		}
		case 7:{
			times=0;
			memset(osv,0,13*sizeof(char));
			memset(lp,0,13*sizeof(char));
			char lop[]= " BANG DIEM CUA LOP ";
			str tit[3]={" MA LOP      :[            ]",
						" MA MON HOC  :[            ]",
						" LAN THI     :[            ]"};
			InputCheck(3,lop,tit,ck);
			if(dung == -2) goto MENU;
			int n = checkMalop(lp);
	
			Clear();
			ShowCur(false);
			PreorderDiemLOP(dsl.nodes[n].ptrdssv,osv);
			str header[4]={"MAMH","MASV","LAN THI","DIEM"};
			char s[]="BANG DIEM CUA LOP ";
			char *v = strcat(s,strupr(lp));	
			GridView(v,4,header,ck);
			
			GotoXY(0,0); getch();
			goto MENU;
		}
		case 8:{
			strcpy(osv,"");
			char sv[]=" PHIEU DIEM SINH VIEN ";
			str tit[1]={"MA SINH VIEN :[            ]"};
			InputCheck(1,sv,tit,ck);
			if(dung == -2) goto MENU;
			Clear();
			for(int i=0;i<dsl.n;i++){
				NODEPTR o = SearchSV(dsl.nodes[i].ptrdssv,osv);
				if(o != NULL && o->sv.ptrdsd != NULL)
					IndslkDiem(o->sv.ptrdsd);
			}
			str header[3]={"MAMH","LAN THI","DIEM"};
			char s[]="PHIEU DIEM CUA SV ";
			char *v = strcat(s,osv);	
			GridView(v,3,header,ck);
			ShowCur(false);
			GotoXY(0,0);getch();
			goto MENU;
		}
	}
	return 0;
}
