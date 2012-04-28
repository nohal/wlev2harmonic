///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 10 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wlev2harmonicguidef.h"

///////////////////////////////////////////////////////////////////////////

wlev2harmonicguidef::wlev2harmonicguidef( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar = new wxMenuBar( 0 );
	m_menuFile = new wxMenu();
	wxMenuItem* m_menuItmExit;
	m_menuItmExit = new wxMenuItem( m_menuFile, wxID_ANY, wxString( _("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( m_menuItmExit );
	
	m_menubar->Append( m_menuFile, _("File") ); 
	
	this->SetMenuBar( m_menubar );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_notebook1 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panelConvert = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	m_textWlev = new wxTextCtrl( m_panelConvert, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxTE_DONTWRAP|wxTE_MULTILINE );
	m_textWlev->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 76, 90, 90, false, wxEmptyString ) );
	
	bSizer3->Add( m_textWlev, 1, wxALL|wxEXPAND, 5 );
	
	m_buttonLoadWlev = new wxButton( m_panelConvert, wxID_ANY, _("Load file..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_buttonLoadWlev, 0, wxALL, 5 );
	
	
	bSizer2->Add( bSizer3, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonConvert = new wxButton( m_panelConvert, wxID_ANY, _(">>>"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	m_buttonConvert->SetDefault(); 
	bSizer4->Add( m_buttonConvert, 0, wxALIGN_CENTER|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer2->Add( bSizer4, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	m_rbFrmCHS = new wxRadioButton( m_panelConvert, wxID_ANY, _("CHS"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_rbFrmCHS, 0, wxALL, 5 );
	
	m_rbFrmHarm = new wxRadioButton( m_panelConvert, wxID_ANY, _("173 harmonics"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_rbFrmHarm, 0, wxALL, 5 );
	
	
	bSizer5->Add( bSizer6, 0, wxEXPAND, 5 );
	
	m_textHarmonic = new wxTextCtrl( m_panelConvert, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxTE_DONTWRAP|wxTE_MULTILINE );
	m_textHarmonic->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 76, 90, 90, false, wxEmptyString ) );
	
	bSizer5->Add( m_textHarmonic, 1, wxALL|wxEXPAND, 5 );
	
	m_buttonSaveHarmonic = new wxButton( m_panelConvert, wxID_ANY, _("Save file..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_buttonSaveHarmonic, 0, wxALL, 5 );
	
	
	bSizer2->Add( bSizer5, 1, wxEXPAND, 5 );
	
	
	m_panelConvert->SetSizer( bSizer2 );
	m_panelConvert->Layout();
	bSizer2->Fit( m_panelConvert );
	m_notebook1->AddPage( m_panelConvert, _("Wlev to harmonic"), false );
	
	bSizer1->Add( m_notebook1, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( wlev2harmonicguidef::OnExit ) );
	this->Connect( m_menuItmExit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( wlev2harmonicguidef::OnExit ) );
	m_buttonLoadWlev->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( wlev2harmonicguidef::OnLoadWlev ), NULL, this );
	m_buttonConvert->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( wlev2harmonicguidef::OnConvertToHarmonic ), NULL, this );
	m_buttonSaveHarmonic->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( wlev2harmonicguidef::OnSaveHarmonic ), NULL, this );
}

wlev2harmonicguidef::~wlev2harmonicguidef()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( wlev2harmonicguidef::OnExit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( wlev2harmonicguidef::OnExit ) );
	m_buttonLoadWlev->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( wlev2harmonicguidef::OnLoadWlev ), NULL, this );
	m_buttonConvert->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( wlev2harmonicguidef::OnConvertToHarmonic ), NULL, this );
	m_buttonSaveHarmonic->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( wlev2harmonicguidef::OnSaveHarmonic ), NULL, this );
	
}
