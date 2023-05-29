
#ifndef BALLOT_H_
#define BALLOT_H_

#include "Candidate.h"
#include <string>
#include <vector>

namespace VotingSystem {

/**
 * @brief A basic Ballot class
 *
 * Contains an ID integer, as well as a vector of Candidate pointers.
 * In IR, the candidates are meant to be ranked by the voter's preference.
 * In OPL, since the rules state each ballot only votes for one candidate,
 * the vector would only contain one entry.
 **/
class Ballot {
 public:
  /**
   * @brief Ballot constructor
   * @param id an integer which contains Ballot's ID. Intended to be unique to ballot
   * @return void
   *
   * Sets ballot's id_ attribute to id, and creates an empty rankedCandidates_ vector,
   * to store candidates 
   */
  Ballot(int id);
  /**
   * @brief Ballot destructor
   * @return void
   *
   * Does not delete the candidates in the candidates vector.
   */
  ~Ballot() {}

  /**
   * @brief Adds a candidate to the rankedCandidates_ vector
   * @param c a Candidate reference pointing to the candidate to be added
   * @return void
   *
   * The method will NOT add a candidate to rankedCandidates_ vector if the passed
   * in candidate's id already exists in the vector.
   */
  void addCandidate(Candidate *c);
  
  /**
   * @brief ID getter method
   * @return the ballot's ID
   */
  int getId() { return id_; }

  /**
   * @brief rankedCandidates_ getter method
   * @return the ballot's rankedCandidates_ vector
   */
  std::vector<Candidate*> getRankedCandidates() { return rankedCandidates_; }

 protected:
  /// An ID for the ballot, to be set at time of instantiation.
  int id_;
  /// List of candidates, ranked by voter's preference if applicable
  std::vector<Candidate*> rankedCandidates_; // rename to candidates_?
};

} // namespace VotingSystem
 
#endif  // BALLOT_H_
