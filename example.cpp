#include <iostream>

#include "time_window_helper.h"

#include "persek_protocol/str_helper.h"     // persek_protocol::StrHelper
#include "utils/boost_epoch.h"              // from_epoch_sec

std::string epoch_to_simple_string( uint32_t ts )
{
    return boost::posix_time::to_simple_string( from_epoch_sec( ts ) );
}

void test( const persek_protocol::TimeWindow & time_window, const persek_protocol::Weekdays & weekdays, uint32_t time )
{
    std::cout << "test: time window [ " <<  time_window << "], wd " << weekdays << ", time " << time << " (" << epoch_to_simple_string( time ) << ")\n";

    auto corrected  = time_window::get_next_fitting_time( time_window, weekdays, time );

    std::cout << "test: fit in time window: " << (( time == corrected ) ? "Y" : "N" )
            << ", time " << time << " (" << epoch_to_simple_string( time ) << ")\n"
            << ", corrected " << corrected << " (" << epoch_to_simple_string( corrected ) << ")\n";

}

int main()
{
    std::cout << "\n*********************************\n" << std::endl;

    uint32_t sun = 1505037600;  // Sun Sep 10 12:00:00 CEST 2017
    uint32_t mon = 1505124000;  // Mon Sep 11 12:00:00 CEST 2017

    return 0;
}
