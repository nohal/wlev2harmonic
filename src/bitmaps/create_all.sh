#!/bin/bash
#/******************************************************************************
# * $Id: *.sh,v 1.0 2012/04/21 01:54:37 nohal Exp $
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

# Require icotool from package icoutils
# Require convert from package ImageMagick
# Require inkscape

$path/other_svg_src/create_opencpn_main_icon.sh $path

