/******************************************************************************
*
* Project:  wlev2harmonic
* Purpose:  wlev2harmonic Main wxWidgets Program
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

#include "wx/print.h"
#include "wx/printdlg.h"
#include "wx/artprov.h"
#include "wx/stdpaths.h"
#include <wx/intl.h>
#include <wx/listctrl.h>
#include <wx/aui/aui.h>
#include <version.h> //Gunther
#include <wx/dialog.h>
#include <wx/progdlg.h>

#if wxCHECK_VERSION(2, 9, 0)
#include <wx/dialog.h>
#else
//  #include "scrollingdialog.h"
#endif

#ifdef __WXMSW__
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <psapi.h>
#endif

#ifndef __WXMSW__
#include <signal.h>
#include <setjmp.h>
#endif

#include "wlev2harmonic.h"

#include <wx/image.h>
#include "wx/apptrait.h"


// `Main program' equivalent, creating windows and returning main app frame
//------------------------------------------------------------------------------
// MyApp
//------------------------------------------------------------------------------

IMPLEMENT_APP(MyApp)

      BEGIN_EVENT_TABLE(MyApp, wxApp)
      EVT_ACTIVATE_APP(MyApp::OnActivateApp)
      END_EVENT_TABLE()

#include "wx/dynlib.h"

      void MyApp::OnInitCmdLine(wxCmdLineParser& parser)
{
      //Add some application specific command line options
      //parser.AddSwitch(_T("p"));
}

bool MyApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
      //g_bportable = parser.Found(_T("p"));

      return true;
}

void MyApp::OnActivateApp(wxActivateEvent& event)
{
      //    Code carefully in this method.
      //    It is called in some unexpected places,
      //    such as on closure of dialogs, etc.

      //      Activating?

      if(!event.GetActive())
      {

      }

      event.Skip();
}

bool MyApp::OnInit()
{
      if (!wxApp::OnInit())
            return false;

      //    On MSW, force the entire process to run on one CPU core only
      //    This resolves some difficulty with wxThread syncronization
#ifdef __WXMSW__
      //Gets the current process handle
      HANDLE hProc = GetCurrentProcess();
      DWORD procMask;
      DWORD sysMask;
      HANDLE hDup;
      DuplicateHandle(hProc,
            hProc,
            hProc,
            &hDup,
            0,
            FALSE,
            DUPLICATE_SAME_ACCESS);

      //Gets the current process affinity mask
      GetProcessAffinityMask(hDup,&procMask,&sysMask);

      // Take a simple approach, and assume up to 4 processors
      DWORD newMask;
      if((procMask & 1) == 1) newMask = 1;
      else if((procMask & 2) == 2) newMask = 2;
      else if((procMask & 4) == 4) newMask = 4;
      else if((procMask & 8) == 8) newMask = 8;

      //Set te affinity mask for the process
      BOOL res = SetProcessAffinityMask(hDup,(DWORD_PTR)newMask);

      if(res == 0 )
      {
            //Error setting affinity mask!!
      }
#endif

      setlocale(LC_NUMERIC,"C");

      mainwindow = new wlev2harmonicgui(NULL);
      mainwindow->app = this;
      mainwindow->Show(true);

      return TRUE;
}

int MyApp::OnExit()
{
      return TRUE;
}
