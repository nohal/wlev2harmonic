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

#include <wx/tokenzr.h>

#include "wlev.h"

wlev::wlev()
{
      //hcs = new HarmonicConstants();
}

wlev::~wlev()
{
      //delete(hcs);
}

//Parses the first line of the WLEV file
//Format: fixed length fields
//Example:
//WaterLevConstit 00001 Terschellinger Bank                          2011/01/01||
void wlev::ParseFirstLine(wxString line)
{
      this->station_name = line.SubString(22, 66).Trim();
}

//Parses the second line of the WLEV file
//Format: 
//Example:
//!Observed    53 32.2000N   5  3.6000E                        +01   0100:00   ||
void wlev::ParseSecondLine(wxString line)
{
      bool lat = false;
      bool lon = false;
      bool minutes = false;
      bool tz = false;
      wxStringTokenizer tk(line, _T(" "), FALSE);
      wxString s;
      while (tk.HasMoreTokens())
      {
            s = tk.GetNextToken().Trim();
            wxString ss;
            if (s != wxEmptyString)
                  ss = s.Left(s.Length() - 1);
            double tmp;
            if (s != wxEmptyString && (s.ToDouble(&tmp) || ss.ToDouble(&tmp)) && (!lat || !lon))
            {
                  if(!lat)
                  {
                        if (!minutes)
                        {
                              s.ToDouble(&this->lat);
                              minutes = true;
                        }
                        else
                        {
                              double n;
                              s.Left(s.Length() - 1).ToDouble(&n);
                              this->lat += n/60;
                              if (s.EndsWith(_T("S")))
                                    this->lat = 0 - this->lat;
                              lat = true;
                              minutes = false;
                        }
                  } 
                  else if (!lon)
                  {
                        if (!minutes)
                        {
                              s.ToDouble(&this->lon);
                              minutes = true;
                        }
                        else
                        {
                              double n;
                              s.Left(s.Length() - 1).ToDouble(&n);
                              this->lon += n/60;
                              if (s.EndsWith(_T("W")))
                                    this->lon = 0 - this->lon;
                              lon = true;
                        }
                  }
            }
            if (lat && lon && !tz)
            {
                  if (tk.HasMoreTokens())
                        s = tk.GetNextToken().Trim();
                  while (s == wxEmptyString && tk.HasMoreTokens())
                        s = tk.GetNextToken().Trim();
                  long tzone = 0;
                  s.Right(2).ToLong(&tzone);
                  if (s.StartsWith(_T("+")))
                        this->timezone = tzone;
                  else
                        this->timezone = -tzone;
                  return; //we are done
            }
      }
}

//Parses the amplitude unit line of the WLEV file
//Example:
//03 Amplitude     metres     0       TW                                       ||
void wlev::ParseAmplitudeUnitLine(wxString line)
{
      wxStringTokenizer tk(line, _T(" "), FALSE);
      wxString s;
      while (tk.HasMoreTokens())
      {
            s = tk.GetNextToken().Trim();
            if (s == _T("Amplitude"))
            {
                  if (tk.HasMoreTokens())
                        s = tk.GetNextToken().Trim();
                  while (s == wxEmptyString && tk.HasMoreTokens())
                        s = tk.GetNextToken().Trim();
                  this->units = s;
                  return; //we are done
            }
      }
}

//Parses the amplitude value line of the WLEV file
//Example:
//A0= 1.5600 Rayleigh=    , ResErr=0.0211, MatrixCond=      , Ctime=201201     ||
void wlev::ParseAmplitudeValueLine(wxString line)
{
      wxStringTokenizer tk(line, _T(" "), FALSE);
      wxString s;
      while (tk.HasMoreTokens())
      {
            s = tk.GetNextToken();
            if (s.StartsWith(_T("A0=")))
            {
                  if (tk.HasMoreTokens())
                        s = tk.GetNextToken().Trim();
                  while (s == wxEmptyString && tk.HasMoreTokens())
                        s = tk.GetNextToken().Trim();
                  s.ToDouble(&this->amplitude);
                  return; //we are done
            }
      }
}

//Parses the amplitude value line of the WLEV file
//Example:
//Z0       0.000  1.5600   0.00  0  0  0  0  0  0 46
void wlev::ParseConstLine(wxString line)
{
      HarmonicConstant hc;
      wxStringTokenizer tk(line, _T(" "), FALSE);
      wxString s;
      while (tk.HasMoreTokens())
      {
            s = tk.GetNextToken().Trim();
            hc.const_code = s;
            if (tk.HasMoreTokens())
                  s = tk.GetNextToken().Trim();
            while (s == wxEmptyString && tk.HasMoreTokens())
                  s = tk.GetNextToken().Trim();
            s.ToDouble(&hc.frequency);
            if (tk.HasMoreTokens())
                  s = tk.GetNextToken().Trim();
            while (s == wxEmptyString && tk.HasMoreTokens())
                  s = tk.GetNextToken().Trim();
            s.ToDouble(&hc.value);
            if (tk.HasMoreTokens())
                  s = tk.GetNextToken().Trim();
            while (s == wxEmptyString && tk.HasMoreTokens())
                  s = tk.GetNextToken().Trim();
            s.ToDouble(&hc.angle);

            this->hcs[hc.const_code] = hc;
      }
}

void wlev::Parse(wxString text)
{
      wxStringTokenizer tk(text, _T("\n"));
      wxString line;
      while (tk.HasMoreTokens())
      {
            line = tk.GetNextToken();
            if (line.StartsWith(_T("WaterLevConstit")))
                  ParseFirstLine(line);
            else if (line.StartsWith(_T("!Observed")))
                  ParseSecondLine(line);
            else if (line.StartsWith(_T("03 Amplitude")))
                  ParseAmplitudeUnitLine(line);
            else if (line.StartsWith(_T("A0=")))
                  ParseAmplitudeValueLine(line);
            else if (!line.EndsWith(_T("||")))
                  ParseConstLine(line);
      }
}

//Produces the station header
//Format:
//# !units: meters
//# !longitude: 4.2710
//# !latitude: 51.3493
//ANVERS, BELGIQUE
//01:00 :Europe/Brussels
//2.6520 meters
wxString wlev::GetStationText()
{
      wxString s = wxEmptyString;
      s.Append(wxString::Format(_T("# !units: %s\n"), this->units.c_str()));
      s.Append(wxString::Format(_T("# !longitude: %.4f\n"), this->lon));
      s.Append(wxString::Format(_T("# !latitude: %.4f\n"), this->lat));
      s.Append(wxString::Format(_T("%s, COUNTRY\n"), this->station_name.c_str()));
      s.Append(wxString::Format(_T("%02d:00 :TZDEFINITION\n"), this->timezone));
      s.Append(wxString::Format(_T("%.4f %s\n"), this->amplitude, this->units.c_str()));
      s.Append(GetHCText(_T("J1")));
      s.Append(GetHCText(_T("K1")));
      s.Append(GetHCText(_T("K2")));
      s.Append(GetHCText(_T("L2")));
      s.Append(GetHCText(_T("M1")));
      s.Append(GetHCText(_T("M2")));
      s.Append(GetHCText(_T("M3")));
      s.Append(GetHCText(_T("M4")));
      s.Append(GetHCText(_T("M6")));
      s.Append(GetHCText(_T("M8")));
      s.Append(GetHCText(_T("N2")));
      s.Append(GetHCText(_T("2N2")));
      s.Append(GetHCText(_T("O1")));
      s.Append(GetHCText(_T("OO1")));
      s.Append(GetHCText(_T("P1")));
      s.Append(GetHCText(_T("Q1")));
      s.Append(GetHCText(_T("2Q1")));
      s.Append(GetHCText(_T("R2")));
      s.Append(GetHCText(_T("S1")));
      s.Append(GetHCText(_T("S2")));
      s.Append(GetHCText(_T("S4")));
      s.Append(GetHCText(_T("S6")));
      s.Append(GetHCText(_T("T2")));
      s.Append(GetHCText(_T("LDA2")));
      s.Append(GetHCText(_T("MU2")));
      s.Append(GetHCText(_T("NU2")));
      s.Append(GetHCText(_T("RHO1")));
      s.Append(GetHCText(_T("MK3")));
      s.Append(GetHCText(_T("2MK3")));
      s.Append(GetHCText(_T("MN4")));
      s.Append(GetHCText(_T("MS4")));
      s.Append(GetHCText(_T("2SM2")));
      s.Append(GetHCText(_T("MF")));
      s.Append(GetHCText(_T("MSF")));
      s.Append(GetHCText(_T("MM")));
      s.Append(GetHCText(_T("SA")));
      s.Append(GetHCText(_T("SSA")));
      s.Append(GetHCText(_T("SA-IOS")));
      s.Append(GetHCText(_T("MF-IOS")));
      s.Append(GetHCText(_T("S1-IOS")));
      s.Append(GetHCText(_T("OO1-IOS")));
      s.Append(GetHCText(_T("R2-IOS")));
      s.Append(GetHCText(_T("A7")));
      s.Append(GetHCText(_T("2MK5")));
      s.Append(GetHCText(_T("2MK6")));
      s.Append(GetHCText(_T("2MN2")));
      s.Append(GetHCText(_T("2MN6")));
      s.Append(GetHCText(_T("2MS6")));
      s.Append(GetHCText(_T("2NM6")));
      s.Append(GetHCText(_T("2SK5")));
      s.Append(GetHCText(_T("2SM6")));
      s.Append(GetHCText(_T("3MK7")));
      s.Append(GetHCText(_T("3MN8")));
      s.Append(GetHCText(_T("3MS2")));
      s.Append(GetHCText(_T("3MS4")));
      s.Append(GetHCText(_T("3MS8")));
      s.Append(GetHCText(_T("ALP1")));
      s.Append(GetHCText(_T("BET1")));
      s.Append(GetHCText(_T("CHI1")));
      s.Append(GetHCText(_T("H1")));
      s.Append(GetHCText(_T("H2")));
      s.Append(GetHCText(_T("KJ2")));
      s.Append(GetHCText(_T("ETA2")));
      s.Append(GetHCText(_T("KQ1")));
      s.Append(GetHCText(_T("UPS1")));
      s.Append(GetHCText(_T("M10")));
      s.Append(GetHCText(_T("M12")));
      s.Append(GetHCText(_T("MK4")));
      s.Append(GetHCText(_T("MKS2")));
      s.Append(GetHCText(_T("MNS2")));
      s.Append(GetHCText(_T("EPS2")));
      s.Append(GetHCText(_T("MO3")));
      s.Append(GetHCText(_T("MP1")));
      s.Append(GetHCText(_T("TAU1")));
      s.Append(GetHCText(_T("MPS2")));
      s.Append(GetHCText(_T("MSK6")));
      s.Append(GetHCText(_T("MSM")));
      s.Append(GetHCText(_T("MSN2")));
      s.Append(GetHCText(_T("MSN6")));
      s.Append(GetHCText(_T("NLK2")));
      s.Append(GetHCText(_T("NO1")));
      s.Append(GetHCText(_T("OP2")));
      s.Append(GetHCText(_T("OQ2")));
      s.Append(GetHCText(_T("PHI1")));
      s.Append(GetHCText(_T("KP1")));
      s.Append(GetHCText(_T("PI1")));
      s.Append(GetHCText(_T("TK1")));
      s.Append(GetHCText(_T("PSI1")));
      s.Append(GetHCText(_T("RP1")));
      s.Append(GetHCText(_T("S3")));
      s.Append(GetHCText(_T("SIG1")));
      s.Append(GetHCText(_T("SK3")));
      s.Append(GetHCText(_T("SK4")));
      s.Append(GetHCText(_T("SN4")));
      s.Append(GetHCText(_T("SNK6")));
      s.Append(GetHCText(_T("SO1")));
      s.Append(GetHCText(_T("SO3")));
      s.Append(GetHCText(_T("THE1")));
      s.Append(GetHCText(_T("2PO1")));
      s.Append(GetHCText(_T("2NS2")));
      s.Append(GetHCText(_T("MLN2S2")));
      s.Append(GetHCText(_T("2ML2S2")));
      s.Append(GetHCText(_T("SKM2")));
      s.Append(GetHCText(_T("2MS2K2")));
      s.Append(GetHCText(_T("MKL2S2")));
      s.Append(GetHCText(_T("M2(KS)2")));
      s.Append(GetHCText(_T("2SN(MK)2")));
      s.Append(GetHCText(_T("2KM(SN)2")));
      s.Append(GetHCText(_T("NO3")));
      s.Append(GetHCText(_T("2MLS4")));
      s.Append(GetHCText(_T("ML4")));
      s.Append(GetHCText(_T("N4")));
      s.Append(GetHCText(_T("SL4")));
      s.Append(GetHCText(_T("MNO5")));
      s.Append(GetHCText(_T("2MO5")));
      s.Append(GetHCText(_T("MSK5")));
      s.Append(GetHCText(_T("3KM5")));
      s.Append(GetHCText(_T("2MP5")));
      s.Append(GetHCText(_T("3MP5")));
      s.Append(GetHCText(_T("MNK5")));
      s.Append(GetHCText(_T("2NMLS6")));
      s.Append(GetHCText(_T("MSL6")));
      s.Append(GetHCText(_T("2ML6")));
      s.Append(GetHCText(_T("2MNLS6")));
      s.Append(GetHCText(_T("3MLS6")));
      s.Append(GetHCText(_T("2MNO7")));
      s.Append(GetHCText(_T("2NMK7")));
      s.Append(GetHCText(_T("2MSO7")));
      s.Append(GetHCText(_T("MSKO7")));
      s.Append(GetHCText(_T("2MSN8")));
      s.Append(GetHCText(_T("2(MS)8")));
      s.Append(GetHCText(_T("2(MN)8")));
      s.Append(GetHCText(_T("2MSL8")));
      s.Append(GetHCText(_T("4MLS8")));
      s.Append(GetHCText(_T("3ML8")));
      s.Append(GetHCText(_T("3MK8")));
      s.Append(GetHCText(_T("2MSK8")));
      s.Append(GetHCText(_T("2M2NK9")));
      s.Append(GetHCText(_T("3MNK9")));
      s.Append(GetHCText(_T("4MK9")));
      s.Append(GetHCText(_T("3MSK9")));
      s.Append(GetHCText(_T("4MN10")));
      s.Append(GetHCText(_T("3MNS10")));
      s.Append(GetHCText(_T("4MS10")));
      s.Append(GetHCText(_T("3MSL10")));
      s.Append(GetHCText(_T("3M2S10")));
      s.Append(GetHCText(_T("4MSK11")));
      s.Append(GetHCText(_T("4MNS12")));
      s.Append(GetHCText(_T("5MS12")));
      s.Append(GetHCText(_T("4MSL12")));
      s.Append(GetHCText(_T("4M2S12")));
      s.Append(GetHCText(_T("M1C")));
      s.Append(GetHCText(_T("3MKS2")));
      s.Append(GetHCText(_T("OQ2-HORN")));
      s.Append(GetHCText(_T("MSK2")));
      s.Append(GetHCText(_T("MSP2")));
      s.Append(GetHCText(_T("2MP3")));
      s.Append(GetHCText(_T("4MS4")));
      s.Append(GetHCText(_T("2MNS4")));
      s.Append(GetHCText(_T("2MSK4")));
      s.Append(GetHCText(_T("3MN4")));
      s.Append(GetHCText(_T("2MSN4")));
      s.Append(GetHCText(_T("3MK5")));
      s.Append(GetHCText(_T("3MO5")));
      s.Append(GetHCText(_T("3MNS6")));
      s.Append(GetHCText(_T("4MS6")));
      s.Append(GetHCText(_T("2MNU6")));
      s.Append(GetHCText(_T("3MSK6")));
      s.Append(GetHCText(_T("MKNU6")));
      s.Append(GetHCText(_T("3MSN6")));
      s.Append(GetHCText(_T("M7")));
      s.Append(GetHCText(_T("2MNK8")));
      s.Append(GetHCText(_T("2(MS)N10")));
      s.Append(_T("\n#\n"));
      return s;
}

//Produces the text line for a single harmonic constant
//Format:
//J1             0.0070  126.80
wxString wlev::GetHCText(wxString hc)
{
      HarmonicConstant c = this->hcs[hc];
      if (c.const_code == wxEmptyString) //not found
      {
            c.const_code = hc;
            c.angle = 0.0;
            c.frequency = 0.0;
            c.value = 0.0;
      }
      wxString s = wxString::Format(_T("%s%.4f  %06.2f\n"), c.const_code.Pad(15).Left(15).c_str(), c.value, c.angle);
      return s;
}
