
#include <gtest/gtest.h>
#include "../src/include/IRBallot.h"
#include "../src/include/IRElection.h"
#include "../src/include/Candidate.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace VotingSystem;
/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST(RedistributeTest, BaseRedistribute) {
  //Everyone has all choices ranked
  vector<std::string> vect{"testing/IR_input_files/IR_Redistribute_Base.csv"};
  IRElection Elect("Minnesota IR", vect, 0);
  Elect.readHeader(0);
  Elect.readBallots();
  Candidate *one = Elect.getCandidatesList()[0];
  Candidate *two = Elect.getCandidatesList()[1];
  Candidate *three = Elect.getCandidatesList()[2];
  one->setEliminate(0);
  Elect.redistribute(one);
  EXPECT_EQ(two->getNumVotes(), 2);
  EXPECT_EQ(three->getNumVotes(), 1);
}
TEST(RedistributeTest, OneRanked) {
  //all have only one choice ranked
  vector<std::string> vect{"testing/IR_input_files/IR_Redistribute_Ranked.csv"};
  IRElection Elect("Minnesota IR", vect, 0);
  Elect.readHeader(0);
  Elect.readBallots();
  Candidate *one = Elect.getCandidatesList()[0];
  Candidate *two = Elect.getCandidatesList()[1];
  Candidate *three = Elect.getCandidatesList()[2];
  one->setEliminate(0);
  Elect.redistribute(one);
  EXPECT_EQ(two->getNumVotes(), 2);
  EXPECT_EQ(three->getNumVotes(), 1);
}
