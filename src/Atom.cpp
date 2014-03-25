/****************************************************************************
 * Atom implements a mechanism whereby each user action is atomic in terms of
 * display update and undo/redo
 *  Author:  Bill Forster
 *  Licence: See licencing information in ChessPosition.cpp
 *  Copyright 2010, Triple Happy Ltd.  All rights reserved.
 ****************************************************************************/
#define _CRT_SECURE_NO_DEPRECATE
#include "GameDocument.h"
#include "GameLogic.h"
#include "Undo.h"
#include "Atom.h"

Atomic::Atomic( bool set_focus )
{
    if( stack_count++ == 0 ) 
        gl->atom.Begin(set_focus);
}

Atomic::~Atomic()
{
    if( --stack_count == 0 ) 
        gl->atom.End();
}

int Atomic::stack_count = 0;
GameLogic * Atomic::gl = 0;
Atom::Atom( GameLogic *gl )
{
    Atomic::gl = gl;
    this->gl = gl;
    running = false;
}

void Atom::SetInsertionPoint( long pos )
{
    if( running )
    {
        insertion_point=true;
        this->pos=pos;
    }
    else
        gl->lb->SetInsertionPoint(pos);
}

unsigned long Atom::GetInsertionPoint()
{
    if( running && (insertion_point||display||redisplay) )
        return pos;
    else
        return gl->lb->GetInsertionPoint();
}

void Atom::Display( long pos )
{
    if( running )
    {
        display=true;
        this->pos=pos;
    }
    else
        gl->gd.Display(pos);
}

void Atom::Redisplay( long pos)
{
    if( running )
    {
        redisplay=true;
        this->pos=pos;
    }
    else
        gl->gd.Redisplay(pos);
}

void Atom::Begin( bool set_focus )
{
    this->set_focus=set_focus;
    insertion_point=false;
    display=false;
    redisplay=false;
    undo=false;
    status_update=false;
    running=true;
    undo_previous_posn = gl->lb->GetInsertionPoint();
}

void Atom::End()
{
    if( redisplay )
        gl->gd.Redisplay(pos);
    else if( display )
        gl->gd.Display(pos);
    else if( insertion_point )
    {
        gl->lb->SetInsertionPoint(pos);
        gl->lb->ShowPosition(pos);
        gl->lb->Refresh();
    }
    if( undo )
        gl->undo.Save(undo_previous_posn,gl->gd,gl->state);
    if( undo||status_update )
        gl->StatusUpdate();
    if( set_focus )
        gl->SetFocusOnList();
    set_focus=false;
    insertion_point=false;
    display=false;
    redisplay=false;
    undo=false;
    status_update=false;
    running=false;
}

