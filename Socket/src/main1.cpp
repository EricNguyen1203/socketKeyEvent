#include <iostream>

using namespace std;

long long solve(){
    int m, n, x, y;
    cin >> n >> m >> x >> y;

    char arr[100][1000];
    long long res = 0;
    int count = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> arr[i][j];

    for(int i = 0; i < n; i++){
        count = 0;
        for(int j = 0; j < m; j++){
            if(arr[i][j] == '.')
                count++;
            else {
                res += (2*x < y) ? (count*x) : ((count/2)*y + (count%2)*x);
                count = 0;
                }
        }
        res += (2*x < y) ? (count*x) : ((count/2)*y + (count%2)*x);
    }
    return res;
}

int main(){
    int t;
    cin >> t;

    while(t--){
        cout << solve() << endl;
    }
}