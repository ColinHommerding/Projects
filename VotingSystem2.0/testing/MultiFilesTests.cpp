
#include "gtest/gtest.h"
#include "../src/include/IRElection.h"
#include "../src/include/Candidate.h"
#include "../src/include/OPLElection.h"
#include <stdio.h>
#include <string>
#include <vector>

namespace VS = VotingSystem;

bool file_exists(std::string filename){
  std::ifstream f;
  f.open(filename, std::ifstream::in);
  bool isgood = f.good();
  f.close();
  return isgood;
}

void TestAndRemoveFiles(VS::Election *e, bool testExists) {
  // Find and store audit file name
  time_t date = e->getDate();
  char auditName[100];
  strftime(auditName, 100, "election_audit_%m_%d_%Y_%H%M%S.txt", localtime(&date));
  std::string audit(auditName);

  // Find and store media file name
  char mediaName[100];
  strftime(mediaName, 100, "election_media_MN_%m-%d-%Y_%I%M%S.txt", localtime(&date));
  std::string media(mediaName);
  
  // Test existence of audit and media files
  if (testExists) {
    EXPECT_TRUE(file_exists(audit));
    EXPECT_TRUE(file_exists(media));
  } else {
    EXPECT_FALSE(file_exists(audit));
    EXPECT_FALSE(file_exists(media));
  }

  // If files exist, delete them
  remove(auditName);
  remove(mediaName);
}

// Test for intended usage with 2 files and 20 files
TEST(MultiFilesTests, IRNormalUsageIdenticalContents) {
  std::vector<std::string> test2 = {"testing/IR_input_files/multiFiles/IR_MultiFiles1.csv",
				    "testing/IR_input_files/multiFiles/IR_MultiFiles2.csv"};
  // Run election with 2 files
  VS::IRElection elect("MN", test2, 1);
  elect.run();
  std::vector<VS::Candidate *> cands = elect.getCandidatesList();
  std::vector<VS::Candidate *> winners = elect.getWinners();
  
  // Test total Ballots
  EXPECT_EQ(20, elect.getBallotNum());
  // Test winner
  EXPECT_EQ("Burns", winners[0]->getAbbrevName());
  EXPECT_EQ(12, winners[0]->getNumVotes());

  // Test vote distribution of candidates not eliminated
  EXPECT_EQ("Appleseed", cands[0]->getAbbrevName());
  EXPECT_FALSE(cands[0]->isEliminated());
  EXPECT_EQ(8, cands[0]->getNumVotes());

  // Test if audit and media files exist, and if so, remove them
  // so as not to clutter the directory
  TestAndRemoveFiles(&elect, 1);



  std::vector<std::string> test20 = {"testing/IR_input_files/multiFiles/IR_MultiFiles1.csv",
				     "testing/IR_input_files/multiFiles/IR_MultiFiles2.csv",
				     "testing/IR_input_files/multiFiles/IR_MultiFiles3.csv",
				     "testing/IR_input_files/multiFiles/IR_MultiFiles4.csv",
				     "testing/IR_input_files/multiFiles/IR_MultiFiles5.csv",
				     "testing/IR_input_files/multiFiles/IR_MultiFiles6.csv",
				     "testing/IR_input_files/multiFiles/IR_MultiFiles7.csv",
				     "testing/IR_input_files/multiFiles/IR_MultiFiles8.csv",
				     "testing/IR_input_files/multiFiles/IR_MultiFiles9.csv",
				     "testing/IR_input_files/multiFiles/IR_MultiFiles10.csv",
				     "testing/IR_input_files/multiFiles/IR_MultiFiles11.csv",
				     "testing/IR_input_files/multiFiles/IR_MultiFiles12.csv",
				     "testing/IR_input_files/multiFiles/IR_MultiFiles13.csv",
				     "testing/IR_input_files/multiFiles/IR_MultiFiles14.csv",
				     "testing/IR_input_files/multiFiles/IR_MultiFiles15.csv",
				     "testing/IR_input_files/multiFiles/IR_MultiFiles16.csv",
				     "testing/IR_input_files/multiFiles/IR_MultiFiles17.csv",
				     "testing/IR_input_files/multiFiles/IR_MultiFiles18.csv",
				     "testing/IR_input_files/multiFiles/IR_MultiFiles19.csv",
				     "testing/IR_input_files/multiFiles/IR_MultiFiles20.csv"};
  
  // Run election with 20 files
  VS::IRElection elect2("MN", test20, 1);
  elect2.run();
  cands = elect2.getCandidatesList();
  winners = elect2.getWinners();
  
  // Test winner
  EXPECT_EQ("Burns", winners[0]->getAbbrevName());
  EXPECT_EQ(120, winners[0]->getNumVotes());

  // Test vote distribution of candidates not eliminated
  EXPECT_EQ("Appleseed", cands[0]->getAbbrevName());
  EXPECT_FALSE(cands[0]->isEliminated());
  EXPECT_EQ(80, cands[0]->getNumVotes());

  // Test if audit and media files exist, and if so, remove them
  // so as not to clutter the directory
  TestAndRemoveFiles(&elect2, 1);
}



// Test for intended usage with 2 files and 20 files
TEST(MultiFilesTests, OPLNormalUsageIdenticalContents) {
  std::vector<std::string> test2 = {"testing/OPL_input_files/multiFiles/OPL_MultiFiles1.csv",
				    "testing/OPL_input_files/multiFiles/OPL_MultiFiles2.csv"};
  // Run election with 2 files
  VS::OPLElection elect("MN", test2, 1);
  elect.run();
  std::vector<VS::Candidate *> cands = elect.getCandidatesList();
  std::vector<VS::Candidate *> winners = elect.getWinners();
  
  // Test winners
  EXPECT_EQ("Appleseed", winners[0]->getAbbrevName());
  EXPECT_EQ("Burns", winners[1]->getAbbrevName());
  EXPECT_EQ("Doe", winners[2]->getAbbrevName());
  EXPECT_EQ("Indy", winners[3]->getAbbrevName());

  // Test if audit and media files exist, and if so, remove them
  // so as not to clutter the directory
  TestAndRemoveFiles(&elect, 1);

  std::vector<std::string> test20 = {"testing/OPL_input_files/multiFiles/OPL_MultiFiles1.csv",
				     "testing/OPL_input_files/multiFiles/OPL_MultiFiles2.csv",
				     "testing/OPL_input_files/multiFiles/OPL_MultiFiles3.csv",
				     "testing/OPL_input_files/multiFiles/OPL_MultiFiles4.csv",
				     "testing/OPL_input_files/multiFiles/OPL_MultiFiles5.csv",
				     "testing/OPL_input_files/multiFiles/OPL_MultiFiles6.csv",
				     "testing/OPL_input_files/multiFiles/OPL_MultiFiles7.csv",
				     "testing/OPL_input_files/multiFiles/OPL_MultiFiles8.csv",
				     "testing/OPL_input_files/multiFiles/OPL_MultiFiles9.csv",
				     "testing/OPL_input_files/multiFiles/OPL_MultiFiles10.csv",
				     "testing/OPL_input_files/multiFiles/OPL_MultiFiles11.csv",
				     "testing/OPL_input_files/multiFiles/OPL_MultiFiles12.csv",
				     "testing/OPL_input_files/multiFiles/OPL_MultiFiles13.csv",
				     "testing/OPL_input_files/multiFiles/OPL_MultiFiles14.csv",
				     "testing/OPL_input_files/multiFiles/OPL_MultiFiles15.csv",
				     "testing/OPL_input_files/multiFiles/OPL_MultiFiles16.csv",
				     "testing/OPL_input_files/multiFiles/OPL_MultiFiles17.csv",
				     "testing/OPL_input_files/multiFiles/OPL_MultiFiles18.csv",
				     "testing/OPL_input_files/multiFiles/OPL_MultiFiles19.csv",
				     "testing/OPL_input_files/multiFiles/OPL_MultiFiles20.csv"};
  
  // Run election with 20 files
  VS::OPLElection elect2("MN", test20, 1);
  elect2.run();
  cands = elect2.getCandidatesList();
  winners = elect2.getWinners();
  
  // Test winners
  EXPECT_EQ("Appleseed", winners[0]->getAbbrevName());
  EXPECT_EQ("Burns", winners[1]->getAbbrevName());
  EXPECT_EQ("Doe", winners[2]->getAbbrevName());
  EXPECT_EQ("Indy", winners[3]->getAbbrevName());

  // Test if audit and media files exist, and if so, remove them
  // so as not to clutter the directory
  TestAndRemoveFiles(&elect2, 1);
}



// Test for intended usage with 3 files of differing ballot contents
TEST(MultiFilesTests, IRNormalUsageVariedBallotCounts) {
  std::vector<std::string> test = {"testing/IR_input_files/multiFiles/IR_MultiFiles1.csv",
				   "testing/IR_input_files/multiFiles/IR_MultiFilesDiffNum1.csv",
				   "testing/IR_input_files/multiFiles/IR_MultiFilesDiffNum2.csv"};
  // Run election with 2 files
  VS::IRElection elect("MN", test, 1);
  elect.run();
  std::vector<VS::Candidate *> cands = elect.getCandidatesList();
  std::vector<VS::Candidate *> winners = elect.getWinners();
  
  // Test winner
  EXPECT_EQ("Burns", winners[0]->getAbbrevName());
  EXPECT_EQ(9, winners[0]->getNumVotes());

  // Test vote distribution of candidates not eliminated
  EXPECT_EQ("Appleseed", cands[0]->getAbbrevName());
  EXPECT_FALSE(cands[0]->isEliminated());
  EXPECT_EQ(7, cands[0]->getNumVotes());

  // Test if audit and media files exist, and if so, remove them
  // so as not to clutter the directory
  TestAndRemoveFiles(&elect, 1);
}



// Test for intended usage with 3 files of differing ballot contents
TEST(MultiFilesTests, OPLNormalUsageVariedBallotCounts) {
  std::vector<std::string> test = {"testing/OPL_input_files/multiFiles/OPL_MultiFiles1.csv",
				   "testing/OPL_input_files/multiFiles/OPL_MultiFilesDiffNum1.csv",
				   "testing/OPL_input_files/multiFiles/OPL_MultiFilesDiffNum2.csv"};
  // Run election with 2 files
  VS::OPLElection elect("MN", test, 1);
  elect.run();
  std::vector<VS::Candidate *> cands = elect.getCandidatesList();
  std::vector<VS::Candidate *> winners = elect.getWinners();
  
  // Test winners
  EXPECT_EQ("Appleseed", winners[0]->getAbbrevName());
  EXPECT_EQ("Burns", winners[1]->getAbbrevName());
  EXPECT_EQ("Doe", winners[2]->getAbbrevName());
  EXPECT_EQ("Indy", winners[3]->getAbbrevName());

  // Test if audit and media files exist, and if so, remove them
  // so as not to clutter the directory
  TestAndRemoveFiles(&elect, 1);
}



// Test for correctness with one file with no ballots, and no files with ballots
TEST(MultiFilesTests, IRNormalUsageNoBallotFiles) {
  std::string header = "testing/IR_input_files/multiFiles/";
  std::vector<std::string> test = {header + "IR_MultiFiles1.csv",
				   header + "IR_MultiFiles2.csv",
				   header + "IR_MultiFilesNoBallots1.csv"};
  // Run election
  VS::IRElection elect("MN", test, 1);
  elect.run();
  std::vector<VS::Candidate *> cands = elect.getCandidatesList();
  std::vector<VS::Candidate *> winners = elect.getWinners();
  
  // Test winner
  EXPECT_EQ("Burns", winners[0]->getAbbrevName());
  EXPECT_EQ(12, winners[0]->getNumVotes());

  // Test vote distribution of candidates not eliminated
  EXPECT_EQ("Appleseed", cands[0]->getAbbrevName());
  EXPECT_FALSE(cands[0]->isEliminated());
  EXPECT_EQ(8, cands[0]->getNumVotes());

  // Test if audit and media files exist, and if so, remove them
  // so as not to clutter the directory
  TestAndRemoveFiles(&elect, 1);

  std::vector<std::string> test1 = {header + "IR_MultiFilesNoBallots1.csv",
  				    header + "IR_MultiFilesNoBallots2.csv",
  				    header + "IR_MultiFilesNoBallots3.csv"};
  // Run election
  VS::IRElection elect2("MN", test1, 1);
  elect2.run();
  // Test winner
  EXPECT_EQ(0, elect2.getBallotNum());

  // Test if audit and media files exist, and if so, remove them
  // so as not to clutter the directory
  TestAndRemoveFiles(&elect, 0);
}



// Test for correctness with one file with no ballots, and no files with ballots
TEST(MultiFilesTests, OPLNormalUsageNoBallotFiles) {
  std::string header = "testing/OPL_input_files/multiFiles/";
  std::vector<std::string> test = {header + "OPL_MultiFiles1.csv",
				   header + "OPL_MultiFiles2.csv",
				   header + "OPL_MultiFilesNoBallots1.csv"};
  // Run election
  VS::OPLElection elect("MN", test, 1);
  elect.run();
  std::vector<VS::Candidate *> cands = elect.getCandidatesList();
  std::vector<VS::Candidate *> winners = elect.getWinners();
  
  // Test winners
  EXPECT_EQ("Appleseed", winners[0]->getAbbrevName());
  EXPECT_EQ("Burns", winners[1]->getAbbrevName());
  EXPECT_EQ("Doe", winners[2]->getAbbrevName());
  EXPECT_EQ("Indy", winners[3]->getAbbrevName());;

  // Test if audit and media files exist, and if so, remove them
  // so as not to clutter the directory
  TestAndRemoveFiles(&elect, 1);

  std::vector<std::string> test1 = {header + "OPL_MultiFilesNoBallots1.csv",
  				    header + "OPL_MultiFilesNoBallots2.csv",
  				    header + "OPL_MultiFilesNoBallots3.csv"};
  // Run election
  VS::OPLElection elect2("MN", test1, 1);
  elect2.run();
  EXPECT_EQ(0,elect2.getBallotNum());
  

  // Test if audit and media files exist, and if so, remove them
  // so as not to clutter the directory
  TestAndRemoveFiles(&elect2, 0);
}



// TEST(MultiFilesTests, IRErrorMismatchElectionTypes) {
//   std::string IRheader = "testing/IR_input_files/multiFiles/";
//   std::string OPLheader = "testing/OPL_input_files/multiFiles/";
 
//   // Test first file wrong
//   std::vector<std::string> test = {OPLheader + "OPL_MultiFiles1.csv",
// 				   IRheader + "IR_MultiFiles1.csv",
// 				   IRheader + "IR_MultiFiles2.csv"};
//   // Run election
//   VS::IRElection elect("MN", test, 1);
//   elect.run();

//   // Test if audit and media files do not exist
//   TestAndRemoveFiles(&elect, 0);

//   // Test second file wrong
//   std::vector<std::string> test = {IRheader + "IR_MultiFiles1.csv",
// 				   OPLheader + "OPL_MultiFiles1.csv",
// 				   IRheader + "IR_MultiFiles2.csv"};
//   // Run election
//   VS::IRElection elect2("MN", test, 1);
//   elect2.run();

//   // Test if audit and media files do not exist
//   TestAndRemoveFiles(&elect2, 0);

//   // Test last file wrong
//   std::vector<std::string> test = {IRheader + "IR_MultiFiles1.csv",
// 				   IRheader + "IR_MultiFiles2.csv",
// 				   OPLheader + "OPL_MultiFiles1.csv"};
//   // Run election
//   VS::IRElection elect3("MN", test, 1);
//   elect3.run();

//   // Test if audit and media files do not exist
//   TestAndRemoveFiles(&elect3, 0);


//   // Test first file wrong
//   std::vector<std::string> test = {IRheader + "IR_MultiFiles1.csv",
// 				   OPLheader + "OPL_MultiFiles1.csv",
// 				   OPLheader + "OPL_MultiFiles2.csv"};
//   // Run election
//   VS::OPLElection elect4("MN", test, 1);
//   elect4.run();

//   // Test if audit and media files do not exist
//   TestAndRemoveFiles(&elect4, 0);

//   // Test second file wrong
//   std::vector<std::string> test = {OPLheader + "OPL_MultiFiles1.csv",
// 				   IRheader + "IR_MultiFiles1.csv",
// 				   OPLheader + "OPL_MultiFiles2.csv"};
//   // Run election
//   VS::OPLElection elect5("MN", test, 1);
//   elect5.run();

//   // Test if audit and media files do not exist
//   TestAndRemoveFiles(&elect5, 0);

//   // Test last file wrong
//   std::vector<std::string> test = {OPLheader + "OPL_MultiFiles1.csv",
// 				   OPLheader + "OPL_MultiFiles2.csv",
// 				   IRheader + "IR_MultiFiles1.csv"};
//   // Run election
//   VS::OPLElection elect6("MN", test, 1);
//   elect6.run();

//   // Test if audit and media files do not exist
//   TestAndRemoveFiles(&elect6, 0);
// }



TEST(MultiFilesTests, IRErrorMismatchNumCandidates) {
  std::string IRheader = "testing/IR_input_files/multiFiles/";
 
  // Test first file wrong
  std::vector<std::string> test = {IRheader + "IR_MultiFilesDiffNumCands.csv",
				   IRheader + "IR_MultiFiles1.csv",
				   IRheader + "IR_MultiFiles2.csv"};
  // Run election
  VS::IRElection elect("MN", test, 1);
  elect.run();

  // Test if audit and media files do not exist
  TestAndRemoveFiles(&elect, 0);

  // Test second file wrong
  test = {IRheader + "IR_MultiFiles1.csv",
	  IRheader + "IR_MultiFilesDiffNumCands.csv",
	  IRheader + "IR_MultiFiles2.csv"};
  // Run election
  VS::IRElection elect2("MN", test, 1);
  elect2.run();

  // Test if audit and media files do not exist
  TestAndRemoveFiles(&elect2, 0);

  // Test third file wrong
  test = {IRheader + "IR_MultiFiles1.csv",
	  IRheader + "IR_MultiFiles2.csv",
	  IRheader + "IR_MultiFilesDiffNumCands.csv"};
  // Run election
  VS::IRElection elect3("MN", test, 1);
  elect3.run();

  // Test if audit and media files do not exist
  TestAndRemoveFiles(&elect3, 0);
}



TEST(MultiFilesTests, OPLErrorMismatchNumCandidates) {
  std::string OPLheader = "testing/OPL_input_files/multiFiles/";
 
  // Test first file wrong
  std::vector<std::string> test = {OPLheader + "OPL_MultiFilesDiffNumCands.csv",
				   OPLheader + "OPL_MultiFiles1.csv",
				   OPLheader + "OPL_MultiFiles2.csv"};
  // Run election
  VS::OPLElection elect("MN", test, 1);
  elect.run();

  // Test if audit and media files do not exist
  TestAndRemoveFiles(&elect, 0);

  // Test second file wrong
  test = {OPLheader + "OPL_MultiFiles1.csv",
	  OPLheader + "OPL_MultiFilesDiffNumCands.csv",
	  OPLheader + "OPL_MultiFiles2.csv"};
  // Run election
  VS::OPLElection elect2("MN", test, 1);
  elect2.run();

  // Test if audit and media files do not exist
  TestAndRemoveFiles(&elect2, 0);

  // Test third file wrong
  test = {OPLheader + "OPL_MultiFiles1.csv",
	  OPLheader + "OPL_MultiFiles2.csv",
	  OPLheader + "OPL_MultiFilesDiffNumCands.csv"};
  // Run election
  VS::OPLElection elect3("MN", test, 1);
  elect3.run();

  // Test if audit and media files do not exist
  TestAndRemoveFiles(&elect3, 0);
}



TEST(MultiFilesTests, IRErrorMismatchCandidateNames) {
  std::string IRheader = "testing/IR_input_files/multiFiles/";
 
  // Test first file wrong
  std::vector<std::string> test = {IRheader + "IR_MultiFilesDiffCandName.csv",
				   IRheader + "IR_MultiFiles1.csv",
				   IRheader + "IR_MultiFiles2.csv"};
  // Run election
  VS::IRElection elect("MN", test, 1);
  elect.run();

  // Test if audit and media files do not exist
  TestAndRemoveFiles(&elect, 0);

  // Test second file wrong
  test = {IRheader + "IR_MultiFiles1.csv",
	  IRheader + "IR_MultiFilesDiffCandName.csv",
	  IRheader + "IR_MultiFiles2.csv"};
  // Run election
  VS::IRElection elect2("MN", test, 1);
  elect2.run();

  // Test if audit and media files do not exist
  TestAndRemoveFiles(&elect2, 0);

  // Test third file wrong
  test = {IRheader + "IR_MultiFiles1.csv",
	  IRheader + "IR_MultiFiles2.csv",
	  IRheader + "IR_MultiFilesDiffCandName.csv"};
  // Run election
  VS::IRElection elect3("MN", test, 1);
  elect3.run();

  // Test if audit and media files do not exist
  TestAndRemoveFiles(&elect3, 0);
}



TEST(MultiFilesTests, OPLErrorMismatchCandidateNames) {
  std::string OPLheader = "testing/OPL_input_files/multiFiles/";
 
  // Test first file wrong
  std::vector<std::string> test = {OPLheader + "OPL_MultiFilesDiffCandName.csv",
				   OPLheader + "OPL_MultiFiles1.csv",
				   OPLheader + "OPL_MultiFiles2.csv"};
  // Run election
  VS::OPLElection elect("MN", test, 1);
  elect.run();

  // Test if audit and media files do not exist
  TestAndRemoveFiles(&elect, 0);

  // Test second file wrong
  test = {OPLheader + "OPL_MultiFiles1.csv",
	  OPLheader + "OPL_MultiFilesDiffCandName.csv",
	  OPLheader + "OPL_MultiFiles2.csv"};
  // Run election
  VS::OPLElection elect2("MN", test, 1);
  elect2.run();

  // Test if audit and media files do not exist
  TestAndRemoveFiles(&elect2, 0);

  // Test third file wrong
  test = {OPLheader + "OPL_MultiFiles1.csv",
	  OPLheader + "OPL_MultiFiles2.csv",
	  OPLheader + "OPL_MultiFilesDiffCandName.csv"};
  // Run election
  VS::OPLElection elect3("MN", test, 1);
  elect3.run();

  // Test if audit and media files do not exist
  TestAndRemoveFiles(&elect3, 0);
}



TEST(MultiFilesTests, IRErrorMismatchCandidatesParty) {
  std::string IRheader = "testing/IR_input_files/multiFiles/";
 
  // Test first file wrong
  std::vector<std::string> test = {IRheader + "IR_MultiFilesDiffCandParty.csv",
				   IRheader + "IR_MultiFiles1.csv",
				   IRheader + "IR_MultiFiles2.csv"};
  // Run election
  VS::IRElection elect("MN", test, 1);
  elect.run();

  // Test if audit and media files do not exist
  TestAndRemoveFiles(&elect, 0);

  // Test second file wrong
  test = {IRheader + "IR_MultiFiles1.csv",
	  IRheader + "IR_MultiFilesDiffCandParty.csv",
	  IRheader + "IR_MultiFiles2.csv"};
  // Run election
  VS::IRElection elect2("MN", test, 1);
  elect2.run();

  // Test if audit and media files do not exist
  TestAndRemoveFiles(&elect2, 0);

  // Test third file wrong
  test = {IRheader + "IR_MultiFiles1.csv",
	  IRheader + "IR_MultiFiles2.csv",
	  IRheader + "IR_MultiFilesDiffCandParty.csv"};
  // Run election
  VS::IRElection elect3("MN", test, 1);
  elect3.run();

  // Test if audit and media files do not exist
  TestAndRemoveFiles(&elect3, 0);
}



TEST(MultiFilesTests, OPLErrorMismatchCandidatesParty) {
  std::string OPLheader = "testing/OPL_input_files/multiFiles/";
 
  // Test first file wrong
  std::vector<std::string> test = {OPLheader + "OPL_MultiFilesDiffCandParty.csv",
				   OPLheader + "OPL_MultiFiles1.csv",
				   OPLheader + "OPL_MultiFiles2.csv"};
  // Run election
  VS::OPLElection elect("MN", test, 1);
  elect.run();

  // Test if audit and media files do not exist
  TestAndRemoveFiles(&elect, 0);

  // Test second file wrong
  test = {OPLheader + "OPL_MultiFiles1.csv",
	  OPLheader + "OPL_MultiFilesDiffCandParty.csv",
	  OPLheader + "OPL_MultiFiles2.csv"};
  // Run election
  VS::OPLElection elect2("MN", test, 1);
  elect2.run();

  // Test if audit and media files do not exist
  TestAndRemoveFiles(&elect2, 0);

  // Test third file wrong
  test = {OPLheader + "OPL_MultiFiles1.csv",
	  OPLheader + "OPL_MultiFiles2.csv",
	  OPLheader + "OPL_MultiFilesDiffCandParty.csv"};
  // Run election
  VS::OPLElection elect3("MN", test, 1);
  elect3.run();

  // Test if audit and media files do not exist
  TestAndRemoveFiles(&elect3, 0);
}



TEST(MultiFilesTests, OPLErrorMismatchNumSeats) {
  std::string OPLheader = "testing/OPL_input_files/multiFiles/";
 
  // Test first file wrong
  std::vector<std::string> test = {OPLheader + "OPL_MultiFilesDiffNumSeats.csv",
				   OPLheader + "OPL_MultiFiles1.csv",
				   OPLheader + "OPL_MultiFiles2.csv"};
  // Run election
  VS::OPLElection elect("MN", test, 1);
  elect.run();

  // Test if audit and media files do not exist
  TestAndRemoveFiles(&elect, 0);

  // Test second file wrong
  test = {OPLheader + "OPL_MultiFiles1.csv",
	  OPLheader + "OPL_MultiFilesDiffNumSeats.csv",
	  OPLheader + "OPL_MultiFiles2.csv"};
  // Run election
  VS::OPLElection elect2("MN", test, 1);
  elect2.run();

  // Test if audit and media files do not exist
  TestAndRemoveFiles(&elect2, 0);

  // Test third file wrong
  test = {OPLheader + "OPL_MultiFiles1.csv",
	  OPLheader + "OPL_MultiFiles2.csv",
	  OPLheader + "OPL_MultiFilesDiffNumSeats.csv"};
  // Run election
  VS::OPLElection elect3("MN", test, 1);
  elect3.run();

  // Test if audit and media files do not exist
  TestAndRemoveFiles(&elect3, 0);
}
