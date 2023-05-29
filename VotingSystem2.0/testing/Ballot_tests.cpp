
#include "gtest/gtest.h"
#include "../src/include/Ballot.h"
#include <string>
#include <vector>

namespace VS = VotingSystem;

/**
 * Ballot constructor tests
 **/

// Ballots should be created with an ID equal to the passed in value,
// and an empty rankedCandidates_ vector
TEST(BallotConstructorTests, CreateBallotWithID) {
    VS::Ballot *b1 = new VS::Ballot(1);
    VS::Ballot *b2 = new VS::Ballot(0);
    VS::Ballot *b3 = new VS::Ballot(-2);

    // Check if ballot IDs are consistent
    EXPECT_EQ(1, b1->getId());
    EXPECT_EQ(0, b2->getId());
    EXPECT_EQ(-2, b3->getId());

    // Check that rankedCandidates_ vector is empty
    EXPECT_TRUE(b1->getRankedCandidates().size() == 0);
    EXPECT_TRUE(b2->getRankedCandidates().size() == 0);
    EXPECT_TRUE(b3->getRankedCandidates().size() == 0);

    delete b1;
    delete b2;
    delete b3;
}


/**
 * addCandidate tests
 **/

// addCandidate shall append the passed in Candidate object to the end
// of the rankedCandidates_ vector
TEST(AddCandidateTests, AddCandidates) {
    VS::Ballot *b = new VS::Ballot(0);
    b->addCandidate(new VS::Candidate("Candidate","Party",1));
    b->addCandidate(new VS::Candidate("Candidate","Party",2));
    b->addCandidate(new VS::Candidate("Candidate","Party",0));

    // log the id of each candidate when iterating through rankedCandidates_ vector
    std::vector<int> ids;
    for(int i = 0; i < b->getRankedCandidates().size(); i++) {
      ids.push_back(b->getRankedCandidates()[i]->getId());
    }

    // establish expected order of candidate IDs
    std::vector<int> correctOrder{1,2,0};

    EXPECT_EQ(correctOrder, ids);

    // delete allocated memory
    for (int i = 0; i < b->getRankedCandidates().size(); i++) {
      delete b->getRankedCandidates()[i];
    }
    delete b;
}

// addCandidate shall not append any NULL Candidate object
TEST(AddCandidateTests, DoNotAddNullCandidates) {
    VS::Ballot *b = new VS::Ballot(0);
    b->addCandidate(nullptr);
    b->addCandidate(new VS::Candidate("Candidate","Party",1));
    b->addCandidate(new VS::Candidate("Candidate","Party",2));
    b->addCandidate(nullptr);
    b->addCandidate(new VS::Candidate("Candidate","Party",0));
    b->addCandidate(nullptr);
    
    // log the id of each candidate when iterating through getRankedCandidates() vector
    std::vector<int> ids;
    for(int i = 0; i < b->getRankedCandidates().size(); i++) {
	ids.push_back(b->getRankedCandidates()[i]->getId());
    }

    // establish expected order of candidate IDs
    std::vector<int> correctOrder{1,2,0};

    EXPECT_EQ(correctOrder, ids);

    // delete allocated memory
    for (int i = 0; i < b->getRankedCandidates().size(); i++) {
	delete b->getRankedCandidates()[i];
    }
    delete b;
}

// addCandidate shall not append any Candidate with ID already existing
// in rankedCandidates
TEST(AddCandidateTests, DoNotAddDuplicateIdCandidates) {
    VS::Ballot *b = new VS::Ballot(0);
    b->addCandidate(new VS::Candidate("Candidate","Party",1));
    b->addCandidate(new VS::Candidate("Candidate","Party",2));
    VS::Candidate *copyCand2 = new VS::Candidate("CandidateCopy","Party",2);
    VS::Candidate *copyCand1 = new VS::Candidate("CandidateCopy","Party",1);
    b->addCandidate(copyCand2);
    b->addCandidate(copyCand1);
    b->addCandidate(new VS::Candidate("Candidate","Party",0));

    // log the id of each candidate when iterating through getRankedCandidates() vector
    std::vector<int> ids;
    for(int i = 0; i < b->getRankedCandidates().size(); i++) {
	ids.push_back(b->getRankedCandidates()[i]->getId());
    }

    // establish expected order of candidate IDs
    std::vector<int> correctOrder{1,2,0};

    // Candidates should be in order
    EXPECT_EQ(correctOrder, ids);

    // No "CandidateCopy" named candidates should be in getRankedCandidates()
    for (int i = 0; i < b->getRankedCandidates().size(); i++) {
      EXPECT_EQ(b->getRankedCandidates()[i]->getName(), "Candidate");
    }

    // delete allocated memory
    for (int i = 0; i < b->getRankedCandidates().size(); i++) {
	delete b->getRankedCandidates()[i];
    }
    delete b;
    delete copyCand1;
    delete copyCand2;
}

/*
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
*/
