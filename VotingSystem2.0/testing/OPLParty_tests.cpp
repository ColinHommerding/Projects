
#include "gtest/gtest.h"
#include "../src/include/OPLParty.h"
#include <algorithm>
#include <string>
#include <vector>

namespace VS = VotingSystem;

std::vector<VS::Candidate*> createCandidateVector(int n) {
    std::vector<VS::Candidate*> candidates;
    if (n > 0) {
	for(int i = 0; i < n; i++) {
	     // each candidate has a unique ID
	    candidates.push_back(new VS::Candidate("Candidate","Party",i));
	}
    }
    return candidates;
}

void addCandidateVector(VS::OPLParty *p, std::vector<VS::Candidate*> cv) {
  for (int i = 0; i < cv.size(); i++) {
      p->addCandidate(cv[i]);
  }
}

/**
 * Description: These tests are for OPLParty() constructor method.
 **/

// OPLParty constructor should initialize all values to zero, the candidates_ vector
// to an empty vector, and name_ to the passed in string.
TEST(OPLPartyConstructorTests, InitializeSingleWordName) {
  VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);

    EXPECT_EQ(0, OPLp->getVotes());
    EXPECT_EQ(0, OPLp->getRemainingVotes());
    EXPECT_EQ(0, OPLp->getSeats());
    EXPECT_EQ(0, OPLp->getCandidates().size());
    EXPECT_EQ("Silly", OPLp->getName());

    delete OPLp;
}

// Entire passed in name string should be set to name_
TEST(OPLPartyConstructorTests, InitializeMultipleWordName) {
  VS::OPLParty *OPLp = new VS::OPLParty("Slightly Silly", 0);

    EXPECT_EQ(0, OPLp->getVotes());
    EXPECT_EQ(0, OPLp->getRemainingVotes());
    EXPECT_EQ(0, OPLp->getSeats());
    EXPECT_EQ(0, OPLp->getCandidates().size());
    EXPECT_EQ("Slightly Silly", OPLp->getName());

    delete OPLp;
}

// If passed in string is empty, should still be set to name_
TEST(OPLPartyConstructorTests, InitializeEmptyString) {
  VS::OPLParty *OPLp = new VS::OPLParty("", 0);

    EXPECT_EQ(0, OPLp->getVotes());
    EXPECT_EQ(0, OPLp->getRemainingVotes());
    EXPECT_EQ(0, OPLp->getSeats());
    EXPECT_EQ(0, OPLp->getCandidates().size());
    EXPECT_EQ("", OPLp->getName());

    delete OPLp;
}


// addCandidate shall append the passed in Candidate object to the end
// of the candidates_ vector
TEST(OPLPartyAddCandidateTests, AddCandidates) {
  VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    OPLp->addCandidate(new VS::Candidate("Candidate","Party",1));
    OPLp->addCandidate(new VS::Candidate("Candidate","Party",2));
    OPLp->addCandidate(new VS::Candidate("Candidate","Party",0));

    // log the id of each candidate when iterating through candidates_ vector
    std::vector<int> ids;
    for(int i = 0; i < OPLp->getCandidates().size(); i++) {
      ids.push_back(OPLp->getCandidates()[i]->getId());
    }

    // establish expected order of candidate IDs
    std::vector<int> correctOrder{1,2,0};

    EXPECT_EQ(correctOrder, ids);

    // delete allocated memory
    for (int i = 0; i < OPLp->getCandidates().size(); i++) {
      delete OPLp->getCandidates()[i];
    }
    delete OPLp;
}

// addCandidate shall not append any NULL Candidate object
TEST(OPLPartyAddCandidateTests, DoNotAddNullCandidates) {
  VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    OPLp->addCandidate(nullptr);
    OPLp->addCandidate(new VS::Candidate("Candidate","Party",1));
    OPLp->addCandidate(new VS::Candidate("Candidate","Party",2));
    OPLp->addCandidate(nullptr);
    OPLp->addCandidate(new VS::Candidate("Candidate","Party",0));
    OPLp->addCandidate(nullptr);
    
    // log the id of each candidate when iterating through candidates_ vector
    std::vector<int> ids;
    for(int i = 0; i < OPLp->getCandidates().size(); i++) {
	ids.push_back(OPLp->getCandidates()[i]->getId());
    }

    // establish expected order of candidate IDs
    std::vector<int> correctOrder{1,2,0};

    EXPECT_EQ(correctOrder, ids);

    // delete allocated memory
    for (int i = 0; i < OPLp->getCandidates().size(); i++) {
	delete OPLp->getCandidates()[i];
    }
    delete OPLp;
}

// addCandidate shall not append any Candidate with ID already existing
// in candidates
TEST(OPLPartyAddCandidateTests, DoNotAddDuplicateIdCandidates) {
  VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    OPLp->addCandidate(new VS::Candidate("Candidate","Party",1));
    OPLp->addCandidate(new VS::Candidate("Candidate","Party",2));
    VS::Candidate *copyCand2 = new VS::Candidate("CandidateCopy","Party",2);
    VS::Candidate *copyCand1 = new VS::Candidate("CandidateCopy","Party",1);
    OPLp->addCandidate(copyCand2);
    OPLp->addCandidate(copyCand1);
    OPLp->addCandidate(new VS::Candidate("Candidate","Party",0));

    // log the id of each candidate when iterating through candidates_ vector
    std::vector<int> ids;
    for(int i = 0; i < OPLp->getCandidates().size(); i++) {
	ids.push_back(OPLp->getCandidates()[i]->getId());
    }

    // establish expected order of candidate IDs
    std::vector<int> correctOrder{1,2,0};

    // Candidates should be in order
    EXPECT_EQ(correctOrder, ids);

    // No "CandidateCopy" named candidates should be in getRankedCandidates()
    for (int i = 0; i < OPLp->getCandidates().size(); i++) {
      EXPECT_EQ(OPLp->getCandidates()[i]->getName(), "Candidate");
    }

    // delete allocated memory
    for (int i = 0; i < OPLp->getCandidates().size(); i++) {
	delete OPLp->getCandidates()[i];
    }
    delete OPLp;
    delete copyCand1;
    delete copyCand2;
}


/**
 * Description: coinFlipTests
 **/

// coinFlip should work fairly between two candidates
TEST(CoinFlipTests, TwoTied) {
  VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    std::vector<VS::Candidate*> candidates = createCandidateVector(2);
    addCandidateVector(OPLp,candidates);
    float numTrials = 10000;
    
    std::vector<float> cnts{0,0};
    for (int i = 0; i < numTrials; i++) {
	VS::Candidate *winner = OPLp->coinFlip(candidates);
	if (winner == candidates[0]) {
	    cnts[0]++;
	} else if (winner == candidates[1]){
	    cnts[1] = cnts[1]+1;
	}
    }

    // expect coinFlip to have returned a valid entry every loop iteration
    EXPECT_EQ(numTrials, cnts[0]+cnts[1]);
    // expect CoinFlip to return candidates[0] half of the time
    EXPECT_NEAR(0.5, cnts[0]/numTrials, 0.05); //0.45--0.55 will pass
    // and candidates[1] half of the time
    EXPECT_NEAR(0.5, cnts[1]/numTrials, 0.05);

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}

// coinFlip should work fairly on any n-length vector
TEST(CoinFlipTests, FourTied) {
  VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    std::vector<VS::Candidate*> candidates = createCandidateVector(4);
    addCandidateVector(OPLp,candidates);
    float numTrials = 10000;
    
    std::vector<float> cnts{0,0,0,0};
    for (int i = 0; i < numTrials; i++) {
	VS::Candidate *winner = OPLp->coinFlip(candidates);
	if (winner == candidates[0]) {
	    cnts[0]++;
	} else if (winner == candidates[1]) {
	    cnts[1]++;
	} else if (winner == candidates[2]) {
	    cnts[2]++;
	} else if (winner == candidates[3]) {
	    cnts[3]++;
	}
    }

    // expect coinFlip to have returned a valid entry every loop iteration
    EXPECT_EQ(numTrials, cnts[0]+cnts[1]+cnts[2]+cnts[3]);
    // expect CoinFlip to return each candidate a quarter of the time
    EXPECT_NEAR(0.25, cnts[0]/numTrials, 0.05);
    EXPECT_NEAR(0.25, cnts[1]/numTrials, 0.05);
    EXPECT_NEAR(0.25, cnts[2]/numTrials, 0.05);
    EXPECT_NEAR(0.25, cnts[3]/numTrials, 0.05);

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}

// coinFlip should always return the single candidate in a size 1 vector
TEST(CoinFlipTests, OneCandidate) {
  VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    std::vector<VS::Candidate*> candidates = createCandidateVector(1);
    addCandidateVector(OPLp,candidates);
    float numTrials = 10000;
    
    std::vector<float> cnts{0};
    for (int i = 0; i < numTrials; i++) {
	VS::Candidate *winner = OPLp->coinFlip(candidates);
	if (winner == candidates[0]) {
	    cnts[0]++;
	}
    }

    // expect CoinFlip to return the only candidate 100% of the time
    EXPECT_EQ(1, cnts[0]/numTrials);

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}

// coinFlip should return nullptr if a zero-length vector passed in
TEST(CoinFlipTests, ZeroCandidates) {
  VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    std::vector<VS::Candidate*> candidates = createCandidateVector(0);
    addCandidateVector(OPLp,candidates);
  
    VS::Candidate *winner = OPLp->coinFlip(candidates);

    // expect CoinFlip to return null
    EXPECT_EQ(nullptr, winner);
 }

// coinFlip should work for any input vector of pointers
TEST(CoinFlipTests, InputVectorOfIntPtrs) {
    int x = 1;
    int y = 2;    
    std::vector<int*> ints{&x,&y};
    

    VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    std::vector<VS::Candidate*> candidates = createCandidateVector(2);
    addCandidateVector(OPLp,candidates);
    float numTrials = 10000;
    
    std::vector<float> cnts{0,0};
    for (int i = 0; i < numTrials; i++) {
	int *choice = OPLp->coinFlip(ints);
	if (choice == ints[0]) {
	    cnts[0]++;
	} else if (choice == ints[1]) {
	    cnts[1]++;
	}
    }

    // coinFlip should have chosen a valid choice every time
    EXPECT_EQ(numTrials, cnts[0]+cnts[1]);
    // expect CoinFlip to return ints[0] half of the time
    EXPECT_NEAR(0.5, cnts[0]/numTrials, 0.05);
    // and ints[1] half of the time
    EXPECT_NEAR(0.5, cnts[1]/numTrials, 0.05);

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}

/**
 * Description: These tests are for addSeats method in OPLParty object, which adds
 *              the integer argument to the OPLParty's numSeats_ attribute.
 **/

// addSeats should add to numSeats_ the value passed in
TEST(AddSeatsTests, addPositiveSeat) { 
    // OPLparty will initialize with 0 seats
  VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    std::vector<VS::Candidate*> candidates = createCandidateVector(2);
    addCandidateVector(OPLp,candidates);
    OPLp->addSeats(2);

    EXPECT_EQ(2, OPLp->getSeats());

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}

// addSeats shouldn't add any seats if 0 is passed in
TEST(AddSeatsTests, addZeroSeat) {
  VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    std::vector<VS::Candidate*> candidates = createCandidateVector(2);
    addCandidateVector(OPLp,candidates);
    OPLp->addSeats(0);

    EXPECT_EQ(0, OPLp->getSeats());

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}

// addSeats should subtract seats if negative int passed in
TEST(AddSeatsTests, addNegativeSeat) {
  VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    std::vector<VS::Candidate*> candidates = createCandidateVector(2);
    addCandidateVector(OPLp,candidates);
    OPLp->addSeats(5);
    OPLp->addSeats(-2);

    EXPECT_EQ(3, OPLp->getSeats());

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}

// numSeats_ should never go below 0
TEST(AddSeatsTests, noNegativeSeatVal) {
  VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    std::vector<VS::Candidate*> candidates = createCandidateVector(2);
    addCandidateVector(OPLp,candidates);
    OPLp->addSeats(-2);
    EXPECT_EQ(0, OPLp->getSeats());

    OPLp->addSeats(2);
    OPLp->addSeats(-4);
    EXPECT_EQ(0, OPLp->getSeats());

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}

/**
 * Tests for sumCandidateVotes
 */

// sumCandiateVotes should sum together the votes of all the candidates and store in numVotes_
TEST(SumCandidateVotesTests, SumCandidatesVotes) {
    std::vector<VS::Candidate*> candidates = createCandidateVector(3);

    // C1 has 5 votes, C2 has 2, C3 has 1
    for (int i = 0; i < 5; i++) {
	candidates[0]->addBallot(nullptr);
    }
    for (int i = 0; i < 2; i++) {
	candidates[1]->addBallot(nullptr);
    }
    for (int i = 0; i < 1; i++) {
	candidates[2]->addBallot(nullptr);
    }
    VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    addCandidateVector(OPLp,candidates);

    // should return 5+2+1 = 8
    OPLp->sumCandidateVotes();
    EXPECT_EQ(8, OPLp->getVotes());

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}

// sumCandidateVotes should work for an arbitrary number of candidates
TEST(SumCandidateVotesTests, OneCandidateInParty) {
    std::vector<VS::Candidate*> candidates = createCandidateVector(1);

    // Candidate has 5 votes
    for (int i = 0; i < 5; i++) {
	candidates[0]->addBallot(nullptr);
    }
    VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    addCandidateVector(OPLp,candidates);

    // should return 5 votes
    OPLp->sumCandidateVotes();
    EXPECT_EQ(5, OPLp->getVotes());

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}

// sumCandidateVotes should return 0 if no candidates got votes
TEST(SumCandidateVotesTests, CandidatesHaveZeroVotes) {
    // Assuming Candidate objects initialize with 0 votes
    std::vector<VS::Candidate*> candidates = createCandidateVector(3);
    VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    addCandidateVector(OPLp,candidates);

    OPLp->sumCandidateVotes();
    EXPECT_EQ(0, OPLp->getVotes());

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}

// sumCandidateVotes should return -1 if no candidates exist
TEST(SumCandidateVotesTests, NoCandidates) {
    std::vector<VS::Candidate*> candidates = createCandidateVector(0);
    VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    addCandidateVector(OPLp,candidates);

    OPLp->sumCandidateVotes();
    EXPECT_EQ(-1, OPLp->getVotes());

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}

// Any subsequence call to sumCandidateVotes should update numVotes_, not
// add the sum to the existing numVotes_.
TEST(SumCandidateVotesTests, NumVotesUpdatedNotSummed) {
    std::vector<VS::Candidate*> candidates = createCandidateVector(3);
    // C0 has 5 votes, C1 has 2, C2 has 1
    for (int i = 0; i < 5; i++) {
	candidates[0]->addBallot(nullptr);
    }
    for (int i = 0; i < 2; i++) {
	candidates[1]->addBallot(nullptr);
    }
    for (int i = 0; i < 1; i++) {
	candidates[2]->addBallot(nullptr);
    }
    VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    addCandidateVector(OPLp,candidates);

    // Initial sum to numVotes_
    OPLp->sumCandidateVotes();

    // add 3 votes to C0, 2 votes to C1, 0 votes to C2
    for (int i = 0; i < 3; i++) {
	candidates[0]->addBallot(nullptr);
    }
    for (int i = 0; i < 2; i++) {
	candidates[1]->addBallot(nullptr);
    }

    // should be 13, not 8+13 = 25
    OPLp->sumCandidateVotes();
    EXPECT_EQ(13, OPLp->getVotes());

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}


/**
 * test UpdateRemainingVotes
 **/

// UpdateRemainingVotes should set remainderVotes_ attribute
TEST(UpdateRemainingVotesTests, UpdateRemainingVotes) {
    std::vector<VS::Candidate*> candidates = createCandidateVector(3);
    VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);

    OPLp->updateRemainingVotes(38);

    EXPECT_EQ(38, OPLp->getRemainingVotes());

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}

TEST(UpdateRemainingVotesTests, UpdateRemainingVotesToZero) {
    std::vector<VS::Candidate*> candidates = createCandidateVector(3);
    VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);

    OPLp->updateRemainingVotes(0);

    EXPECT_EQ(0, OPLp->getRemainingVotes());

    OPLp->updateRemainingVotes(38);
    OPLp->updateRemainingVotes(0);
    EXPECT_EQ(0, OPLp->getRemainingVotes());

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}

// updateRemainingVotes should update, not sum to existing remainderVotes_ value
TEST(UpdateRemainingVotesTests, UpdateRemainingVotesUpdatesNotSums) {
    std::vector<VS::Candidate*> candidates = createCandidateVector(3);
    VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);

    OPLp->updateRemainingVotes(38);
    OPLp->updateRemainingVotes(20);

    EXPECT_EQ(20, OPLp->getRemainingVotes());

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}

// updateRemainingVotes should never update remainderVotes_ to a negative value,
// if a negative value is passed in it should update to 0.
TEST(UpdateRemainingVotesTests, NeverUpdateToNegative) {
    std::vector<VS::Candidate*> candidates = createCandidateVector(3);
    VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);

    OPLp->updateRemainingVotes(-5);

    EXPECT_EQ(0, OPLp->getRemainingVotes());

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}


/**
 * tests for OrderCandidates
 **/

// orderCandidates should rearrange candidates_ vector in decreasing order
// by each candidate's numVotes_.
TEST(OrderCandidatesTests, OrderCandidates) {
    std::vector<VS::Candidate*> candidates = createCandidateVector(4);
    VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    addCandidateVector(OPLp,candidates);
    // C0 has 3 votes, C1 has 5, C2 has 1, C3 has 8
    for (int i = 0; i < 3; i++) {
	candidates[0]->addBallot(nullptr);
    }
    for (int i = 0; i < 5; i++) {
	candidates[1]->addBallot(nullptr);
    }
    for (int i = 0; i < 1; i++) {
	candidates[2]->addBallot(nullptr);
    }
    for (int i = 0; i < 8; i++) {
	candidates[3]->addBallot(nullptr);
    }

    OPLp->orderCandidates(0);

    // log the id of each candidate when iterating through candidates_ vector
    std::vector<int> ids;
    std::vector<VS::Candidate*> OPLcands = OPLp->getCandidates();
    for(int i = 0; i < OPLcands.size(); i++) {
	ids.push_back(OPLcands[i]->getId());
    }

    // establish expected order of candidate IDs
    std::vector<int> correctOrder{3,1,0,2};
    
    EXPECT_EQ(ids, correctOrder);

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}

// orderCandidates should not change the order if candidates_ vector already
// in order
TEST(OrderCandidatesTests, CandidatesAlreadyInOrder) {
    std::vector<VS::Candidate*> candidates = createCandidateVector(4);
    VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    addCandidateVector(OPLp,candidates);
    // C0 has 5 votes, C1 has 2, C2 has 1, C3 has 0
    for (int i = 0; i < 5; i++) {
	candidates[0]->addBallot(nullptr);
    }
    for (int i = 0; i < 3; i++) {
	candidates[1]->addBallot(nullptr);
    }
    for (int i = 0; i < 1; i++) {
	candidates[2]->addBallot(nullptr);
    }

    OPLp->orderCandidates(0);

    // log the id of each candidate when iterating through candidates_ vector
    std::vector<int> ids;
    std::vector<VS::Candidate*> OPLcands = OPLp->getCandidates();
    for(int i = 0; i < OPLcands.size(); i++) {
	ids.push_back(OPLcands[i]->getId());
    }

    // establish expected order of candidate IDs
    std::vector<int> correctOrder{0,1,2,3};
    
    EXPECT_EQ(ids, correctOrder);

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}

// orderCandidates should do nothing if there are no candidates
TEST(OrderCandidatesTests, NoCandidatesToOrder) {
    std::vector<VS::Candidate*> candidates = createCandidateVector(0);
    VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    addCandidateVector(OPLp,candidates);

    OPLp->orderCandidates(0);
    

    EXPECT_TRUE(candidates.empty());

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}

// orderCandidates should do nothing if candidates_ vector has
// only one candidate
TEST(OrderCandidatesTests, OneCandidate) {
    std::vector<VS::Candidate*> candidates = createCandidateVector(1);
    VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    addCandidateVector(OPLp,candidates);
    // C0 has 5 votes
    for (int i = 0; i < 5; i++) {
	candidates[0]->addBallot(nullptr);
    }

    OPLp->orderCandidates(0);

    // log the id of each candidate when iterating through candidates_ vector
    std::vector<int> ids;
    std::vector<VS::Candidate*> OPLcands = OPLp->getCandidates();
    for(int i = 0; i < OPLcands.size(); i++) {
	ids.push_back(OPLcands[i]->getId());
    }

    // establish expected order of candidate IDs
    std::vector<int> correctOrder{0};
    
    EXPECT_EQ(ids, correctOrder);

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}

// orderCandidates should randomly order tied candidates
TEST(OrderCandidatesTests, HasTwoTiedCandidates) {
    std::vector<VS::Candidate*> candidates = createCandidateVector(4);
    VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    addCandidateVector(OPLp,candidates);
    float numTrials = 10000;
    
    // C0 has 1 vote, C1 has 2, C2 has 2, C3 has 0
    for (int i = 0; i < 1; i++) {
	candidates[0]->addBallot(nullptr);
    }
    for (int i = 0; i < 2; i++) {
	candidates[1]->addBallot(nullptr);
    }
    for (int i = 0; i < 2; i++) {
	candidates[2]->addBallot(nullptr);
    }

    // Create vector to log occurances of the two possible orders
    std::vector<float> log{0,0};
    
    for (int i = 0; i < numTrials; i++) {
	OPLp->orderCandidates(0);

	// log the id of each candidate when iterating through candidates_ vector
	std::vector<int> ids;
	std::vector<VS::Candidate*> OPLcands = OPLp->getCandidates();
	for(int i = 0; i < OPLcands.size(); i++) {
	    ids.push_back(OPLcands[i]->getId());
	}
	

	// establish expected order of candidate IDs
	std::vector<int> order0{1,2,0,3};
	std::vector<int> order1{2,1,0,3};

	if (ids == order0) {
	    log[0]++;
	} else if (ids == order1) {
	    log[1]++;
	}
    }

    EXPECT_EQ(numTrials, log[0]+log[1]);
    EXPECT_NEAR(0.5, log[0]/numTrials, 0.05);
    EXPECT_NEAR(0.5, log[1]/numTrials, 0.05);

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}

// orderCandidates should randomly order tied candidates
TEST(OrderCandidatesTests, HasThreeTiedCandidates) {
    std::vector<VS::Candidate*> candidates = createCandidateVector(4);
    VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    addCandidateVector(OPLp,candidates);
    float numTrials = 10000;    
    // C0 has 2 votes, C1 has 2, C2 has 2, C3 has 0
    for (int i = 0; i < 2; i++) {
	candidates[0]->addBallot(nullptr);
    }
    for (int i = 0; i < 2; i++) {
	candidates[1]->addBallot(nullptr);
    }
    for (int i = 0; i < 2; i++) {
	candidates[2]->addBallot(nullptr);
    }

    // Create vector to log occurances of the six possible orders
    std::vector<float> log{0,0,0,0,0,0};
    
    for (int i = 0; i < numTrials; i++) {
	OPLp->orderCandidates(0);

	// log the id of each candidate when iterating through candidates_ vector
	std::vector<int> ids;
	std::vector<VS::Candidate*> OPLcands = OPLp->getCandidates();
	for(int i = 0; i < OPLcands.size(); i++) {
	    ids.push_back(OPLcands[i]->getId());
	}
	

	// establish expected order of candidate IDs
	std::vector<int> order0{0,1,2,3};
	std::vector<int> order1{0,2,1,3};
	std::vector<int> order2{1,0,2,3};
	std::vector<int> order3{1,2,0,3};
	std::vector<int> order4{2,0,1,3};
	std::vector<int> order5{2,1,0,3};

	if (ids == order0) {
	    log[0]++;
	} else if (ids == order1) {
	    log[1]++;
	} else if (ids == order2) {
	    log[2]++;
	} else if (ids == order3) {
	    log[3]++;
	} else if (ids == order4) {
	    log[4]++;
	} else if (ids == order5) {
	    log[5]++;
	}
    }

    EXPECT_EQ(numTrials, log[0]+log[1]+log[2]+log[3]+log[4]+log[5]+log[6]);
    EXPECT_NEAR(0.167, log[0]/numTrials, 0.05);
    EXPECT_NEAR(0.167, log[1]/numTrials, 0.05);
    EXPECT_NEAR(0.167, log[2]/numTrials, 0.05);
    EXPECT_NEAR(0.167, log[3]/numTrials, 0.05);
    EXPECT_NEAR(0.167, log[4]/numTrials, 0.05);
    EXPECT_NEAR(0.167, log[5]/numTrials, 0.05);

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}

// orderCandidates should randomly order tied candidates
TEST(OrderCandidatesTests, AllCandidatesTied) {
    std::vector<VS::Candidate*> candidates = createCandidateVector(3);
    VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    addCandidateVector(OPLp,candidates);
    float numTrials = 10000;
    // C0 has 2 votes, C1 has 2, C2 has 2
    for (int i = 0; i < 2; i++) {
	candidates[0]->addBallot(nullptr);
    }
    for (int i = 0; i < 2; i++) {
	candidates[1]->addBallot(nullptr);
    }
    for (int i = 0; i < 2; i++) {
	candidates[2]->addBallot(nullptr);
    }

    // Create vector to log occurances of the six possible orders
    std::vector<float> log{0,0,0,0,0,0};
    
    for (int i = 0; i < numTrials; i++) {
	OPLp->orderCandidates(0);

	// log the id of each candidate when iterating through candidates_ vector
	std::vector<int> ids;
	std::vector<VS::Candidate*> OPLcands = OPLp->getCandidates();
	for(int i = 0; i < OPLcands.size(); i++) {
	    ids.push_back(OPLcands[i]->getId());
	}
	

	// establish expected order of candidate IDs
	std::vector<int> order0{0,1,2};
	std::vector<int> order1{0,2,1};
	std::vector<int> order2{1,0,2};
	std::vector<int> order3{1,2,0};
	std::vector<int> order4{2,0,1};
	std::vector<int> order5{2,1,0};

	if (ids == order0) {
	    log[0]++;
	} else if (ids == order1) {
	    log[1]++;
	} else if (ids == order2) {
	    log[2]++;
	} else if (ids == order3) {
	    log[3]++;
	} else if (ids == order4) {
	    log[4]++;
	} else if (ids == order5) {
	    log[5]++;
	}
    }

    EXPECT_EQ(numTrials, log[0]+log[1]+log[2]+log[3]+log[4]+log[5]+log[6]);
    EXPECT_NEAR(0.167, log[0]/numTrials, 0.05);
    EXPECT_NEAR(0.167, log[1]/numTrials, 0.05);
    EXPECT_NEAR(0.167, log[2]/numTrials, 0.05);
    EXPECT_NEAR(0.167, log[3]/numTrials, 0.05);
    EXPECT_NEAR(0.167, log[4]/numTrials, 0.05);
    EXPECT_NEAR(0.167, log[5]/numTrials, 0.05);

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}

// orderCandidates should order candidates by ascending ID when debug mode
// is on
TEST(OrderCandidatesTests, DebugMode) {
    std::vector<VS::Candidate*> candidates = createCandidateVector(4);
    VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    addCandidateVector(OPLp,candidates);
    float numTrials = 10000;
    // C0 has 2 votes, C1 has 0, C2 has 2, C3 has 2
    for (int i = 0; i < 2; i++) {
	candidates[0]->addBallot(nullptr);
    }
    for (int i = 0; i < 2; i++) {
	candidates[3]->addBallot(nullptr);
    }
    for (int i = 0; i < 2; i++) {
	candidates[2]->addBallot(nullptr);
    }

    // Create vector to log occurances of the six possible orders
    std::vector<float> log{0,0,0,0,0,0};
    
    for (int i = 0; i < numTrials; i++) {
	OPLp->orderCandidates(1);

	// log the id of each candidate when iterating through candidates_ vector
	std::vector<int> ids;
	std::vector<VS::Candidate*> OPLcands = OPLp->getCandidates();
	for(int i = 0; i < OPLcands.size(); i++) {
	    ids.push_back(OPLcands[i]->getId());
	}
	

	// establish expected order of candidate IDs
	std::vector<int> order0{0,3,2,1};
	std::vector<int> order1{0,2,3,1};
	std::vector<int> order2{3,0,2,1};
	std::vector<int> order3{3,2,0,1};
	std::vector<int> order4{2,0,3,1};
	std::vector<int> order5{2,3,0,1};

	if (ids == order0) {
	    log[0]++;
	} else if (ids == order1) {
	    log[1]++;
	} else if (ids == order2) {
	    log[2]++;
	} else if (ids == order3) {
	    log[3]++;
	} else if (ids == order4) {
	    log[4]++;
	} else if (ids == order5) {
	    log[5]++;
	}
    }

    EXPECT_EQ(numTrials, log[0]+log[1]+log[2]+log[3]+log[4]+log[5]+log[6]);
    EXPECT_EQ(numTrials, log[1]); // expect order {0,2,3,1} to occur all the time

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}


/**
 * assignCandidatesToSeats tests
 **/

// assignCandidatesToSeats should return as a Candidate* vector the first
// n candidates in the party's candidates_ vector, where n = numSeats_.
// It is assumed that the OrderCandidates() method has been called before this.
TEST(AssignCandidatesToSeatsTests, MoreCandidatesThanSeats) {
    std::vector<VS::Candidate*> candidates = createCandidateVector(5);
    std::vector<VS::Candidate*> winners;
    VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    addCandidateVector(OPLp,candidates);
    OPLp->addSeats(3);

    winners = OPLp->assignCandidatesToSeats();

    // Check if the three winners we expected (the first three entries in candidates vector)
    // are present in winners vector
    std::vector<VS::Candidate*> OPLcands = OPLp->getCandidates();
    EXPECT_TRUE(std::find(winners.begin(), winners.end(), OPLcands.at(0)) != winners.end());
    EXPECT_TRUE(std::find(winners.begin(), winners.end(), OPLcands.at(1)) != winners.end());
    EXPECT_TRUE(std::find(winners.begin(), winners.end(), OPLcands.at(2)) != winners.end());

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}

// If there are more seats than candidates, all candidates should be returned
TEST(AssignCandidatesToSeatsTests, MoreSeatsThanCandidates) {
    std::vector<VS::Candidate*> candidates = createCandidateVector(5);
    std::vector<VS::Candidate*> winners;
    VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    addCandidateVector(OPLp,candidates);
    OPLp->addSeats(8);

    winners = OPLp->assignCandidatesToSeats();

    // Check if the three winners we expected (the first three entries in candidates vector)
    // are present in winners vector
    std::vector<VS::Candidate*> OPLcands = OPLp->getCandidates();
    EXPECT_TRUE(std::find(winners.begin(), winners.end(), OPLcands.at(0)) != winners.end());
    EXPECT_TRUE(std::find(winners.begin(), winners.end(), OPLcands.at(1)) != winners.end());
    EXPECT_TRUE(std::find(winners.begin(), winners.end(), OPLcands.at(2)) != winners.end());
    EXPECT_TRUE(std::find(winners.begin(), winners.end(), OPLcands.at(3)) != winners.end());
    EXPECT_TRUE(std::find(winners.begin(), winners.end(), OPLcands.at(4)) != winners.end());

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}

// If a party wins zero seats, returns an empty winners vector
TEST(AssignCandidatesToSeatsTests, ZeroSeats) {
    std::vector<VS::Candidate*> candidates = createCandidateVector(5);
    std::vector<VS::Candidate*> winners;
    VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    addCandidateVector(OPLp,candidates);

    winners = OPLp->assignCandidatesToSeats();

    // Check that there are no winners
    EXPECT_EQ(0, winners.size());

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}

// If there are no candidates, returns empty winners vector
TEST(AssignCandidatesToSeatsTests, ZeroCandidates) {
    std::vector<VS::Candidate*> candidates = createCandidateVector(0);
    std::vector<VS::Candidate*> winners;
    VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    addCandidateVector(OPLp,candidates);
    OPLp->addSeats(8);

    winners = OPLp->assignCandidatesToSeats();

    EXPECT_EQ(0, winners.size());

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}

// If there are no seats and no candidates, returns empty winners vector
TEST(AssignCandidatesToSeatsTests, ZeroSeatsAndCandidates) {
    std::vector<VS::Candidate*> candidates = createCandidateVector(0);
    std::vector<VS::Candidate*> winners;
    VS::OPLParty *OPLp = new VS::OPLParty("Silly", 0);
    addCandidateVector(OPLp,candidates);
    OPLp->addSeats(0);

    winners = OPLp->assignCandidatesToSeats();

    EXPECT_EQ(0, winners.size());

    // delete allocated memory
    for (int i = 0; i < candidates.size(); i++) {
	delete candidates[i];
    }
    delete OPLp;
}
