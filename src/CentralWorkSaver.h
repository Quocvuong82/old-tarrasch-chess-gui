/****************************************************************************
 * Central Work Saver  This object tracks the top level state, e.g
 *                     whether we are editing a file or not, for the purpose
 *                     of saving our work.
 *                     Both prompted saves (eg when user opens a new file) and
 *                     unprompted saves (on File Save or SaveAs) are
 *                     implemented
 *  Author:  Bill Forster
 *  Licence: See licencing information in ChessPosition.cpp
 *  Copyright 2010, Triple Happy Ltd.  All rights reserved.
 ****************************************************************************/
#ifndef TOP_LEVEL_CONTEXT_H
#define TOP_LEVEL_CONTEXT_H
#include "Undo.h"
#include "GameDocument.h"
#include "GamesCache.h"

class CentralWorkSaver
{    
public:
    CentralWorkSaver() {}
    void Init( Undo *undo, GameDocument *gd, GamesCache *gc, GamesCache *gc_clipboard ) {this->undo=undo, this->gd=gd; this->gc=gc; this->gc_clipboard=gc_clipboard;}
    void SetTitle();
    bool FileNew();
    bool FileOpen();
    bool FileSave();
    bool FileSaveAs();
    bool GameNew();
    bool PositionNew();
    bool Exit();

private:
    bool TestFileExists();
    bool TestFileModified();
    bool TestGameModified();
    bool TestGameInFile();
    void AddGameToFile();
    void PutBackDocument();

    enum FILE_MODE
    {
        FILE_EXISTS_GAME_MODIFIED,
        FILE_EXISTS_GAME_UNCHANGED,
        FILE_EXISTS_GAME_NEW,
        FILE_NEW_GAME_NEW,
    };

    void Save( bool prompt, bool save_as );

    // Prompt user whether to save game, allow game detail editing, returns wxYES or wxNO or wxCANCEL
    int SaveGamePrompt( bool prompt, FILE_MODE fm, bool save_as );

    // Save file
    void SaveFile( bool prompt, FILE_MODE fm, bool save_as );

    Undo         *undo;
    GameDocument *gd;
    GamesCache   *gc;
    GamesCache   *gc_clipboard;
    bool         any_cancel;
};

#endif    // TOP_LEVEL_CONTEXT_H
