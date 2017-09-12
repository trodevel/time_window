/*

Time.

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

// $Revision: 7818 $ $Date:: 2017-09-12 #$ $Author: serge $

#ifndef TIME_WINDOW__TIME_H
#define TIME_WINDOW__TIME_H

#include "persek_protocol/persek_protocol.h"    // persek_protocol::Weekdays

namespace time_window
{

namespace tw
{

struct Time
{
    uint32_t    y;
    uint32_t    m;
    uint32_t    d;

    persek_protocol::Weekdays::weekdays_e   weekday;

    uint8_t     hh;
    uint8_t     mm;
    uint8_t     ss;
};


void init(
        Time  * res,
        uint32_t    y,
        uint32_t    m,
        uint32_t    d,

        persek_protocol::Weekdays::weekdays_e   weekday,

        uint8_t     hh,
        uint8_t     mm,
        uint8_t     ss );

} // namespace tw

} // namespace time_window

#endif // TIME_WINDOW__TIME_H
