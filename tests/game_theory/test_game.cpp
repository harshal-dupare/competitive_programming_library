#include <bits/stdc++.h>
#include "../../lib/game_theory/game.hpp"

using namespace std;

void test_game()
{
    game g;
    string fname = "test.gbt";
    g.GAMBIT_input(fname);

    // // uncomment only if need to see game
    // cout<<"game table"<<endl;
    // cout<<g<<endl;

    debug(g.num_players);
    debug(g.num_moves);
    // debug(g.payoffs); // uncomment only if need to see payoffs
    for (int player_id = 0; player_id < g.num_players; player_id++)
    {
        auto Strategies = g.get_strategies(player_id);
        // print sds,wds,vwds for each player
        debug(player_id, Strategies);
    }

    // get all 3 equilibriums
    auto equilibriums = g.get_equilibriums(true, true, true);
    debug(equilibriums);

    // get nash equilibriums as id of startegies for each player size =: (number_nash_eq, num_players)
    // note for vectors debug first outputs  the size of the vector after = : then on next line it outputs the elements of the vector
    auto Nash_equilibriums = g.get_nash_equilibriums();
    debug(Nash_equilibriums);
}

int main()
{
    test_game();
    return 0;
}