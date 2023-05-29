
#include "gtest/gtest.h"
#include "../src/include/IRBallot.h"
#include <string>
#include <vector>

namespace VS = VotingSystem;

/**
 * IRBallot constructor tests
 **/

// IRBallots should be created with an ID equal to the passed in value,
// an empty rankedCandidates_ vector, and currCandidateIdx_ set to 0
TEST(IRBallotConstructorTests, CreateBallotWithID) {
    VS::IRBallot *b1 = new VS::IRBallot(1);
    VS::IRBallot *b2 = new VS::IRBallot(0);
    VS::IRBallot *b3 = new VS::IRBallot(-2);

    // Check if ballot IDs are consistent
    EXPECT_EQ(1, b1->getId());
    EXPECT_EQ(0, b2->getId());
    EXPECT_EQ(-2, b3->getId());

    // Check that rankedCandidates_ vector is empty
    EXPECT_TRUE(b1->getRankedCandidates().size() == 0);
    EXPECT_TRUE(b2->getRankedCandidates().size() == 0);
    EXPECT_TRUE(b3->getRankedCandidates().size() == 0);

    // Check that currCandidateIdx_ is 0;
    EXPECT_EQ(b1->getCurrCandidateIdx(), 0);
    EXPECT_EQ(b2->getCurrCandidateIdx(), 0);
    EXPECT_EQ(b3->getCurrCandidateIdx(), 0);

    delete b1;
    delete b2;
    delete b3;
}

/**
 * getCandidate tests
 **/

// getCandidate shall return the candidate at the index stored in
// currCandidateIdx. It is assumed that currCandidateIdx corresponds
// to a valid index into the rankedCandidates_ vector.
TEST(GetCandidateTests, GetCandidate) {
    VS::IRBallot *b = new VS::IRBallot(1);
    b->addCandidate(new VS::Candidate("Candidate","Party",1));
    b->addCandidate(new VS::Candidate("Candidate","Party",2));
    b->addCandidate(new VS::Candidate("Candidate","Party",0));

    // Check that candidate in position 0 is returned
    EXPECT_EQ(b->getCandidate()->getId(), 1);
    // Subsequent calls without calling nextCandidate() should return the same
    EXPECT_EQ(b->getCandidate()->getId(), 1);

    // Check that candidate in position 1 is returned
    b->nextCandidate();
    EXPECT_EQ(b->getCandidate()->getId(), 2);

    // Check that candidate in position 2 is returned
    b->nextCandidate();
    EXPECT_EQ(b->getCandidate()->getId(), 0);

    // delete allocated memory
    for (int i = 0; i < b->getRankedCandidates().size(); i++) {
      delete b->getRankedCandidates()[i];
    }
    delete b;
}

// getCandidate shall return a nullptr if there are no candidates
// in rankedCandidates_
TEST(GetCandidateTests, NoCandidates) {
    VS::IRBallot *b = new VS::IRBallot(1);

    EXPECT_EQ(b->getCandidate(), nullptr);

    delete b;
}

/**
 * nextCandidate tests
 **/

// nextCandidate shall increment currCandidateIdx_ whenever it is called
TEST(NextCandidateTests, IncrementsCurrCandidateIdx) {
    VS::IRBallot *b = new VS::IRBallot(1);
    b->addCandidate(new VS::Candidate("Candidate","Party",1));
    b->addCandidate(new VS::Candidate("Candidate","Party",2));
    b->addCandidate(new VS::Candidate("Candidate","Party",0));

    EXPECT_EQ(b->getCurrCandidateIdx(), 0);
    EXPECT_EQ(b->getCurrCandidateIdx(), 0);
    b->nextCandidate();
    EXPECT_EQ(b->getCurrCandidateIdx(), 1);
    b->nextCandidate();
    EXPECT_EQ(b->getCurrCandidateIdx(), 2);

    // delete allocated memory
    for (int i = 0; i < b->getRankedCandidates().size(); i++) {
      delete b->getRankedCandidates()[i];
    }
    delete b;
}

// nextCandidate shall not increment currCandidateIdx_ if such an
// incrementation will result in an out of bounds error
TEST(NextCandidateTests, DoesNotIncrementBeyondBounds) {
    VS::IRBallot *b = new VS::IRBallot(1);
    b->addCandidate(new VS::Candidate("Candidate","Party",1));
    b->addCandidate(new VS::Candidate("Candidate","Party",2));
    b->addCandidate(new VS::Candidate("Candidate","Party",0));

    b->nextCandidate();
    b->nextCandidate();
    EXPECT_EQ(b->getCurrCandidateIdx(), 2);

    // this should not increment currCandidateIdx_ since there
    // are only three candidates.
    b->nextCandidate();
    // currCandidateIdx_ should still be 2
    EXPECT_EQ(b->getCurrCandidateIdx(), 2);

    // delete allocated memory
    for (int i = 0; i < b->getRankedCandidates().size(); i++) {
      delete b->getRankedCandidates()[i];
    }
    delete b;
}
