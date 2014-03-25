/****************************************************************************
 * Provide a mechanism for locating games in one or more pgn files
 *  Author:  Bill Forster
 *  Licence: See licencing information in ChessPosition.cpp
 *  Copyright 2010, Triple Happy Ltd.  All rights reserved.
 ****************************************************************************/
#ifndef PGN_FILES_H
#define PGN_FILES_H
#include <stdio.h>
#include <string>
#include <map>
#include "GamesCache.h"

struct PgnFile
{
    PgnFile() { mode=closed; delete_on_exit=false;
                filelen=0; file_read=0; file_write=0; }
    enum {closed,creating,reading,modifying,copying} mode;
    bool delete_on_exit;
    std::string filename;
    std::string filename_temp;
    FILE   *file_read;
    FILE   *file_write;
    time_t  file_modification_time;
    long    filelen;
};

class PgnFiles
{
public:
    PgnFiles()  { files.clear(); next_handle=1; }
    ~PgnFiles();

    // Start reading a file and introduce it into the system
    FILE *OpenRead   ( std::string filename, int &handle );

    // Create a file and introduce it into the system
    FILE *OpenCreate ( std::string filename, int &handle );

    // Is a previously used file known and available (unmodified and ready to go)
    bool IsAvailable ( int handle );

    // Is a file already known and available (unmodified and ready to go)
    bool IsAvailable( std::string filename, int &handle );

    // Reopen a known file for reading
    FILE *ReopenRead ( int handle );

    // Reopen a known file for modification
    bool ReopenModify( int handle, FILE * &pgn_in, FILE * &pgn_out );

    // Reopen a known file for copy
    bool ReopenCopy( int handle, std::string new_filename, FILE * &pgn_in, FILE * &pgn_out );

    // Close all files
    void Close( GamesCache *gc_clipboard );

    // If a modified file is known, update length and time
    void UpdateKnownFile( std::string &filename, time_t filetime_before, long filelen_before, long delta );

private:
    bool IsAvailable( std::map<int,PgnFile>::iterator it );
    std::map<int,PgnFile> files;
    int next_handle;
};

#endif  // PGN_FILES_H
