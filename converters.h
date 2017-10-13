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

// $Revision: 8018 $ $Date:: 2017-10-11 #$ $Author: serge $

#ifndef TIME_WINDOW__CONVERTERS_H
#define TIME_WINDOW__CONVERTERS_H

#include "Time.h"               // Time

#include <boost/date_time/gregorian/gregorian_types.hpp>    // boost::gregorian::greg_weekday
#include <boost/date_time/posix_time/posix_time_types.hpp>  // boost::posix_time::ptime, no i/o just types

namespace time_window
{

namespace tw
{

persek_protocol::Weekdays::weekdays_e to_weekday( const boost::gregorian::greg_weekday & gwd );

Time  to_intern_time( uint32_t time );
Time  to_intern_time( const boost::posix_time::ptime & time );
uint32_t to_epoch_time( const Time & time );
boost::posix_time::ptime to_ptime( const Time & time );
Time & iterate( Time & time );

}

} // namespace time_window

#endif // TIME_WINDOW__CONVERTERS_H
