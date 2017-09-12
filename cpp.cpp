#include "hpp.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
int main(int argc, char *argv[], char *envp[]) {
	env = new Env("global");					// create global env
	Sym* V = new Vector(); env->set("argv",V);	// \ create argv[] vector
	env->set("argc",new Num(argc));
	for (int i=0;i<argc;i++)
		V->push(new Str(argv[i]));				// /
	env_init();									// continue with env_init
	return yyparse(); }							// run source parser from stdin

Sym::Sym(string T, string V) { tag = T; val = V; }
Sym::Sym(string V):Sym("sym",V){}
Sym::~Sym(){/* does nothing */}

Sym* Sym::push(Sym*o) { nest.push_back(o); return this; }
Sym* Sym::set(string A,Sym*o) { attr[A]=o; return this; }

set<Sym*> dump_used;
string Sym::dump(int depth) {
	// <header>
	string S = "\n"+pad(depth)+head();
	// infty recursion fix
	if (depth==0) dump_used.clear();								// top clear
	if (dump_used.find(this) != dump_used.end() ) return S+" ...";	// infty
	dump_used.insert(this);											// save
	// attr{}ibutes
	for (auto i=attr.begin(),e=attr.end();i!=e;i++)
		S += "\n"+pad(depth+1) + i->first + " =" + i->second->dump(depth+2);
	// nest[]ed
	for (auto j=nest.begin(),e=nest.end();j!=e;j++)
		S += (*j)->dump(depth+1);
	return S; }
string Sym::head() { ostringstream os;
	os<<"<"<<tag<<":"<<val<<"> @"<<this; return os.str(); }
string Sym::pad(int n) { string S;
	for (int i=0;i<n;i++) S += '\t'; return S; }

Sym* Sym::eval(Sym*E) { return this; }

Str::Str(string V):Sym("str",V){}
string Str::head() { ostringstream os; os<<"'"<<val<<"' @"<<this; return os.str(); }

Num::Num(string V):Sym("num",V) { val = atof(V.c_str()); }
Num::Num(int N):Sym("num","") { val = N; }
string Num::head() { ostringstream os; os<<val<<" @"<<this; return os.str(); }

Op::Op(string V):Sym("op",V){}
Sym* Op::eval(Sym*E) {
	if (val=="=") { E->set(nest[0]->val,nest[1]); return nest[1]; }
	return this; }

Vector::Vector():Sym("vector",""){}
string Vector::head() { ostringstream os; os<<"[] @"<<this; return os.str(); }

Env::Env(string V):Sym("env",V) { next = NULL; }
Env *env = NULL, *meta=NULL;
void env_init() {
	// self link
	env->set("global",env);
	// meta info
	meta = new Env("meta"); env->set("meta",meta);
	meta->set("MODULE",new Str(MODULE));
	meta->set("TITLE",new Str(TITLE));
	meta->set("AUTHOR",new Str(AUTHOR));
	meta->set("LICENSE",new Str(LICENSE));
	meta->set("GITHUB",new Str(GITHUB));
}
