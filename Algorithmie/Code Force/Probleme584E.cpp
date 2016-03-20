/*#include<iostream>
#include<math.h>
#include<string.h>
#include<vector>
#include<queue>
#include<stdio.h>
using namespace std;

int a[2005];
int b[2005];
int c[2005];
int d[2005];
int ans1[520005];
int ans2[520005];
int main()
{
    int n;
    int tot = 0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
        scanf("%d",&b[i]),c[b[i]]=i;
    int ans= 0;
    for(int i=1;i<=n;i++)
    {
        if(a[i]!=b[i]){
            int k = -1;
            for(int j=i+1;j<=n;j++)
                if(a[j]==b[i])
                {
                    k = j;
                    break;
                }
            while(k!=i)
            {
                for(int j = i;j<k;j++)
                {
                    if(c[a[j]]>=k)
                    {
                        ans += std::abs(k-j);
                        swap(k,j);
                        swap(a[k],a[j]);
                        ans1[tot]=k;
                        ans2[tot]=j;
                        tot++;
                        break;
                    }
                }
            }
        }
    }
    cout<<ans<<endl;
    cout<<tot<<endl;
    for(int i=0;i<tot;i++)
        printf("%d %d\n",ans1[i],ans2[i]);
}

*/