#include <bits/stdc++.h>
using namespace std;

void HOKSHA() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

}
int dx[] = {1,-1,0,0};
int dy[] ={0,0,1,-1};
// create class to save information about current state like the value of array
// and parent of it
#define  all(a)  a.begin() a.end()

class Game {
public: vector<vector<char>>state;
public : Game* parent = nullptr;
public: int level = 0;
public:
     Game(){
         state.resize(3,vector<char>(3));
     }
     void setIntialState(){
         for (int i = 0; i < 3; i++)
             for (int j = 0; j < 3; j++)
                 cin >>  state[i][j];
     }
     void getState(){
         cout << "=================" << endl;
         for (int i = 0; i < 3; i++){
             for (int j = 0; j < 3; j++){
                 cout << state[i][j] << " ";
             }
             cout << endl;
         }
         cout << "=================" << endl;
     }
     bool isGoalState(){
         vector<vector<char>>Goal = {{'1','2','3'},
                                     {'4','5','6'},
                                     {'7','8', '*'}};
         for (int i = 0; i < 3; i++){
             for (int j = 0 ; j < 3; j++)
                 if (state[i][j] != Goal[i][j]) return false;
         }
         return true;
     }
     void printPath(){
         cout << "the solution is found by * BFS * after :" << level << " operation " << endl;
         deque<vector<vector<char>>>solution;
         Game* path = this;
         while (true){
             vector<vector<char>>now(3,vector<char>(3));
             for (int i = 0; i < 3; i++){
                 for (int j = 0; j < 3; j++){
                     now[i][j] = path->state[i][j];
                 }
             }
             solution.push_front(now);
             if (path->parent == nullptr) break;
             path = path->parent;
         }
         cout << "=================" << endl;
         for (int i = 0; i < (int)solution.size(); i++){
             for (int j = 0; j < 3; j++){
                 for (int k = 0; k < 3; k++){
                     cout << solution[i][j][k] << " ";
                 }
                 cout << endl;
             }
             cout << "=================" << endl;
         }
     }
     bool move(int i, int j){
         return i >= 0 && i < 3 && j >= 0 && j < 3;
     }
    vector<Game*> valid_Actions(){
        vector<Game*> actions;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (this->state[i][j] == '*'){
                    for (int k = 0; k < 4; k++){
                        int nx = i + dx[k];
                        int ny = j + dy[k];
                        if (move(nx,ny)){
                            Game* new_state = new Game(*this);
                            swap(new_state->state[i][j], new_state->state[nx][ny]);
                            actions.push_back(new_state); 
                        }
                    }
                }
            }
        }
        return actions;
    }

};
bool ok = false;
void BFS_8_solver(Game* intial){
    queue<Game*>q;
    map<vector<vector<char>>,bool>visted;
    visted[intial->state] = true;
    q.push(intial);
    int n = 0;
    while (!q.empty()){
        Game* node = q.front();
        q.pop();
        if (node->isGoalState()){
            node->printPath();
            ok = true;
            return void(cout  << "DONE");
        }
        vector<Game*>actions = node->valid_Actions();
        for (auto i : actions){
            if (!visted[i->state]) {
                visted[i->state] = true;
                i->level = node->level + 1;
                q.push(i);
                i->parent = node;
            }
        }

    }
}
int getInvCount(vector<vector<char>>& puzzle) {
    int inv_count = 0;
    for (int i = 0; i < 9 - 1; i++) {
        for (int j = i+1; j < 9; j++) {
            // Value '0' is used for empty space
            if (puzzle[i/3][i%3] != '0' && puzzle[j/3][j%3] != '0' && puzzle[i/3][i%3] > puzzle[j/3][j%3]) {
                inv_count++;
            }
        }
    }
    return inv_count;
}
bool isSolvable(vector<vector<char>>& puzzle) {
    int invCount = getInvCount(puzzle);
    return (invCount % 2 == 0);
}
signed main() {
    HOKSHA();
    int t = 1;
    // cin >> t;
    while (t--) {
            cout << "Enter the 8 puzzel and make the empty cell * " << endl;
            Game* intial = new Game();
           intial->setIntialState();
           ok  = isSolvable(intial->state);
           if (ok)  BFS_8_solver(intial);
           else
             cout << "the puzzel is not solvable" << endl;



    }
    return 0;
}
