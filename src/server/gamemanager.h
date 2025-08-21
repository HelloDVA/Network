
#include <memory>
#include <unordered_map>
#include <queue>
#include <mutex>

#include "game.h"

class WebSocketSession;

class GameManager {
    public:
        static std::queue<std::shared_ptr<WebSocketSession>> match_queue;

        static GameManager& Instance();
        void JoinMatch(std::shared_ptr<WebSocketSession> player);
        void HandleMove(int room_id, std::shared_ptr<WebSocketSession> player, int x, int y);

    private:
        GameManager() {}
        GameManager(const GameManager&) = delete;
        GameManager& operator=(const GameManager&) = delete;

        struct Room {
            std::shared_ptr<WebSocketSession> player1;
            std::shared_ptr<WebSocketSession> player2;
            Game game;
        };
        std::unordered_map<int, Room> rooms_;

        static std::mutex mutex_;
        static int roomid;
};
