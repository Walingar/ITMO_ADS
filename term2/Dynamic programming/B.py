import sys
 
sys.stdin = open("lcs.in")
sys.stdout = open("lcs.out", "w")
n = int(input())
a = list(map(int, input().split()))
m = int(input())
b = list(map(int, input().split()))
dp = [[0] * (m + 1) for i in range(n + 1)]
p = [[0] * (m + 1) for i in range(n + 1)]
 
for i in range(1, n + 1):
    for j in range(1, m + 1):
        if a[i - 1] == b[j - 1]:
            dp[i][j] = dp[i - 1][j - 1] + 1
            p[i][j] = [i - 1, j - 1]
        else:
            if dp[i - 1][j] >= dp[i][j - 1]:
                dp[i][j] = dp[i - 1][j]
                p[i][j] = [i - 1, j]
            else:
                dp[i][j] = dp[i][j - 1]
                p[i][j] = [i, j - 1]
i = n
j = m
ans = []
print(dp[n][m])
del dp
while i != 0 and j != 0:
    if p[i][j] == [i - 1, j - 1]:
        ans.append(a[i - 1])
        i -= 1
        j -= 1
    else:
        if p[i][j] == [i - 1, j]:
            i -= 1
        else:
            j -= 1
 
print(*ans[::-1])
sys.stdin.close()
sys.stdout.close()