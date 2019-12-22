#include <iostream>
#include "hash_table.h"

#include <string>
#include <ctime>
#include <chrono>
#include <random>
#include <iterator>
#include <chrono>
#include <fstream>

constexpr int TEST_COUNT = 10;

#define BOOST_TEST_MODULE test_main

#include <boost/test/included/unit_test.hpp>
using namespace std;

using namespace boost::unit_test;
BOOST_AUTO_TEST_SUITE(test_suite_main)

BOOST_AUTO_TEST_CASE(hash_table_with_chains_test)
{
    otus::HashTable<int, std::string> table;

    table.push(63, "alabama");
    table.push(103, "atata");
    table.push(73, "yohoho");
    table.push(503, "aloha");
    table.push(43, "newyork");
    table.push(83, "chicago");
    table.push(703, "lalala");
    table.push(203, "azaza");
    table.push(53, "losangeles");
    table.push(13, "idaho");
    table.push(33, "sacramento");
    table.push(113, "washington");
    table.push(123, "man");
    table.push(133, "arcanzas");
    table.push(55, "bibibi");
    table.push(87, "arrriva");
    table.push(18, "hmmmmmm");

    BOOST_CHECK_MESSAGE(table.get(63) == "alabama", "wrong value");
    BOOST_CHECK_MESSAGE(table.get(703) == "lalala", "wrong value");
    BOOST_CHECK_MESSAGE(table.get(53) == "losangeles", "wrong value");
    BOOST_CHECK_MESSAGE(table.get(55) == "bibibi", "wrong value");
}

BOOST_AUTO_TEST_SUITE_END()
