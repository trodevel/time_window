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

// $Revision: 9081 $ $Date:: 2018-05-04 #$ $Author: serge $

#include "Time.h"                   // self

namespace time_window
{

namespace tw
{

void init(
        Time  * res,
        uint32_t    y,
        uint32_t    m,
        uint32_t    d,

        basic_objects::Weekdays::weekdays_e   weekday,

        uint8_t     hh,
        uint8_t     mm,
        uint8_t     ss )
{
    res->y      = y;
    res->m      = m;
    res->d      = d;

    res->weekday    = weekday;

    res->hh     = hh;
    res->mm     = mm;
    res->ss     = ss;
}

} // namespace tw

} // namespace time_window
