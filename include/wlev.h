/******************************************************************************
*
* Project:  wlev2harmonic
* Purpose:  wlev data and parsing and formating
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

#ifndef __WLEV_H__
#define __WLEV_H__

#include <wx/string.h>
#include <wx/hashmap.h>

class HarmonicConstant
{
    public:
      wxString const_code;
      double frequency; //Frequency
      double value; //HARMONIC - Value in meters
      double angle; //HARMONIC - angle in degree for the zone time (if so, otherwise GMT)
      double val4; //From here on: Doodsons numbers, a number to be ignore for the purpose
      double val5;
      double val6;
      double val7;
      double val8;
      double val9;
      double val10;
};

WX_DECLARE_STRING_HASH_MAP( HarmonicConstant, HarmonicConstants);

class wlev
{
    public:
      wlev();
      ~wlev();

      wxString GetStationText();
      void Parse(wxString text);
      
    private:
      void ParseFirstLine(wxString line);
      void ParseSecondLine(wxString line);
      void ParseAmplitudeUnitLine(wxString line);
      void ParseAmplitudeValueLine(wxString line);
      void ParseConstLine(wxString line);

      wxString GetHCText(wxString hc, wxString wlev_name = wxEmptyString);

      wxString station_name;
      double amplitude;
      wxString units;
      double lat;
      double lon;
      int timezone;
      HarmonicConstants hcs;
};

#endif //__WLEV_H__
