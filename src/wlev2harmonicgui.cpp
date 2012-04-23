/******************************************************************************
*
* Project:  wlev2harmonic
* Purpose:  wlev2harmonic GUI implementation
* Author:   Pavel Kalian
*
***************************************************************************
*   Copyright (C) 2012 by Pavel Kalian   *
*   pavel@kalian.cz   *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.             *
***************************************************************************
*
*/

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
#include "wx/wx.h"
#endif //precompiled headers

#include <wx/filedlg.h>
#include <wx/textfile.h>

#include "wlev2harmonicgui.h"
#include "wlev2harmonic.h"
#include "wlev.h"

wlev2harmonicgui::wlev2harmonicgui( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wlev2harmonicguidef( parent, id, title, pos, size, style)
{
}

void wlev2harmonicgui::OnExit( wxCommandEvent& event )
{
      this->Close();
      app->Exit();
}

void wlev2harmonicgui::OnExit( wxCloseEvent& event )
{
      app->Exit();
}

void wlev2harmonicgui::OnLoadWlev( wxCommandEvent& event )
{
      wxString filename = wxFileSelector(_("Choose a WLEV file to open..."), 0, 0, _T("wlev"), _T("WLEV files (*.wlev)|*.wlev|All files (*.*)|*.*"));
      if ( !filename.empty() )
      {
            // open the file
            wxTextFile tfile;
            tfile.Open(filename);
 
            // read the first line
            wxString str = tfile.GetFirstLine();
            //processLine(str); // placeholder, do whatever you want with the string
 
            // read all lines one by one
            // until the end of the file
            while(!tfile.Eof())
            {
                  str.Append(_T("\n"));
                  str.Append(tfile.GetNextLine());
            }
            m_textWlev->SetValue(str);
      }
}

void wlev2harmonicgui::OnConvertToHarmonic( wxCommandEvent& event )
{
      wlev w;
      w.Parse(m_textWlev->GetValue());
      m_textHarmonic->SetValue(w.GetStationText());
}

void wlev2harmonicgui::OnSaveHarmonic( wxCommandEvent& event )
{
      wxString filename = wxFileSelector(_("Choose a file to save..."), 0, 0, _T("harm"), _T("TXT files (*.txt)|*.txt|All files (*.*)|*.*"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
      if (filename != wxEmptyString)
      {
            wxTextFile f(filename);
            if (wxFileExists(filename))
                  wxRemoveFile(filename);
            f.Create();
            f.AddLine(m_textHarmonic->GetValue());
            f.Write();
            f.Close();
      }
}