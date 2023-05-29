
#include "include/IRBallot.h"

#define DEBUG 0

namespace VS = VotingSystem;

VS::IRBallot::IRBallot(int id) : Ballot(id) {
  currCandidateIdx_ = 0;
}

VS::Candidate *VS::IRBallot::getCandidate() {
  // check if currCandidateIdx_ is a valid entry
  if (currCandidateIdx_ < rankedCandidates_.size() && currCandidateIdx_ >= 0) {
    return rankedCandidates_[currCandidateIdx_];
  } else {
    // return nullptr if entry not valid
    return nullptr;
  }
}

int VS::IRBallot::nextCandidate() {
  // increment if currCandidateIdx_ does not point to the last
  // entry in rankedCandidates_.
  if (currCandidateIdx_ < rankedCandidates_.size() - 1) {
#if DEBUG
    std::cout << "IRBallot " << id_ << ": failed to increment currCandidateIdx_\n";
#endif
    currCandidateIdx_++;
    return 1;
  }
  return 0;
}
