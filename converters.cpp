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

// $Revision: 7819 $ $Date:: 2017-09-12 #$ $Author: serge $

#include "converters.h"     // self

#include "utils/boost_epoch.h"      // from_epoch_sec()

namespace time_window
{

namespace tw
{

persek_protocol::Weekdays::weekdays_e to_weekday( const boost::gregorian::greg_weekday & gwd )
{
    auto wd = gwd.as_enum();

    switch( wd )
    {
    case boost::gregorian::Monday:
        return persek_protocol::Weekdays::weekdays_e::MO;
    case boost::gregorian::Tuesday:
        return persek_protocol::Weekdays::weekdays_e::TU;
    case boost::gregorian::Wednesday:
        return persek_protocol::Weekdays::weekdays_e::WE;
    case boost::gregorian::Thursday:
        return persek_protocol::Weekdays::weekdays_e::TH;
    case boost::gregorian::Friday:
        return persek_protocol::Weekdays::weekdays_e::FR;
    case boost::gregorian::Saturday:
        return persek_protocol::Weekdays::weekdays_e::SA;
    case boost::gregorian::Sunday:
        return persek_protocol::Weekdays::weekdays_e::SU;
    default:
        break;
    }

    return persek_protocol::Weekdays::weekdays_e::MO;
}

Time  to_intern_time( uint32_t time )
{
    auto ptime  = from_epoch_sec( time );

    Time res;

    init( & res,
            ptime.date().year(),
            ptime.date().month(),
            ptime.date().day(),
            to_weekday( ptime.date().day_of_week() ),
            ptime.time_of_day().hours(),
            ptime.time_of_day().minutes(),
            ptime.time_of_day().seconds()
            );

    return res;
}

uint32_t to_epoch_time( const Time & time )
{
    boost::posix_time::ptime ptime( boost::gregorian::date( time.y, time.m, time.d ), boost::posix_time::time_duration( time.hh, time.mm, time.ss ) );

    return to_epoch( ptime );
}

Time & iterate( Time & time )
{
    boost::gregorian::date d( time.y, time.m, time.d );

    boost::gregorian::date_duration dd(1);

    auto new_date = d + dd;

    time.y  = new_date.year();
    time.m  = new_date.month();
    time.d  = new_date.day();

    return time;
}

} // namespace tw

} // namespace time_window
