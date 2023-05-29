
#ifndef IRBALLOT_H_
#define IRBALLOT_H_

#include "Ballot.h"
#include <string>
#include <vector>

namespace VotingSystem {

/**
 * @brief A basic IRBallot class that inherits from Ballot
 *
 * Contains an ID integer, as well as a vector of Candidate pointers.
 * In IR, the candidates are meant to be ranked by the voter's preference.
 * In OPL, since the rules state each ballot only votes for one candidate,
 * the vector would only contain one entry.
 **/
class IRBallot : public Ballot {
 public:
  /**
   * @brief IRBallot constructor
   * @param id an integer which contains IRBallot's ID. Intended to be unique to ballot
   * @return void
   *
   * Sets ballot's id_ attribute to id, and creates an empty rankedCandidates_ vector,
   * to store candidates. Sets currCandidateIdx_ to 0
   */
  IRBallot(int id);

  /**
   * @brief IRBallot destructor
   * @return void
   *
   * Does not delete the candidates in the candidates vector.
   */
  ~IRBallot() {}

  /**
   * @brief candidate getter
   * @return The candidate at currCandidate_ index
   *
   * If currCandidateIdx_ is out of range, returns a nullptr
   */
  Candidate *getCandidate();

  /**
   * @brief currCandidateIdx_ getter method
   * @return currCandidateIdx_
   */
  unsigned int getCurrCandidateIdx() { return currCandidateIdx_; }

  /**
   * @brief increments currCandidateIdx by 1
   * @return 1 if currCandidateIdx incremented succesfully, else 0
   *
   * Does not increment if such an increment would produce an index which is
   * out of bounds of the current rankedCandidate_'s size
   */
  int nextCandidate();

 private:
  /// stores an index into rankedCandidates_ vector.
  unsigned int currCandidateIdx_;
};

} // namespace VotingSystem

#endif  // IRBALLOT_H_
