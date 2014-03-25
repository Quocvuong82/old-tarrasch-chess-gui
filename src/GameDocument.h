/****************************************************************************
 * Full game representation
 *  Author:  Bill Forster
 *  Licence: See licencing information in ChessPosition.cpp
 *  Copyright 2010, Triple Happy Ltd.  All rights reserved.
 ****************************************************************************/

#ifndef GAME_DOCUMENT_H
#define GAME_DOCUMENT_H
#include <string>
#include <vector>
#include "ChessRules.h"
#include "MoveTree.h"
#include "NavigationKey.h"
#include "GameView.h"
#include "GameLifecycle.h"

class GameLogic;
class GameDocument
{
public:
    GameDocument( GameLogic *gl );
    GameDocument();
    GameLogic *gl;

    // Allow sorts
    bool operator< (const GameDocument &rhs) const
    {
        return sort_idx < rhs.sort_idx;
    }

    // Copy constructor
    GameDocument( const GameDocument& src )
    {
        *this = src;    // use the assignment operator
    }

    // Assignment operator
    GameDocument& operator=( const GameDocument& src )
    {
        gl = src.gl;

        // Copy all data fields
        game_details_edited = src.game_details_edited;
        modified        = src.modified;
        in_memory       = src.in_memory; 
        current_game    = src.current_game; 
        pgn_handle      = src.pgn_handle;
        sort_idx        = src.sort_idx;
        focus           = false; //src.focus;
        selected        = src.selected;
        game_nbr        = src.game_nbr;
        white           = src.white;          
        black           = src.black;          
        event           = src.event;          
        site            = src.site;           
        date            = src.date;           
        round           = src.round;          
        result          = src.result;         
        eco             = src.eco;            
        white_elo       = src.white_elo;      
        black_elo       = src.black_elo;      
        start_position  = src.start_position;
        master_position = src.master_position;
        tree            = src.tree;           
        fposn1          = src.fposn1;   
        fposn2          = src.fposn2;   
        fposn3          = src.fposn3;   
        moves_txt       = src.moves_txt;      
        gv              = src.gv;

        // Need to rebuild using our copy of the tree to avoid
        //  raw ptrs to the old tree
        tree.root = &start_position;
        Rebuild();
        return( *this );
    }

    void FleshOutDate();
    void FleshOutMoves();
    void Init( const thc::ChessPosition &start_position );
    void ToFileTxtGameDetails( std::string &str );
    void ToFileTxtGameBody( std::string &str );
    bool IsDiff( GameDocument &other );
    bool PgnParse( bool use_semi, int &nbr_converted, const std::string str, thc::ChessRules &cr, VARIATION *pvar, bool use_current_language=false, int imove=-1 );
    MoveTree *MakeMove( GAME_MOVE game_move, bool allow_overwrite );
    MoveTree *KibitzCaptureStart( const char *engine_name, const char *txt, std::vector<thc::Move> &var,
            bool &use_repeat_one_move,
            GAME_MOVE &repeat_one_move     // eg variation = e4,c5 new_variation = Nf3,Nc6 etc.
                                          //  must make new_variation = c5,Nf3,Nc6 etc.
    );
    void KibitzCapture( MoveTree *node, const char *txt, std::vector<thc::Move> &var,
            bool use_repeat_one_move,
            GAME_MOVE &repeat_one_move      // eg variation = e4,c5 new_variation = Nf3,Nc6 etc.
                                            //  must make new_variation = c5,Nf3,Nc6 etc.
    );
    void Promote();
    void Demote();
    bool PromotePaste( std::string &str );
    void PromoteToVariation( unsigned long offset_within_comment=0 );
    void PromoteRestToVariation();
    void DemoteToComment();
    void Rebuild() { gv.Build( result, &tree, this->start_position ); }
    void DeleteRestOfVariation();
    void RedisplayRequest( MoveTree *found );
    void Redisplay( unsigned long pos );

    // Get a picture of the game, various recipes
    //

    // Where are we in the document
    unsigned long GetInsertionPoint();
    void SetInsertionPoint( unsigned long pos );

    // A start position, a vector of moves, leading to a final position    
    void GetSummary( thc::ChessPosition &start_position, std::vector<GAME_MOVE> &game_moves, thc::ChessPosition &pos );

    // The current position, title text for the last move played eg "Position after 23...Nxd5"
    //  Return ptr to the last move played,  NULL if no last move OR if nbr_half_moves_lag
    GAME_MOVE *GetSummary( thc::ChessRules &cr, std::string &title_txt, int nbr_half_moves_lag=0 );

    // The current position, move text for the last move played eg "23...Nxd5"
    //  Return ptr to the last move played,  NULL if no last move OR if nbr_half_moves_lag
    GAME_MOVE *GetSummaryMove( thc::ChessRules &cr, std::string &move_txt );

    //  We should define and use some simple recipes like this
    MoveTree *GetSummary();

    // Are we at the end of the main line (will a new game be the main game, or not)
    bool AtEndOfMainLine();

    // Are we currently in the main game, or not
    bool AreWeInMain();

    bool IsEmpty() { return !HaveMoves(); }
    bool HaveMoves();
    bool IsAtEnd();
 
    // Pass through to GameView
    void Debug()
        {  gv.Debug(); }
    void Display( unsigned long pos )
        {  gv.Display(pos); }
    bool IsInComment( wxRichTextCtrl *ctrl )
        {  return gv.IsInComment(ctrl); }
    bool CommentEdit( wxRichTextCtrl *ctrl, long keycode )
        {   std::string txt_to_insert; 
            gv.comment_edited = false;
            bool done = gv.CommentEdit(ctrl,txt_to_insert,keycode);
            return done;
        }
    bool CommentEdit( wxRichTextCtrl *ctrl, std::string &txt_to_insert )
        {
            gv.comment_edited = false;
            bool done = gv.CommentEdit(ctrl,txt_to_insert);
            return done;
        }
    bool IsSelectionInComment( wxRichTextCtrl *ctrl )
        {  return gv.IsSelectionInComment(ctrl); }
    void DeleteSelection( wxRichTextCtrl *ctrl )
        {  return gv.DeleteSelection(ctrl); }

    unsigned long NavigationKey( unsigned long pos, NAVIGATION_KEY nk )
        {  return gv.NavigationKey(pos,nk); }
    MoveTree *Locate( unsigned long pos, thc::ChessRules &cr, std::string &title, bool &at_move0 )
        {   cr = start_position;
            return gv.Locate( pos, cr, title, at_move0 ); }
    MoveTree *Locate( unsigned long pos, thc::ChessRules &cr, std::string &title )
        {   cr = start_position;
            bool at_move0; return gv.Locate( pos, cr, title, at_move0 );   }
    MoveTree *Locate( unsigned long pos, thc::ChessRules &cr )
        {   cr = start_position;
            std::string title; bool at_move0; return gv.Locate( pos, cr, title, at_move0 ); }


    // Data
    bool        game_details_edited;
    bool        modified;
    bool        in_memory;
    bool        current_game;
    int         pgn_handle;
    bool        selected;
    bool        focus;
    int         sort_idx;
    int         game_nbr;
    MoveTree    *gbl_plast_move;

    std::string white;          // "White"
    std::string black;          // "Black"
    std::string event;          // "Event"
    std::string site;           // "Site"
    std::string date;           // "Date"
    std::string round;          // "Round"
    std::string result;         // "Result"
    std::string eco;            // "ECO"
    std::string white_elo;      // "WhiteElo"
    std::string black_elo;      // "BlackElo"
    thc::ChessPosition start_position;  // the start position
    thc::ChessRules master_position;    // the current position
    MoveTree  tree;                     // the moves
    unsigned long fposn1;       // offset of tags in .pgn file
    unsigned long fposn2;       // offset where moves are in .pgn file
    unsigned long fposn3;       // offset where moves end in .pgn file
    std::string moves_txt;      // "1.e4 e5 2.Nf3.."
    GameView gv;
};

#endif //GAME_DOCUMENT_H
