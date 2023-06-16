#include <iostream>
#include <vector>
#include <cmath>
#include <deque>
#include <map>
#include <random>
#include <algorithm>
using namespace std;

bool useStrangeSolution=true;
bool isfor2=true;
const int MAXN=int(3e2)+7;
const pair<int,int> dways[8]={{1,0},{0,1},{-1,0},{0,-1},{1,1},{-1,1},{1,-1},{-1,-1}};

int n,m,k,g;
int maze[MAXN][MAXN];

int dist[MAXN][MAXN];
pair<int,int> pr[MAXN][MAXN];
map<pair<int,int>,int> getways(bool isstrangesolution) {
    map<pair<int,int>,int> result;
    deque <pair<int,int>> q;
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            dist[i][j]=-1;
            pr[i][j]={i,j};
            if (maze[i][j]==g) {
                q.push_back({i,j});
                dist[i][j]=0;
            }
        }
    }
    while (!q.empty()) {
        auto [r,c]=q.front();
        q.pop_front();
        for (int i=0;i<8;i++) {
            int newr=r+dways[i].first;
            int newc=c+dways[i].second;
            if (0<=newr && newr<n && 0<=newc && newc<m) {
                if (dist[newr][newc]==-1) {
                    if (maze[newr][newc]==0) {
                        dist[newr][newc]=dist[r][c]+1;
                        pr[newr][newc]={r,c};
                        q.push_back({newr,newc});
                    } else if (maze[newr][newc]==-g && (maze[r][c]==g || maze[r][c]==-g)) {
                        dist[newr][newc]=dist[r][c];
                        pr[newr][newc]={newr,newc};
                        q.push_front({newr,newc});
                    } else if (1<=maze[newr][newc] && maze[newr][newc]<=k && (maze[r][c]==g || maze[r][c]==0 || maze[r][c]==-g)) {
                        dist[newr][newc]=dist[r][c]+1;
                        pr[newr][newc]={r,c};
                        q.push_back({newr,newc});
                    }
                }
            }
        }
    }
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            if (1<=maze[i][j] && maze[i][j]<=k && maze[i][j]!=g && dist[i][j]!=-1 && !isstrangesolution) {
                int r=i,c=j;
                int cnt=dist[i][j];
                int ar=i,ac=j;
                while (!(pr[r][c].first==r && pr[r][c].second==c)) {
                    ar=r;
                    ac=c;
                    int fr=pr[r][c].first;
                    int fc=pr[r][c].second;
                    r=fr;
                    c=fc;
                }
                if (result.find({ar,ac})==result.end()) {
                    result[{ar,ac}]=cnt;
                } else {
                    result[{ar,ac}]=min(result[{ar,ac}],cnt);
                }
            }
        }
    }
    int nearst=n*m;
    for (auto [i,j]:result) {
        nearst=min(nearst,j);
    }
    if (result.size()==0 || (nearst>2 && isfor2)) {
        result.clear();
        for (int i=0;i<n;i++) {
            for (int j=0;j<m;j++) {
                if (dist[i][j]==1) {
                    result[{i,j}]=1;
                }
            }
        }
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    mt19937 GRAND(int(1e9+7));
    cin >> n >> m >> k;
    cin >> g;
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            cin >> maze[i][j];
        }
    }
    char run='r';
    while (run=='r') {
        vector <pair<int,pair<int,int>>> ans;
        for (int k2=0;k2<3;k2++) {
            map<pair<int,int>,int> res=getways(GRAND()%10==0 && useStrangeSolution);
            vector <pair<int,pair<int,int>>> an1,an2;
            for (auto [i,j]:res) {
                an1.push_back({j,i});
            }
            sort(an1.begin(),an1.end());
            map <int,vector<pair<int,int>>> ann;
            for (auto [j,i]:an1) {
                ann[j].push_back(i);
            }
            for (auto [j,i]:ann) {
                shuffle(i.begin(),i.end(),GRAND);
                for (auto k:i) {
                    an2.push_back({j,k});
                }
            }
            for (auto [j,i]:an2) {
                ans.push_back({j,i});
                int r=i.first;
                int c=i.second;
                if (maze[r][c]==0) maze[r][c]=g;
                else maze[r][c]=-g;
                break;
            }
        }
        cout << g << " " << min(int(ans.size()),3) << " ";
        for (int i=0;i<min(int(ans.size()),3);i++) {
            cout << ans[i].second.first+1 << " " << ans[i].second.second+1 << " ";
        }
        cout << "\n";

        // cout << "---\n";
        // for (int i=0;i<n;i++) {
        //     for (int j=0;j<m;j++) {
        //         cout << maze[i][j] << " ";
        //     } cout << "\n";
        // }
        // cout << "---\n";

        cout.flush();
        cin >> run;
        if (run=='o') {
            return 0;
        }
        for (int i=0;i<k-1;i++) {
            int gother,A;
            cin >> gother >> A;
            for (int j=0;j<A;j++) {
                int r,c;
                cin >> r >> c;
                r--;
                c--;
                if (maze[r][c]==0) {
                    maze[r][c]=gother;
                } else {
                    maze[r][c]=-gother;
                }
            }
        }
    }
}