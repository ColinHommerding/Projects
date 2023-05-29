
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

TEST(FindWinnerTest, MajorityWin) {
  //multiple people, one has more than 50%
  vector<std::string> vect{"testing/IR_input_files/IR_FindWinner_MajorityWin.csv"};
  IRElection Elect("Minnesota IR", vect, 0);
  Elect.readHeader(0);
  Elect.readBallots();
  Candidate *one = Elect.getCandidatesList()[0];
  Candidate *two = Elect.getCandidatesList()[1];
  Candidate *three = Elect.getCandidatesList()[2];
  ASSERT_EQ(Elect.findWinner(), one);
}
TEST(FindWinnerTest, PopularityWin) {
  //has to be 2 people
  vector<std::string> vect{"testing/IR_input_files/IR_FindWinner_PopularityWin.csv"};
  IRElection Elect("Minnesota IR", vect, 0);
  Elect.readHeader(0);
  Elect.readBallots();
  Candidate *one = Elect.getCandidatesList()[0];
  Candidate *two = Elect.getCandidatesList()[1];
  ASSERT_EQ(Elect.findWinner(), one);
}
TEST(FindWinnerTest, PopularityTie) {
  //2 people tied and it comes down to popularity
  //has to be 2 people
  vector<std::string> vect{"testing/IR_input_files/IR_FindWinner_PopularityTie.csv"};
  IRElection Elect("Minnesota IR", vect, 0);
  Elect.readHeader(0);
  Elect.readBallots();
  Candidate *one = Elect.getCandidatesList()[0];
  Candidate *two = Elect.getCandidatesList()[1];
  Candidate *win = Elect.findWinner();
  EXPECT_TRUE(win == one || win == two);
}
