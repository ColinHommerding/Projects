
#ifndef POELECTION_H
#define POELECTION_H

#include "Candidate.h"
#include "Ballot.h"
#include "Election.h"
#include <vector>
#include <iostream>
#include <istream>
#include <fstream>
#include <string>
namespace VotingSystem {

/**
 * @brief Class that handles Popularity Only Elections.
 *
 * The run() method is the main driver function and will be called from main after the
 * IRElection object is created.
 */
class POElection : public Election {  // make sure this extends election
  public:
    /**
    * @brief POElection constructor.
    * @param elName the name of the election
    * @param filenames_vec a vector of strings containing the names of all the input files
    * @param debug a integer that toggles non-deterministic mode
    *
    * Sets the name of the election and the vector containing all PO election input file names.
    */
  POElection(std::string elName, std::vector<std::string> filenames_vec, int debug);

  /**
   * @brief POElection destructor
   * @return void
   */
  ~POElection() {}

  /**
   * @brief inputFile getter
   * @return an ifstream object containing the input file
   */
  std::ifstream *getInputFile() { return &inputFile_; }

  /**
   * @brief auditFile getter
   * @return an ofstream object containing the audit file
   */
  std::ofstream *getAuditFile() { return &auditFile_; }

  /**
   * @brief Runs POElection
   * @return void
   *
   * Run is the main driver function, and makes all the needed function calls to
   * successfully run and log the election.
   */
  void run();

  /**
   * @brief check consistency header
   * @return bool
   *
   * return true if input files has the same header, false otherwise
   */
  bool check_header_consistency();

  /**
   * @brief Reads first four lines of input file
   * @return void
   *
   * readHeader is specific to POElection files. It parses the number of candidates,
   * number of ballots, and candidates from all of the input files, stores that info, calculates
   * any derived information like numBallotsToWin, and logs the Election Overview and
   * Candidates sections to the audit file.
   */
  void readHeader(int fileno);

  /**
   * @brief Verify input file information.
   * @return void
   *
   * Asks user to verify the candidates and election information by typing Y/N into the terminal.
   * Election calculation continues if Y, while audit file is deleted and program terminates if N.
   */
  void verifyInfo();

  /**
   * @brief Parse ballots
   * @param startID the value from which to start the ballot ID-ing from. Defaults at 0.
   * @return void
   *
   * Iterates through the rest of all of the PO election input files and creates a Ballot object with the proper
   * information for each line. Logs who each ballot voted for in the audit file.
   */
  void readBallots(int startID = 0);

  /**
   * @brief generateTermOutput is not written yet - but it will output text to the terminal with an overview of the election.
   */
  void generateTermOutput() {}

  /**
   * @brief generateMediaFile is not written yet - but it will create a media file with an overview of the election.
   */
  void generateMediaFile() {}

 private:
};
}  //  Namespace VotingSystem
#endif
