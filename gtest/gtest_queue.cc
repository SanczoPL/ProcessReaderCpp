#include "gtest/gtest.h"
#include "gmock/gmock.h" 
#include "gtest_queue.h"
#include "../include/queue.h"

using ::testing::AtLeast;


TEST_F(Test_ProcessQueue, isEmpty)
{
    ProcessQueue * pQ = new ProcessQueue();
    EXPECT_EQ(pQ->isEmpty(), true);
    EXPECT_EQ(pQ->getCount(), 0);
    pQ->push_back(123,"123");
    EXPECT_EQ(pQ->isEmpty(), false);
    EXPECT_EQ(pQ->getCount(), 1);
    delete pQ;
}

TEST_F(Test_ProcessQueue, push_back)
{
	ProcessQueue * pQ = new ProcessQueue();
    EXPECT_EQ(pQ->isEmpty(), true);
    EXPECT_EQ(pQ->getCount(), 0);
    pQ->push_back(111,"111");
    pQ->push_back(111,"222");
    EXPECT_EQ(pQ->isEmpty(), false);
    EXPECT_EQ(pQ->getCount(), 2);
    delete pQ;
}


TEST_F(Test_ProcessQueue, pop_front)
{
	ProcessQueue * pQ = new ProcessQueue();
    EXPECT_EQ(pQ->isEmpty(), true);
    EXPECT_EQ(pQ->getCount(), 0);
    pQ->push_back(111,"111");
    pQ->push_back(111,"222");
    EXPECT_EQ(pQ->isEmpty(), false);
    EXPECT_EQ(pQ->getCount(), 2);

    pQ->pop_front();
    EXPECT_EQ(pQ->isEmpty(), false);
    EXPECT_EQ(pQ->getCount(), 1);
    pQ->pop_front();
    EXPECT_EQ(pQ->isEmpty(), true);
    EXPECT_EQ(pQ->getCount(), 0);

    delete pQ;
}

TEST_F(Test_ProcessQueue, findNameInQueue)
{
	ProcessQueue * pQ = new ProcessQueue();
    EXPECT_EQ(pQ->isEmpty(), true);
    EXPECT_EQ(pQ->getCount(), 0);
    pQ->push_back(111,"111");
    pQ->push_back(222,"222");
    EXPECT_EQ(pQ->isEmpty(), false);
    EXPECT_EQ(pQ->getCount(), 2);

    ProcessQueue * findQ = pQ->findNameInQueue("111");
    EXPECT_EQ(findQ->isEmpty(), false);
    EXPECT_EQ(findQ->getCount(), 1);
    delete pQ;
    delete findQ;
}

TEST_F(Test_ProcessQueue, findPidInQueue)
{
	ProcessQueue * pQ = new ProcessQueue();
    EXPECT_EQ(pQ->isEmpty(), true);
    EXPECT_EQ(pQ->getCount(), 0);
    pQ->push_back(111,"111");
    pQ->push_back(222,"222");
    EXPECT_EQ(pQ->isEmpty(), false);
    EXPECT_EQ(pQ->getCount(), 2);

    ProcessQueue * findQ = pQ->findPidInQueue(111);
    EXPECT_EQ(findQ->isEmpty(), false);
    EXPECT_EQ(findQ->getCount(), 1);
    delete pQ;
    delete findQ;
}


TEST_F(Test_ProcessQueue, printQueue)
{
	ProcessQueue * pQ = new ProcessQueue();
    EXPECT_EQ(pQ->isEmpty(), true);
    EXPECT_EQ(pQ->getCount(), 0);
    pQ->push_back(111,"111");
    pQ->push_back(222,"222");
    EXPECT_EQ(pQ->isEmpty(), false);
    EXPECT_EQ(pQ->getCount(), 2);

    pQ->printQueue();
    delete pQ;
}

TEST_F(Test_ProcessQueue, printNameFromQueue)
{
	ProcessQueue * pQ = new ProcessQueue();
    EXPECT_EQ(pQ->isEmpty(), true);
    EXPECT_EQ(pQ->getCount(), 0);
    pQ->push_back(111,"111");
    pQ->push_back(222,"222");
    EXPECT_EQ(pQ->isEmpty(), false);
    EXPECT_EQ(pQ->getCount(), 2);

    EXPECT_EQ(pQ->printNameFromQueue(), true);

    pQ->pop_front();
    EXPECT_EQ(pQ->isEmpty(), false);
    EXPECT_EQ(pQ->getCount(), 1);
    pQ->pop_front();
    EXPECT_EQ(pQ->isEmpty(), true);
    EXPECT_EQ(pQ->getCount(), 0);
    EXPECT_EQ(pQ->printNameFromQueue(), false);

    delete pQ;
}

TEST_F(Test_ProcessQueue, printPidFromQueue)
{
	ProcessQueue * pQ = new ProcessQueue();
    EXPECT_EQ(pQ->isEmpty(), true);
    EXPECT_EQ(pQ->getCount(), 0);
    pQ->push_back(111,"111");
    pQ->push_back(222,"222");
    EXPECT_EQ(pQ->isEmpty(), false);
    EXPECT_EQ(pQ->getCount(), 2);

    EXPECT_EQ(pQ->printPidFromQueue(), true);

    pQ->pop_front();
    EXPECT_EQ(pQ->isEmpty(), false);
    EXPECT_EQ(pQ->getCount(), 1);
    pQ->pop_front();
    EXPECT_EQ(pQ->isEmpty(), true);
    EXPECT_EQ(pQ->getCount(), 0);
    EXPECT_EQ(pQ->printPidFromQueue(), false);

    delete pQ;
}


TEST_F(Test_ProcessQueue, deleteQueue)
{
	ProcessQueue * pQ = new ProcessQueue();
    EXPECT_EQ(pQ->isEmpty(), true);
    EXPECT_EQ(pQ->getCount(), 0);
    pQ->push_back(111,"111");
    pQ->push_back(222,"222");
    EXPECT_EQ(pQ->isEmpty(), false);
    EXPECT_EQ(pQ->getCount(), 2);

    EXPECT_EQ(pQ->printPidFromQueue(), true);

    pQ->pop_front();
    EXPECT_EQ(pQ->isEmpty(), false);
    EXPECT_EQ(pQ->getCount(), 1);
    pQ->pop_front();
    EXPECT_EQ(pQ->isEmpty(), true);
    EXPECT_EQ(pQ->getCount(), 0);
    EXPECT_EQ(pQ->printPidFromQueue(), false);

    EXPECT_EQ(pQ->deleteQueue(), true);
}


