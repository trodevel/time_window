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

// $Revision: 9081 $ $Date:: 2018-05-04 #$ $Author: serge $

#ifndef TIME_WINDOW__TIME_WINDOW_HELPER_H
#define TIME_WINDOW__TIME_WINDOW_HELPER_H

#include "basic_objects/basic_objects.h"    // TimeWindow

#include <boost/date_time/posix_time/posix_time_types.hpp>    // boost::posix_time::ptime, no i/o just types

namespace time_window
{

uint32_t get_next_fitting_time( const basic_objects::TimeWindow & tw, const basic_objects::Weekdays & wd, uint32_t time );
boost::posix_time::ptime get_next_fitting_time( const basic_objects::TimeWindow & tw, const basic_objects::Weekdays & wd, const boost::posix_time::ptime & time );


} // namespace time_window

#endif // TIME_WINDOW__TIME_WINDOW_HELPER_H
