#!/bin/bash
#/******************************************************************************
# * $Id: *.sh,v 1.8 2012/04/21 01:54:37 nohal Exp $
# *
# * Project:  wlev2harmonic
# * Purpose:  helper shell script
# * Author:   Pavel Kalian
# *
# ***************************************************************************
# *   Copyright (C) 2012 by Pavel Kalian   *
# *   pavel@kalian.cz   *
# *                                                                         *
# *   This program is free software; you can redistribute it and/or modify  *
# *   it under the terms of the GNU General Public License as published by  *
# *   the Free Software Foundation; either version 2 of the License, or     *
# *   (at your option) any later version.                                   *
# *                                                                         *
# *   This program is distributed in the hope that it will be useful,       *
# *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
# *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
# *   GNU General Public License for more details.                          *
# *                                                                         *
# *   You should have received a copy of the GNU General Public License     *
# *   along with this program; if not, write to the                         *
# *   Free Software Foundation, Inc.,                                       *
# *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
# ***************************************************************************
# */

path=$(dirname $0)
output=$1

echo creating PNG icon
#convert to png
inkscape --without-gui --export-png=$path/wlev2harmonic_64x64.png --export-dpi=72 --export-background=rgb\(255,255,255\) --export-width=64 --export-height=64 $path/wlev2harmonic.svg >/dev/null
inkscape --without-gui --export-png=$path/wlev2harmonic_48x48.png --export-dpi=72 --export-background=rgb\(255,255,255\) --export-width=48 --export-height=48 $path/wlev2harmonic.svg >/dev/null
inkscape --without-gui --export-png=$path/wlev2harmonic_32x32.png --export-dpi=72 --export-background=rgb\(255,255,255\) --export-width=32 --export-height=32 $path/wlev2harmonic.svg >/dev/null
inkscape --without-gui --export-png=$path/wlev2harmonic_16x16.png --export-dpi=72 --export-background=rgb\(255,255,255\) --export-width=16 --export-height=16 $path/wlev2harmonic.svg >/dev/null

echo creating XPM icon
#convert to xpm
convert $path/wlev2harmonic_32x32.png $path/wlev2harmonic.xpm
#chang static char to static const char
sed 's/static char/static const char/' <$path/wlev2harmonic.xpm >$output/wlev2harmonic.xpm

echo creating ICO icon
#create ico
icotool -c -o $output/wlev2harmonic.ico $path/wlev2harmonic_64x64.png $path/wlev2harmonic_48x48.png $path/wlev2harmonic_32x32.png $path/wlev2harmonic_16x16.png

mv $path/wlev2harmonic_48x48.png $output/wlev2harmonic.png

rm $path/wlev2harmonic.xpm $path/wlev2harmonic_64x64.png $path/wlev2harmonic_32x32.png $path/wlev2harmonic_16x16.png

