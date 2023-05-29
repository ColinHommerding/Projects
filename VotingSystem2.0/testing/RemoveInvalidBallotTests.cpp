
#include "MultiFilesTests.h"
#include "gtest/gtest.h"
#include "../src/include/IRElection.h"
#include "../src/include/Candidate.h"

//Test: Single IR input files , No invalid ballots.
TEST(RemoveInvalidBallotsTests, OneFileNoInvalid)
{
    std::vector<std::string> inputFile = {"testing/IR_input_files/IR_Invalid_NoBallots.csv"};
    VS::IRElection elect("MN", inputFile, 1);
    elect.run();
    std::vector<VS::Candidate *> cands = elect.getCandidatesList();
    std::vector<VS::Candidate *> winners = elect.getWinners();

    // Test total Ballots
    EXPECT_EQ(10, elect.getBallotNum());
    // Test winner
    EXPECT_EQ("Burns", winners[0]->getAbbrevName());
    EXPECT_EQ(6, winners[0]->getNumVotes());

    // Test vote distribution of candidates not eliminated
    EXPECT_EQ("Appleseed", cands[0]->getAbbrevName());
    EXPECT_FALSE(cands[0]->isEliminated());
    EXPECT_EQ(4, cands[0]->getNumVotes());

    // Test if audit and media files exist, and if so, remove them
    // so as not to clutter the directory
    TestAndRemoveFiles(&elect, 1);
}

//Test: Single IR input files , some invalid ballots.
TEST(RemoveInvalidBallotsTests, OneFileSomeInvalid)
{
    std::vector<std::string> inputFile = {"testing/IR_input_files/IR_Invalid_ManyBallots.csv"};
    VS::IRElection elect("MN", inputFile, 1);
    elect.run();
    std::vector<VS::Candidate *> cands = elect.getCandidatesList();
    std::vector<VS::Candidate *> winners = elect.getWinners();

    // Test total Ballots
    EXPECT_EQ(5, elect.getBallotNum());
    // Test winner
    EXPECT_EQ("Appleseed", winners[0]->getAbbrevName());


    // Test if audit and media files exist, and if so, remove them
    // so as not to clutter the directory
    TestAndRemoveFiles(&elect, 1);
}

//Test: Single IR input files , all invalid ballots.
TEST(RemoveInvalidBallotsTests, OneFileAllInvalid)
{
    std::vector<std::string> inputFile = {"testing/IR_input_files/IR_Invalid_AllBallots.csv"};
    VS::IRElection elect("MN", inputFile, 1);
    elect.run();
    std::vector<VS::Candidate *> cands = elect.getCandidatesList();
    std::vector<VS::Candidate *> winners = elect.getWinners();

    // Test total Ballots
    EXPECT_EQ(0, elect.getBallotNum());
    
    // Test if audit and media files exist, and if so, remove them
    // so as not to clutter the directory
    TestAndRemoveFiles(&elect, 0);
}

TEST(RemoveInvalidBallotsTests, EvenCandidates){
std::vector<std::string> inputFile = {"testing/IR_input_files/IR_Invalid_EvenCands.csv"};
    VS::IRElection elect("MN", inputFile, 1);
    elect.run();
    std::vector<VS::Candidate *> cands = elect.getCandidatesList();
    std::vector<VS::Candidate *> winners = elect.getWinners();

    // Test total Ballots
    EXPECT_EQ(6, elect.getBallotNum());
    // Test winner
    EXPECT_EQ("Charlie", winners[0]->getAbbrevName());


    // Test if audit and media files exist, and if so, remove them
    // so as not to clutter the directory
    TestAndRemoveFiles(&elect, 1);
}



//Test: Multi IR input files , all files have no invalid ballots.
TEST(RemoveInvalidBallotsTests, MultiInvalid)
{
    std::vector<std::string> inputFile = {"testing/IR_input_files/multiFiles/IR_Invalid_MultiFile1.csv",
                "testing/IR_input_files/multiFiles/IR_Invalid_MultiFile2.csv"};
    VS::IRElection elect("MN", inputFile, 1);
    elect.run();
    std::vector<VS::Candidate *> cands = elect.getCandidatesList();
    std::vector<VS::Candidate *> winners = elect.getWinners();

    // Test total Ballots
    EXPECT_EQ(10, elect.getBallotNum());
    // Test winner
    EXPECT_EQ("Appleseed", winners[0]->getAbbrevName());


    // Test if audit and media files exist, and if so, remove them
    // so as not to clutter the directory
    TestAndRemoveFiles(&elect, 1);
}

