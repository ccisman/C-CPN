#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<regex>
#include<fstream>
using namespace std;
#define ERROR 0
#define OK 1
#define $Neg 1     //! ��
#define $Impli 2   //-> �̺�
#define $Equ 3    //<-> �ȼ�
#define $And 4   //&& ��ȡ
#define $Or 5     //|| ��ȡ
#define $Alw 6    // [] G
#define $Eve 7    // <> F
#define $Until 8   // U
#define $Rele 9   // R
#define $Next 10  // X
#define $Lpar 11   // (
#define $Rpar 12  // )
#define $ID 13    
#define $End 14
#define $root 15



typedef struct Lexer_word
{
	string character;
	int typenum;
}word;

class Lexer  
{
private:
	char formula[10000];
	int pointer;
	int length;
public:
	Lexer(char *form, int len);
	int GetWord(word &w);
};

class AtmoicProps
{
public:
	vector<word> APs;
	vector<string> place, transition, others;
	void GetAllAPs(Lexer lex);
	void AP2PT(bool onlyPT);
	void extract_PT(string s, bool onlyPT);
};

void getPTinformula(string filename, vector<string> &place, vector<string> &transition, vector<string> &others , bool onlyPT);