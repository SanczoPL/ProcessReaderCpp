#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::AtLeast;


class Test_ProcessReader : public ::testing::Test {
protected:
	Test_ProcessReader(){}
	~Test_ProcessReader() override{}
	void SetUp() override{}
	void TearDown() override {}
};