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

// $Revision: 7852 $ $Date:: 2017-09-18 #$ $Author: serge $

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

bool operator==( const Time & time, const persek_protocol::Weekdays & tw )
{
    return tw.mask & time.weekday;
}

bool operator==( const Time & time, const persek_protocol::TimePoint24 & tw )
{
    if( time.hh != tw.hh )
        return false;

    if( time.mm != tw.mm )
        return false;

    return true;
}

bool operator<( const Time & time, const persek_protocol::TimePoint24 & tw )
{
    if( time.hh < tw.hh )
        return true;

    if( time.hh == tw.hh )
    {
        if( time.mm < tw.mm )
            return true;
    }

    return false;
}

bool operator>( const Time & time, const persek_protocol::TimePoint24 & tw )
{
    if( time.hh > tw.hh )
        return true;

    if( time.hh == tw.hh )
    {
        if( time.mm > tw.mm )
            return true;
    }

    return false;
}

bool operator<=( const Time & time, const persek_protocol::TimePoint24 & tw )
{
    if( time.hh < tw.hh )
        return true;

    if( time.hh == tw.hh )
    {
        if( time.mm <= tw.mm )
            return true;
    }

    return false;
}

bool operator>=( const Time & time, const persek_protocol::TimePoint24 & tw )
{
    if( time.hh > tw.hh )
        return true;

    if( time.hh == tw.hh )
    {
        if( time.mm >= tw.mm )
            return true;
    }

    return false;
}

bool operator< ( const persek_protocol::TimePoint24 & lhs, const persek_protocol::TimePoint24 & rhs )
{
    if( lhs.hh < rhs.hh )
        return true;

    if( lhs.hh == rhs.hh )
    {
        if( lhs.mm < rhs.mm )
            return true;
    }

    return false;
}

TimeWindowComp compare_norm( const persek_protocol::TimeWindow & tw, const Time & time )
{
    if( time < tw.from )
        return TimeWindowComp::BEFORE;

    if( time > tw.to )
        return TimeWindowComp::AFTER;

    return TimeWindowComp::FIT;
}

TimeWindowComp compare_crossed( const persek_protocol::TimeWindow & tw, const Time & time )
{
    if( time >= tw.from )
        return TimeWindowComp::FIT;

    if( time <= tw.to )
        return TimeWindowComp::FIT;

    return TimeWindowComp::BEFORE;
}

bool tw_is_crossed( const persek_protocol::TimeWindow & tw )
{
    return tw.to < tw.from;
}

TimeWindowComp compare( const persek_protocol::TimeWindow & tw, const Time & time, bool is_crossed )
{
    if( is_crossed )
        return compare_crossed( tw, time );

    return compare_norm( tw, time );
}

bool fit_in_weekdays( const persek_protocol::Weekdays & wd, const Time & time )
{
    return time == wd;
}

Time get_next_fitting_date( const persek_protocol::Weekdays & wd, const Time & time )
{
    Time res    = time;

    do
    {
        iterate( res );
    } while( fit_in_weekdays( wd, res ) == false );

    return res;
}

void apply_next_day_window_from_time( Time * res, const persek_protocol::TimeWindow & tw, bool is_crossed )
{
    if( is_crossed )
    {
        res->hh  = 0;
        res->mm  = 0;
    }
    else
    {
        res->hh  = tw.from.hh;
        res->mm  = tw.from.mm;
    }
}

Time get_next_fitting_time( const persek_protocol::TimeWindow & tw, const persek_protocol::Weekdays & wd, const Time & time )
{
    auto is_crossed = tw_is_crossed( tw );

    if( fit_in_weekdays( wd, time ) )
    {
        if( compare( tw, time, is_crossed ) == TimeWindowComp::FIT )
        {
            return time;
        }
        else if( compare( tw, time, is_crossed ) == TimeWindowComp::BEFORE )
        {
            Time res = time;

            res.hh  = tw.from.hh;
            res.mm  = tw.from.mm;

            return res;
        }
        //else if( compare( tw, time ) == TimeWindowComp::AFTER )
    }

    Time res = get_next_fitting_date( wd, time );

    apply_next_day_window_from_time( & res, tw, is_crossed );

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
