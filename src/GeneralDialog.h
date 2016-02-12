/****************************************************************************
 * Custom dialog - General options
 *  Author:  Bill Forster
 *  Licence: See licencing information in ChessPosition.cpp
 *  Copyright 2010, Triple Happy Ltd.  All rights reserved.
 ****************************************************************************/
#ifndef GENERAL_DIALOG_H
#define GENERAL_DIALOG_H
#include "wx/spinctrl.h"
#include "ChessRules.h"
#include "SuspendEngine.h"
#include "Repository.h"
class BoardSetupControl;

// Control identifiers
enum
{
    ID_GENERAL_DIALOG    = 10000,
    ID_NOTATION_LANGUAGE = 10001,
    ID_NO_ITALICS        = 10002,
    ID_STRAIGHT_TO_GAME  = 10003,
    ID_LARGE_FONT        = 10004, 
    ID_SMALL_BOARD       = 10005,
    ID_NO_AUTO_FLIP      = 10006,
    ID_STRAIGHT_TO_FIRST_GAME  = 10007,
    ID_EMIT_BELL         = 10008
};

// GeneralDialog class declaration
class GeneralDialog: public wxDialog
{    
    DECLARE_CLASS( GeneralDialog )
    DECLARE_EVENT_TABLE()

public:

    // Constructors
    GeneralDialog( wxWindow* parent, GeneralConfig *dat_ptr,
      wxWindowID id = ID_GENERAL_DIALOG,
      const wxString& caption = wxT("General settings"),
      const wxPoint& pos = wxDefaultPosition,
      const wxSize& size = wxDefaultSize,
      long style = wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX );

    // Member initialisation
    void Init( GeneralConfig *dat_ptr );

    // Creation
    bool Create( wxWindow* parent,
      wxWindowID id = ID_GENERAL_DIALOG,
      const wxString& caption = wxT("General settings"),
      const wxPoint& pos = wxDefaultPosition,
      const wxSize& size = wxDefaultSize,
      long style = wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX );

    // Creates the controls and sizers
    void CreateControls();

    // Sets the validators for the dialog controls
    void SetDialogValidators();

    // Sets the help text for the dialog controls
    void SetDialogHelp();


    // wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_HELP
    void OnHelpClick( wxCommandEvent& event );

    // wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
    void OnOkClick( wxCommandEvent& event );

    void OnNotationLanguage( wxCommandEvent& event );
    wxArrayString   labels;

    // Data members
public:
    wxComboBox*     notation_language_ctrl;
    wxButton*       ok_button;
    wxString        combo_label;
    GeneralConfig   dat;
    SuspendEngine   suspendor;  // the mere presence of this var suspends the engine during the dialog
};

#endif    // GENERAL_DIALOG_H
