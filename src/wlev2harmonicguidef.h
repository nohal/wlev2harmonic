///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 10 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __WLEV2HARMONICGUIDEF_H__
#define __WLEV2HARMONICGUIDEF_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class wlev2harmonicguidef
///////////////////////////////////////////////////////////////////////////////
class wlev2harmonicguidef : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* m_menubar;
		wxMenu* m_menuFile;
		wxNotebook* m_notebook1;
		wxPanel* m_panelConvert;
		wxTextCtrl* m_textWlev;
		wxButton* m_buttonLoadWlev;
		wxButton* m_buttonConvert;
		wxTextCtrl* m_textHarmonic;
		wxButton* m_buttonSaveHarmonic;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnExit( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnExit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLoadWlev( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnConvertToHarmonic( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSaveHarmonic( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		wlev2harmonicguidef( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 798,521 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~wlev2harmonicguidef();
	
};

#endif //__WLEV2HARMONICGUIDEF_H__
