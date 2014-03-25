/****************************************************************************
 * Atom implements a mechanism whereby each user action is atomic in terms of
 * display update and undo/redo
 *  Author:  Bill Forster
 *  Licence: See licencing information in ChessPosition.cpp
 *  Copyright 2010, Triple Happy Ltd.  All rights reserved.
 ****************************************************************************/
#ifndef ATOM_H
#define ATOM_H

class GameLogic;

class Atomic
{
public:
    Atomic( bool set_focus=true );
    ~Atomic();
    static GameLogic *gl;
    static int stack_count;
};

class Atom
{
public:
    Atom::Atom( GameLogic *gl );

    // Do one undo save, redisplay or status update at end of a command
    void Begin( bool set_focus=true );
    void SetInsertionPoint( long pos );
    unsigned long GetInsertionPoint();
    void Display( long pos );
    void Redisplay( long pos);
    void Undo()
    {
        undo=true;
    }
    void Focus()
    {
        set_focus=true;
    }
    void StatusUpdate()
    {
        status_update=true;
    }
    void End();
    void NotUndoAble()
    {
        undo=false;
    }

private:
    long undo_previous_posn;
    long pos;
    bool running;
    bool set_focus;
    bool insertion_point;
    bool display;
    bool redisplay;
    bool undo;
    bool status_update;
    GameLogic *gl;
};

#endif // ATOM_H
