
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

#include <cmath>
#include <memory>
#include <mutex>
#include <queue>

#include "gamemanager.h"
#include "websocket.h"

using json = nlohmann::json;

std::queue<std::shared_ptr<WebSocketSession>> GameManager::match_queue;
int GameManager::roomid = 1;
std::mutex GameManager::mutex_;

GameManager& GameManager::Instance() {
    static GameManager game_manager;
    return game_manager;
}

void GameManager::JoinMatch(std::shared_ptr<WebSocketSession> player) {
    // match_queue needs lock before use
    // empty add new player
    // two players in queue, start a game
    if(match_queue.empty()) {
        std::lock_guard<std::mutex> lock(mutex_);
        match_queue.emplace(player);
    } else {
        std::lock_guard<std::mutex> lock(mutex_);
        std::shared_ptr<WebSocketSession> player_o = match_queue.front();
        match_queue.pop();

        // start game player1 is black, player_o is white.
        Game game = Game();
        Room room = {player, player_o, game};
        rooms_[roomid] = room;
        roomid ++;

        json response_json1; 
        response_json1["roomid"] = roomid; 
        response_json1["type"] = "start"; 
        response_json1["role"] = -1; 
        std::string game_response1 = response_json1.dump(); 
        player->DoWrite(game_response1);

        json response_json2; 
        response_json2["roomid"] = roomid; 
        response_json2["type"] = "start"; 
        response_json2["role"] = 1; 
        std::string game_response2 = response_json2.dump(); 
        player->DoWrite(game_response2);
   }
}

void GameManager::HandleMove(int room_id, std::shared_ptr<WebSocketSession> player, int x, int y) {

    auto it = rooms_.find(room_id);
    if (it == rooms_.end())
        return;
    Room& room = it->second;

    int role = 0;
    if (player == room.player1)
        role = -1;
    if (player == room.player2) 
        role = 1;
    
    std::string response_message;
    bool game_state = room.game.MakeMove(x, y, role);
    if (game_state) {
        json response_json; 
        response_json["type"] = "end"; 
        response_json["x"] = x; 
        response_json["y"] = y; 
        response_json["winner"] = role; 
        response_message = response_json.dump(); 
        room.player1->DoWrite(response_message);
        room.player2->DoWrite(response_message);
        return;
    } 

    // brodcast the mvoe message
    json response_json; 
    response_json["type"] = "move"; 
    response_json["x"] = x; 
    response_json["y"] = y; 
    response_json["role"] = role; 
    response_message = response_json.dump(); 
    room.player1->DoWrite(response_message);
    room.player2->DoWrite(response_message);
}
