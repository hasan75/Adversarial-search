#include <bits/stdc++.h>

using namespace std;

#define N 4
#define CPU_TURN 'X'
#define USER_TURN 'O'
#define WIN 500
#define LOSS -500
#define DRAW 0
#define EMPTY_CELL ' '

map<pair<vector<vector<char>>,int>,int>Map;


void board_print(vector<vector<char>>board)
{
    cout << endl;
    for(int i = 0 ; i < N; i++){
        for(int j = 0; j < N; j++){
            if(j == N-1){
                cout << board[i][j] << endl;
            }
            else{
                cout << board[i][j] << " | ";
            }
        }
        cout << "-------------" << endl;
    }

    cout << endl;

}

int cur_state_value(vector<vector<char>>board)
{
    for (int row = 0; row<N; row++){
        if (board[row][0]==board[row][1] && board[row][1]==board[row][2] && board[row][3] == board[row][2] ){
            if (board[row][0] == CPU_TURN)
                return WIN;
            else if(board[row][0] == USER_TURN)
                return LOSS;

        }
    }


    for (int col = 0; col<N; col++)
    {
        if (board[0][col]==board[1][col] && board[1][col]==board[2][col] && board[2][col]==board[3][col]){
            if (board[0][col] == CPU_TURN)
                return WIN;
            else if(board[0][col] == USER_TURN)
                return LOSS;


        }
    }



    if (board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[2][2]==board[3][3]){
        if (board[0][0] == CPU_TURN)
            return WIN;
        else if(board[0][0] == USER_TURN)
            return LOSS;


    }

    if (board[0][3]==board[1][2] && board[1][2]==board[2][1] && board[2][1]==board[3][0]){
        if (board[0][3] == CPU_TURN)
            return WIN;
        else if(board[0][3] == USER_TURN)
            return LOSS;


    }

    return DRAW;



    return DRAW;


}

bool is_board_filled(vector<vector<char>>board)
{


    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(board[i][j] == EMPTY_CELL){
                return false;
            }
        }
    }

    return true;
}

vector<pair<int,int>>get_moves(vector<vector<char>>board)
{
    vector<pair<int,int>>moves;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(board[i][j] == EMPTY_CELL){
                moves.push_back({i,j});
            }
        }
    }

    return moves;
}

int run_tic_tac_toe(vector<vector<char>>board,int depth,bool cpu_turn,int alpha,int beta)
{
    int cur_val = cur_state_value(board);

    ///base cases
    if(cur_val == WIN) return WIN - depth;
    if(cur_val == LOSS) return LOSS + depth;
    if(is_board_filled(board)) return DRAW;

    if(Map.find({board,cpu_turn}) != Map.end()) return Map[{board,cpu_turn}];

    vector<pair<int,int>>moves = get_moves(board);
    if(cpu_turn){
        int best_score = LOSS;

        for(int ind = 0; ind  < moves.size(); ind++){
            pair<int,int>cur_move = moves[ind];
            board[cur_move.first][cur_move.second] = CPU_TURN;
            best_score = max(best_score,run_tic_tac_toe(board,depth+1,!cpu_turn,alpha,beta));
            board[cur_move.first][cur_move.second] = EMPTY_CELL;
            alpha = max(alpha,best_score);
            if(beta <= alpha){
                break;
            }

        }
        Map[{board,cpu_turn}] = best_score;
        return best_score;
    }
    else{
        int best_score = WIN;

        for(int ind = 0; ind  < moves.size(); ind++){
            pair<int,int>cur_move = moves[ind];
            board[cur_move.first][cur_move.second] = USER_TURN;
            best_score = min(best_score,run_tic_tac_toe(board,depth+1,!cpu_turn,alpha,beta));
            board[cur_move.first][cur_move.second] = EMPTY_CELL;
            beta = min(beta,best_score);
            if(beta <= alpha){
                break;
            }

        }
        Map[{board,cpu_turn}] = best_score;
        return best_score;
    }

}

bool is_winning_state(vector<vector<char>>board,char turn)
{
    for (int row = 0; row<N; row++){
        if (board[row][0]==board[row][1] && board[row][1]==board[row][2] && board[row][3] == board[row][2] ){
            if (board[row][0] == turn)
                return true;


        }
    }


    for (int col = 0; col<N; col++)
    {
        if (board[0][col]==board[1][col] && board[1][col]==board[2][col] && board[2][col]==board[3][col]){
            if (board[0][col] == turn)
                return true;


        }
    }



    if (board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[2][2]==board[3][3]){
        if (board[0][0] == turn)
            return true;


    }

    if (board[0][3]==board[1][2] && board[1][2]==board[2][1] && board[2][1]==board[3][0]){
        if (board[0][3] == turn)
            return true;


    }

    return false;
}

pair<int,int>find_best_move(vector<vector<char>>board)
{
    int bestScore = -10000;
    pair<int,int>bestMove = {-1,-1};
    vector<pair<int,int>>moves = get_moves(board);

    for(int ind = 0; ind  < moves.size(); ind++){
        pair<int,int>cur_move = moves[ind];
        board[cur_move.first][cur_move.second] = CPU_TURN;
        int curScore = run_tic_tac_toe(board, 0, false,LOSS,WIN);
        board[cur_move.first][cur_move.second] = EMPTY_CELL;
        if(curScore > bestScore){
            bestScore = curScore;
            bestMove = {cur_move.first,cur_move.second};
        }
    }

    return bestMove;

}


char get_opposite_turn(char turn)
{
    if(turn == CPU_TURN){
        return USER_TURN;
    }
    else{
        return CPU_TURN;
    }
}




bool valid_move_check(vector<vector<char>>board,int row,int col)
{
    if(row < 0 || row >= N || col < 0 || col >= N || board[row][col] != EMPTY_CELL) return false;

    return true;
}

int main()
{
    vector<vector<char>>board(N,vector<char>(N));

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            board[i][j] = EMPTY_CELL;
        }
    }


    //board_print(board);

    //pair<int,int>best = find_best_move(board);
    //cout << "yes "<< best.first << " " << best.second <<  endl;



    char cur_turn ;


    /*cout << "CPU TURN" << endl;


    int row = rand() % N;
    int col = rand() % N;
    board[row][col] = CPU_TURN;
    cur_turn = USER_TURN;
    board_print(board);*/

    cout << "CHOOSE 1 FOR YOUR FIRST TURN OR 2 FOR CPU FIRST TURN" << endl;
    int which;
    cin >> which;

    if(which == 1){
        cur_turn = USER_TURN;
    }
    else{
        cout << "CPU TURN" << endl;
        cur_turn = CPU_TURN;
        int row = rand() % N;
        int col = rand() % N;
        board[row][col] = CPU_TURN;
        board_print(board);
        cur_turn = USER_TURN;

    }


    while(true){

        if(cur_turn == USER_TURN){
            int row,col;
            cout << "YOUR TURN" << endl;
            cout << "CHOOSE A COORDINATE" << endl;
            cout << "SELECT ROW:\n";
            cin >> row;
            cout << "SELECT COL:\n";
            cin >> col;
            if(valid_move_check(board,row,col) == false){
                cout << "CHOSEN COORDINATE IS NOT VALID!!! TRY ANOTHER ONE :(" << endl;
                continue;
            }
            else{
                board[row][col] = USER_TURN;
                board_print(board);
                cur_turn = get_opposite_turn(cur_turn);
            }
        }
        else{
            cout << "CPU TURN" << endl;
            pair<int,int>best = find_best_move(board);
            board[best.first][best.second] = CPU_TURN;
            board_print(board);
            cur_turn = get_opposite_turn(cur_turn);
        }

        if(is_winning_state(board,CPU_TURN)){
            cout << "CPU WINS!!!" << endl;
            board_print(board);
            break;
        }

        if(is_winning_state(board,USER_TURN)){
            cout << "YOU WIN!!!" << endl;
            board_print(board);
            break;
        }

        if(is_board_filled(board)){
            cout << "ENDS WITH DRAW :(" << endl;
            board_print(board);
            break;
        }
    }

    return 0;


}
