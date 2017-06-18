#ifndef ALG_CPP_
#define ALG_CPP_
#include "struct.h"
//--prototype
int KeyPressed(int dung, int n, int ck);
void InputCheck(int n,char* s,str menumh[8],int ck);
void GridView(char s[],int tab,str header[4],int ck);
void InsertDiem(NODE &K,_diem d);
NODEPTR SearchSV(NODEPTR t,char masv[]);
int checkFull(str stemp[],int n);
int IsDigital(char A[]);
int checkMaMH(char token[]);
int checkMalop(char stemp[]);
int checkDiem(char A[]);
void SwapSV(_sinhvien &sva, _sinhvien &svb);
void InsertNodeSV(NODEPTR &p, _sinhvien sv);
void InsertDiem(NODE &K,_diem d);
int duyetdslk(NODE d,char mamh[]);
//------UDF for graphics----
#define SELECT   241
#define UNSELECT 23

enum status{ UP,DOWN,LEFT,RIGHT,ENTER,BACK,EXIT,MUSIC };

void GridView(char s[],int tab,str header[4],int ck){
	int l = strlen(s);
	int x = ((70-10)/2)-(l/2)+10;
	GotoXY(x,2); printf("%s",s);
	int sp = (70-10+3)/tab;
	for(int i = 0,j = sp;i < tab;i++,j += sp){
		if(i == 0) GotoXY(j+2,4);
		else GotoXY(j,4); printf("%s",header[i]);
	}
	GotoXY(10,4); printf("%s","STT");
	for(int i = 10;i < 70;i++) {		
		GotoXY(i,3);printf("%c",char(95));
	}
	for(int i = 10;i < 70;i++) {
		GotoXY(i,5); printf("%c",char(196));
	}		
}
void Box(int x,int y,int w,int h){
	for(int i = x;i <= x+w;i++){
		for(int j = y;j <= y+h ;j++){
			if(i == x && j == y) {
				GotoXY(i,j);printf("%c",char(201)); //top left
			}
			else if(i == x && j == y+h){
				GotoXY(i,j);printf("%c",char(200)); //bot left
			}
			else if(i == x+w && j == y){
				GotoXY(i,j);printf("%c",char(187)); //
			}
			else if(i == x+w && j == y+h){
				GotoXY(x+w,y+h);printf("%c",char(188));
			}
			else if(j == y){
				GotoXY(i,j);printf("%c",char(205));
			}
			else if(j == y+h){
				GotoXY(i,j);printf("%c",char(205));
			}
			else if(i == x){
				GotoXY(i,j);printf("%c",char(186));
			}
			else if(i == x+w){				
				GotoXY(i,j);printf("%c",char(186));
			}
			else
				continue;
		}
	}
}
void TextBox(char *s, int x,int y,int w,int h){	
	int l=strlen(s);
	for(int i=x;i<=(x+w);i++){
		for(int j=y;j<=y+h;j++){
			if(i==x&&j==y) {
				GotoXY(i,j);printf("%c",char(201)); //trai tren
			}
			else if(i == x && j == y+h){
				GotoXY(i,j);printf("%c",char(200)); //trai duoi
			}
			else if(i == x+w && j == y){
				GotoXY(i,j);printf("%c",char(187));
			}
			else if(i==(x+w) &&j==(y+h)){
				GotoXY(x+w,y+h);printf("%c",char(188));
			}
			else if(j==y){//bar ngang ne
				if(i<x+l+1) continue;			
				GotoXY(i,j);
				printf("%c",char(205));				
			}
			else if(j==y+h){
				GotoXY(i,j);printf("%c",char(205));
			}
			else if(i==x){	
				GotoXY(i,j);printf("%c",char(186));
			}
			else if(i==x+w){		
				GotoXY(i,j);printf("%c",char(186));
			}
			else
				continue;
		}
	}
	GotoXY(x+1,y);
	printf("%s",s);
}

status key(int z){
	if(z == 224){
		char c = getch();
		if (c == 72) return UP;
		if (c == 80) return DOWN;
		if (c == 77) return RIGHT;
		if (c == 75) return LEFT;
	}
	else{
		if (z == 32) return MUSIC;
		if (z == 27) return EXIT;
		if (z == 13)
			return ENTER;
		else
			return BACK;
	}
}
int m=0;
int Menu(int n,int &out,int &pos){
	str smenu[9]= { " NHAP LOP             !", 
					" IN DANH SACH LOP     !",
					" NHAP SINHVIEN        !",
					" IN DANH SACH SINHVIEN!",
					" NHAP MON HOC         !",
					" IN DANH SACH MON HOC !",
					" NHAP DIEM            !",
					" IN BANG DIEM LOP     !",
					" PHIEU DIEM SV        !"};
								
	int *color = (int*)malloc(n*sizeof(int));
	for(int i = 0;i < n;i++){
		color[i] = UNSELECT;
	}
	int x = pos;
	color[x]=SELECT;
	while(1){
		Clear();
		if (m == 1) MessageBeep(0);
		for(int i = 0;i < n;i++){
			TextColor(color[i]);
			if(i == pos){
				GotoXY(26,3+i);
				printf("%d %c%s \n",i+1,char(16),smenu[i]);
			}else{
				GotoXY(26,3+i);
				printf("%d   %s\n",i+1,smenu[i]);
			}
		}
		TextColor(23);
		GotoXY(00,15); printf("[SELECT:ENTER]");
		GotoXY(20,15); printf("[MUSIC%c:SPACE]",char(14));
		GotoXY(38,15); printf("[EXIT:ESC]");
		GotoXY(55,15); printf("[UP:%c/%c]",char(30),char(17));
		GotoXY(70,15); printf("[DOWN:%c/%c]",char(31),char(16));
		Box(25,2,28,10);
		
		int z = getch();
		status stt = key(z);
		switch(stt){
			case UP   : case LEFT : {								
				(pos == 0)? pos = n-1:pos--;
				break;
			};
			case DOWN : case RIGHT: {				
				(pos == n-1)? pos = 0:pos++;
				break;
			}	
			case ENTER: return pos;
			case BACK : break;
			case EXIT : {
				out = 1;
				return pos;			
			}
			case MUSIC : {
				(m == 1)? m = 0:m = 1;
				break;
			}
		}
		for(int i = 0;i < n;i++)
			color[i] = UNSELECT;
		color[pos] = SELECT;	 			
	}//end while 
}
void Notify(int x,int y,int c1,int c2,char s[],int sec){
	if (m == 1) MessageBeep(0x00000010L);
	TextColor(c1);
	GotoXY(x,y);
	printf("%s",s);
	Sleep(sec);
	for(int i=0;i<strlen(s);i++) s[i]=' ';
	GotoXY(x,y);
	printf("%s",s);
	TextColor(c2);
}
str stemp[5];
int KeyPressed(int dung,int n,int ck){
	int l, max;
	(ck == 1 )? max = 3 : max = 11;
	AGAIN:
	l = strlen(stemp[k]);	
	if(kbhit()){	
		int key = getch();		
		switch(key){
			case 27: return -2; 
			case 13:{
				if(tt==n || strlen(stemp[k+1]) > 0){//enter len xg d
					if(checkFull(stemp,n)){
						if(ck==0){ //dang nhap lop
							if(checkMalop(stemp[0])!=-1){
								char s[]="Lop bi trung!";
								Notify(30,10,28,31,s,1000);
								tt=1;k=0;
								GotoXY(40 +strlen(stemp[k]),tt+3);
								goto AGAIN;
							}							
							if(!IsDigital(stemp[2])||strlen(stemp[2])<4){
								char s[]="Nam khong hop le!";
								Notify(30,10,28,31,s,1000);
								tt=3,k=2;
								GotoXY(40+strlen(stemp[2]),2+4);
								goto AGAIN;
							}
							int n = dsl.n;
							strcpy(dsl.nodes[n].MALOP,strupr(stemp[0]));//strupr
							strcpy(dsl.nodes[n].TENLOP,strupr(stemp[1]));
							dsl.nodes[n].NAMNH = atoi(stemp[2]);
							dsl.n++;
						}
						if(ck==1) {
							strcpy(ol,stemp[0]);
							if(l<4 || !IsDigital(stemp[0])){ 
								char s[]="Nam khong hop le!";
								Notify(30,10,28,31,s,1000);
								k=0;tt=1;
								GotoXY(40+strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							int dc=0;
							for(int i=0;i<dsl.n;i++){
								if(dsl.nodes[i].NAMNH==atoi(stemp[0])){				
									dc++;
								}
							}
							if(dc==0){
								char t[]="Nien khoa khong ton tai!";
								Notify(27,10,28,31,t,1000);							
								GotoXY(40+strlen(stemp[k]),k+1+3);
								goto AGAIN;
							}							
						}
						if(ck==-2){
							NODEPTR q;
							for(int i=0;i<dsl.n;i++){
								q = SearchSV(dsl.nodes[i].ptrdssv,strupr(stemp[0]));
								if(q!=NULL) break;
							}
							if(q!=NULL){
								char s[]="Ma sinh vien ton tai!";
								Notify(30,10,28,31,s,1000);
								k=0,tt=1;
								GotoXY(40+strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							if(!IsDigital(stemp[4]) || strlen(stemp[4])<10){
								char s[]="SDT khong hop le!";
								Notify(30,10,28,31,s,1000);
								k=4,tt=5;
								GotoXY(40+strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							int n=checkMalop(lp);	
							_sinhvien sv;
							strcpy(sv.MASV,stemp[0]);
							strcpy(sv.HO,stemp[1]);
							strcpy(sv.TEN,stemp[2]);
							strcpy(sv.PHAI,stemp[3]);
							strcpy(sv.SODT,stemp[4]);
							InsertNodeSV(dsl.nodes[n].ptrdssv,sv);				
						}
						if(ck == 2){ 
							if(checkMalop(stemp[0]) == -1){
								char t[]="Lop khong ton tai!";
								Notify(30,10,28,31,t,1000);
								k=0;tt=1;
								GotoXY(40+strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							strcpy(lp,strupr(stemp[0]));				
						}
						if(ck==3){	
							strcpy(lp,stemp[0]);		
							if(checkMalop(lp) == -1){
								char f[]="Lop khong ton tai!";
								Notify(30,10,28,31,f,1000);
								k=0,tt=1;								
								GotoXY(40+strlen(stemp[k]),tt+3);
								goto AGAIN;
							}				
							int n = checkMalop(lp);
							if(dsl.nodes[n].ptrdssv == NULL){
								char f[]="Lop khong co sinh vien!";
								Notify(27,10,28,31,f,1000);
								k=0,tt=1;								
								GotoXY(40+strlen(stemp[k]),tt+3);
								goto AGAIN;
							}						
						}
						if(ck==4){
							if(checkMaMH(stemp[0])==0){
								char s[]="Mon hoc bi trung!";
								Notify(30,10,28,31,s,1000);
								tt=1;k=0;
								GotoXY(40 +strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							if(!IsDigital(stemp[2])){
								char s[]="STC khong hop le!";
								Notify(30,10,28,31,s,1000);
								tt=3;k=2;
								GotoXY(40 +strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							if(!IsDigital(stemp[3])){
								char s[]="STC khong hop le!";
								Notify(30,10,28,31,s,1000);
								tt=4;k=3;
								GotoXY(40 +strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							int n = dsmh.n;
							strcpy(dsmh.nodes[n].MAMH,stemp[0]);
							strcpy(dsmh.nodes[n].TENMH,stemp[1]);
							dsmh.nodes[n].STCLT = atoi(stemp[2]);
							dsmh.nodes[n].STCTH = atoi(stemp[3]);
							dsmh.n++;
						}
						
						
						if(ck==-6){
							if(checkMaMH(stemp[0])){
								char s[]="Mon hoc khong ton tai!";
								Notify(30,10,28,31,s,1000);
								tt=1;k=0;
								GotoXY(40 +strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							if(!IsDigital(stemp[1])){
								char s[]="So lan thi khong hop le";
								Notify(30,10,28,31,s,1000);
								tt=2;k=1;
								GotoXY(40 +strlen(stemp[k]),tt+3);
								goto AGAIN;
							}	
							NODEPTR t=NULL;
							for(int i=0;i<dsl.n;i++){
								NODEPTR q = SearchSV(dsl.nodes[i].ptrdssv,strupr(osv));
								if(q != NULL) {
									t=q;break;
								}
							}
							int w = duyetdslk(t->sv.ptrdsd,strupr(stemp[0]));		
							if(atoi(stemp[1]) != w+1){
								char s[]="Lan thi tiep theo phai lien sau";
								Notify(24,10,28,31,s,1000);
								tt=2;k=1;
								GotoXY(40 +strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							if(!checkDiem(stemp[2])){
								char s[]="Diem khong hop le";
								Notify(30,10,28,31,s,1000);
								tt=3;k=2;
								GotoXY(40 +strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							_diem d;
							strcpy(d.MAMH,strupr(stemp[0]));
							d.LAN = atoi(stemp[1]);
							d.DIEM = atof(stemp[2]);
							for(int i=0;i<dsl.n;i++){
								NODEPTR q = SearchSV(dsl.nodes[i].ptrdssv,osv);
								if(q != NULL) {
									InsertDiem(q->sv.ptrdsd,d);
									break;
								}
							}
						}	
						if(ck==6){
							strcpy(osv,strupr(stemp[0]));//stored osv
							//strcpy(stemp[0],"");
							NODEPTR s=NULL;int n=0;
							for(int i=0;i<dsl.n;i++){
								NODEPTR q = SearchSV(dsl.nodes[i].ptrdssv,osv);
								if(q!=NULL){
									s=q;
									break;
								}
							}
							if(s==NULL){
								char s[]="Ma sinh vien khong ton tai!";
								Notify(26,10,28,31,s,1000);
								k=0,tt=1;
								GotoXY(40+strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
						}					
						if(ck==7){
							if(checkMalop(stemp[0])==-1){
								char y[]="Lop khong ton tai!";
								Notify(30,10,28,31,y,1000);
								k=0,tt=1;
								GotoXY(40+strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							strcpy(lp,strupr(stemp[0]));
							if(checkMaMH(stemp[1])){
								char y[]="Mon hoc khong ton tai!";
								Notify(30,10,28,31,y,1000);
								k=1;tt=2;
								GotoXY(40+strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							strcpy(osv,strupr(stemp[1]));
							if(!IsDigital(stemp[2]) || atoi(stemp[2])==0){
								char s[]="So lan thi khong hop le!";
								Notify(30,10,28,31,s,1000);
								tt=3;k=2;
								GotoXY(40 +strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							times=atoi(stemp[2]);														
						}
						if(ck==8){	
							strcpy(osv,strupr(stemp[0]));//lay dc masv					
							NODEPTR t=NULL;
							for(int i=0;i<dsl.n;i++){	
								NODEPTR s = SearchSV(dsl.nodes[i].ptrdssv,osv);								
								if(s!=NULL) { //s != NULL => tim thay sv
									t=s;
									break;
								}
							}
							if(t == NULL){
								char s[]="Ma sinh vien khong ton tai!";
								Notify(26,10,28,31,s,1000);
								k=0,tt=1;
								GotoXY(40+strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							if(t->sv.ptrdsd == NULL){
								char s[]="Sinh vien chua co diem!";
								Notify(26,10,28,31,s,1000);
								k=0,tt=1;
								GotoXY(40+strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
						}
						return -1;//da nhap du field
					}
					else{
						for(int i=0;i<n;i++){
							if(strlen(stemp[i])==0){
								tt=i+1;k=i;break;
							}
						}
						char s[]="Error Data!";						
						Notify(25,10,28,31,s,1000);	
						GotoXY(40+strlen(stemp[k]),tt+3);	
						goto AGAIN;	
					}
				}else{
					if(tt==n) tt=1; else tt++;						
					if(k==n-1) k=0; else k++;	
					if(strlen(stemp[k])!=0){
						for(int i=0;i<n;i++){
							if(strlen(stemp[i])==0){	
								tt=i+1;k=i;break;
							}
						}
					}																				
					GotoXY(40+strlen(stemp[k]),tt+3);	
					goto AGAIN;
				}		
			}
			case 8:{/*  BACKSPACE KEY: dell a char	*/											
				stemp[k][strlen(stemp[k])-1] ='\0';
				if(l > 0){
					GotoXY(40+l,tt+3);
					printf("\b");				
					printf(" ");		
					printf("\b");
				}
				goto AGAIN;	
			}		
			case 224:{/*  VK KEY: move direction,up,down  */
				key = getch();
				switch(key){	
					case 75: case 72:{/* VK_UP,VK_LEFT: up*/													
						(tt==1)? tt=n:tt--;
						(k==0)? k=n-1:k--;
						GotoXY(40 +strlen(stemp[k]),tt+3);
						goto AGAIN;
					}
					case 77: case 80:{/* VK_DOWN,VK_RIGHT: down*/
						(tt==n)? tt=1:tt++;						
						(k==n-1)? k=0: k++;
						GotoXY(40 +strlen(stemp[k]),tt+3);	
						goto AGAIN;
					}	
				}
				break;
			}																
			default:{/*Print a char to console*/
				if(ck == 0 && k == 2 ) max = 3;
				if(l > max){
					char s[] = "Vuot qua so ki tu";
					Notify(30,10,28,31,s,1000);
					GotoXY(40+strlen(stemp[k]),k+1+3);
				}else{
					GotoXY(40+strlen(stemp[k]),k+1+3);																	
					printf("%c",toupper(key));
					stemp[k][l] = toupper(key);
					stemp[k][++l] = '\0';
					goto AGAIN;
				}							
			}
		}
	}	
}
void InputUI(int rong,char* s,str menumh[],int n,int ck){
	TextBox(s,24,3,29,3+n-2);		
	GotoXY(00,15); printf("[BACK:ESC]");
	GotoXY(22,15); printf("[INSERT:ENTER]");
	GotoXY(50,15); printf("[UP:%c/%c]",char(30),char(17));
	GotoXY(70,15); printf("[DOWN:%c/%c]",char(31),char(16));
	for(int i = 4;i < n+4 ;i++){
		GotoXY(25,i); printf(menumh[i-4]);
	}
	TextColor(31);
	GotoXY(40,4);
	int k;
	do{	
		k = KeyPressed(dung,n,ck);		
	}while(k != -1 && k != -2 && k != -3);
	dung = k;
}

void InputCheck(int n,char* s,str menumh[8],int ck){
	Clear();
	TextColor(23);
	int c;
	do{
		Clear();
		
		tt=1,c=0,k=0; //reset global variable
		for(int i=0;i<n;i++){
			memset(stemp[i],0,255);
		}

		InputUI(dung,s,menumh,n,ck);
		
		if(ck == 2 && lp != NULL) break;
		if(ck == 1 || ck == 3 || ck == 8) break;
		else{
			TextColor(23);
			for(int i=0;i<n;i++){
				GotoXY(40,i+1+3); printf("%s",stemp[i]);
			}
			if(dung == -3) break ;
			
			if(dung == -1) {
				switch(ck) {
					case 5: {
						TextColor(31);
						return;
					}
					case 2:	break;
					case 4:	break;
					case 6: {
						c=0; continue;
						break;
					}
					case 7: {
						TextColor(31);
						return ;
					}
				}
				GotoXY(25,10);
				TextColor(26);
				printf("THEM THANH CONG!");
				GotoXY(25,11);
				printf("ENTER DE TIEP TUC, PHIM BAT KI DE THOAT!");
				TextColor(23);
			}else
				break;
			c = getch();
		}									
	}while(c == 13 || c == 13);
}
// UDF for Datastruct & Algorithms
int checkFull(str stemp[],int n){
	for(int i=0;i<n;i++){
		if(strlen(stemp[i])==0) return 0;
	}
	return 1;
}
int IsDigital(char A[]){
	int l=strlen(A);
	for(int i=0;i<l;i++)
		if(!isdigit(A[i])) return 0;
	return 1;
}
int checkMaMH(char token[]){
	for(int i=0;i<dsmh.n;i++)
		if(strcmp(dsmh.nodes[i].MAMH,token)==0) return 0;
	return 1;
}
int checkMalop(char stemp[]){
	for(int i=0;i<dsl.n;i++)
		if(strcmp(strlwr(dsl.nodes[i].MALOP),strlwr(stemp)) == 0) return i;//giong nhau
	return -1;
}

int checkDiem(char A[]){
	int c=0;
	if(atof(A) > 10 || atof(A) < 0) return 0;
	for(int i = 0;i < strlen(A);i++) 
		if(!isdigit(A[i])) 
			if(A[i] == '.') c++;
			else return 0;
	if (c > 1) return 0;
	return 1;
}
void SwapSV(_sinhvien &sva, _sinhvien &svb){
	_sinhvien svtemp = sva;
	sva = svb;
	svb = svtemp;
}
void InsertNodeSV(NODEPTR &p, _sinhvien sv){
	if(p == NULL){
		p = new nodesv;
		p->sv = sv;
		p->left = NULL;
		p->right = NULL;		
	}
	else{
		if(strcmp(strupr(sv.MASV),strupr(p->sv.MASV))<0)
			InsertNodeSV(p->left,sv);
		else
			InsertNodeSV(p->right,sv);
	}
}
NODEPTR SearchSV(NODEPTR t,char masv[]){
	NODEPTR p;
	p=t;
	while(p!=NULL && !(strcmp(strupr(p->sv.MASV),strupr(masv))==0)){
		if(strcmp(strupr(masv),strupr(p->sv.MASV))<0)
			p=p->left;
		else
			p=p->right;
	}
	return p;
}

struct dssinhvien {
	int n;
	_sinhvien nodes[MAXLIST];
};
struct dssinhvien dssv;
//copy dssv->dssv liner
void Preorder(NODEPTR p,int &i,struct dssinhvien &dssv){
	if(p!=NULL){
		strcpy(dssv.nodes[i].HO,p->sv.HO);
		strcpy(dssv.nodes[i].MASV,p->sv.MASV);
		strcpy(dssv.nodes[i].TEN,p->sv.TEN);
		strcpy(dssv.nodes[i].PHAI,p->sv.PHAI);
		strcpy(dssv.nodes[i].SODT,p->sv.SODT);
		
		dssv.n++;
		i++;
		Preorder(p->left,i,dssv);
		Preorder(p->right,i,dssv);
	}
}
void OrderSV(struct dssinhvien dssv){
	//order sv by name (bubble sort)
	for(int i=0;i<dssv.n;i++){
		for(int j=dssv.n-1;j>=i;j--){ //need to check
			if(strcmp(dssv.nodes[j].TEN,dssv.nodes[j-1].TEN)<0)
				SwapSV(dssv.nodes[j],dssv.nodes[j-1]);
			if(strcmp(dssv.nodes[j].TEN,dssv.nodes[j-1].TEN)==0)
				if(strcmp(dssv.nodes[j].HO,dssv.nodes[j-1].HO)<0)
					SwapSV(dssv.nodes[j],dssv.nodes[j-1]);
			
		}
	}
	//printf out console
	for(int i=0;i<dssv.n;i++){
		GotoXY(10,i+6);
		printf("%d \n",i);
		GotoXY(13,i+6);
		printf("%s\n",dssv.nodes[i].MASV);
		GotoXY(24,i+6);
		printf("%s\n",dssv.nodes[i].HO);
		GotoXY(36,i+6);
		printf("%s\n",dssv.nodes[i].TEN);
		GotoXY(48,i+6);
		printf("%s\n",dssv.nodes[i].PHAI);
		GotoXY(60,i+6);
		printf("%s\n",dssv.nodes[i].SODT);
	}
}
void IndslkDiem(NODE d){
	NODE q = d;
	int i=0,v=0;
	while(q != NULL){
		NODE t=d;int j=0;
		int pra=1;
		while(t!=NULL){
			if(strcmp(strupr(q->diem.MAMH),strupr(t->diem.MAMH)) == 0 ){
				if(q->diem.DIEM < t->diem.DIEM) {
					if(j!=i) pra = 0;
				}
				if(q->diem.DIEM == t->diem.DIEM) {
					if(j>i) pra = 0;
				}
			}		
			j++;
			t=t->next;
		}//end while inside
		if(pra == 1){	
			GotoXY(10,v+6); printf("%d",v);
			GotoXY(23,v+6); printf("%s\n",q->diem.MAMH);
			GotoXY(42,v+6); printf("%d\n",q->diem.LAN);
			GotoXY(63,v+6); printf("%3.1f\n",q->diem.DIEM);
			v++;
		}
		i++;
		q=q->next;		
	}
}
void duyetdslkLOP(NODEPTR T,NODE d,char mamh[],int times){
	NODE q = d;
	int i=0;
	while(q != NULL){
		if(strcmp(strupr(mamh),strupr(q->diem.MAMH))==0 && q->diem.LAN==times){
			GotoXY(10,i+6); printf("%d\n",i+1);
			GotoXY(17,i+6); printf("%s \n",q->diem.MAMH); 
			GotoXY(30,i+6);printf("%s\n",T->sv.MASV);
			GotoXY(45,i+6); printf("%d \n",q->diem.LAN);
			GotoXY(60,i+6);printf("%3.1f \n",q->diem.DIEM);
			i++;
			
		}	
		q = q->next;
	}
	if(i==0){
		GotoXY(21,6); printf("Khong tim thong tin thay theo yeu cau!");
	}
}
void PreorderDiemLOP(NODEPTR T,char mamh[]){
	NODEPTR p=T;
	if(p!=NULL){
		if(p->sv.ptrdsd != NULL)	
			duyetdslkLOP(T,p->sv.ptrdsd,mamh,times);
		PreorderDiemLOP(p->left,mamh);
		PreorderDiemLOP(p->right,mamh);
	}
}
void InsertDiem(NODE &K,_diem d){
	NODE p;
	p= (NODE) malloc(sizeof(struct nodesv));
	p->diem=d;
	p->next = K;
	K = p;	
}
//check lan thi(times)
int duyetdslk(NODE d,char mamh[]){
	NODE q = d;
	int  v = 0;
	if(q == NULL) return 0;
	while(q != NULL){
		if(strcmp(strupr(mamh),strupr(q->diem.MAMH))==0)
			if(q->diem.LAN >= v) v = q->diem.LAN;
		q = q->next;
	}
	return v;
}
//UDF for FILE io
void readFileLop(dslop &dsl){
	char path[]="bin\\class.ini";
	FILE *fp = fopen(path,"r");
	if(fp == NULL) printf("Error read file!");
	else{
		dsl.n=0;
		int c = fgetc(fp);
		if (c == EOF) return;
		else ungetc(c, fp);  
		while(!feof(fp)){				
			fgets(dsl.nodes[dsl.n].MALOP,225,fp);
			strtok(dsl.nodes[dsl.n].MALOP,"\n");			
			fgets(dsl.nodes[dsl.n].TENLOP,225,fp);
			strtok(dsl.nodes[dsl.n].TENLOP,"\n");
			fscanf(fp,"%d\n",&dsl.nodes[dsl.n].NAMNH);
			dsl.n++;
		}
	}
	fclose(fp);
}
void writeFileLop(dslop dsl){
	char path[]="bin\\class.ini";
	FILE *fp = fopen(path,"w+");
	if(fp == NULL) printf("Error write file!");
	else{
		for(int i=0;i<dsl.n;i++){
			fprintf(fp,"%s\n",strupr(dsl.nodes[i].MALOP));
			fprintf(fp,"%s\n",strupr(dsl.nodes[i].TENLOP));
			fprintf(fp,"%d\n",dsl.nodes[i].NAMNH);			
		}		
	}
	fclose(fp);
}

void readFileDiem(dslop &dsl){
	char path[]="bin\\point.ini";
	FILE *fp = fopen(path,"r");
	if(fp == NULL){
		printf("Error read file!");	
	}
	else{
		int c = fgetc(fp);
		if (c == EOF) return;
		else ungetc(c, fp);
		while(!feof(fp)){					
			char svtemp[13];
			_diem d;			
			fgets(svtemp,255,fp);
			strtok(svtemp,"\n");				
			fgets(d.MAMH,225,fp);//1
			strtok(d.MAMH,"\n");		
			fscanf(fp,"%d\n",&d.LAN);//2			
			fscanf(fp,"%f\n",&d.DIEM);//3
			for(int i=0;i<dsl.n;i++){
				NODEPTR q = SearchSV(dsl.nodes[i].ptrdssv,strupr(svtemp));
				if(q != NULL){ //tim thay sv
					InsertDiem(q->sv.ptrdsd,d);
					break;
				}	
			}
			strcpy(svtemp,"");						
		}		
	}
	fclose(fp);	
}
void readFileMonHoc(dsmonhoc &dsmh){
	char path[]="bin\\subject.ini";
	FILE *fp = fopen(path,"r");
	if(fp == NULL){
		printf("Error read file!");
	}else{
		dsmh.n=0;
    	int c = fgetc(fp);
		if (c == EOF)return;
		else ungetc(c, fp);   
		while(!feof(fp)){
			fgets(dsmh.nodes[dsmh.n].MAMH,255,fp);
			strtok(dsmh.nodes[dsmh.n].MAMH,"\n");
			fgets(dsmh.nodes[dsmh.n].TENMH,255,fp);
			strtok(dsmh.nodes[dsmh.n].TENMH,"\n");
			fscanf(fp,"%d\n",&dsmh.nodes[dsmh.n].STCLT);
			fscanf(fp,"%d\n",&dsmh.nodes[dsmh.n].STCTH);	
			dsmh.n++;	
		}
	}
	fclose(fp);
}
void readFileSinhVien(dslop &dsl){
	char path[]="bin\\student.ini";
	FILE *fp = fopen(path,"r");
	if(fp == NULL) printf("Error read file!");
	else{	
		int c = fgetc(fp);
		if (c == EOF) return;
		else ungetc(c, fp);
		while(!feof(fp)){
			char mltemp[13];
			_sinhvien sv;			
			fgets(mltemp,255,fp);
			strtok(mltemp,"\n");				
			fgets(sv.MASV,255,fp);
			strtok(sv.MASV,"\n");			
			fgets(sv.HO,255,fp);
			strtok(sv.HO,"\n");			
			fgets(sv.TEN,255,fp);
			strtok(sv.TEN,"\n");			
			fgets(sv.PHAI,255,fp);
			strtok(sv.PHAI,"\n");			
			fgets(sv.SODT,255,fp);
			strtok(sv.SODT,"\n");
			for(int i=0;i<dsl.n;i++){
				if(strcmp(dsl.nodes[i].MALOP,mltemp)==0){
					InsertNodeSV(dsl.nodes[i].ptrdssv,sv);
				}
			}	
			strcpy(mltemp,"");
		}
	}
	fclose(fp);		
}
void writeFileMonHoc(dsmonhoc dsmh){
	char path[]="bin\\subject.ini";
	FILE *fp = fopen(path,"w+");
	if(fp == NULL) printf("Error write file!");
	else{
		for(int i=0;i<dsmh.n;i++){
			fprintf(fp,"%s\n",dsmh.nodes[i].MAMH);
			fprintf(fp,"%s\n",dsmh.nodes[i].TENMH);
			fprintf(fp,"%d\n",dsmh.nodes[i].STCLT);
			fprintf(fp,"%d\n",dsmh.nodes[i].STCTH);
		}			
	}
	fclose(fp);
}
void writeFileSV(FILE *fp,NODEPTR p,char malop[]){
	if(p!=NULL){	
		fprintf(fp,"%s\n",strupr(malop));
		fprintf(fp,"%s\n",strupr(p->sv.MASV));
		fprintf(fp,"%s\n",strupr(p->sv.HO));
		fprintf(fp,"%s\n",strupr(p->sv.TEN));
		fprintf(fp,"%s\n",strupr(p->sv.PHAI));
		fprintf(fp,"%s\n",strupr(p->sv.SODT));
		writeFileSV(fp,p->left,malop);
		writeFileSV(fp,p->right,malop);
	}
}
void writeFileSinhVien(dslop dsl){
	char path[]="bin\\student.ini";
	FILE *fp = fopen(path,"w+");
	if(fp == NULL) printf("Error write file!");
	else
		for(int i=0;i<dsl.n;i++)
			writeFileSV(fp,dsl.nodes[i].ptrdssv,strupr(dsl.nodes[i].MALOP));
	fclose(fp);
}
void writeD(FILE *fp,NODE o,char masv[]){
	NODE q=o;
	while(q!=NULL){
		fprintf(fp,"%s\n",strupr(masv));
		fprintf(fp,"%s\n",strupr(q->diem.MAMH));
		fprintf(fp,"%d\n",q->diem.LAN);
		fprintf(fp,"%f\n",q->diem.DIEM);
		q=q->next;
	}
}
void writeFileD(FILE *fp,NODEPTR p){
	if(p!=NULL){
		writeD(fp,p->sv.ptrdsd,p->sv.MASV);
		writeFileD(fp,p->left);
		writeFileD(fp,p->right);
	}
}
void writeFileDiem(dslop dsl){
	char path[]="bin\\point.ini";
	FILE *fp = fopen(path,"w+");
	if(fp == NULL) printf("Error write file!");
	else{
		for(int i=0;i<dsl.n;i++){
			writeFileD(fp,dsl.nodes[i].ptrdssv);
		}		
	}
	fclose(fp);
}
void ReadFile(){
	readFileMonHoc(dsmh);
	readFileLop(dsl);
	readFileSinhVien(dsl);
	readFileDiem(dsl);
}
void WriteFile(){
	writeFileMonHoc(dsmh);
	writeFileLop(dsl);
	writeFileSinhVien(dsl);
	writeFileDiem(dsl);
}
#endif
