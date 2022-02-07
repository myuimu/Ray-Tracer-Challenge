#include <boost/test/unit_test.hpp>
#include "canvas/canvas.h"
#include "ray.h"

using namespace ray;

BOOST_AUTO_TEST_SUITE(canvasTest)

/*-----CONSTRUCTOR TESTS-----*/

BOOST_AUTO_TEST_CASE(createBlankCanvas) {
    auto c = canvas(10, 20);

    BOOST_CHECK_EQUAL(c.getWidth(), 10);
    BOOST_CHECK_EQUAL(c.getHeight(), 20);
}

/*-----I/O TESTS-----*/

BOOST_AUTO_TEST_CASE(writeToCanvas) {
    auto c = canvas(10, 20);
    auto red = color(1, 0, 0);

    c.plot(2, 3, red);

    BOOST_CHECK_EQUAL(c.getPixel(2, 3), red);
}

BOOST_AUTO_TEST_CASE(canvasPpmHeader) {
    auto c = canvas(5, 3);

    std::stringstream ss;
    ss << c;

    std::string line;
    std::string testStrings[3] = {
        "P3",
        "5 3",
        "255"
    };
    for (int i = 0; i < 3; i++) {
        std::getline(ss, line);
        BOOST_CHECK_EQUAL(line, testStrings[i]);
    }
}

BOOST_AUTO_TEST_CASE(canvasPpmBody) {
    auto c = canvas(5, 3);
    auto c1 = color(1.5, 0, 0);
    auto c2 = color(0, 0.5, 0);
    auto c3 = color(-0.5, 0, 1);

    c.plot(0, 0, c1);
    c.plot(2, 1, c2);
    c.plot(4, 2, c3);

    std::stringstream ss;
    ss << c;

    std::string line;
    std::string testStrings[6] = {
        "P3",
        "5 3",
        "255",
        "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ",
        "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0 ",
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255 "
    };
    for (int i = 0; i < 6; i++) {
        std::getline(ss, line);
        BOOST_CHECK_EQUAL(line, testStrings[i]);
    }
}

BOOST_AUTO_TEST_CASE(ppmNoLineLongerThan70Characters) {
    auto c = canvas(10, 2, color(1, 0.8, 0.6));

    std::stringstream ss;
    ss << c;

    std::string line;
    std::string testStrings[7] = {
        "P3",
        "10 2",
        "255",
        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 ",
        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 ",
        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 ",
        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 "
    };
    for (int i = 0; i < 7; i++) {
        std::getline(ss, line);
        BOOST_CHECK_EQUAL(line, testStrings[i]);
    }
}

BOOST_AUTO_TEST_CASE(ppmEndsWithNewline) {
    auto c = canvas(5, 3);

    std::stringstream ss;
    ss << c;
    auto canvasString = ss.str();

    BOOST_CHECK_EQUAL(canvasString.at(canvasString.length() - 1), '\n');
}

BOOST_AUTO_TEST_SUITE_END()