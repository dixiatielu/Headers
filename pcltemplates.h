/************
Author:DXTL
Last Update:2019.10.16
Copyright 2019
Version Alpha 0.0.0
*************/
#ifndef PCLTPL_H
#define PCLTPL_H
#include <cstring>
template<typename T>
class XDS
{
	private:
		T n;
		long long lazy[35000000];
		long long val[35000000];
		inline T lson(T x){return x << 1;}
		inline T rson(T x){return x << 1 | 1;}
		inline void build(T now,T l,T r,long long a[])
		{
			lazy[now] = 0;
			if(l == r)
			{
				val[now] = a[l];
				return;
			}
			T mid = (l + r) >> 1;
			build(lson(now),l,mid,a);
			build(rson(now),mid + 1,r,a);
			val[now] = val[lson(now)] + val[rson(now)];
		}
		inline void add(T now,T l,T r,T va)
		{
			lazy[now] += va;
			val[now] += va * 1ll * (r - l + 1);
		}
		inline void pushdown(T now,T l,T r,T mid)
		{
			if(!lazy[now])
			{
				return;
			}
			add(lson(now),l,mid,lazy[now]);
			add(rson(now),mid + 1,r,lazy[now]);
			lazy[now] = 0;
		}
		inline void mutify(T now,T l,T r,T x,T y,T va)
		{
			if(l >= x && r <= y)
			{
				val[now] += 1ll * (r - l + 1) * va;
				lazy[now] += va;
				return;
			}
			T mid = (l + r) >> 1;
			pushdown(now,l,r,mid);
			if(x <= mid)
			{
				mutify(lson(now),l,mid,x,y,va);
			}
			if(mid < y)
			{
				mutify(rson(now),mid + 1,r,x,y,va);
			}
			val[now] = val[lson(now)] + val[rson(now)];
		}
		inline long long query(T now,T l,T r,T x,T y)
		{
			if(l >= x && r <= y)
			{
				return val[now];
			}
			long long res = 0;
			T mid = (l + r) >> 1;
			pushdown(now,l,r,mid);
			if(x <= mid)
			{
				res += query(lson(now),l,mid,x,y);
			}
			if(mid < y)
			{
				res += query(rson(now),mid + 1,r,x,y);
			}
			return res;
		}
	public:
		inline void Rbuild(T _n,long long a[])
		{
			n = _n;
			build(1,1,n,a);
		}
		inline void Rmutify(T x,T y,T k)
		{
			mutify(1,1,n,x,y,k);
		}
		inline long long Rquery(T x,T y)
		{
			return query(1,1,n,x,y);
		}
};
#endif
