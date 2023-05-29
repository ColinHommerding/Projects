
#include "include/Election.h"

namespace VS = VotingSystem;

unsigned int VS::Election::seed_ = time(NULL);

VS::Election::Election(std::string elName, std::vector<std::string> filenames_vec, int debug)
{
  winners_ = std::vector<VS::Candidate *>();
  party_ = std::vector<VS::OPLParty *>();
  electionDate_ = time(NULL);
  //inputFile_.open(filename);
  // Create audit file name
  char auditName[100];
  strftime(auditName, 100, "election_audit_%m_%d_%Y_%H%M%S.txt", localtime(&electionDate_));
  // convert auditName to std::string
  std::string audit(auditName);
  auditFile_.open(audit);
  numCandidates_ = 0;
  numBallots_ = 0;
  electionName_ = elName;
  electionType_ = "";
  candidatesList_ = std::vector<VS::Candidate *>();
  ballotsList_ = std::vector<VS::Ballot *>();
  debugMode_ = debug;
  numFiles_ = filenames_vec.size();
  filenames_ = filenames_vec;
}

VS::Election::~Election()
{
  //inputFile_.close();
  auditFile_.close();
}

void VS::Election::removeAuditFile()
{
  //remove auditFile
  char auditName[100];
  strftime(auditName, 100, "election_audit_%m_%d_%Y_%H%M%S.txt", localtime(&electionDate_));
  remove(auditName);
}

