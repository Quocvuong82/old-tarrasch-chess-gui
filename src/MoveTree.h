/****************************************************************************
 * Representation of a game's tree of variations
 *  Author:  Bill Forster
 *  Licence: See licencing information in ChessPosition.cpp
 *  Copyright 2010, Triple Happy Ltd.  All rights reserved.
 ****************************************************************************/

#ifndef MOVE_TREE_H
#define MOVE_TREE_H
#include <string>
#include <vector>
#include "ChessRules.h"

struct GAME_MOVE
{
    thc::Move move;
    int   human_millisecs_time;
    int   engine_millisecs_time;
    bool  flag_ingame;
    bool  white_clock_visible;
    bool  black_clock_visible;
    bool  human_is_white;
    std::string pre_comment;
    std::string comment;
    char nag_value1;
    char nag_value2;
    GAME_MOVE() { nag_value1=0; nag_value1=0; flag_ingame=0; white_clock_visible=false; black_clock_visible=false;
                  human_is_white=false; human_millisecs_time=0; engine_millisecs_time=0; }
};

class MoveTree
{

public:
    thc::ChessPosition *root;
    GAME_MOVE   game_move;
    std::vector<std::vector<MoveTree>> variations;
    MoveTree() { root=NULL; variations.clear(); }
    void Init( thc::ChessPosition &start_position )
    {
        root = &start_position;
        variations.clear();    // start the root variation (there will be only one)
        std::vector<MoveTree> variation;
        variations.push_back(variation);
    }
    void Dump( std::string& str );

    // Promote the entire variation containing a child node
    //  Return ptr to child node in its new position in the promoted variation
    MoveTree *Promote( MoveTree *child );

    // Demote the entire variation containing a child node
    //  Return ptr to child node in its new position in the demoted variation
    MoveTree *Demote( MoveTree *child );

    // Delete the rest of a variation
    void DeleteRestOfVariation( MoveTree *child );

    // Delete variation
    void DeleteVariation( MoveTree *child );

    // Given a child node, find its parent
    MoveTree *Parent( MoveTree *child, thc::ChessRules &cr_out, int &ivar, int &imove );
    MoveTree *ParentCrawler( int& level, bool& first, MoveTree *child, thc::ChessRules &cr, thc::ChessRules &cr_out, int &ivar, int &imove );
};

typedef std::vector<MoveTree> VARIATION;

#endif //MOVE_TREE_H
