/*
   Vimpc
   Copyright (C) 2010 - 2013 Nathan Sweetman

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

   nowplayingwindow.cpp - class representing a scrollable ncurses window
   */

#include "nowplayingwindow.hpp"

#include <iostream>

#include "clientstate.hpp"
#include "mpdclient.hpp"
#include "screen.hpp"

using namespace Ui;

NowPlayingWindow::NowPlayingWindow(Main::Settings const & settings, Ui::Screen & screen, Mpc::ClientState & clientState, std::string name) :
   ScrollWindow    (screen, name),
   clientState_    (clientState)
{
   Redraw();
}

NowPlayingWindow::~NowPlayingWindow()
{
}

void NowPlayingWindow::Print(uint32_t line) const
{
   if (line == 0)
   {
      WINDOW * window = N_WINDOW();

      for (unsigned int i = 0; i < screen_.MaxRows(); ++i)
      {
         mvwhline(window, i, 0, ' ', screen_.MaxColumns());
      }

      wprintw(window, "%d", clientState_.Stats()->artists_);
   }
}


void NowPlayingWindow::Redraw()
{
}
/* vim: set sw=3 ts=3: */
