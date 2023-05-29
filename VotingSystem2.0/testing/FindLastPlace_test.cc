
#include <gtest/gtest.h>
#include "../src/include/IRBallot.h"
#include "../src/include/IRElection.h"
#include "../src/include/Candidate.h"
#include <iostream>
#include <vector>
#include <string>

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
using namespace std;
using namespace VotingSystem;

TEST(FindLastPlaceTest, NormalCase) {
  //multiple people, one has fewest
  vector<std::string> vect{"testing/IR_input_files/IR_FindLastPlace_Normal.csv"};
  IRElection Elect("Minnesota IR", vect, 0);
  Elect.readHeader(0);
  Elect.readBallots();
  Candidate *one = Elect.getCandidatesList()[0];
  Candidate *two = Elect.getCandidatesList()[1];
  Candidate *three = Elect.getCandidatesList()[2];
  ASSERT_EQ(Elect.findLastPlace(), three);
}
TEST(FindLastPlaceTest, TieCase) {
  //2 or more people tied for fewest votes
  vector<std::string> vect{"testing/IR_input_files/IR_FindLastPlace_Tie.csv"};
  IRElection Elect("Minnesota IR", vect, 0);
  Elect.readHeader(0);
  Elect.readBallots();
  Candidate *one = Elect.getCandidatesList()[0];
  Candidate *two = Elect.getCandidatesList()[1];
  Candidate *three = Elect.getCandidatesList()[2];
  Candidate *last = Elect.findLastPlace();
  EXPECT_TRUE(last == two || last == three);
}
