#include <iostream>

#include "time_window_helper.h"

#include "persek_protocol/str_helper.h"     // persek_protocol::StrHelper
#include "utils/boost_epoch.h"              // from_epoch_sec

std::string epoch_to_simple_string( uint32_t ts )
{
    return boost::posix_time::to_simple_string( from_epoch_sec( ts ) );
}

uint32_t to_epoch( const std::string & str )
{
    return to_epoch( boost::posix_time::time_from_string( str ) );
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

const persek_protocol::TimeWindow & get_tw_evening_hours()
{
    static const persek_protocol::TimeWindow res =
        {
                { 17, 0 }, { 23, 30 }
        };

    return res;
}

const persek_protocol::TimeWindow & get_tw_crossed_hours()
{
    static const persek_protocol::TimeWindow res =
        {
                { 17, 0 }, { 9, 0 }
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
            ( persek_protocol::Weekdays::weekdays_e::WE
            + persek_protocol::Weekdays::weekdays_e::FR
            )
        };

    return res;
}

void test( const persek_protocol::TimeWindow & time_window, const persek_protocol::Weekdays & weekdays, uint32_t time, uint32_t expected_time )
{
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


void test( const persek_protocol::TimeWindow & time_window, const persek_protocol::Weekdays & weekdays, const std::string & time_s, const std::string & expected_res_s )
{
    auto time           = to_epoch( time_s );
    auto expected_time  = to_epoch( expected_res_s );

    test( time_window, weekdays, time, expected_time );
}

int main()
{
    std::cout << "\n*********************************\n" << std::endl;

    std::string sun = "2017-09-10 10:00:00";    // Sun Sep 10 12:00:00 CEST 2017

    test( get_tw_whole_day(), get_wd_whole_week(),  sun, "2017-09-10 10:00:00" );
    test( get_tw_whole_day(), get_wd_work_week(),   sun, "2017-09-11 00:00:00" );
    test( get_tw_whole_day(), get_wd_work_week_2(), sun, "2017-09-11 00:00:00" );
    test( get_tw_whole_day(), get_wd_weekend(),     sun, "2017-09-10 10:00:00" );
    test( get_tw_whole_day(), get_wd_some_days(),   sun, "2017-09-13 00:00:00" );

    std::cout << "\n*********************************\n" << std::endl;

    test( get_tw_day_hours(), get_wd_whole_week(),  sun, "2017-09-10 10:00:00" );
    test( get_tw_day_hours(), get_wd_work_week(),   sun, "2017-09-11 09:00:00" );
    test( get_tw_day_hours(), get_wd_work_week_2(), sun, "2017-09-11 09:00:00" );
    test( get_tw_day_hours(), get_wd_weekend(),     sun, "2017-09-10 10:00:00" );
    test( get_tw_day_hours(), get_wd_some_days(),   sun, "2017-09-13 09:00:00" );

    std::cout << "\n*********************************\n" << std::endl;

    test( get_tw_evening_hours(), get_wd_whole_week(),  sun, "2017-09-10 17:00:00" );
    test( get_tw_evening_hours(), get_wd_work_week(),   sun, "2017-09-11 17:00:00" );
    test( get_tw_evening_hours(), get_wd_work_week_2(), sun, "2017-09-11 17:00:00" );
    test( get_tw_evening_hours(), get_wd_weekend(),     sun, "2017-09-10 17:00:00" );
    test( get_tw_evening_hours(), get_wd_some_days(),   sun, "2017-09-13 17:00:00" );

    std::cout << "\n*********************************\n" << std::endl;

    test( get_tw_crossed_hours(), get_wd_whole_week(),  sun, "2017-09-10 17:00:00" );
    test( get_tw_crossed_hours(), get_wd_work_week(),   sun, "2017-09-11 00:00:00" );
    test( get_tw_crossed_hours(), get_wd_work_week_2(), sun, "2017-09-11 00:00:00" );
    test( get_tw_crossed_hours(), get_wd_weekend(),     sun, "2017-09-10 17:00:00" );
    test( get_tw_crossed_hours(), get_wd_some_days(),   sun, "2017-09-13 00:00:00" );

    std::cout << "\n*********************************\n" << std::endl;
    std::cout << "\n*********************************\n" << std::endl;

    std::string mon = "2017-09-11 10:00:00";    // Mon Sep 11 12:00:00 CEST 2017

    test( get_tw_whole_day(), get_wd_whole_week(),  mon, "2017-09-11 10:00:00" );
    test( get_tw_whole_day(), get_wd_work_week(),   mon, "2017-09-11 10:00:00" );
    test( get_tw_whole_day(), get_wd_work_week_2(), mon, "2017-09-11 10:00:00" );
    test( get_tw_whole_day(), get_wd_weekend(),     mon, "2017-09-16 00:00:00" );
    test( get_tw_whole_day(), get_wd_some_days(),   mon, "2017-09-13 00:00:00" );

    std::cout << "\n*********************************\n" << std::endl;

    test( get_tw_day_hours(), get_wd_whole_week(),  mon, "2017-09-11 10:00:00" );
    test( get_tw_day_hours(), get_wd_work_week(),   mon, "2017-09-11 10:00:00" );
    test( get_tw_day_hours(), get_wd_work_week_2(), mon, "2017-09-11 10:00:00" );
    test( get_tw_day_hours(), get_wd_weekend(),     mon, "2017-09-16 09:00:00" );
    test( get_tw_day_hours(), get_wd_some_days(),   mon, "2017-09-13 09:00:00" );

    std::cout << "\n*********************************\n" << std::endl;

    test( get_tw_evening_hours(), get_wd_whole_week(),  mon, "2017-09-11 17:00:00" );
    test( get_tw_evening_hours(), get_wd_work_week(),   mon, "2017-09-11 17:00:00" );
    test( get_tw_evening_hours(), get_wd_work_week_2(), mon, "2017-09-11 17:00:00" );
    test( get_tw_evening_hours(), get_wd_weekend(),     mon, "2017-09-16 17:00:00" );
    test( get_tw_evening_hours(), get_wd_some_days(),   mon, "2017-09-13 17:00:00" );

    std::cout << "\n*********************************\n" << std::endl;

    test( get_tw_crossed_hours(), get_wd_whole_week(),  mon, "2017-09-11 17:00:00" );
    test( get_tw_crossed_hours(), get_wd_work_week(),   mon, "2017-09-11 17:00:00" );
    test( get_tw_crossed_hours(), get_wd_work_week_2(), mon, "2017-09-11 17:00:00" );
    test( get_tw_crossed_hours(), get_wd_weekend(),     mon, "2017-09-16 00:00:00" );
    test( get_tw_crossed_hours(), get_wd_some_days(),   mon, "2017-09-13 00:00:00" );

    std::cout << "\n*********************************\n" << std::endl;
    std::cout << "\n*********************************\n" << std::endl;

    std::string sun2 = "2017-09-10 18:00:00";    // Sun Sep 10 12:00:00 CEST 2017

    test( get_tw_day_hours(), get_wd_whole_week(),  sun2, "2017-09-11 09:00:00" );

    return 0;
}
