/****************************************************************************
 * Simple language support (for notation only)
 *  Author:  Bill Forster
 *  Licence: See licencing information in ChessPosition.cpp
 *  Copyright 2010, Triple Happy Ltd.  All rights reserved.
 ****************************************************************************/
#ifndef LANG_H
#define LANG_H
#include <string>
#include "wx/wx.h"

// Convert line of text, any language to any language
void LangLine( std::string &s, const char *from, const char *to );

// Get a list of known languages, NULL terminated, 1st is a template
const char **LangGetKnownArray();

// Start a check for changed language (return ptr to current lang lookup)
const char * LangCheckDiffBegin();

// End a check for changed language (return ptr to new lang lookup or NULL if no change)
const char * LangCheckDiffEnd();

// Set new language (sets English if string is invalid)
void LangSet( wxString &txt );

// Get current language
const char *LangGet();

// Convert native move to current language
void LangOut( std::string &s );

// Convert move, current language to English
void LangToEnglish( std::string &s, const char *language_lookup=0 );

// Convert line of text, any language to any language
void LangLine( std::string &s, const char *from, const char *to );

// Check a language specification string, uppercasing it if necessary
bool LangValidateString( wxString &txt );

#endif // LANG_H
