#include <map>
#include <set>
#include <cmath>
#include <stack>
#include <ctime>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cassert>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1010;

struct node{
	bool flag;
	double val;
	char op;
	int lc, rc;
}oper[maxn];

int n;
char s[maxn];

void Init(void)
{
	n = 1; 
	for(const char *p = s, *q; *p && *p != '='; p ++)
	{
		string ss; ss.clear();
		for(q = p; isdigit(*q) || *q == '.'; q ++)
		{
			ss += *q;
		}
		if( p == q )
		{
			oper[n].op = *p; oper[n].flag = 1; oper[n].val = 0.0;
			oper[n].lc = oper[n].rc = 0;
			n ++;
		}
		else {
			p = -- q;
			oper[n].val = atof(ss.c_str());
			oper[n].flag = 0; oper[n].op = '\0'; oper[n].lc = oper[n].rc = 0;
			n ++;
		}
	}
}

int build_tree(int x, int y)
{
	int p1 = 0, p2 = 0, c = 0;

	if( x == y )  return x;

	for(int i = x; i <= y; i ++)
	{
		if( !oper[i].flag ) continue;
		if( oper[i].op == '(' ) c ++;
		else if( oper[i].op == ')' ) c --;
		else if( oper[i].op == '+' || oper[i].op == '-' ) { if( !c ) p1 = i; }	
		else if( oper[i].op == '*' || oper[i].op == '/' ) { if( !c ) p2 = i; }
	}

	if( p1 <= 0 ) p1 = p2;
	if( p1 <= 0 ) return build_tree(x+1, y-1);

	oper[p1].lc = build_tree(x, p1-1);
	oper[p1].rc = build_tree(p1+1, y);

	return p1;
}

void PostTraverse(int root)
{
	if( !root ) return ;
	PostTraverse(oper[root].lc);
	PostTraverse(oper[root].rc);
	if( oper[root].lc == 0 ) return ;
	switch( oper[root].op )
	{
		case '+': oper[root].val = oper[oper[root].lc].val + oper[oper[root].rc].val; break;
		case '-': oper[root].val = oper[oper[root].lc].val - oper[oper[root].rc].val; break;
		case '*': oper[root].val = oper[oper[root].lc].val * oper[oper[root].rc].val; break;
		case '/': oper[root].val = oper[oper[root].lc].val / oper[oper[root].rc].val; break;
	}
}

void Process(void)
{
	Init();
	// for(int i = 1; i < n; i ++)
	// 	if( !oper[i].flag ) printf("%.2lf", oper[i].val);
	// 	else printf("%c", oper[i].op);
	int root = build_tree(1, n-1);
	//printf("%d ", root);
	PostTraverse(root);
	printf("%.2lf\n", oper[root].val);
}

int main(int argc, char const *argv[])
{
#ifndef ONLINE_JUDGE
		freopen("test.in", "r", stdin);
#endif
	int cnt;
	scanf("%d ", &cnt);
	while( cnt -- )
	{
		scanf("%s ", s);
		Process();
	}
	return 0;
}