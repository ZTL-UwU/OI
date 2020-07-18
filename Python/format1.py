//C++:
inline long long extend_gcd(long long a,long long b,long long &x,long long &y)
{
    if(a==0&&b==0)
        return -1ll;
    if(b==0)
    {
        x=1ll;
        y=0ll;
        return a;
    }
    long long d=extend_gcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
inline long long mod_reverse(long long a,long long n)
{
    long long x,y,d=extend_gcd(a,n,x,y);
    if(d==1)
        {
                    if(x%n<=0)return x%n+n;
                    else return x%n;
                 }
    else
        return -1ll;
}

//Python:
def ext_euclid(a, b):
    old_r, r = a, b
    old_s, s = 1, 0
    old_t, t = 0, 1
    if b == 0:
        return 1, 0, a
    else:
        while (r != 0):
            q = old_r // r
            old_r, r = r, old_r - q * r
            old_s, s = s, old_s - q * s
            old_t, t = t, old_t - q * t
    return old_s, old_t, old_r


def inv(a, p):
    _a, _, _ = ext_euclid(a, p)
    return ((_a % p) + p) % p