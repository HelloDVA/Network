

class Game {
    public:
        Game();
        bool MakeMove(int x, int y, int player);
        bool CheckWin(int x, int y, int player);
        void Reset();

    private:
		static const int directions_[4][2];

        int board_[15][15];
};
