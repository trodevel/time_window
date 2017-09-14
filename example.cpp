#include <iostream>

#include "time_window_helper.h"

#include "persek_protocol/str_helper.h"     // persek_protocol::StrHelper
#include "utils/boost_epoch.h"              // from_epoch_sec

std::string epoch_to_simple_string( uint32_t ts )
{
    return boost::posix_time::to_simple_string( from_epoch_sec( ts ) );
}

uint32_t get_next_fitting_time( const persek_protocol::TimeWindow & time_window, const persek_protocol::Weekdays & weekdays, uint32_t time )
{
    std::cout << "test: time window [" <<  time_window << "], wd " << weekdays << ", time " << time << " (" << epoch_to_simple_string( time ) << ")\n";

    auto corrected  = time_window::get_next_fitting_time( time_window, weekdays, time );

    std::cout << "test: fit in time window: " << ( ( time == corrected ) ? "Y" : "N" )
            << ", time " << time << " (" << epoch_to_simple_string( time ) << ")"
            << ", corrected " << corrected << " (" << epoch_to_simple_string( corrected ) << ")\n";

    return corrected;
}

const persek_protocol::TimeWindow & get_tw_whole_day()
{
    static const persek_protocol::TimeWindow res =
        {
                { 0, 0 }, { 23, 59 }
        };

    return res;
}

const persek_protocol::TimeWindow & get_tw_day_hours()
{
    static const persek_protocol::TimeWindow res =
        {
                { 9, 0 }, { 17, 00 }
        };

    return res;
}

const persek_protocol::Weekdays & get_wd_whole_week()
{
    static const persek_protocol::Weekdays res =
        {
            ( persek_protocol::Weekdays::weekdays_e::MO
            + persek_protocol::Weekdays::weekdays_e::TU
            + persek_protocol::Weekdays::weekdays_e::WE
            + persek_protocol::Weekdays::weekdays_e::TH
            + persek_protocol::Weekdays::weekdays_e::FR
            + persek_protocol::Weekdays::weekdays_e::SA
            + persek_protocol::Weekdays::weekdays_e::SU
            )
        };

    return res;
}

const persek_protocol::Weekdays & get_wd_work_week()
{
    static const persek_protocol::Weekdays res =
        {
            ( persek_protocol::Weekdays::weekdays_e::MO
            + persek_protocol::Weekdays::weekdays_e::TU
            + persek_protocol::Weekdays::weekdays_e::WE
            + persek_protocol::Weekdays::weekdays_e::TH
            + persek_protocol::Weekdays::weekdays_e::FR
            )
        };

    return res;
}

const persek_protocol::Weekdays & get_wd_work_week_2()
{
    static const persek_protocol::Weekdays res =
        {
            ( persek_protocol::Weekdays::weekdays_e::MO
            + persek_protocol::Weekdays::weekdays_e::TU
            + persek_protocol::Weekdays::weekdays_e::WE
            + persek_protocol::Weekdays::weekdays_e::TH
            + persek_protocol::Weekdays::weekdays_e::FR
            + persek_protocol::Weekdays::weekdays_e::SA
            )
        };

    return res;
}

const persek_protocol::Weekdays & get_wd_weekend()
{
    static const persek_protocol::Weekdays res =
        {
            ( persek_protocol::Weekdays::weekdays_e::SA
            + persek_protocol::Weekdays::weekdays_e::SU
            )
        };

    return res;
}


const persek_protocol::Weekdays & get_wd_some_days()
{
    static const persek_protocol::Weekdays res =
        {
            ( persek_protocol::Weekdays::weekdays_e::TU
            + persek_protocol::Weekdays::weekdays_e::TH
            )
        };

    return res;
}

void test( const persek_protocol::TimeWindow & time_window, const persek_protocol::Weekdays & weekdays, uint32_t time, const std::string & expected_res )
{
    auto expected_ptime = boost::posix_time::time_from_string( expected_res );

    auto expected_time = to_epoch( expected_ptime );

    auto res = get_next_fitting_time( time_window, weekdays, time );

    if( res == expected_time )
    {
        std::cout << "OK" << std::endl;
    }
    else
    {
        std::cout << "FAILED: expected " << epoch_to_simple_string( expected_time ) << ", got " << epoch_to_simple_string( res ) << std::endl;
    }
}



int main()
{
    std::cout << "\n*********************************\n" << std::endl;

    uint32_t sun = 1505037600;  // Sun Sep 10 12:00:00 CEST 2017
    uint32_t mon = 1505124000;  // Mon Sep 11 12:00:00 CEST 2017

    test( get_tw_whole_day(), get_wd_whole_week(),  sun, "2017-09-10 10:00:00" );
    test( get_tw_whole_day(), get_wd_work_week(),   sun, "2017-09-11 00:00:00" );
    test( get_tw_whole_day(), get_wd_work_week_2(), sun, "2017-09-11 00:00:00" );
    test( get_tw_whole_day(), get_wd_weekend(),     sun, "2017-09-10 00:00:00" );
    test( get_tw_whole_day(), get_wd_some_days(),   sun, "2017-09-12 00:00:00" );

    std::cout << "\n*********************************\n" << std::endl;

    test( get_tw_day_hours(), get_wd_whole_week(),  sun, "2017-09-10 10:00:00" );
    test( get_tw_day_hours(), get_wd_work_week(),   sun, "2017-09-11 09:00:00" );
    test( get_tw_day_hours(), get_wd_work_week_2(), sun, "2017-09-11 09:00:00" );
    test( get_tw_day_hours(), get_wd_weekend(),     sun, "2017-09-10 10:00:00" );
    test( get_tw_day_hours(), get_wd_some_days(),   sun, "2017-09-12 09:00:00" );

    return 0;
}
