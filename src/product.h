#ifndef PRODUCT_H
#define PRODUCT_H
#define max_to_string 30
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<set>
#include<vector>
#include<string>
#include<cstdlib>
#include "cpn.h"
#include "RG.h"
#include"SBA.h"
#define max_array_num 10000
using namespace std;

/*********************************Global_functions***********************************/
bool judgeF(string s);           
int convert(RG rg, C_Petri ptnet, int i, int j);
int sumtoken(C_Petri ptnet, RG rg, string s, int statenum);         
int localBA(SBA ba, string val);                                              
int localRG(RG rg, string val);                                              
bool handleFLTLF(C_Petri ptnet, RG rg, string s, int statenum);  
void handleLTLCstep(C_Petri ptnet, RG rg, int &front_sum, int &latter_sum, string s, int statenum);
bool handleLTLC(C_Petri ptnet, RG rg, string s, int statenum);   
/*******************************Global_functions End**********************************/

typedef struct Product
{                                      
	string RGname;           
	int RGname_id;
	string BAname;           
	int BAname_id;
	int pro_id;                         

};

typedef struct 	T         
{
	Product s;            
	Product e;          


};

typedef struct node   
{
	int to;        
	int next;     
};

class Product_Automata
{
private:
	vector<Product> status;     
	vector<T> transition;          
	vector<Product> initial_status; //
	vector<Product> isaccept;       //
	vector<int> isAccept_id;           
	int *heads;
	int *DFN;
	int *LOW;
	int *stack;
	int *visit;
	node *edge;
	bool result;
public:
	Product_Automata();
	void getProduct(C_Petri ptnet, RG rg, SBA ba);
	void addisaccept(SBA ba, int i, Product n);
	void addinitial_status(SBA ba, int i, int j, Product n);
	void addstatus(Product n);
	void addtransitionR(RG rg, SBA ba, int i, int j, Product n, ofstream &outfile);
	void addtransitionF(RG rg, SBA ba, int i, int j, Product n, ofstream &outfile); 
	void tarjan(int x, node *edge, int *LOW, int *DFN, int *stack, int *visit, int *heads);                
	void ModelChecker(C_Petri ptnet, RG rg, SBA ba, string propertyid);
	void initate_array();
	~Product_Automata();
	//void garbowbfs(int cur, int temper);

};
bool isLabel(C_Petri ptnet, RG rg, SBA ba, int vi, int sj, ofstream &ofe);       
void add(int x, int y, node *edge, int *heads);           


#endif
