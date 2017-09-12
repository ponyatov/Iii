#ifndef _H_HPP
#define _H_HPP

// meta info

#define MODULE	"I"
#define TITLE	"Interpreter"
#define AUTHOR	"Dmitry Ponyatov <dponyatov@gmail.com>"
#define LICENSE	"GNU LesserGPL"
#define GITHUB	"https://github.com/ponyatov/I"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>		// for nest[]ed
#include <map>			// for attr[]ibutes
#include <set>			// for dump() with infty recursion fix

using namespace std;

struct Sym {							// === [sym]bol
	string tag,val;							// tag (class,type) and item value
	Sym(string T,string V);					// <T:V> constructor
	Sym(string V);							// <sym:V> constructor
	virtual ~Sym();							// destructor
	vector<Sym*> nest; Sym* push(Sym*);		// == nest[]ed elements
	map<string,Sym*> attr;					// == attr{}ibutes
	Sym* set(string,Sym*);					// setter
	virtual string dump(int depth=0);		// == dump object in text form
	virtual string head();					// <T:V> header in text form
	string pad(int);						// left pad with tabs
	virtual Sym* eval(Sym*);				// == evaluate in environment
	Sym* next=NULL;							// ptr to next env in chain
	virtual Sym* lookup(string);			// lookup over chained Env's
};

struct Env:Sym { Env(string,Env*); };		// environment {table}
extern Env* env;							// global environment
extern void env_init();						// init global env

struct Str:Sym { Str(string);				// string
	string head(); };
struct Num:Sym { Num(string); double val;	// number
	Num(int); string head(); };

struct Op:Sym { Op(string); 				// operator
	Sym* eval(Sym*); };

struct Vector:Sym { Vector();				// [ vec tor ]
	string head(); };

extern int yylex();							// lexer/parser interface
extern int yylineno;
extern char* yytext;
#define TOC(C,X) { yylval.o = new C(yytext); return X; }	/* token */
extern int yyparse();
extern void yyerror(string);
#include "ypp.tab.hpp"

#endif // _H_HPP
