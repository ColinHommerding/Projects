
#include "include/Candidate.h"

using namespace VotingSystem;
using namespace std;

Candidate::Candidate(string Cname, string PartyName, int Cid)
{
    id_ = Cid;
    numVotes_ = 0;
    eliminatedRound_ = 0;
    eliminated_ = false;
    name_ = Cname;
    abbrevName_ = Cname;
    // trim abbrevName_ to store only last name of candidate
    if (Cname != "")
    {
        // remove trailing whitespace
        if (abbrevName_.find_last_not_of(' ') != string::npos)
        {
            abbrevName_ = abbrevName_.substr(0, abbrevName_.find_last_not_of(' ') + 1);
        }
        // remove all but last name
        if (abbrevName_.find_last_of(' ') != string::npos)
        {
            abbrevName_ = abbrevName_.substr(abbrevName_.find_last_of(' '), abbrevName_.size());
        }
        // remove leading whitespace
        if (abbrevName_.find_first_not_of(' ') > 0)
        {
            abbrevName_ = abbrevName_.substr(abbrevName_.find_first_not_of(' '), abbrevName_.size());
        }
    }
    party_ = PartyName;
    ballotList_ = vector<Ballot *>();
}

//Returns the ID of the candidate stored in the id_ attribute.
int Candidate::getId()
{
    return id_;
}

//Returns the current number of votes a candidate has in the numVotes variable.
int Candidate::getNumVotes()
{
    return numVotes_;
}

//Return elimatedRound
int Candidate::getElimatedRound()
{
    return eliminatedRound_;
}

//Returns true if the candidate was eliminated and is out of the running for winning the election.
//Returns false if the candidate is still in the running to win.
bool Candidate::isEliminated()
{
    return eliminated_;
}

//Returns the name of a candidate stored in the name_ attribute
string Candidate::getName()
{
    return name_;
}

//(new)Return the abbrevName
string Candidate::getAbbrevName()
{
    return abbrevName_;
}

//Returns the party_that the candidate is a member of stored in the party_variable.
string Candidate::getParty()
{
    return party_;
}

//Returns an array containing each ballot cast for that candidate contained in the ballotList_array.
//Specifically used for Instant Runoff Elections.
vector<Ballot *> Candidate::getBallots()
{
    return ballotList_;
}

//set isEliminated to true and update the eliminatedRound number as well
void Candidate::setEliminate(int roundNum)
{
    eliminated_ = true;
    if (roundNum > 0)
    {
        eliminatedRound_ = roundNum;
    }
}

//Takes a pointer to a ballot and adds that ballot to the candidates ballot array.
void Candidate::addBallot(Ballot *b)
{
    ballotList_.push_back(b);
    numVotes_++;
}

//increase NumVote by i
void Candidate::increaseNumVote(int i)
{
    numVotes_ += i;
}
