#define BOOST_TEST_MODULE ip_filter_test_module

#include "ip_class.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ip_filter_test)

BOOST_AUTO_TEST_CASE(ip_cmp_test)
{
    ip ip1 = {"10","2","3", "4"};
    ip ip2 = {"1","2","3", "4"};
    BOOST_CHECK(ip_cmp(ip2, ip1));

    ip1 = {"1","2","3", "4"};
    ip2 = {"1","2","3", "4"};
    BOOST_CHECK(!ip_cmp(ip2, ip1));

    ip1 = {"1","20","3", "4"};
    ip2 = {"1","2","3", "4"};
    BOOST_CHECK(ip_cmp(ip2, ip1));

    ip1 = {"1","2","3", "40"};
    ip2 = {"1","2","3", "4"};
    BOOST_CHECK(ip_cmp(ip2, ip1));

    ip1 = {"1","2","3", "4"};
    ip2 = {"1","20","3", "4"};
    BOOST_CHECK(!ip_cmp(ip2, ip1));
}

BOOST_AUTO_TEST_SUITE_END()
