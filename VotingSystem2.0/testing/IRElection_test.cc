
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

TEST(IRElectionTest, NormalConstructor) {
  vector<std::string> vect{"testing/IR_input_files/IR_FindWinner_MajorityWin.csv"};
  IRElection Elect("MN", vect, 0);
  ASSERT_EQ("MN", Elect.getName());
  ASSERT_TRUE(Elect.getInputFile()->good());
  ASSERT_TRUE(Elect.getAuditFile()->good());
}
