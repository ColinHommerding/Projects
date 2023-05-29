
#include "gtest/gtest.h"
#include <algorithm>
#include <string>
#include <vector>
#include "../src/include/Candidate.h"
#include "../src/include/Ballot.h"

namespace VS = VotingSystem;

/** 
*   This is a helper function that create a vector of ballot, the parameter n shows
*   how many ballot should be in this vector
**/
std::vector<VS::Ballot *> createBallotVector(int n)
{
    std::vector<VS::Ballot *> BallotVector;
    if (n > 0)
    {
        for (int i = 0; i < n; i++)
        {
            BallotVector.push_back(new VS::Ballot(i)); //no sure what's the construtor parameter for ballot
        }
    }
    return BallotVector;
}

//Test Candidate constructor
TEST(CandidateConstructorTests, normalParameters)
{
    VS::Candidate Cand("Trump", "Republican", 0);

    EXPECT_EQ("Trump", Cand.getName());
    EXPECT_EQ("Republican", Cand.getParty());
    EXPECT_EQ(0, Cand.getId());
    EXPECT_EQ(0, Cand.getNumVotes());
    EXPECT_EQ(0, Cand.getBallots().size());
    EXPECT_FALSE(Cand.isEliminated());
}

//Test Candidate addBallot
TEST(CandidateAddBallotTests, normalBallotArray)
{
    VS::Candidate Cand("Trump", "Republican", 0);
    std::vector<VS::Ballot *> BallotVector = createBallotVector(3);
    for (auto element : BallotVector)
    {
        Cand.addBallot(element);
    }
    EXPECT_EQ(3, Cand.getNumVotes());
    EXPECT_EQ(3, Cand.getBallots().size());
}

TEST(CandidateAddBallotTests, EmptyBallotArray)
{
    VS::Candidate Cand("Trump", "Republican", 0);
    std::vector<VS::Ballot *> BallotVector = createBallotVector(0);
    for (auto element : BallotVector)
    {
        Cand.addBallot(element);
    }
    EXPECT_EQ(0, Cand.getNumVotes());
    EXPECT_EQ(0, Cand.getBallots().size());
}

//Test setEliminated
TEST(CandidateSetEliminated, setEliminated)
{
    VS::Candidate Cand("Trump", "Republican", 0);
    EXPECT_FALSE(Cand.isEliminated());
    Cand.setEliminate(10);
    EXPECT_TRUE(Cand.isEliminated());
    EXPECT_EQ(10, Cand.getElimatedRound());
}

TEST(CandidateSetEliminated, setEliminatedWithNegValue)
{
    VS::Candidate Cand("Trump", "Republican", 0);
    EXPECT_FALSE(Cand.isEliminated());
    Cand.setEliminate(-1);
    EXPECT_TRUE(Cand.isEliminated());
    EXPECT_EQ(0, Cand.getElimatedRound());
}
