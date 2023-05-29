
#include "include/Ballot.h"
#include <cstdio>

#define DEBUG 0

namespace VS = VotingSystem;

VS::Ballot::Ballot(int id) {
  id_ = id;
  // empty vector
  rankedCandidates_ = std::vector<VS::Candidate*>();
}

void VS::Ballot::addCandidate(VS::Candidate *c) {
  // Check if null candidate. If so, do not add
  if (c == nullptr) {
    return;
  }
  // check if ID of target candidate is already in vector
  // if so, do not add candidate.
  for (unsigned int i = 0; i < rankedCandidates_.size(); i++) {
    if (rankedCandidates_[i]->getId() == c->getId()) {
#if DEBUG
      std::cout << "Ballot " << id_ << ": Candidate "
		<< c->getId() << "(" << c->getName() << ") not added, id already exists\n";
#endif
      return;
    }
  }
  rankedCandidates_.push_back(c);
}
