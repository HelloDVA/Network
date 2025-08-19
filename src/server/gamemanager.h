
#include <memory>
#include <unordered_map>

#include "game.h"

class WebSocketSession;

class GameManager {
    public:
        static GameManager& Instance();
        void JoinMatch(int room_id, std::shared_ptr<WebSocketSession> player);
        void HandleMove(int room_id, std::shared_ptr<WebSocketSession> player, int x, int y);

    private:
        struct Room {
            std::shared_ptr<WebSocketSession> player1;
            std::shared_ptr<WebSocketSession> player2;
            Game game;
        };
        std::unordered_map<int, Room> rooms_;

};
