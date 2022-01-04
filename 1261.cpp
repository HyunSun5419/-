#include <iostream>
#include <string>
#include <queue>

using namespace std;

priority_queue<pair<int, pair<int, int> > > pq; // <distance <x, y>>
bool map[101][101] = {false, };
int dist[101][101];
int N;
int M;
int INF = 987654321;

bool possible(int r, int c) {
    if(r < 1 || r > N) return false;
    if(c < 1 || c > M) return false;

    return true;
}

pair<int, int> next_state(int r, int c, int state) {
    if(state == 0) return make_pair(r-1, c);
    if(state == 1) return make_pair(r+1, c);
    if(state == 2) return make_pair(r, c-1);
    
    return make_pair(r, c+1);
}

int main() {    

    string input;
    cin >> M >> N;
    
    for(int i = 1; i <= N; i++) {
        cin >> input;
        for(int j = 0; j < input.size(); j++) {
            map[i][j+1] = input[j] - '0';
            dist[i][j+1] = INF;
        }
    }

    dist[1][1] = 0;
    pq.push(make_pair(0, make_pair(1,1)));

    while(!pq.empty()) {
        int x_current = pq.top().second.first;
        int y_current = pq.top().second.second;
        int distance = -pq.top().first;
        pq.pop();

        if(distance > dist[x_current][y_current]) continue;

        for(int i = 0; i < 4; i++) {
            int x_next = next_state(x_current, y_current, i).first;
            int y_next = next_state(x_current, y_current, i).second;
            int nextDistance = distance;
            if(!possible(x_next, y_next)) continue;

            nextDistance += map[x_next][y_next];

            if(nextDistance < dist[x_next][y_next]) {
                dist[x_next][y_next] = nextDistance;
                pq.push(make_pair(-nextDistance, make_pair(x_next, y_next)));
            } 
        }
    }

    cout << dist[N][M] << "\n";

    return 0;
}