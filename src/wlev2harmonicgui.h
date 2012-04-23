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

#ifndef __WLEV2HARMONICGUI_H__
#define __WLEV2HARMONICGUI_H__

#include "wlev2harmonicguidef.h"

class MyApp;

class wlev2harmonicgui : public wlev2harmonicguidef
{
      public:
      MyApp *app;
      wlev2harmonicgui( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 780,580 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

      private:
      void OnExit( wxCommandEvent& event );
      void OnExit( wxCloseEvent& event );
      void OnLoadWlev( wxCommandEvent& event );
	void OnConvertToHarmonic( wxCommandEvent& event );
	void OnSaveHarmonic( wxCommandEvent& event );
};

#endif //__WLEV2HARMONICGUI_H__
