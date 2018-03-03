import sys
sys.stdin = open("lis.in")
sys.stdout = open("lis.out", "w")
n = input()
a = list(map(int, input().split()))
dp = [1] * len(a)
p = [-1] * len(a)
for i in range(len(a)):
    for j in range(i):
        if a[j] < a[i]:
            dp[i] = max(dp[i], dp[j] + 1)
            if dp[j] + 1 == dp[i]:
                p[i] = j
ans = max(dp)
print(ans)
ansArray = []
for i in range(len(dp)):
    if dp[i] == ans:
        ansArray.append(a[i])
        j = p[i]
        while j != -1:
            ansArray.append(a[j])
            j = p[j]
        print(*ansArray[::-1])
        break
sys.stdin.close()
sys.stdout.close()