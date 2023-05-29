
#include "gtest/gtest.h"
#include "../src/include/POElection.h"
#include "../src/include/Candidate.h"
#include <stdio.h>
#include <string>
#include <vector>

namespace VS = VotingSystem;

// Test that PO parses files correctly with one input file
TEST(POElectionTests, PONormalUsageOneFile) {
  std::vector<std::string> test = {"testing/PO_input_files/PO_MultiFiles1.csv"};

  // Read POElection Header
  VS::POElection elect("MN", test, 1);
  elect.run();

  // Get each candidate
  std::vector<VS::Candidate*> cands = elect.getCandidatesList();

  // Check if each candidate is named and has the correct number of votes
  std::vector<std::string> names = {"Pike","Foster","Deutsch","Borg","Jones","Smith"};
  std::vector<std::string> parties = {"D","D","R","R","R","I"};
  std::vector<int> votes = {3,2,0,2,1,1};

  // Test all candidates have correct values
  for (int i = 0; i < cands.size(); i++) {
    EXPECT_EQ(names[i], cands[i]->getName());
    EXPECT_EQ(parties[i], cands[i]->getParty());
    EXPECT_EQ(votes[i], cands[i]->getNumVotes());
  }
}

// Test that PO parses files correctly with multiple input files
TEST(POElectionTests, PONormalUsageMultiFiles) {
  std::vector<std::string> test = {"testing/PO_input_files/PO_MultiFiles1.csv",
				   "testing/PO_input_files/PO_MultiFiles2.csv"};

  // Read POElection Header
  VS::POElection elect("MN", test, 1);
  elect.run();

  // Get each candidate
  std::vector<VS::Candidate*> cands = elect.getCandidatesList();

  // Check if each candidate is named and has the correct number of votes
  std::vector<std::string> names = {"Pike","Foster","Deutsch","Borg","Jones","Smith"};
  std::vector<std::string> parties = {"D","D","R","R","R","I"};
  std::vector<int> votes = {6,4,0,4,2,2};

  // Test all candidates have correct values
  for (int i = 0; i < cands.size(); i++) {
    EXPECT_EQ(names[i], cands[i]->getName());
    EXPECT_EQ(parties[i], cands[i]->getParty());
    EXPECT_EQ(votes[i], cands[i]->getNumVotes());
  }
}

// Test that election not run if there is an inconsistency in files
TEST(POElectionTests, POErrorDiffNumCands) {
  std::vector<std::string> test = {"testing/PO_input_files/PO_MultiFiles1.csv",
				   "testing/PO_input_files/PO_MultiFiles2.csv",
				   "testing/PO_input_files/PO_MultiFiles_inconsistent.csv"};

  // Read POElection Header
  VS::POElection elect("MN", test, 1);
  elect.run();

  // Get each candidate
  std::vector<VS::Candidate*> cands = elect.getCandidatesList();

  // Test that there are no candidates in the election, indicating not run
  EXPECT_EQ(0, cands.size());
}


TEST(POReadHeader, ReadHeaderCorrectly) {
  std::vector<std::string> test = {"testing/PO_input_files/PO_MultiFiles1.csv"};

  // Read POElection Header
  VS::POElection elect("MN", test, 1);
  elect.readHeader(0);
  EXPECT_EQ(9, elect.getBallotNum());
  EXPECT_EQ(6, elect.getCandidateNum());
}

TEST(POCheckHeaderConsistency, ConsistentHeaders) {
  std::vector<std::string> test = {"testing/PO_input_files/PO_MultiFiles1.csv", "testing/PO_input_files/PO_MultiFiles2.csv"};

  // Read POElection Header
  VS::POElection elect("MN", test, 1);
  EXPECT_EQ(true, elect.check_header_consistency());
}

TEST(POCheckHeaderConsistency, InconsistentHeaders) {
  std::vector<std::string> test = {"testing/PO_input_files/PO_MultiFiles_inconsistent1.csv", "testing/PO_input_files/PO_MultiFiles_inconsistent2.csv"};

  // Read POElection Header
  VS::POElection elect("MN", test, 1);
  EXPECT_EQ(false, elect.check_header_consistency());
}

TEST(POReadBallots, ReadBallotsCorrectly) {
  std::vector<std::string> test = {"testing/PO_input_files/PO_MultiFiles1.csv"};

  // Read POElection Header
  VS::POElection elect("MN", test, 1);
  elect.readHeader(0);
  elect.readBallots();
  EXPECT_EQ(9, elect.getBallotsList().size());
}


