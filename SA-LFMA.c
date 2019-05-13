#include <stdio.h>
#include <malloc.h>
#include <string.h>
//#define L_TYPE 0
//#define S_TYPE 1
#define bool char
//#define true 1
//#define false 0
#define MAXN 65537
bool t[MAXN << 1];
int sa[MAXN], ht[MAXN], rk[MAXN];
bool islms(const int i, const bool *t) { 
    return i > 0 && t[i] && !t[i - 1]; 
}
void sort(int* s, int *sa, const int len, const int sigma, const int sz, bool *t, int *b, int *cb, int *p) {
//    	printf("aaa\n");
    memset(b, 0, sizeof(int) * sigma);
    memset(sa, -1, sizeof(int) * len);
    for (int i = 0; i < len; i++){
		b[s[i]]++;
	}
    cb[0] = b[0];
    for (int i = 1; i < sigma; i++) cb[i] = cb[i - 1] + b[i];
    for (int i = sz - 1; i >= 0; i--) sa[--cb[s[p[i]]]] = p[i];
    for (int i = 1; i < sigma; i++) cb[i] = cb[i - 1] + b[i - 1];
    for (int i = 0; i < len; i++) if (sa[i] > 0 && !t[sa[i] - 1]) sa[cb[s[sa[i] - 1]]++] = sa[i] - 1;
    cb[0] = b[0];
    for (int i = 1; i < sigma; i++) cb[i] = cb[i - 1] + b[i];
    for (int i = len - 1; i >= 0; i--) if (sa[i] > 0 && t[sa[i] - 1]) sa[--cb[s[sa[i] - 1]]] = sa[i] - 1;
}
void sais(int* s, int *sa, const int len, bool *t, int *b, int *b1, const int sigma) {
//    	printf("here\n");
    int i, j, x, p = -1, cnt = 0, sz = 0, *cb = b + sigma;
    for (t[len - 1] = 1, i = len - 2; i >= 0; i--) t[i] = s[i] < s[i + 1] || (s[i] == s[i + 1] && t[i + 1]);
    for (i = 1; i < len; i++) if (t[i] && !t[i - 1]) b1[sz++] = i;
    sort(s, sa, len, sigma, sz, t, b, cb, b1);
    for (i = sz = 0; i < len; i++) if (islms(sa[i], t)) sa[sz++] = sa[i];
    for (i = sz; i < len; i++) sa[i] = -1;
    for (i = 0; i < sz; i++) {
        for (x = sa[i], j = 0; j < len; j++) {
            if (p == -1 || s[x + j] != s[p + j] || t[x + j] != t[p + j]) { cnt++, p = x; break; }
            else if (j > 0 && (islms(x + j, t) || islms(p + j, t))) break;
        }
        sa[sz + (x >>= 1)] = cnt - 1;
    }
    for (i = j = len - 1; i >= sz; i--) if (sa[i] >= 0) sa[j--] = sa[i];
    int *s1 = sa + len - sz, *b2 = b1 + sz;
    if (cnt < sz) sais(s1, sa, sz, t + len, b, b1 + sz, cnt);
    else for (i = 0; i < sz; i++) sa[s1[i]] = i;
    for (i = 0; i < sz; i++) b2[i] = b1[sa[i]];
    sort(s, sa, len, sigma, sz, t, b, cb, b2);
}
void getHeight(int* s, int n) {
    for (int i = 1; i <= n; i++) rk[sa[i]] = i;
    int j = 0, k = 0;
    for (int i = 0; i < n; ht[rk[i++]] = k)
        for (k ? k-- : 0, j = sa[rk[i] - 1]; s[i + k] == s[j + k]; k++);
}
void init(int* s, const int len, const int sigma) {
//    	memset(t,0,sizeof(t));
//    	memset(sa,0,sizeof(sa));
//    	memset(ht,0,sizeof(ht));
//    	memset(rk,0,sizeof(rk));
    sais(s, sa, len, t, rk, ht, sigma), rk[0] = 0;
}
//int SA[10000005];
//int height[10000005];
//int lRPOS[10000005];
//int lRLEN[10000005];
//int rRPOS[10000005];
//int rRLEN[10000005];
//int RPOS[10000005];
//int RLEN[10000005];
//int n;
//void init(){
//	memset(lRLEN,0,sizeof(lRLEN));
//	memset(lRPOS,-1,sizeof(lRPOS));
//	memset(rRLEN,0,sizeof(rRLEN));
//	memset(rRPOS,-1,sizeof(rRPOS));	
//}
//void func1(){
//	stack<pair<int,int> >stk;
//	for(int i=0;i<n;i++){
//		if(stk.empty())
//			stk.push({SA[i],0});
//		else{ 
//			int lcp=height[i];
//			while(!stk.empty()&&stk.top().first>SA[i]){
//				lcp=min(lcp,stk.top().second);
//				stk.pop();
//			}
//			if(!stk.empty()&&lcp>0){
//				lRPOS[SA[i]]=stk.top().first;
//				lRLEN[SA[i]]=lcp;
//			}
//			stk.push({SA[i],lcp});
//		}
//	}	
//}
//void func2(){
//	stack<pair<int,int> >stk;
//	for(int i=n-1;i>=0;i--){
//		if(stk.empty())
//			stk.push({SA[i],0});
//		else{ 
//			int lcp=height[i+1];
//			while(!stk.empty()&&stk.top().first>SA[i]){
//				lcp=min(lcp,stk.top().second);
//				stk.pop();
//			}
//			if(!stk.empty()&&lcp>0){
//				rRPOS[SA[i]]=stk.top().first;
//				rRLEN[SA[i]]=lcp;
//			}
//			stk.push({SA[i],lcp});
//		}
//	}	
//}
//void getres(){
//	for(int i=0;i<n;i++){
//		if(lRLEN[i]>rRLEN[i]){
//			RLEN[i]=lRLEN[i];
//			RPOS[i]=lRPOS[i];
//		}else{
//			RLEN[i]=rRLEN[i];
//			RPOS[i]=rRPOS[i];
//		}
//	}
//}
//void output(){
//	for(int i=0;i<n;i++)cout<<SA[i]<<'\t';cout<<endl;
//	for(int i=0;i<n;i++)cout<<height[i]<<'\t';cout<<endl;
//	for(int i=0;i<n;i++)cout<<lRPOS[i]<<'\t';cout<<endl;
//	for(int i=0;i<n;i++)cout<<lRLEN[i]<<'\t';cout<<endl;
//	for(int i=0;i<n;i++)cout<<rRPOS[i]<<'\t';cout<<endl;
//	for(int i=0;i<n;i++)cout<<rRLEN[i]<<'\t';cout<<endl;
//	for(int i=0;i<n;i++)cout<<RPOS[i]<<'\t';cout<<endl;
//	for(int i=0;i<n;i++)cout<<RLEN[i]<<'\t';cout<<endl;
//}
//void readfile(){
//	freopen("a.txt","r",stdin);
//	ios::sync_with_stdio(false);cin.tie(0);
//	cin>>s;
//}
char s[100005];
int ss[100005];

int main() {
//	readfile();
//	freopen("b.txt","w",stdout);
//	s="aaabbaaabbbaa";
//	char*s="banana";
	scanf("%s",s);
	int n=strlen(s);
	for(int i=0;i<=n;i++)ss[i]=s[i];
	ss[n]=0;
    init(ss, n + 1, 256);
    getHeight(ss,n);
	for(int i=1;i<=n;i++)printf("%d ",sa[i]+1);
	printf("\n");
	for(int i=2;i<=n;i++)printf("%d ",ht[i]);
	
//	init();
//	func1();
//	func2();
//	getres();
//
//	output();
	
    return 0;
}
