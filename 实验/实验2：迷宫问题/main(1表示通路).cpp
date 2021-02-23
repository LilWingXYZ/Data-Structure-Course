#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

int n,m;

const int maxn=20;

int maxtri[maxn][maxn];
int flag[maxn][maxn];

vector<pair<int,int> > ans;

pair<int ,int> begin_point,end_point;

int X[4]={0,-1,0,1};
int Y[4]={-1,0,1,0};

int p_flag=0;

void DFS(int x,int y)
{
    flag[x][y]=1;
    ans.push_back(make_pair(x,y));
    if(x==end_point.first&&y==end_point.second)
    {
        if(p_flag==0)    p_flag=1;
        //ans.push_back(make_pair(x,y));
        for(int i=0;i<ans.size();i++)
        {
            if(i>0)
            {
                printf("->");
            }
            printf("(%d,%d)",ans[i].first,ans[i].second);
        }
        printf("\n");
        return ;
    }
    for(int i=0;i<4;i++)
    {
        int newx=x+X[i];
        int newy=y+Y[i];
        if(newx>=1&&newx<=n&&newy>=1&&newy<=m&&maxtri[newx][newy]==1&&flag[newx][newy]==0)
        {
            DFS(newx,newy);
            ans.pop_back();
            flag[newx][newy]=0;
        }
    }
    return ;
}

int main()
{
    cout<<"输入m,n "<<endl;
    memset(flag,0,sizeof(flag));
    scanf("%d %d",&n,&m);
    cout<<"输入一个m行n列的矩阵，及其起点与终点(1表示通路，0表示无路)" <<endl; 
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&maxtri[i][j]);
        }
    }
    //画边界
    for(int i=0;i<=n+1;i++)
    {
        for(int j=0;j<=m+1;j++)
        {
            if(i==0||j==0||i==n+1||j==m+1)
            {
                maxtri[i][j]=0;
            }
        }
    }
    scanf("%d %d",&begin_point.first,&begin_point.second);
    scanf("%d %d",&end_point.first,&end_point.second);
    DFS(begin_point.first,begin_point.second);
    if(p_flag==0)
    {
        printf("-1\n");
    }
    return 0;
}

