#pragma once
#include"TBA.h"

typedef int SVertexType;
typedef struct SArcNode
{
	int adjvex;
	SArcNode *nextarc = NULL;           
}SArcNode;
typedef struct SVNode
{
	SVertexType data = -1;		
	bool isAccept;        
	bool isInitial;         
	set<int> incoming;    
	set<int> outset;        

	string label;
	set<string> fullfilledAP;
	SArcNode *firstarc = NULL;    
}SVNode;

class SBA
{
public:
	int svex_num;
	SVNode svertics[MAX_VERTEX_NUM];
public:
	SBA();
	void CreatSBA(TBA &tba);
	void Simplify();
	void Compress();
private:
	void AddArc(int pri, int suc);
	void Delallarc(int vexloc);
	void Delarc(int vexloc, int adj);
	void findnextempty(int start, int &next);
	void findnextoccupied(int start, int &next, int &vexn);
};
