package tictactoe;

public class TicTacToe{
    private byte board[][];
    public TicTacToe(){
        board = new byte[3][3];
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                board[i][j] = 0;
            }
        }
    }
    private boolean checkwinner(int player){
        for(int i = 0; i < 3; i++){
            if(board[i][0] == player && board[i][1] == player && board[i][2] == player)return true;
            if(board[0][i] == player && board[1][i] == player && board[2][i] == player)return true;
        }
        if(board[0][0] == player && board[1][1] == player && board[2][2] == player)return true;
        if(board[0][2] == player && board[1][1] == player && board[2][0] == player)return true;
        return false;
    }
    public int place(int player, int row, int column){
        assert(player == 1 || player == 2);
        assert(0 <= row && row <= 2);
        assert(0 <= column && column <= 2);
        if(board[row][column] != 0)return 3;
        board[row][column] = (byte)player;
        if(checkwinner(1))return 1;
        if(checkwinner(2))return 2;
        return 0;
    }
}
