
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

TEST(RunRunoffTest, BaseTest) {
  //normal election
  vector<std::string> vect{"testing/IR_input_files/IR_RunRunoff.csv"};
  IRElection Elect("Minnesota IR", vect, 0);
  Elect.readHeader(0);
  Elect.readBallots();
  Candidate *one = Elect.getCandidatesList()[0];
  Candidate *two = Elect.getCandidatesList()[1];
  Candidate *three = Elect.getCandidatesList()[2];
  Elect.findWinner();
  Elect.runRunoff();
  ASSERT_EQ(one->getNumVotes(), 3);
  ASSERT_EQ(two->getNumVotes(), 2);

  // Find and store audit file name
  time_t date = Elect.getDate();
  char auditName[100];
  strftime(auditName, 100, "election_audit_%m_%d_%Y_%H%M%S.txt", localtime(&date));
  // Remove resulting audit file
  remove(auditName);
}
