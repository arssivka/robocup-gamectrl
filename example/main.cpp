/// Copyright © 2018 Arseniy Ivin <arssivka@yandex.ru>
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software
/// and associated documentation files (the “Software”), to deal in the Software without
/// restriction, including without limitation the rights to use, copy, modify, merge, publish,
/// distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
/// Software is furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all copies or
/// substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
/// BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
/// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
/// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
/// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
///
/// \autor Arseniy Ivin <arssivka@yandex.ru>
/// \date 3/21/18

#include <iostream>
#include <chrono>
#include <thread>
#include <robocup/game_controller_client_t.h>

int main(int argc, const char** argv) {
    int exit_code = EXIT_FAILURE;
    const int iter_num = 8;
    const int team_number = 1;
    const int player_number = 1;
    const std::chrono::milliseconds sleep_duration{500};

    robocup::game_controller_client_t client(player_number, team_number); // You can set player and team numbers later

    for (int iter = 0; iter < iter_num; ++iter) {
        client.update(); // Receive incoming messages and sent alive signal
        if (!client.is_server_responds()) { // Checking that the server is responding
            exit_code = EXIT_SUCCESS;
            // Print some data from package
            std::cout << "Incoming message data:" << std::endl;
            const auto& data = client.get_game_ctrl_data();
            std::cout << "    Drop in team: " << (int) data.drop_in_team << std::endl;
            std::cout << "    Drop in time: " << (int) data.drop_in_time << std::endl;
            std::cout << "    First half: " << (int) data.first_half << std::endl;
            std::cout << "    Game type: " << (int) data.game_type << std::endl;
            std::cout << "    Kick off team: " << (int) data.kick_off_team << std::endl;
            std::cout << "    Packet number: " << (int) data.packet_number << std::endl;
            std::cout << "    Players per team: " << (int) data.players_per_team << std::endl;
            std::cout << "    Secondary state: " << (int) data.secondary_state << std::endl;
            std::cout << "    Secondary time: " << (int) data.secondary_time << std::endl;
            std::cout << "    Secs remaining: " << (int) data.secs_remaining << std::endl;
            std::cout << "    State: " << (int) data.state << std::endl;
            std::cout << "    Version: " << (int) data.version << std::endl;
            for (const auto& team : data.teams) {
                std::cout << "    Team " << (int) team.team_number << " info:" << std::endl;
                std::cout << "       Penalty shot: " << (int) team.penalty_shot << std::endl;
                std::cout << "       Team colour: " << (int) team.team_colour << std::endl;
                std::cout << "       Score: " << (int) team.score << std::endl;
                std::cout << "       Coach/Penalty: " << (int) team.coach.penalty << std::endl;
                std::cout << "       Coach/Secs till unpenalised: " << (int) team.coach.secs_till_unpenalised << std::endl;
                for (int i = 0; i < MAX_NUM_PLAYERS; ++i) {
                    const auto& player = team.players[i];
                    std::cout << "       Player " << i + 1 << " info: ";
                    std::cout << "penalty: " << (int) player.penalty << ", ";
                    std::cout << "secs till unpenalised: " << (int) player.secs_till_unpenalised << std::endl;
                }
            }
        } else {
            std::cout << "Waiting for a message..." << std::endl;
        }
        std::this_thread::sleep_for(sleep_duration);
    }

    return exit_code;
}