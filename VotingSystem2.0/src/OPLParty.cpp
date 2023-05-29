
#include "include/OPLParty.h"
#include <algorithm>
#include <ctime>

namespace VS = VotingSystem;

unsigned int VS::OPLParty::seed_ = time(NULL);

VS::OPLParty::OPLParty(std::string name, int partyID) {
  name_ = name;
  seed_ = time(NULL);
  numVotes_ = 0;
  remainderVotes_ = 0;
  numSeats_ = 0;
  candidates_ = std::vector<Candidate*>();
  winnerCandidates_ = std::vector<Candidate*>();
  id = partyID;
}

void VS::OPLParty::addCandidate(VS::Candidate *c) {
  // Check if null candidate. If so, do not add
  if (c == nullptr) {
    return;
  }
  // check if ID of target candidate is already in vector
  // if so, do not add candidate.
  for (unsigned int i = 0; i < candidates_.size(); i++) {
    if (candidates_[i]->getId() == c->getId()) {
#if DEBUG
      std::cout << "OPLParty " << name_ << ": Candidate "
		<< c->getId() << "(" << c->getName() << ") not added, id already exists\n";
#endif
      return;
    }
  }
  candidates_.push_back(c);
}

void VS::OPLParty::sumCandidateVotes() {
  // check if no candidates
  if (candidates_.size() == 0) {
    numVotes_ = -1;
  } else {
    numVotes_ = 0; // reset numVotes_ to 0
    for (unsigned int i = 0; i < candidates_.size(); i++) {
      numVotes_ += candidates_[i]->getNumVotes();
    }
  }
}

void VS::OPLParty::addSeats(int n) {
  if(numSeats_ + n < 0) {
    numSeats_ = 0;
  } else {
    numSeats_ += n;
  }
}

void VS::OPLParty::updateRemainingVotes(int n) {
  if (n > 0) {
    remainderVotes_ = n;
  } else {
    remainderVotes_ = 0;
  }
}

void VS::OPLParty::orderCandidates(bool debug) {
  // Create lambda function that compares two candidates
  // by their number of votes
  auto compare = [] (Candidate *a, Candidate *b) {
    // compares >= instead of < since we ultimately want to sort
    // candidates by decreasing number of votes, not by increasing
    return a->getNumVotes() >= b->getNumVotes();
  };
  
  // Sort candidates using above comp function
  std::sort(candidates_.begin(), candidates_.end(), compare);
  
  // initialize variables
  size_t i = 0;
  size_t j = i+1;
  std::vector<Candidate*> ties;
  // Go through candidates_ and randomly rearrange any candidates with
  // the same number of votes
  while (i < candidates_.size()) {
    j = i+1;
    while ((j < candidates_.size()) &&
	   (candidates_[j]->getNumVotes() == candidates_[i]->getNumVotes())) {
      j++;  // j is first candidate after i with a different numVotes_ than i
    }
    while (j - i > 1) {
      // populate ties vector with all candidates in range [i,j)
      for (size_t k = i; k < j; k++) {
	ties.push_back(candidates_[k]);
      }
      // randomly select one of the tied candidates
      Candidate *c;
      if (debug) {
	c = nullptr;
	for (int i = 0; i < ties.size(); i++) {
	  if (c == nullptr || ties[i]->getId() < c->getId()) {
	    c = ties[i];
	  }
	}
      } else {
      c = coinFlip(ties);
      }
      // find selected candidate's index in candidates_
      int cIdx;
      for (int k = i; i < j; k++) {
	if (candidates_[k]->getId() == c->getId()) {
	  cIdx = k;
	  break;
	}
      }
      // clear ties vector
      ties.clear();
      // swap candidate at i with selected candidate
      Candidate *cAtI = candidates_[i];
      candidates_.erase(candidates_.begin() + i);
      candidates_.insert(candidates_.begin() + i,c);
      candidates_.erase(candidates_.begin() + cIdx);
      candidates_.insert(candidates_.begin() + cIdx,cAtI);

      // increment i
      i++;
    }
    // i and j are next to each other -> increment i
    i++;
  }
}

std::vector<VS::Candidate*> VS::OPLParty::assignCandidatesToSeats() {
  // return all candidates if there are equal or more seats than candidates
  int candidatesLength = candidates_.size();
  if (numSeats_ >= candidatesLength) {
    winnerCandidates_.insert( winnerCandidates_.end(), candidates_.begin(), candidates_.end() );
    return candidates_;
  } else {
    // vector to store candidates who were awarded seats
    std::vector<VS::Candidate*> winners;
    // push top numSeats_ candidates to winners
    for (int i = 0; i < numSeats_; i++) {
      winnerCandidates_.push_back(candidates_[i]);
      winners.push_back(candidates_[i]);
    }
    return winners;
  }
}
