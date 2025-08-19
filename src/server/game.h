

class Game {
    public:
        Game();
        bool MakeMove(int x, int y, int player);
        bool CheckWin(int x, int y, int player);
        void Reset();

    private:
        int board[15][15];
};
