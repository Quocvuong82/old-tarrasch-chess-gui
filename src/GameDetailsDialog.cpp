/****************************************************************************
 * Custom dialog - Game Details
 *  Author:  Bill Forster
 *  Licence: See licencing information in ChessPosition.cpp
 *  Copyright 2010, Triple Happy Ltd.  All rights reserved.
 ****************************************************************************/
#define _CRT_SECURE_NO_DEPRECATE
#include <time.h>
#include "wx/wx.h"
#include "wx/valtext.h"
#include "wx/valgen.h"
#include "Appdefs.h"
#include "GameDetailsDialog.h"

// GameDetailsDialog type definition
IMPLEMENT_CLASS( GameDetailsDialog, wxDialog )

// GameDetailsDialog event table definition
BEGIN_EVENT_TABLE( GameDetailsDialog, wxDialog )
    EVT_BUTTON( ID_GAME_DETAILS_RESET, GameDetailsDialog::OnResetClick )
    EVT_BUTTON( wxID_HELP, GameDetailsDialog::OnHelpClick )
    EVT_BUTTON( wxID_OK, GameDetailsDialog::OnOkClick )
END_EVENT_TABLE()

// GameDetailsDialog constructors
GameDetailsDialog::GameDetailsDialog()
{
    Init();
}

GameDetailsDialog::GameDetailsDialog( wxWindow* parent,
  wxWindowID id, const wxString& caption,
  const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}

// Initialisation
void GameDetailsDialog::Init()
{
    white       = "";               // White
    black       = "";               // Black
    event       = "";               // Event
    site        = "";               // Site
    date        = "";               // Date
    round       = "";               // Round
    board_nbr   = "";               // Board
    result      = "";               // Result
    white_elo   = "";               // WhiteElo
    black_elo   = "";               // BlackElo
}

// Create dialog
bool GameDetailsDialog::Create( wxWindow* parent,
  wxWindowID id, const wxString& caption,
  const wxPoint& pos, const wxSize& size, long style )
{
    bool okay=true;

    // We have to set extra styles before creating the dialog
    SetExtraStyle( wxWS_EX_BLOCK_EVENTS|wxDIALOG_EX_CONTEXTHELP );
    if( !wxDialog::Create( parent, id, caption, pos, size, style ) )
        okay = false;
    else
    {

        CreateControls();
        SetDialogHelp();
        SetDialogValidators();

        // This fits the dialog to the minimum size dictated by the sizers
        GetSizer()->Fit(this);
        
        // This ensures that the dialog cannot be sized smaller than the minimum size
        GetSizer()->SetSizeHints(this);

        // Centre the dialog on the parent or (if none) screen
        Centre();
    }
    return okay;
}

#define SMALL 5
#define LARGE 2

// Control creation for GameDetailsDialog
void GameDetailsDialog::CreateControls()
{    

    // A top-level sizer
    wxBoxSizer* top_sizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(top_sizer);
    
    // A second box sizer to give more space around the controls
    wxBoxSizer* box_sizer = new wxBoxSizer(wxVERTICAL);
    top_sizer->Add(box_sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, SMALL);

//    // A friendly message
//    wxStaticText* descr = new wxStaticText( this, wxID_STATIC,
//        wxT("Game Details."), wxDefaultPosition, wxDefaultSize, 0 );
//    box_sizer->Add(descr, 0, wxALIGN_LEFT|wxALL, SMALL);

    // Spacer
    box_sizer->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, SMALL);

/*
   +-H1-------------+
   |+-V1--+  +-V2--+|
   ||+---+|  |+---+||
   |||   ||  ||   |||
   ||+---+|  |+---+||
   ||     |  |     ||
   ||+---+|  |+---+||
   |||   ||  ||   |||
   ||+---+|  |+---+||
   |+-----+  +-----+|
   +----------------+

   +-H2-------------+
   |+-----+  +-----+|
   ||     |  |     ||
   |+-----+  +-----+|
   +----------------+

          .....

   +-HN-------------+
   |+-----+  +-----+|
   ||     |  |     ||
   |+-----+  +-----+|
   +----------------+
*/

    //wxBoxSizer* H1 = new wxBoxSizer(wxHORIZONTAL);
    //wxBoxSizer* V1 = new wxBoxSizer(wxVERTICAL);
    wxFlexGridSizer *HV1 = new wxFlexGridSizer( 10, 2, 0, 0 );
    #define WIDTH 200
    wxSize sz=wxSize(WIDTH,wxDefaultCoord);

        // Label for white
        wxStaticText* white_label = new wxStaticText ( this, wxID_STATIC,
            wxT("White "), wxDefaultPosition, wxDefaultSize, 0 );
        HV1->Add(white_label, 0, wxALIGN_LEFT|wxALL, SMALL);

        // Text control for white
        white_ctrl = new wxTextCtrl ( this, ID_WHITE_PLAYER_NAME,  wxT(""), wxDefaultPosition, sz, 0 );
        HV1->Add(white_ctrl, 0, wxGROW|wxALL, SMALL);

        // Label for black
        wxStaticText* black_label = new wxStaticText ( this, wxID_STATIC,
            wxT("Black "), wxDefaultPosition, wxDefaultSize, 0 );
        HV1->Add(black_label, 0, wxALIGN_LEFT|wxALL, SMALL);

        // Text control for black
        black_ctrl = new wxTextCtrl ( this, ID_BLACK_PLAYER_NAME,   wxT(""), wxDefaultPosition, sz, 0 );
        HV1->Add(black_ctrl, 0, wxGROW|wxALL, SMALL);

        // Label for event
        wxStaticText* event_label = new wxStaticText ( this, wxID_STATIC,
            wxT("Event "), wxDefaultPosition, wxDefaultSize, 0 );
        HV1->Add(event_label, 0, wxALIGN_LEFT|wxALL, SMALL);

        // Text control for event
        event_ctrl = new wxTextCtrl ( this, ID_EVENT,           wxT(""), wxDefaultPosition, sz, 0 );
        HV1->Add(event_ctrl, 0, wxGROW|wxALL, SMALL);

        // Label for site
        wxStaticText* site_label = new wxStaticText ( this, wxID_STATIC,
            wxT("Site "), wxDefaultPosition, wxDefaultSize, 0 );
        HV1->Add(site_label, 0, wxALIGN_LEFT|wxALL, SMALL);

        // Text control for site
        site_ctrl = new wxTextCtrl ( this, ID_SITE,            wxT(""), wxDefaultPosition, sz, 0 );
        HV1->Add(site_ctrl, 0, wxGROW|wxALL, SMALL);

        // Label for date
        wxStaticText* date_label = new wxStaticText ( this, wxID_STATIC,
            wxT("Date "), wxDefaultPosition, wxDefaultSize, 0 );
        HV1->Add(date_label, 0, wxALIGN_LEFT|wxALL, SMALL);

        // Text control for date
        date_ctrl = new wxTextCtrl ( this, ID_DATE,            wxT(""), wxDefaultPosition, sz, 0 );
        HV1->Add(date_ctrl, 0, wxGROW|wxALL, SMALL);

        // Label for round
        wxStaticText* round_label = new wxStaticText ( this, wxID_STATIC,
            wxT("Round "), wxDefaultPosition, wxDefaultSize, 0 );
        HV1->Add(round_label, 0, wxALIGN_LEFT|wxALL, SMALL);

        // Text control for round
        round_ctrl = new wxTextCtrl ( this, ID_ROUND,           wxT(""), wxDefaultPosition, sz, 0 );
        HV1->Add(round_ctrl, 0, wxGROW|wxALL, SMALL);
/*
        // Label for board nbr
        wxStaticText* board_nbr_label = new wxStaticText ( this, wxID_STATIC,
            wxT("Board number "), wxDefaultPosition, wxDefaultSize, 0 );
        HV1->Add(board_nbr_label, 0, wxALIGN_LEFT|wxALL, SMALL);

        // Text control for board nbr
        board_nbr_ctrl = new wxTextCtrl ( this, ID_BOARD_NBR,       wxT(""), wxDefaultPosition, sz, 0 );
        HV1->Add(board_nbr_ctrl, 0, wxGROW|wxALL, SMALL);
  */
        // Label for result
        wxStaticText* result_label = new wxStaticText ( this, wxID_STATIC,
            wxT("Result "), wxDefaultPosition, wxDefaultSize, 0 );
        HV1->Add(result_label, 0, wxALIGN_LEFT|wxALL, SMALL);

        // Combo box for result
        wxString choices[4];
        choices[0] = "1-0";
        choices[1] = "0-1";
        choices[2] = "1/2-1/2";
        choices[3] = "(no result)";
        result_ctrl = new wxComboBox ( this, ID_RESULT,  wxT(""), wxDefaultPosition, sz, 4, choices, wxCB_READONLY );
        HV1->Add(result_ctrl, 0, wxGROW|wxALL, SMALL);

        // Label for eco
        wxStaticText* eco_label = new wxStaticText ( this, wxID_STATIC,
            wxT("ECO code "), wxDefaultPosition, wxDefaultSize, 0 );
        HV1->Add(eco_label, 0, wxALIGN_LEFT|wxALL, SMALL);

        // Text control for eco
        eco_ctrl = new wxTextCtrl ( this, ID_ECO,       wxT(""), wxDefaultPosition, sz, 0 );
        HV1->Add(eco_ctrl, 0, wxGROW|wxALL, SMALL);

        // Label for WhiteElo
        #if 1
        wxStaticText* white_elo_label = new wxStaticText ( this, wxID_STATIC,
            wxT("White Elo "), wxDefaultPosition, wxDefaultSize, 0 );
        #else
        wxCheckBox* white_elo_label = new wxCheckBox( this, wxID_STATIC,
           wxT("White Elo "), wxDefaultPosition, wxDefaultSize, 0 );
        white_elo_label->SetValue( true );
        #endif
        HV1->Add(white_elo_label, 0, wxALIGN_LEFT|wxALL, SMALL);
        //small_sizer2->Add( visible_box2, 0,
        //    wxALIGN_CENTER_VERTICAL|wxALL, 5);

        // Text control for WhiteElo
        #if 1
        white_elo_ctrl = new wxTextCtrl ( this, ID_WHITE_ELO,       wxT(""), wxDefaultPosition, sz, 0 );
        // A spin control for WhiteElo
        #else
        wxSpinCtrl* white_elo_ctrl = new wxSpinCtrl ( this, ID_WHITE_ELO,
            wxEmptyString, wxDefaultPosition, wxSize(60, -1),
            wxSP_ARROW_KEYS, 0, 4000, 2000 );
        #endif
        HV1->Add(white_elo_ctrl, 0, wxGROW|wxALL, SMALL);

        // Label for BlackElo
        wxStaticText* black_elo_label = new wxStaticText ( this, wxID_STATIC,
            wxT("Black Elo "), wxDefaultPosition, wxDefaultSize, 0 );
        HV1->Add(black_elo_label, 0, wxALIGN_LEFT|wxALL, SMALL);

        // Text control for BlackElo
        black_elo_ctrl = new wxTextCtrl ( this, ID_BLACK_ELO,       wxT(""), wxDefaultPosition, sz, 0 );
        HV1->Add(black_elo_ctrl, 0, wxGROW|wxALL, SMALL);

    //H1->Add(V1, 1, wxGROW | (wxALL/* & ~wxLEFT */), LARGE);
    //wxBoxSizer* V2 = new wxBoxSizer(wxVERTICAL);

    //H1->Add(V2, 1, wxGROW | (wxALL/* & ~wxLEFT */), LARGE);
    box_sizer->Add(HV1, 1, wxGROW | (wxALL/* & ~wxLEFT */), LARGE);

    // A dividing line before the OK and Cancel buttons
    wxStaticLine* line = new wxStaticLine ( this, wxID_STATIC,
        wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    box_sizer->Add(line, 0, wxGROW|wxALL, SMALL);

    // A horizontal box sizer to contain Reset, OK, Cancel and Help
    wxBoxSizer* okCancelBox = new wxBoxSizer(wxHORIZONTAL);
    box_sizer->Add(okCancelBox, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 15);
/*
    // The Reset button
    wxButton* reset = new wxButton( this, ID_PLAYER_RESET, wxT("&Reset"),
        wxDefaultPosition, wxDefaultSize, 0 );
    okCancelBox->Add(reset, 0, wxALIGN_CENTER_VERTICAL|wxALL, SMALL);
*/
    // The OK button
    wxButton* ok = new wxButton ( this, wxID_OK, wxT("&OK"),
        wxDefaultPosition, wxDefaultSize, 0 );
    okCancelBox->Add(ok, 0, wxALIGN_CENTER_VERTICAL|wxALL, SMALL);

    // The Cancel button
    wxButton* cancel = new wxButton ( this, wxID_CANCEL,
        wxT("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    okCancelBox->Add(cancel, 0, wxALIGN_CENTER_VERTICAL|wxALL, SMALL);

    // The Help button
    wxButton* help = new wxButton( this, wxID_HELP, wxT("&Help"),
        wxDefaultPosition, wxDefaultSize, 0 );
    okCancelBox->Add(help, 0, wxALIGN_CENTER_VERTICAL|wxALL, SMALL);
}

// Set the validators for the dialog controls
void GameDetailsDialog::SetDialogValidators()
{
    FindWindow(ID_WHITE_PLAYER_NAME)->SetValidator(
        wxTextValidator(wxFILTER_NONE, &white));
    FindWindow(ID_BLACK_PLAYER_NAME)->SetValidator(
        wxTextValidator(wxFILTER_NONE, &black)); 
    FindWindow(ID_EVENT)->SetValidator(
        wxTextValidator(wxFILTER_NONE, &event));
    FindWindow(ID_SITE)->SetValidator(
        wxTextValidator(wxFILTER_NONE, &site));
    FindWindow(ID_DATE)->SetValidator(
        wxTextValidator(wxFILTER_ASCII, &date));
    FindWindow(ID_ROUND)->SetValidator(
        wxTextValidator(wxFILTER_ASCII, &round));
//    FindWindow(ID_BOARD_NBR)->SetValidator(
//        wxTextValidator(wxFILTER_ASCII, &board_nbr));
    FindWindow(ID_RESULT)->SetValidator(
        wxGenericValidator(&result));
    FindWindow(ID_ECO)->SetValidator(
        wxTextValidator(wxFILTER_ASCII, &eco));
    FindWindow(ID_WHITE_ELO)->SetValidator(
        wxTextValidator(wxFILTER_ASCII, &white_elo));
    FindWindow(ID_BLACK_ELO)->SetValidator(
        wxTextValidator(wxFILTER_ASCII, &black_elo));
}

// Sets the help text for the dialog controls
void GameDetailsDialog::SetDialogHelp()
{
    wxString white_help    = wxT("White's name.");
    wxString black_help    = wxT("Black's name.");

    FindWindow(ID_WHITE_PLAYER_NAME)->SetHelpText(white_help);
    FindWindow(ID_WHITE_PLAYER_NAME)->SetToolTip(white_help);

    FindWindow(ID_BLACK_PLAYER_NAME)->SetHelpText(black_help);
    FindWindow(ID_BLACK_PLAYER_NAME)->SetToolTip(black_help);
}

/*
// wxEVT_UPDATE_UI event handler for ID_CHECKBOX
void GameDetailsDialog::OnVoteUpdate( wxUpdateUIEvent& event )
{
    wxSpinCtrl* ageCtrl = (wxSpinCtrl*) FindWindow(ID_AGE);
    if (ageCtrl->GetValue() < 18)
    {
        event.Enable(false);
        event.Check(false);
    }
    else
        event.Enable(true);
}
*/

// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_PLAYER_RESET
void GameDetailsDialog::OnResetClick( wxCommandEvent& WXUNUSED(event) )
{
    Init();
    TransferDataToWindow();
}

// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_HELP
void GameDetailsDialog::OnHelpClick( wxCommandEvent& WXUNUSED(event) )
{
    // Normally we would wish to display proper online help.
    // For this example, we're just using a message box.
    /*
    wxGetApp().GetHelpController().DisplaySection(wxT("Personal record dialog"));
     */

    wxString helpText =
      wxT("Use this panel to enter or edit supplementary details that\n")
      wxT("you want associated with this game as stored on file.\n");

    wxMessageBox(helpText,
      wxT("Game Details Dialog Help"),
      wxOK|wxICON_INFORMATION, this);
}

// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
void GameDetailsDialog::OnOkClick( wxCommandEvent& WXUNUSED(event) )
{
    // Validate date
    wxString temp = date_ctrl->GetValue();
    temp.Trim(true);
    temp.Trim(false);
    const char *s = temp.c_str();
    bool ok=false;
    wxString err_msg = "Illegal date: valid format is yyyy.mm.dd, eg 1999.12.31";
    if( temp=="?" || strlen(s)==0 )
        ok = true;
    else if( strlen(s) == 4 )
    {
        int yyyy = atoi(&s[0]);
        bool yyyy_unknown = (s[0]=='?' && s[1]=='?' && s[2]=='?' && s[3]=='?');
        ok = yyyy_unknown || (1000<=yyyy && yyyy<=2999);
    }
    else if( 8<=strlen(s) && strlen(s)<=10 )
    {
        if( s[4]=='.' )
        {
            ok = true;
            int dd_offset = 8;
            if( s[6]=='.' && s[7]!='.' && strlen(s)<10 )
                dd_offset = 7;  // yyyy.m.d or yyyy.m.dd (len=8 or 9)
            else if( s[6]!='.' && s[7]=='.' && strlen(s)>8 )
                dd_offset = 8;  // yyyy.mm.d or yyyy.mm.dd (len=9 or 10)
            else
                ok = false;
            if( ok )
            {
                int yyyy = atoi(&s[0]);
                int mm   = atoi(&s[5]);
                int dd   = atoi(&s[dd_offset]);
                bool yyyy_unknown = (s[0]=='?' && s[1]=='?' && s[2]=='?' && s[3]=='?');
                bool mm_unknown   = (s[5]=='?' && (s[6]=='?'||s[6]=='.') );
                bool dd_unknown   = (s[dd_offset]=='?' && (s[dd_offset+1]=='?'||s[dd_offset+1]=='\0') );
                bool yyyy_ok = yyyy_unknown || (1000<=yyyy && yyyy<=2999);
                bool mm_ok   = mm_unknown   || (1<=mm && mm<=12);
                bool dd_ok   = dd_unknown   || (1<=dd && dd<=31);
                ok = (yyyy_ok && mm_ok && dd_ok);
                if( ok )
                {
                    if( mm == 2 )
                    {
                        bool leap=false;
                        if( yyyy%400 == 0 )
                            leap = true;            //  eg 1600,2000,2400 are leap (also yyyy_unknown as then yyyy==0)
                        else if( yyyy%100 == 0 )
                            leap = false;           //  eg 1700,1800,1900,2100 aren't leap
                        else if( yyyy%4 == 0 )
                            leap = true;            //  eg 1996,2004,2008,2012 are leap
                        ok = (dd <= (leap?29:28));  //  (also dd_unknown is okay as then dd==0)
                    }
                    else if( mm==4 || mm==6 || mm==9 || mm==11 )
                    {
                        ok = dd<=30;  // (also dd_unknown is okay as then dd==0)
                    }
                    if( !ok )
                        err_msg = "Illegal date: there aren't that many days in that month";
                }
            }
        }
    }

    // Validate round
    if( ok )
    {
        temp = round_ctrl->GetValue();
        temp.Trim(true);
        temp.Trim(false);
        if( temp!="?" && temp!='-' )  // both of these explicitly allowed
        {
            s = temp.c_str();
            if( *s )
            {
                int r = atoi(s);
                if( r <= 0 )
                    ok = false;
                while( ok && *s )
                {  // allow digits and '.' characters, '.' must be followed by a digit
                    if( *s!='.' && !isdigit(*s) )
                        ok = false;
                    if( *s=='.' && !isdigit(*(s+1)) )
                        ok = false;
                    s++;
                }
                if( !ok )
                    err_msg = "Illegal round";
            }
        }
    }
/*
    // Validate board number
    if( ok )
    {
        temp = board_nbr_ctrl->GetValue();
        temp.Trim(true);
        temp.Trim(false);
        s = temp.c_str();
        if( temp!="?" && *s )
        {
            int r = atoi(s);
            if( r <= 0 )
            {
                ok = false;
                err_msg = "Illegal board number";
            }
        }
    }
  */
    // Validate result

    // Validate ECO
    if( ok )
    {
        temp = eco_ctrl->GetValue();
        temp.Trim(true);
        temp.Trim(false);
        if( temp != "?" )
        {
            s = temp.c_str();
            ok = (strlen(s)==0);
            // Allow "" (empty) or "A00" (alpha,digit,digit)
            // But also allow say "A000" or "AA00" (possible future formats?)
            if( 3<=strlen(s) && strlen(s)<=4 )
            {
                ok = true;
                for( int i=0; ok && *s; i++ )
                {
                    if( i==0 )
                        ok = (bool)isalpha(*s);
                    else if( i==1 )
                    {
                        if( strlen(s) == 4 )
                            ok = (bool)(isalpha(*s) || isdigit(*s));
                        else  // if( strlen(s) == 3 )
                            ok = (bool)isdigit(*s);
                    }
                    else
                        ok = (bool)isdigit(*s);
                    s++;
                }           
            }
            if( !ok )
                err_msg = "Illegal ECO code";
        }
    }

    // Validate white elo
    if( ok )
    {
        temp = white_elo_ctrl->GetValue();
        temp.Trim(true);
        temp.Trim(false);
        s = temp.c_str();
        if( temp!="?" && *s )
        {
            int r = atoi(s);
            if( r<=0 || r>10000 )
            {
                ok = false;
                err_msg = "Illegal white elo";
            }
        }
    }


    // Validate black elo
    if( ok )
    {
        temp = black_elo_ctrl->GetValue();
        temp.Trim(true);
        temp.Trim(false);
        s = temp.c_str();
        if( temp!="?" && *s )
        {
            int r = atoi(s);
            if( r<=0 || r>10000 )
            {
                ok = false;
                err_msg = "Illegal black elo";
            }
        }
    }
    if( ok )
        AcceptAndClose();
    else
        wxMessageBox( err_msg, "Error in game details", wxOK|wxICON_ERROR );
}

wxString GameDetailsDialog::remember_event;
wxString GameDetailsDialog::remember_site;
bool GameDetailsDialog::Run( GameDocument &gd )
{
    bool ok=false;
    white     = gd.white;          // "White"
    black     = gd.black;          // "Black"
    event     = gd.event;          // "Event"
    site      = gd.site;           // "Site"
    date      = gd.date;           // "Date"
    round     = gd.round;          // "Round"
    result    = gd.result;         // "Result"
    eco       = gd.eco;            // "ECO"
    white_elo = gd.white_elo;      // "WhiteElo"
    black_elo = gd.black_elo;      // "BlackElo"
    if( result!="1-0" && result!="0-1" && result!="1/2-1/2" )
        result = "(no result)";
    if( date=="" )
    {
        time_t rawtime;
        struct tm * timeinfo;
        time( &rawtime );
        timeinfo = localtime( &rawtime );
        char buf[20];
        sprintf( buf, "%04d.%02d.%02d", timeinfo->tm_year+1900, timeinfo->tm_mon+1, timeinfo->tm_mday );
        date = buf;
    }
    if( event=="" )
        event = remember_event;
    if( site=="" )
        site = remember_site;
    if( wxID_OK == ShowModal() )
    {
        ok = true;
        result.Trim(true);
        result.Trim(false);
        white.Trim(true);
        white.Trim(false);
        black.Trim(true);
        black.Trim(false);
        event.Trim(true);
        event.Trim(false);
        site.Trim(true);
        site.Trim(false);
        date.Trim(true);
        date.Trim(false);
        round.Trim(true);
        round.Trim(false);
        eco.Trim(true);
        eco.Trim(false);
        white_elo.Trim(true);
        white_elo.Trim(false);
        black_elo.Trim(true);
        black_elo.Trim(false);
        if( result!="1-0" && result!="0-1" && result!="1/2-1/2" )
            result = "*";
        gd.game_details_edited = true;
        remember_event = event;
        remember_site = site;
        gd.white      = white;        // "White"
        gd.black      = black;        // "Black"
        gd.event      = event;        // "Event"
        gd.site       = site;         // "Site"
        const char *s = date.c_str();
        if( 8<=strlen(s) && strlen(s)<=9 )
        {
            if( s[4]=='.' )
            {
                bool ok = true;
                int dd_offset = 8;
                if( s[6]=='.' && s[7]!='.' )
                    dd_offset = 7;  // yyyy.m.d or yyyy.m.dd (len=8 or 9)
                else if( s[6]!='.' && s[7]=='.' && strlen(s)>8 )
                    dd_offset = 8;  // yyyy.mm.d (len=9)
                else
                    ok = false;
                if( ok )
                {
                    int yyyy = atoi(&s[0]);
                    int mm   = atoi(&s[5]);
                    int dd   = atoi(&s[dd_offset]);
                    char buf[40];
                    sprintf( buf, "%04d.%02d.%02d", yyyy, mm, dd );
                    if( yyyy==0 )
                        memcpy(buf,"????",4);
                    if( mm==0 )
                        memcpy(buf+5,"??",2);
                    if( dd==0 )
                        memcpy(buf+8,"??",2);
                    date = buf;
                }
            }
        }
        gd.date       = date;         // "Date"
        gd.round      = round;        // "Round"
        gd.result     = result;       // "Result"
        gd.eco        = eco;          // "ECO"
        gd.white_elo  = white_elo;    // "WhiteElo"
        gd.black_elo  = black_elo;    // "BlackElo"
    }
    return ok;
}
