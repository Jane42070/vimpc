/*
   Vimpc
   Copyright (C) 2010 Nathan Sweetman

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

   settings.cpp - handle configuration options via :set command
   */

#include "settings.hpp"

#include "dbc.hpp"

#include <stdlib.h>
#include <algorithm>
#include <sstream>

using namespace Main;


Settings & Settings::Instance()
{
   static Settings settings_;
   return settings_; 
}

Settings::Settings() :
   defaultWindow_(Ui::Screen::Console),
   autoScroll_   (false)
{
   settingsTable_["window"]       = &Settings::SetWindow;
   settingsTable_["autoscroll"]   = &Settings::SetAutoScroll;
   settingsTable_["noautoscroll"] = &Settings::SetNoAutoScroll;
}

Settings::~Settings()
{
}


void Settings::Set(std::string const & input)
{
   std::string       setting, arguments;
   std::stringstream settingStream(input);

   std::getline(settingStream, setting,   ' '); 
   std::getline(settingStream, arguments, '\n');

   if (settingsTable_.find(setting) != settingsTable_.end())
   {
      ptrToMember settingFunc = settingsTable_[setting];
      (*this.*settingFunc)(arguments);
   }
}


Ui::Screen::MainWindow Settings::Window() const
{
   return defaultWindow_;
}

void Settings::SetWindow(std::string const & arguments)
{
   std::string window(arguments);
   std::transform(window.begin(), window.end(), window.begin(), ::tolower);

   defaultWindow_ = Ui::Screen::GetWindowFromName(window);
}

bool Settings::AutoScroll() const
{
   return autoScroll_;
}

void Settings::SetAutoScroll(std::string const & arguments)
{
   autoScroll_ = true;    
}

void Settings::SetNoAutoScroll(std::string const & arguments)
{
   autoScroll_ = false;    
}