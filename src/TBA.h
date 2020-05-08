#pragma once
#include"TGBA.h"
#include<fstream>
#include<iomanip>
#include<cstring>
#define MAX_VERTEX_NUM 1000     
#define Nofind -1

class SBA;
/************************Global_Functions****************************/
bool isExist(set<int> a, int val);
void fullfill_info(set<string> transcondi, string &info);
/*********************************************************************/
typedef struct VertexType
{
	int name = -1;               
	int num = -1;                    
} VertexType;              
typedef struct ArcNode
{
	int adjvex;
	ArcNode *nextarc = NULL;               
	string info;                            
	set<string> transi_condi;
	int sstateloc = -1;
}ArcNode;
typedef struct VNode
{
	VertexType data;		
	bool isexplored = false;      
	bool isAccept;
	int outdegree;           
	set<int> incoming;      
	ArcNode *firstarc = NULL;    
}VNode;

class TBA
{
private:
	int vex_num;      
	int arc_num;    
	VNode vertics[MAX_VERTEX_NUM];  
	int visit[MAX_VERTEX_NUM];              
public:
	TBA();
	void CreatTBA(TGBA tgba, formula_stack Ustack);
	void CreatTBAsub(TGBA tgba, formula_stack Ustack);
	void AddArc(int vexloc, ArcNode *&arcloc);     
	bool fetchvirgin(int &adj);        
	int LocateVex(VertexType v);    
	void PrintBuchi(string filename);
	friend class SBA;
};
