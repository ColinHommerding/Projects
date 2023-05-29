
#include "gtest/gtest.h"
#include "../src/include/OPLElection.h"
#include <string>
#include <vector>


/**
*  These tests are for the OPLElection Constructor
 **/


TEST(ConstructorTest, DefaultConstructor)
{
    std::string election = "Election";
    //std::vector<std::string> vect{"electionFile"};
    std::vector<std::string> vect{"electionFile"};

    VotingSystem::OPLElection *OPLe = new VotingSystem::OPLElection(election, vect, 0);

    EXPECT_EQ(OPLe->getElectionName(), "Election");

    delete OPLe;

}

// /**
// *  These tests are for the OPLElection method sumPartyVotes
//  **/


TEST(sumPartyVotesTests, AccurateAdding)
{

    std::string election = "Election";
    //std::vector<std::string> vect{"electionFile"};
    std::vector<std::string> vect{"electionFile"};

    VotingSystem::Candidate *c = new VotingSystem::Candidate("Bill1", "Independent", 1);
    c->increaseNumVote(1);

    VotingSystem::Candidate *c2 = new VotingSystem::Candidate("Carl", "Independent", 2);
    c2->increaseNumVote(2);

    VotingSystem::Candidate *c3 = new VotingSystem::Candidate("Charles", "Democrat", 3);
    c3->increaseNumVote(3);

    VotingSystem::Candidate *c4 = new VotingSystem::Candidate("Tim", "Democrat", 4);
    c4->increaseNumVote(4);

    VotingSystem::Candidate *c5 = new VotingSystem::Candidate("Larry", "Republican", 5);
    c5->increaseNumVote(5);

    VotingSystem::Candidate *c6 = new VotingSystem::Candidate("Frank", "Republican", 6);
    c6->increaseNumVote(6);

    VotingSystem::OPLElection *OPLe = new VotingSystem::OPLElection(election, vect, 0);


    VotingSystem::OPLParty *party1 = new VotingSystem::OPLParty("party1", 1);


    VotingSystem::OPLParty *party2 = new VotingSystem::OPLParty("party2", 2);


    VotingSystem::OPLParty *party3 = new VotingSystem::OPLParty("party3", 3);


    party1->addCandidate(c);

    party1->addCandidate(c2);

    party2->addCandidate(c3);

    party2->addCandidate(c4);

    party3->addCandidate(c5);

    party3->addCandidate(c6);

    OPLe->addParty(party1);
    OPLe->addParty(party2);
    OPLe->addParty(party3);

    OPLe->sumPartyVotes();

    EXPECT_EQ(party1->getVotes(), 3);
    EXPECT_EQ(party2->getVotes(), 7);
    EXPECT_EQ(party3->getVotes(), 11);

}

TEST(sumPartyVotesTests, NoVotes)
{

    std::string election = "Election";
    //std::vector<std::string> vect{"electionFile"};
    std::vector<std::string> vect{"electionFile"};
    VotingSystem::Candidate *c = new VotingSystem::Candidate("Bill2", "Independent", 1);

    VotingSystem::Candidate *c2 = new VotingSystem::Candidate("Carl", "Independent", 2);

    VotingSystem::Candidate *c3 = new VotingSystem::Candidate("Charles", "Democrat", 3);

    VotingSystem::Candidate *c4 = new VotingSystem::Candidate("Tim", "Democrat", 4);

    VotingSystem::Candidate *c5 = new VotingSystem::Candidate("Larry", "Republican", 5);

    VotingSystem::Candidate *c6 = new VotingSystem::Candidate("Frank", "Republican", 6);

    VotingSystem::OPLElection *OPLe = new VotingSystem::OPLElection(election, vect, 0);


    VotingSystem::OPLParty *party1 = new VotingSystem::OPLParty("party1", 1);


    VotingSystem::OPLParty *party2 = new VotingSystem::OPLParty("party2", 2);


    VotingSystem::OPLParty *party3 = new VotingSystem::OPLParty("party3", 3);


    party1->addCandidate(c);

    party1->addCandidate(c2);

    party2->addCandidate(c3);

    party2->addCandidate(c4);

    party3->addCandidate(c5);

    party3->addCandidate(c6);

    OPLe->addParty(party1);
    OPLe->addParty(party2);
    OPLe->addParty(party3);

    OPLe->sumPartyVotes();

    EXPECT_EQ(party1->getVotes(), 0);
    EXPECT_EQ(party2->getVotes(), 0);
    EXPECT_EQ(party3->getVotes(), 0);

}





// /**
// *  These tests are for the OPLElection method rankCandidatesInParties
//  **/


TEST(rankCandidatesInPartiesTests, AccurateRanking)
{
   std::string election = "Election";
    std::vector<std::string> vect{"electionFile"};

    VotingSystem::Candidate *c = new VotingSystem::Candidate("Bill3", "Independent", 1);
    c->increaseNumVote(1);

    VotingSystem::Candidate *c2 = new VotingSystem::Candidate("Carl", "Independent", 2);
    c2->increaseNumVote(2);

    VotingSystem::Candidate *c3 = new VotingSystem::Candidate("Charles", "Democrat", 3);
    c3->increaseNumVote(3);

    VotingSystem::Candidate *c4 = new VotingSystem::Candidate("Tim", "Democrat", 4);
    c4->increaseNumVote(4);

    VotingSystem::Candidate *c5 = new VotingSystem::Candidate("Larry", "Republican", 5);
    c5->increaseNumVote(5);

    VotingSystem::Candidate *c6 = new VotingSystem::Candidate("Frank", "Republican", 6);
    c6->increaseNumVote(6);

    VotingSystem::OPLElection *OPLe = new VotingSystem::OPLElection(election, vect, 0);


    VotingSystem::OPLParty *party1 = new VotingSystem::OPLParty("party1", 1);


    VotingSystem::OPLParty *party2 = new VotingSystem::OPLParty("party2", 2);


    VotingSystem::OPLParty *party3 = new VotingSystem::OPLParty("party3", 3);


    party1->addCandidate(c);

    party1->addCandidate(c2);

    party2->addCandidate(c3);

    party2->addCandidate(c4);

    party3->addCandidate(c5);

    party3->addCandidate(c6);

    OPLe->addParty(party1);
    OPLe->addParty(party2);
    OPLe->addParty(party3);

    OPLe->rankCandidatesInParties();

    EXPECT_EQ(party1->getCandidates()[0]->getName(), "Carl");
    EXPECT_EQ(party1->getCandidates()[1]->getName(), "Bill3");
    EXPECT_EQ(party2->getCandidates()[0]->getName(), "Tim");
    EXPECT_EQ(party2->getCandidates()[1]->getName(), "Charles");
    EXPECT_EQ(party3->getCandidates()[0]->getName(), "Frank");
    EXPECT_EQ(party3->getCandidates()[1]->getName(), "Larry");

}

TEST(rankCandidatesInPartiesTests, NoCandidates)
{
   std::string election = "Election";
    std::vector<std::string> vect{"electionFile"};

    VotingSystem::OPLElection *OPLe = new VotingSystem::OPLElection(election, vect, 0);


    VotingSystem::OPLParty *party1 = new VotingSystem::OPLParty("party1", 1);


    VotingSystem::OPLParty *party2 = new VotingSystem::OPLParty("party2", 2);


    VotingSystem::OPLParty *party3 = new VotingSystem::OPLParty("party3", 3);

    OPLe->addParty(party1);
    OPLe->addParty(party2);
    OPLe->addParty(party3);

    OPLe->rankCandidatesInParties();

    EXPECT_EQ(party1->getCandidates().size(), 0);
    EXPECT_EQ(party2->getCandidates().size(), 0);
    EXPECT_EQ(party3->getCandidates().size(), 0);

}


// /**
// *  These tests are for the OPLElection method allocateFirstSeats()
//  **/


TEST(allocateFirstSeatsTests, AccurateAllocation)
{
    std::string election = "Election";
    std::vector<std::string> vect{"electionFile"};

    VotingSystem::Candidate *c = new VotingSystem::Candidate("Bill4", "Independent", 1);
    c->increaseNumVote(1);

    VotingSystem::Candidate *c2 = new VotingSystem::Candidate("Carl", "Independent", 2);
    c2->increaseNumVote(1);

    VotingSystem::Candidate *c3 = new VotingSystem::Candidate("Charles", "Democrat", 3);
    c3->increaseNumVote(3);

    VotingSystem::Candidate *c4 = new VotingSystem::Candidate("Tim", "Democrat", 4);
    c4->increaseNumVote(4);

    VotingSystem::Candidate *c5 = new VotingSystem::Candidate("Larry", "Republican", 5);
    c5->increaseNumVote(9);

    VotingSystem::Candidate *c6 = new VotingSystem::Candidate("Frank", "Republican", 6);
    c6->increaseNumVote(6);

    VotingSystem::OPLElection *OPLe = new VotingSystem::OPLElection(election, vect, 0);


    VotingSystem::OPLParty *party1 = new VotingSystem::OPLParty("party1", 1);


    VotingSystem::OPLParty *party2 = new VotingSystem::OPLParty("party2", 2);


    VotingSystem::OPLParty *party3 = new VotingSystem::OPLParty("party3", 3);


    party1->addCandidate(c);

    party1->addCandidate(c2);

    party2->addCandidate(c3);

    party2->addCandidate(c4);

    party3->addCandidate(c5);

    party3->addCandidate(c6);

    OPLe->addPartyAlphabetical(party1);
    OPLe->addPartyAlphabetical(party2);
    OPLe->addPartyAlphabetical(party3);
    OPLe->addParty(party1);
    OPLe->addParty(party2);
    OPLe->addParty(party3);
    OPLe->setNumBallots(24);
    OPLe->setSeats(4);
    OPLe->sumPartyVotes();
    OPLe->allocateFirstSeats();

    EXPECT_EQ(party1->getSeats(), 0);
    EXPECT_EQ(party2->getSeats(), 1);
    EXPECT_EQ(party3->getSeats(), 2);

}

TEST(allocateFirstSeatsTests, AllVoteOneCand)
{
    std::string election = "Election";
    std::vector<std::string> vect{"electionFile"};

    VotingSystem::Candidate *c = new VotingSystem::Candidate("Bill5", "Independent", 1);
    c->increaseNumVote(0);

    VotingSystem::Candidate *c2 = new VotingSystem::Candidate("Carl", "Independent", 2);
    c2->increaseNumVote(0);

    VotingSystem::Candidate *c3 = new VotingSystem::Candidate("Charles", "Democrat", 3);
    c3->increaseNumVote(0);

    VotingSystem::Candidate *c4 = new VotingSystem::Candidate("Tim", "Democrat", 4);
    c4->increaseNumVote(0);

    VotingSystem::Candidate *c5 = new VotingSystem::Candidate("Larry", "Republican", 5);
    c5->increaseNumVote(0);

    VotingSystem::Candidate *c6 = new VotingSystem::Candidate("Frank", "Republican", 6);
    c6->increaseNumVote(24);

    VotingSystem::OPLElection *OPLe = new VotingSystem::OPLElection(election, vect, 0);


    VotingSystem::OPLParty *party1 = new VotingSystem::OPLParty("party1", 1);


    VotingSystem::OPLParty *party2 = new VotingSystem::OPLParty("party2", 2);


    VotingSystem::OPLParty *party3 = new VotingSystem::OPLParty("party3", 3);


    party1->addCandidate(c);

    party1->addCandidate(c2);

    party2->addCandidate(c3);

    party2->addCandidate(c4);

    party3->addCandidate(c5);

    party3->addCandidate(c6);

    OPLe->addPartyAlphabetical(party1);
    OPLe->addPartyAlphabetical(party2);
    OPLe->addPartyAlphabetical(party3);
    OPLe->addParty(party1);
    OPLe->addParty(party2);
    OPLe->addParty(party3);
    OPLe->setNumBallots(24);
    OPLe->setSeats(4);
    OPLe->sumPartyVotes();
    OPLe->allocateFirstSeats();

    EXPECT_EQ(party1->getSeats(), 0);
    EXPECT_EQ(party2->getSeats(), 0);
    EXPECT_EQ(party3->getSeats(), 4);

}

TEST(orderPartiesByRemainder, AccurateOrder)
{
    std::string election = "Election";
    std::vector<std::string> vect{"electionFile"};

    VotingSystem::Candidate *c = new VotingSystem::Candidate("Bill6", "Independent", 1);
    c->increaseNumVote(8);

    VotingSystem::Candidate *c2 = new VotingSystem::Candidate("Carl", "Independent", 2);
    c2->increaseNumVote(2);

    VotingSystem::Candidate *c3 = new VotingSystem::Candidate("Charles", "Democrat", 3);
    c3->increaseNumVote(4);

    VotingSystem::Candidate *c4 = new VotingSystem::Candidate("Tim", "Democrat", 4);
    c4->increaseNumVote(5);

    VotingSystem::Candidate *c5 = new VotingSystem::Candidate("Larry", "Republican", 5);
    c5->increaseNumVote(0);

    VotingSystem::Candidate *c6 = new VotingSystem::Candidate("Frank", "Republican", 6);
    c6->increaseNumVote(5);

    VotingSystem::OPLElection *OPLe = new VotingSystem::OPLElection(election, vect, 0);


    VotingSystem::OPLParty *party1 = new VotingSystem::OPLParty("party1", 1);


    VotingSystem::OPLParty *party2 = new VotingSystem::OPLParty("party2", 2);


    VotingSystem::OPLParty *party3 = new VotingSystem::OPLParty("party3", 3);


    party1->addCandidate(c);

    party1->addCandidate(c2);

    party2->addCandidate(c3);

    party2->addCandidate(c4);

    party3->addCandidate(c5);

    party3->addCandidate(c6);

    OPLe->addPartyAlphabetical(party1);
    OPLe->addPartyAlphabetical(party2);
    OPLe->addPartyAlphabetical(party3);
    OPLe->addParty(party1);
    OPLe->addParty(party2);
    OPLe->addParty(party3);
    OPLe->setNumBallots(24);
    OPLe->setSeats(4);
    OPLe->sumPartyVotes();
    OPLe->allocateFirstSeats();
    OPLe->orderPartiesByRemainder();

    EXPECT_EQ(OPLe->getParties()[0]->getName(), "party3");
    EXPECT_EQ(OPLe->getParties()[1]->getName(), "party1");
    EXPECT_EQ(OPLe->getParties()[2]->getName(), "party2");
}


// /**
// *  These tests are for the OPLElection method allocateRemainingSeats()
//  **/


TEST(allocateRemainingSeats, AccurateAllocation)
{
   std::string election = "Election";
    std::vector<std::string> vect{"electionFile"};

    VotingSystem::Candidate *c = new VotingSystem::Candidate("Bill7", "Independent", 1);
    c->increaseNumVote(1);

    VotingSystem::Candidate *c2 = new VotingSystem::Candidate("Carl", "Independent", 2);
    c2->increaseNumVote(1);

    VotingSystem::Candidate *c3 = new VotingSystem::Candidate("Charles", "Democrat", 3);
    c3->increaseNumVote(3);

    VotingSystem::Candidate *c4 = new VotingSystem::Candidate("Tim", "Democrat", 4);
    c4->increaseNumVote(4);

    VotingSystem::Candidate *c5 = new VotingSystem::Candidate("Larry", "Republican", 5);
    c5->increaseNumVote(9);

    VotingSystem::Candidate *c6 = new VotingSystem::Candidate("Frank", "Republican", 6);
    c6->increaseNumVote(6);

    VotingSystem::OPLElection *OPLe = new VotingSystem::OPLElection(election, vect, 0);


    VotingSystem::OPLParty *party1 = new VotingSystem::OPLParty("party1", 1);


    VotingSystem::OPLParty *party2 = new VotingSystem::OPLParty("party2", 2);


    VotingSystem::OPLParty *party3 = new VotingSystem::OPLParty("party3", 3);


    party1->addCandidate(c);

    party1->addCandidate(c2);

    party2->addCandidate(c3);

    party2->addCandidate(c4);

    party3->addCandidate(c5);

    party3->addCandidate(c6);

    OPLe->addPartyAlphabetical(party1);
    OPLe->addPartyAlphabetical(party2);
    OPLe->addPartyAlphabetical(party3);
    OPLe->addParty(party1);
    OPLe->addParty(party2);
    OPLe->addParty(party3);
    OPLe->setNumBallots(24);
    OPLe->setSeats(4);
    OPLe->sumPartyVotes();
    OPLe->allocateFirstSeats();
    OPLe->orderPartiesByRemainder();
    OPLe->allocateRemainingSeats();

    EXPECT_EQ(party1->getSeats(), 0);
    EXPECT_EQ(party2->getSeats(), 1);
    EXPECT_EQ(party3->getSeats(), 3);


}



// /**
// *  These tests are for the OPLElection method assignCandidates()
//  **/

TEST(assignCandidatesTests, CorrectAmount)
{
    std::string election = "Election";
    std::vector<std::string> vect{"electionFile"};

    VotingSystem::Candidate *c = new VotingSystem::Candidate("Bill8", "Independent", 1);
    c->increaseNumVote(1);

    VotingSystem::Candidate *c2 = new VotingSystem::Candidate("Carl", "Independent", 2);
    c2->increaseNumVote(1);

    VotingSystem::Candidate *c3 = new VotingSystem::Candidate("Charles", "Democrat", 3);
    c3->increaseNumVote(3);

    VotingSystem::Candidate *c4 = new VotingSystem::Candidate("Tim", "Democrat", 4);
    c4->increaseNumVote(4);

    VotingSystem::Candidate *c5 = new VotingSystem::Candidate("Larry", "Republican", 5);
    c5->increaseNumVote(9);

    VotingSystem::Candidate *c6 = new VotingSystem::Candidate("Frank", "Republican", 6);
    c6->increaseNumVote(6);

    VotingSystem::OPLElection *OPLe = new VotingSystem::OPLElection(election, vect, 0);


    VotingSystem::OPLParty *party1 = new VotingSystem::OPLParty("party1", 1);


    VotingSystem::OPLParty *party2 = new VotingSystem::OPLParty("party2", 2);


    VotingSystem::OPLParty *party3 = new VotingSystem::OPLParty("party3", 3);


    party1->addCandidate(c);

    party1->addCandidate(c2);

    party2->addCandidate(c3);

    party2->addCandidate(c4);

    party3->addCandidate(c5);

    party3->addCandidate(c6);

    OPLe->addPartyAlphabetical(party1);
    OPLe->addPartyAlphabetical(party2);
    OPLe->addPartyAlphabetical(party3);
    OPLe->addParty(party1);
    OPLe->addParty(party2);
    OPLe->addParty(party3);
    OPLe->setNumBallots(24);
    OPLe->setSeats(4);
    OPLe->sumPartyVotes();
    OPLe->allocateFirstSeats();
    OPLe->orderPartiesByRemainder();
    OPLe->allocateRemainingSeats();
    OPLe->assignCandidates();

    EXPECT_EQ(OPLe->getWinners().size(), 3);

    // Find and store audit file name
    time_t date = OPLe->getDate();
    char auditName[100];
    strftime(auditName, 100, "election_audit_%m_%d_%Y_%H%M%S.txt", localtime(&date));
    // remove audit file
    remove(auditName);
}
