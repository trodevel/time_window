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

// $Revision: 7822 $ $Date:: 2017-09-12 #$ $Author: serge $

#include "time_window_helper.h"     // self

#include "converters.h"             // to_intern_time()

namespace time_window
{

namespace tw
{

enum class TimeWindowComp
{
    BEFORE,
    FIT,
    AFTER
};

TimeWindowComp compare( const persek_protocol::Weekdays & tw, const Time & time )
{
    if( tw.mask & time.weekday )
        return TimeWindowComp::FIT;

    return TimeWindowComp::AFTER;
}

TimeWindowComp compare( const persek_protocol::TimePoint24 & tw, const Time & time )
{
    if( time.hh < tw.hh )
        return TimeWindowComp::BEFORE;

    if( time.hh > tw.hh )
        return TimeWindowComp::AFTER;

    //if( time.hh == tw.hh )
    {
        if( time.mm < tw.mm )
            return TimeWindowComp::BEFORE;
        if( time.mm > tw.mm )
            return TimeWindowComp::AFTER;

        return TimeWindowComp::FIT;
    }
}

TimeWindowComp compare( const persek_protocol::TimeWindow & tw, const Time & time )
{
    if( compare( tw.from, time ) == TimeWindowComp::BEFORE )
        return TimeWindowComp::BEFORE;

    if( compare( tw.to, time ) == TimeWindowComp::AFTER )
        return TimeWindowComp::AFTER;

    return TimeWindowComp::FIT;
}

bool fit_in_time_window( const persek_protocol::TimeWindow & tw, const Time & time )
{
    return compare( tw, time ) == TimeWindowComp::FIT;
}

bool fit_in_weekdays( const persek_protocol::Weekdays & wd, const Time & time )
{
    return compare( wd, time ) == TimeWindowComp::FIT;
}

Time get_next_fitting_date( const persek_protocol::Weekdays & wd, const Time & time )
{
    Time res    = time;

    while( fit_in_weekdays( wd, res ) == false )
    {
        iterate( res );
    }

    return res;
}

Time get_next_fitting_time( const persek_protocol::TimeWindow & tw, const persek_protocol::Weekdays & wd, const Time & time )
{
    if( fit_in_weekdays( wd, time ) )
    {
        if( compare( tw, time ) == TimeWindowComp::FIT )
        {
            return time;
        }
        else if( compare( tw, time ) == TimeWindowComp::BEFORE )
        {
            Time res = time;

            res.hh  = tw.from.hh;
            res.mm  = tw.from.mm;

            return res;
        }
        //else if( compare( tw, time ) == TimeWindowComp::AFTER )
    }

    Time res = get_next_fitting_date( wd, time );

    res.hh  = tw.from.hh;
    res.mm  = tw.from.mm;

    return res;
}

} // namespace tw

uint32_t get_next_fitting_time( const persek_protocol::TimeWindow & tw, const persek_protocol::Weekdays & wd, uint32_t time )
{
    auto ptime  = tw::to_intern_time( time );

    auto res    = tw::get_next_fitting_time( tw, wd, ptime );

    return tw::to_epoch_time( res );
}

} // namespace time_window
