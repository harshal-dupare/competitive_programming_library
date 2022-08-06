#pragma once

#include <vector>
#include <iostream>
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...)
#endif

// README
// I have tried to keep the variables name verbose to avoic commenting too much
// I will explain the ideas behind the code in comments
// ignore the `debug` lines which are commented, they were used for debugging
// didn't removed them as they specify the completion of some major steps-
// -needed to check the correctness of algorithm

using namespace std;
typedef int I;
typedef double R;
// mark it false if you are sure that no exception may happen
// also mark it false when you are testing for performance
constexpr bool DO_ASSERT_CHECK = true;

// splits string by the character `c` ignores empty splits
vector<string> split_by(string &s, char c)
{
    vector<string> vs;
    string tp;
    for (int i = 0; i < (int)s.size(); i++)
    {
        if (s[i] == c)
        {
            if (tp.size() > 0)
            {
                vs.push_back(tp);
                tp.clear();
            }
        }
        else
        {
            tp.push_back(s[i]);
        }
    }

    if (tp.size() > 0)
    {
        vs.push_back(tp);
        tp.clear();
    }
    return vs;
}

// gets cartesian product of elements in `v`'s rows
vector<vector<I>> cartesian_product(const vector<vector<I>> &v)
{
    vector<vector<I>> prod;
    vector<I> dim(v.size());
    for (I i = 0; i < v.size(); i++)
    {
        dim[i] = v[i].size();
        if (DO_ASSERT_CHECK)
            assert(dim[i] > (I)0);
    }
    // ids to iterate over ids of element from cartition product
    std::vector<I> ids(dim.size(), 0);
    I cr = 0;
    while (cr == 0)
    {
        // convert ids vector to cartition product
        vector<I> temp;
        for (I i = 0; i < dim.size(); i++)
        {
            temp.push_back(v[i][ids[i]]);
        }
        // push the cartition product
        prod.push_back(temp);

        // get next cartition product id vector
        cr = 1;
        I id = 0;
        while (id < (I)dim.size() && cr > 0)
        {
            ids[id] += cr;
            cr = ids[id] / dim[id];
            ids[id] %= dim[id];
            id++;
        }
    }
    return prod;
}

class game
{
public:
    I num_players;
    vector<I> num_moves;
    vector<I> _base;
    vector<R> payoffs;

    game() : num_players(0){};
    void GAMBIT_input(const string fpath)
    {
        // reads games from files with gambit format
        // see examlple files to get more idea about the format
        ifstream infile;
        infile.open(fpath.c_str());
        string s;
        bool got_num_players = false, got_num_actions = false, got_payoffs = false;
        string Players = "Players:";
        string Actions = "Actions:";
        while (getline(infile, s))
        {
            // as per the format we must get number of players and their number of mover before the payoffs
            if (!got_num_players && Players == s.substr(0, min(Players.size(), s.size())))
            {
                // read number of players
                s = s.substr(Players.size(), s.size());
                this->num_players = (I)stoi(s);
                if(DO_ASSERT_CHECK) assert(this->num_players>(I)0);
                got_num_players = true;
            }
            if (got_num_players && !got_num_actions && Actions == s.substr(0, min(Actions.size(), s.size())))
            {
                s = s.substr(Actions.size(), s.size());
                vector<string> as = split_by(s, ' '); // read number of actions for each player
                if (DO_ASSERT_CHECK)
                    assert(this->num_players == (I)as.size()); // checking if evyer player is assigned a move or not

                for (int i = 0; i < (int)as.size(); i++)
                    this->num_moves.push_back(stoi(as[i]));
                this->_base.assign(this->num_moves.size(), 1);
                for (int i = 1; i < (int)this->_base.size(); i++)
                {
                    this->_base[i] = this->num_moves[i - 1] * this->_base[i - 1];
                }
                got_num_actions = true;
            }
            if (got_num_actions && got_num_players && !got_payoffs && 0 == (int)s.size())
            {
                // read the payoffs
                getline(infile, s); // assuming that the line after the empty line is the line with all payoff values
                vector<string> sps = split_by(s, ' ');
                I tot_states = this->num_players; // calculate the totoal states times the number os payoffs in each state
                for (auto m : this->num_moves)
                    tot_states *= m;
                if (DO_ASSERT_CHECK)
                    assert(tot_states == (I)sps.size()); // checking if totoal sizes match

                // fill the payoffs
                this->payoffs.assign(tot_states, R());
                
                I loc = 0;
                // we incriment the loc by num_players ad that many have been read at each state
                // till loc is less than total states
                while (loc<tot_states)
                {
                    // convert string to payoff values
                    for (I i = 0; i < this->num_players; i++)
                    {
                        this->payoffs[i + loc] = stod(sps[i + loc]); // converts string to double
                    }

                    // get next loc
                    loc+=this->num_players;
                }
                got_payoffs = true;
            }
        }
        infile.close();
    }
    R get_payoff(const vector<I> &id, I of_player)
    {
        // checking if valid id or not
        if (DO_ASSERT_CHECK)
        {
            assert(id.size() == this->_base.size());
            for (I i = 0; i < this->num_players; i++)
            {
                assert(id[i] >= 0 && id[i] < this->num_moves[i]);
            }
        }
        I loc = 0;
        for (I i = 0; i < (I)this->_base.size(); i++)
        {
            loc += this->_base[i] * id[i];
        }
        loc *= this->num_players;
        loc += of_player;
        return this->payoffs[loc];
    }
    I get_locid(const vector<I> &id, I of_player)
    {
        // checking if valid id or not
        if (DO_ASSERT_CHECK)
        {
            assert(id.size() == this->_base.size());
            for (I i = 0; i < this->num_players; i++)
            {
                assert(id[i] >= 0 && id[i] < this->num_moves[i]);
            }
        }
        I loc = 0;
        for (I i = 0; i < (I)this->_base.size(); i++)
        {
            loc += this->_base[i] * id[i];
        }
        loc *= this->num_players;
        loc += of_player;
        return loc;
    }
    vector<I> get_ids_from_stateloc(I stateloc)
    {
        // translates state loc (location of a set of moves of all players) to id's
        vector<I> ids(this->num_players, 0);
        I i = 0;
        while (stateloc > 0)
        {
            ids[i] = stateloc % this->num_moves[i];
            stateloc /= this->num_moves[i];
            i++;
        }
        return ids;
    }

    // worst case when all stratgeies are sds,wds,vwds i.e. O(states) = O(|states_exclusing_this_players|*num_moves_of_this_player) worstcase complexity
    map<string, vector<I>> get_strategies(const I of_player, bool SDS = true, bool WDS = true, bool VWDS = true)
    {
        //  say we need to find startegies(any of sds,wds,vwds) for player i s*_i
        // so we will go through all the s_{-i} and then wrt each such s_{-i} check which startegies s_i are non-dominated
        // then we have to process the non-dominated sterategies saperately for the cases of sds,wds,vwds and update the candidate staratgey set
        // we assume initially all startegies are in the candidate set
        map<string, vector<I>> Ss;
        vector<I> stratids;

        for (I i = 0; i < this->num_moves[of_player]; i++)
        {
            stratids.push_back(i);
        }
        // initally assume all the moves are in the sets
        if (SDS)
            Ss["SDS"] = stratids;
        if (WDS)
            Ss["WDS"] = stratids;
        if (VWDS)
            Ss["VWDS"] = stratids;
        bool SDS_there = true, WDS_there = true, VWDS_there = true;

        // calculate total number of state excluding i't player
        I tot_states = 1;
        for (I i = 0; i < this->num_players; i++)
        {
            tot_states *= this->num_moves[i];
        }
        // debug(tot_states);

        I base_loc =  0;
        // check next state only if there is possibiity of finding some startegy set
        while (base_loc < tot_states && ((SDS & SDS_there) || (WDS & WDS_there) || (VWDS & VWDS_there)))
        {
            // get the base_location in payoff
            I tbase_loc=this->num_players*base_loc+of_player;
            // debug(base_loc,tbase_loc);

            // get the set of non-dominant startegies if all other players pay this set of startegy
            // assume initially its `0` strategy
            vector<I> maxpayoff_moves = {0};
            R maxpayoffis = this->payoffs[tbase_loc];

            // debug(tbase_loc, maxpayoff_moves, maxpayoffis);

            for (I i = 1; i < this->num_moves[of_player]; i++)
            {
                // get location for i'th strategy
                tbase_loc += this->num_players * this->_base[of_player];

                // update the non-dominanted set
                if (this->payoffs[tbase_loc] > maxpayoffis)
                {
                    maxpayoffis = this->payoffs[tbase_loc];
                    maxpayoff_moves.clear();
                    maxpayoff_moves = {i};
                }
                else if (this->payoffs[tbase_loc] == maxpayoffis)
                {
                    maxpayoff_moves.push_back(i);
                }
                // debug(tbase_loc, maxpayoff_moves, maxpayoffis);
            }

            // debug(maxpayoff_moves, maxpayoffis);
            // debug(Ss);
            // debug(maxpayoff_moves);
            // update the candidate set of startegies for SDS, WDS, VWDS
            if (VWDS && VWDS_there)
            {
                stratids.clear();
                auto tmp = set_intersection(Ss["VWDS"].begin(), Ss["VWDS"].end(), maxpayoff_moves.begin(), maxpayoff_moves.end(), std::inserter(stratids, stratids.begin()));
                if (stratids.empty())
                {
                    VWDS_there = false;
                }
                Ss["VWDS"] = stratids;
                // debug(Ss["VWDS"]);
            }
            if (WDS && WDS_there)
            {
                stratids.clear();
                auto tmp = set_intersection(Ss["WDS"].begin(), Ss["WDS"].end(), maxpayoff_moves.begin(), maxpayoff_moves.end(), std::inserter(stratids, stratids.begin()));
                if (stratids.empty())
                {
                    WDS_there = false;
                }
                Ss["WDS"] = stratids;
                // debug(Ss["WDS"]);
            }
            if (SDS && SDS_there)
            {
                if ((int)maxpayoff_moves.size() != 1)
                {
                    // if size of dominating set is not 1 i.e. there is a startegy which performs as good as some other stargey in this state
                    // then there is no SDS
                    SDS_there = false;
                    Ss["SDS"].clear();
                }
                else
                {
                    // if size is 1 then it must match with the previous candidate SDS
                    // so taking intersection and checking if size is 1
                    // note it can also be checked by .begin() but that wont work for initial condition i.e. when we assume all strategies in SDS set
                    // so intersection is required (atleast initally) and it wont hurt complexity after that as it will have only 1 element in next steps
                    stratids.clear();
                    auto tmp = set_intersection(Ss["SDS"].begin(), Ss["SDS"].end(), maxpayoff_moves.begin(), maxpayoff_moves.end(), std::inserter(stratids, stratids.begin()));
                    if (stratids.empty())
                    {
                        SDS_there = false;
                        Ss["SDS"].clear();
                    }
                    else
                    {
                        Ss["SDS"] = stratids;
                    }
                }
                // debug(Ss["WDS"]);
            }
            
            /*
            1 2 6 12
            2 3 2  4  -> 2 3 4
            1 2 0* 1  -> 1 2 1 -> 17
            0 0 1* 1  -> 0 0 1 -> 12 , 18
            0 0 0* 2  -> 0 0 1 -> 24

            2  2 -> 
            1  0* -> 1 
            0  1* -> 2
            1  1* -> 3
            0  2* -> 4
            */
            // go to the next location
            base_loc+=1;
            if(base_loc%this->_base[of_player]==(I)0)
            {
                // debug(base_loc,this->_base[of_player]);
                if(of_player<this->num_players-1)
                {
                    base_loc+=this->_base[of_player+1]-this->_base[of_player];
                }
                else
                {
                    base_loc+=tot_states-this->_base[of_player];
                }
            }
        }

        // is there is more than 1 at the end of visiting all the states then 
        // there is 1 strategy which it doen't dominate is any of the s_{-i}
        // so clear the vector and mark false
        if (WDS && WDS_there)
        {
            if((int)Ss["WDS"].size()>1)
            {
                Ss["WDS"].clear();
                WDS_there=false;
            }
        }
        // debug(Ss["WDS"]);
        return Ss;
    }
    // worst case when all states are sds,wds,vwds i.e. O(|payoffs|) = O(states*num_players) worstcase complexity
    map<string, vector<vector<I>>> get_equilibriums(bool SDS = true, bool WDS = true, bool VWDS = true)
    {
        // idea is to get all the sds,wds,vwds for each of the players
        // then take the  cartesian product of those startegies for all players
        map<string, vector<vector<I>>> Es;
        vector<vector<I>> VcSDS, VcWDS, VcVWDS;
        bool SDS_there = true, WDS_there = true, VWDS_there = true;
        if (SDS)
            Es["SDS"] = vector<vector<I>>();
        if (WDS)
            Es["WDS"] = vector<vector<I>>();
        if (VWDS)
            Es["VWDS"] = vector<vector<I>>();
        for (I i = 0; i < this->num_players; i++)
        {
            // only compute those strategies for i'th player
            // if everyone before i'th player has non-empty set of those stretegy
            map<string, vector<I>> Ssi = this->get_strategies(i, SDS & SDS_there, WDS & WDS_there, VWDS & VWDS_there);
            // debug(i);
            // debug(Ssi);
            if (SDS && SDS_there)
            {
                // if no such strategy exists mark it false
                if (Ssi["SDS"].empty())
                {
                    SDS_there = false;
                    VcSDS.clear();
                }
                else
                {
                    VcSDS.push_back(vector<I>(Ssi["SDS"].begin(), Ssi["SDS"].end()));
                }
            }
            if (WDS && WDS_there)
            {
                if (Ssi["WDS"].empty())
                {
                    WDS_there = false;
                    VcWDS.clear();
                }
                else
                {
                    VcWDS.push_back(vector<I>(Ssi["WDS"].begin(), Ssi["WDS"].end()));
                }
            }
            if (VWDS && VWDS_there)
            {
                if (Ssi["VWDS"].empty())
                {
                    VWDS_there = false;
                    VcVWDS.clear();
                }
                else
                {
                    VcVWDS.push_back(vector<I>(Ssi["VWDS"].begin(), Ssi["VWDS"].end()));
                }
            }
        }

        if (SDS && SDS_there)
        {
            Es["SDS"] = cartesian_product(VcSDS);
        }
        if (WDS && WDS_there)
        {
            Es["WDS"] = cartesian_product(VcWDS);
        }
        if (VWDS && VWDS_there)
        {
            Es["VWDS"] = cartesian_product(VcVWDS);
        }
        return Es;
    }
    // worst case when all states are neq i.e. O(|payoffs|) = O(states*num_players) worstcase complexity
    vector<vector<I>> get_nash_equilibriums()
    {
        // we will use memoization to keep track of which states each player visited and if they can be neq(nash equilibria) or not
        // idea is to visit state one by one and check wrt each player if it can be neq or not
        // if any player marks it false then next players wont check that state
        // also no player will check same opponents' strategy set twice i.e. if we have checked (s_i,s_{-i}) then we wont check for (s_j,s_{-i})
        // as we have already checked if it can be in non-dominated set or not and based of that updated its neq status
        vector<vector<I>> Neq;
        I states = ((I)this->payoffs.size()) / (this->num_players);                           // number of states of the game
        vector<bool> can_be_neq(states, true);                                                // true if this state can be Neq else false
        vector<vector<bool>> already_checked(this->num_players, vector<bool>(states, false)); // already_checked[i][l] : true if i'th players already checked for l state

        I loc = 0;
        while (loc<states)
        {
            // debug(loc);
            // debug(can_be_neq);
            // debug(already_checked);

            // process if it can be Nash Eq
            if (can_be_neq[loc])
            {
                vector<I> ids = this->get_ids_from_stateloc(loc);
                // check for all players if it can be a Neq for it
                for (I i = 0; i < this->num_players; i++)
                {
                    // the strategy at this loc was already checked and it is in non-dominated set for i'th player
                    // so no need to check twice
                    if (already_checked[i][loc])
                        continue;

                    // if its not already checked

                    // go through all the moves of this player and check in all those states to get non-dominant sets
                    // if the strategy id[i] is in that set then this can be Neq wrt i'th player
                    I tloc = loc - this->_base[i] * ids[i]; // loc after making contribution from i'th player to 0
                    R maxpayoff = this->payoffs[tloc * this->num_players + i];
                    vector<I> maxpayoff_lst = {(I)0}, maxtloc_lst = {tloc};
                    already_checked[i][tloc] = true; // mark move 0 with state tloc as checked
                    for (I j = 0; j < this->num_moves[i] - 1; j++)
                    {
                        tloc += this->_base[i];
                        R npayoff = this->payoffs[tloc * this->num_players + i];
                        already_checked[i][tloc] = true; // mark this state for i'th player as checked
                        if (npayoff > maxpayoff)
                        {
                            for (auto mvloc : maxtloc_lst)
                            {
                                can_be_neq[mvloc] = false;
                            }
                            maxpayoff = npayoff;
                            maxpayoff_lst = {j + (I)1};
                            maxtloc_lst = {tloc};
                        }
                        else if (npayoff == maxpayoff)
                        {
                            maxpayoff_lst.push_back(j + (I)1);
                            maxtloc_lst.push_back(tloc);
                        }
                        else
                        {
                            can_be_neq[tloc] = false;
                        }
                    }
                    // if this state cannot be neq wrt this player so break as we dont need to check wrt next players
                    if (!can_be_neq[loc])
                    {
                        break;
                    }
                }
            }

            // get the next loc
            loc++;
        }

        // go through all states and if it can be neq then add it to the answer
        for (I i = 0; i < (I)can_be_neq.size(); i++)
        {
            if (!can_be_neq[i])
                continue;
            Neq.push_back(this->get_ids_from_stateloc(i));
        }
        return Neq;
    }

    friend ostream &operator<<(ostream &os, const game &g)
    {
        vector<I> ids(g.num_moves.size(), 0);
        I cr = 0;
        while (cr == 0)
        {
            I loc = 0;
            for (I i = 0; i < (I)g.num_moves.size(); i++)
            {
                loc += g._base[i] * ids[i];
            }
            loc *= g.num_players;

            os << "[";
            for (I i = 0; i < g.num_players; i++)
            {
                os << g.payoffs[loc + i] << " ";
            }
            os << "]";

            cr = 1;
            I id = ((I)g.num_moves.size()) - 1;
            while (id >= 0 && cr > 0)
            {
                ids[id] += cr;
                cr = ids[id] / g.num_moves[id];
                ids[id] %= g.num_moves[id];
                id--;
                if (cr > 0)
                {
                    os << "\n";
                }
            }
        }
        return os;
    }
};
