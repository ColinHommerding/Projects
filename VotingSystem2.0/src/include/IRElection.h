
#ifndef IRELECTION_H
#define IRELECTION_H

#include "Candidate.h"
#include "Ballot.h"
#include "IRBallot.h"
#include "Election.h"
#include <vector>
#include <iostream>
#include <istream>
#include <fstream>
#include <string>
namespace VotingSystem {

/**
 * @brief Class that handles Instant Runoff Elections.
 *
 * The run() method is the main driver function and will be called from main after the
 * IRElection object is created.
 */
class IRElection : public Election {  // make sure this extends election
  public:
    /**
    * @brief IRElection constructor.
    * @param elName the name of the election
    * @param filenames_vec a vector of strings containing the names of all the input files
    * @param debug a integer that toggles non-deterministic mode
    *
    * Sets the name of the election and the vector containing all IR election input file names.
    */
  IRElection(std::string elName, std::vector<std::string> filenames_vec, int debug);

  /**
   * @brief IRElection destructor
   * @return void
   */
  ~IRElection() {}

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
   * @brief Runs IRElection
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
   * readHeader is specific to IRElection files. It parses the number of candidates,
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
   * Iterates through the rest of all of the IR election input files and creates a Ballot object with the proper
   * information for each line. Logs who each ballot voted for in the audit file.Includes calls to addRankedCandidates() and also distributeBallot() only if at least
   * half of the candidates on each ballot are ranked, as specified by the product owner.
   */
  void readBallots(int startID = 0);

  /**
   * @brief Writes to the audit file information about the ballots
   * @return void
   *
   * Writes the number of ballots cast, the IDs of each ballot, the number of votes needed to
   * to reach a majority, and a list of each ballot and its contents, to the audit file.
   **/
  void writeBallotsToAudit();

  /**
   * @brief Assigns ballot to candidate
   * @param ballot the IRBallot to be distributed
   * @return void
   *
   * Assigns the given IRBallot to its first choice candidate
   */
  void distributeBallot(IRBallot* ballot);

  /**
   * @brief Helper function for readBallot
   * @param ballot the IRBallot to add candiates into
   * @param places an int array representing a ballot's ranked choices, parsed from the input file
   * @param numUnranked an int representing how many candidates the ballot did not vote for
   * @return void
   *
   * Adds candidates to a ballot in the correct order (first choice added first, second choice
   * added second ... nth choice added nth).
   */
  void addRankedCandidates(IRBallot* ballot, int places[], int numUnranked);

  /**
   * @brief finds a winner given the current state of the election
   * @return a pointer to the winning candidate, if applicable
   *
   * Returns any candidate who has the majority of all votes. If only two candidates remain,
   * returns the candidate with more votes. If no winner can be called, returns nullptr. Logs
   * to the audit file the current round, the vote distribution in that round, and whether
   * a candidate has won or not.
   */
  Candidate* findWinner();

  /**
   * @brief Returns candidate in last place
   * @return void
   *
   * findLastPlace returns the candidate with the fewest votes, to be eliminated.
   * If multiple candidates have the fewest votes, randomly selects one of them.
   * Logs to the audit file which candidate was selected.
   */
  Candidate* findLastPlace();

  /**
   * @brief Eliminates last place candidate and redistributes votes
   * @return void
   *
   * Uses findLastPlace() and redistribute() functions to find the candidate in last place, marks
   * them as eliminated, and redistribute their votes to the remaining candidates.
   */
  void runRunoff();

  /**
   * @brief Redistributes votes of eliminated candidate
   * @param biggestLoser the candidate set to be eliminated from contention
   * @return void
   *
   * Takes a candidate and reassigns all of their ballots based on each ballots
   * next ranked candidate who is also not eliminated. If a ballot has no valid choices left,
   * that ballot is discarded. Logs to the audit file which ballots went to which candidates,
   * and which ballots were eliminated.
   */
  void redistribute(Candidate* biggestLoser);

  /**
   * @brief generateTermOutput is not written yet - but it will output text to the terminal with an overview of the election.
   */
  void generateTermOutput();

  /**
   * @brief generateMediaFile is not written yet - but it will create a media file with an overview of the election.
   */
  void generateMediaFile();

 private:
  /// number of votes a candidate must have to win by majority
  int numBallotsToWin_;
  /// the current round
  int roundNum_;
  /// the number of rounds needed to complete the election
  int numRounds_;
  /// the number of ballots that have been discarded
  int elimBallots_;
  /// the number of candidates that have not been eliminated
  int candidatesLeft_;
};
}  //  Namespace VotingSystem
#endif
