/*

TimeWindow helpers.

Copyright (C) 2017 Sergey Kolevatov

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

*/

// $Revision: 7821 $ $Date:: 2017-09-12 #$ $Author: serge $

#ifndef TIME_WINDOW__TIME_WINDOW_HELPER_H
#define TIME_WINDOW__TIME_WINDOW_HELPER_H

#include "persek_protocol/persek_protocol.h"    // TimeWindow

namespace time_window
{

uint32_t get_next_fitting_time( const persek_protocol::TimeWindow & tw, const persek_protocol::Weekdays & wd, uint32_t time );

} // namespace time_window

#endif // TIME_WINDOW__TIME_WINDOW_HELPER_H
