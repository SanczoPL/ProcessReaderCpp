#include "gtest/gtest.h"
#include "gmock/gmock.h" 
#include "gtest_processreader.h"
#include "../include/processreader.h"

using ::testing::AtLeast;


TEST_F(Test_ProcessReader, printProcess)
{
	std::string procDir = "bin";
	ProcessReader pr(procDir);
	EXPECT_EQ(pr.printProcess(), true);
}

TEST_F(Test_ProcessReader, checkIsDigit)
{
	std::string procDir = "bin";
	ProcessReader pr(procDir);
	EXPECT_EQ(pr.checkIsDigit("!23"), false);
	EXPECT_EQ(pr.checkIsDigit("123"), true);
}

TEST_F(Test_ProcessReader, showName)
{
	std::string procDir = "bin";
	ProcessReader pr(procDir);
	EXPECT_EQ(pr.printProcess(), true);
	std::string s1{"142804"};
	EXPECT_EQ(pr.showName(s1), true);
	std::string s2{"1234"};
	EXPECT_EQ(pr.showName(s2), false);
}

TEST_F(Test_ProcessReader, showPid)
{
	std::string procDir = "bin";
	ProcessReader pr(procDir);
	EXPECT_EQ(pr.printProcess(), true);
	std::string s1{"code"};
	EXPECT_EQ(pr.showPid(s1), true);
	std::string s2{"1234"};
	EXPECT_EQ(pr.showPid(s2), false);
}
