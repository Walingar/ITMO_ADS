import sys
def kth(l,r,k):
    global a
    m = a[(l+r)//2]
    i = 0
    j = r
    while i <= j:
        while a[i] < m: i += 1
        while a[j] > m: j -= 1
        if i <= j:
            temp = a[i]
            a[i] = a[j]
            a[j] = temp
            i += 1
            j -= 1
    if l <= k and k <= j:
        return kth(l, j, k)
    if i <= k and k <= r:
        return kth(i, r, k)
    return a[k]
sys.stdin = open("kth.in")
sys.stdout = open("kth.out", "w")
n,k = map(int,input().split())
a = []
a1,b,c,temp1,temp2 = map(int,input().split())
a.append(temp1)
a.append(temp2)
for i in range(2,n):
    a.append(a1*a[i-1] + b*a[i-2] + c)
print(kth(0,n-1,k-1))
sys.stdin.close()
sys.stdout.close()