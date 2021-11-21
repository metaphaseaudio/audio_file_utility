/*
 * AllTests.cpp
 *      Author: Matt Zapp
 */
#include <gtest/gtest.h>
#include <meta/testing/TestingJUCEContextHandler.h>


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    meta::TestingJUCEContextHandler juce_context_handler;
	const auto result = RUN_ALL_TESTS();
	return result;
}
