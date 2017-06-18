#ifndef STRUCT_H_
#define STRUCT_H_
#include <stdio.h>
#include <conio.h>
#include "mylib.h"

#define MAXLIST 100
typedef char str[31];
//---Global variables--
int times;
char ol[4],osv[13],lp[13];
int ck,tt =1;
int k=0;
int dung=0;

//----MON HOC-----
typedef struct {
	char MAMH[30];
	char TENMH[30];
	int STCLT;
	int STCTH;
}monhoc;
struct dsmonhoc {
	int n;
	monhoc nodes[MAXLIST];
};
struct dsmonhoc dsmh;
//---END MON HOC---

//------DIEM-------
typedef struct{
	char MAMH[30];
	int LAN;//times
	float DIEM;
}_diem;
struct nodediem {
	_diem diem;
	struct nodediem *next; 
};
typedef struct nodediem *NODE;
//----END DIEM-----

//----SINH VIEN----
typedef struct {
	char MASV[30];
	char HO[30];
	char TEN[30];
	char PHAI[15];
	char SODT[15];
	NODE ptrdsd=NULL;
}_sinhvien;
struct nodesv {
	_sinhvien sv;
	struct nodesv *left;
	struct nodesv *right;
 };
typedef struct nodesv *NODEPTR;
//--END SINH VIEN---

//-------LOP--------
typedef struct{
	char MALOP[30];
	char TENLOP[30];
	int NAMNH;
	NODEPTR ptrdssv=NULL;	
}lop;
typedef struct{
	int n;
	lop nodes[MAXLIST];
}dslop;
dslop dsl;
//------END LOP------
#endif
