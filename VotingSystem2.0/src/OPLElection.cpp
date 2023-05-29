
#include "include/OPLElection.h"
#include "include/Election.h"
#include "include/Candidate.h"
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <string>
#include <unordered_map>

namespace VotingSystem
{

    OPLElection::OPLElection(std::string electionName, std::vector<std::string> filenames_vec, int debug)
        : Election(electionName, filenames_vec, debug)
    {
        electionName_ = electionName; //sets election name
        totalSeats_ = 0;
        numParties_ = 0;
        numSeats_ = 0;
        numBallots_ = 0;
        numAllocatedSeats_ = 0;
        quota_ = 0;
    }

    OPLElection::~OPLElection() {}

    void OPLElection::addParty(VotingSystem::OPLParty *party)
    {
        party_.push_back(party);
        numParties_++;
    }

    void OPLElection::setSeats(int seats)
    {
        numSeats_ = seats;
    }

    void OPLElection::setNumBallots(int ballots)
    {
        numBallots_ = ballots;
    }

    void OPLElection::addPartyAlphabetical(VotingSystem::OPLParty *party)
    {
        alphabetPartyList_.push_back(party);
    }

    bool OPLElection::check_header_consistency()
    {
        /**
         *open input files
        */
        std::ifstream fileC;
        std::string LineElectionType;
        std::string LineNumCandidates;
        std::string LineCandidate;
        std::string LineOPLSeats;

        //open first input files and get basic header info
        fileC.open(filenames_[0].c_str());
        //checking whether the file is open or not
        if (!fileC.is_open())
        {
            std::cout << "input file " << filenames_[0] << " can't be opened" << std::endl;
            return false;
        }
        std::getline(fileC, LineElectionType);
        std::getline(fileC, LineNumCandidates);
        std::getline(fileC, LineCandidate);
        std::getline(fileC, LineOPLSeats);
        fileC.close();

        //open rest files and check header consistency
        for (int i = 1; i < filenames_.size(); i++)
        {
            fileC.open(filenames_[i].c_str());
            //checking whether the file is open or not
            if (!fileC.is_open())
            {
                std::cout << "input file " << filenames_[i] << " can't be opened" << std::endl;
                return false;
            }
            //parse header info
            std::string tempType = "";
            std::string tempNumCandidate = "";
            std::string tempCandidate = "";
            std::string tempOPLSeats = "";
            std::getline(fileC, tempType);
            std::getline(fileC, tempNumCandidate);
            std::getline(fileC, tempCandidate);
            std::getline(fileC, tempOPLSeats);

            //compare header infos
            if (tempType != LineElectionType || tempNumCandidate != LineNumCandidates || tempCandidate != LineCandidate || tempOPLSeats != LineOPLSeats)
            {
                if (!debugMode_)
                {
                    std::cout << "Inconsistent header information, check input files." << std::endl;
                }
                fileC.close();
                return false;
            }
            fileC.close();
        }
        return true;
    }

    void OPLElection::readHeader(int fileno)
    {
        if (fileno == 0)
        {
            inputFile_.open(filenames_[fileno]); //opening whichever file

            std::string ln; //creates a buffer to store each line of the csv file
            getline(inputFile_, ln);
            electionType_ = ln; //set election type
            getline(inputFile_, ln);
            numCandidates_ = stoi(ln); //sets number of candidates
            getline(inputFile_, ln);
            std::string name;
            std::string partyName;
            int id = 0;
            int partyId;
            for (int i = 0; i < numCandidates_; i++)
            { //loops for thrugh the candidates line and creates all proper candidates and parties for the election
                ln.erase(0, 1);
                name = ln.substr(0, ln.find(","));
                ln.erase(0, ln.find(",") + 1);
                partyName = ln.substr(0, ln.find("]"));
                if (party_.size() == 0)
                {
                    OPLParty *party = new OPLParty(partyName, partyId);
                    partyId++;
                    party_.push_back(party);
                }
                bool check = true;
                for (int j = 0; j < party_.size(); j++) //loops through party vector to see if party was already created and if not creates and adds the party.
                {

                    if (party_[j]->getName() == partyName)
                    {
                        check = false;
                    }
                    else
                    {
                    }
                }
                if (check)
                {
                    OPLParty *party = new OPLParty(partyName, partyId);
                    partyId++;
                    party_.push_back(party);
                }
                Candidate *newCandidate = new Candidate(name, partyName, id);
                candidatesList_.push_back(newCandidate);
                for (int k = 0; k < party_.size(); k++)
                {
                    if (party_[k]->getName() == partyName)
                    {
                        party_[k]->addCandidate(newCandidate); //adds candidates to proper parties
                    }
                }
                id++;
                if (i == numCandidates_ - 1)
                {
                    break; // break to avoid going out of bounds
                }
                ln.erase(0, ln.find(",") + 1);
            }
            getline(inputFile_, ln);
            totalSeats_ = stoi(ln); //need to keep the total seat data for generate output and media file
            numSeats_ = stoi(ln);   //sets number of seats
            getline(inputFile_, ln);
            numBallots_ = stoi(ln); //sets number of ballots
            recentFileBallots_ = stoi(ln);
            numParties_ = party_.size(); //sets number of parties.

            // Create alphabetCandidatesList_
            for (int i = 0; i < numCandidates_; i++)
            {
                alphabetCandidatesList_.push_back(candidatesList_[i]);
            }
            // sort by candidate's last name
            std::sort(alphabetCandidatesList_.begin(), alphabetCandidatesList_.end(),
                      [](Candidate *a, Candidate *b) {
                          return a->getAbbrevName() < b->getAbbrevName();
                      });

            // create alphabetPartiesList_
            for (int i = 0; i < numParties_; i++)
            {
                alphabetPartyList_.push_back(party_[i]);
            }
            // sort by party's last name
            std::sort(alphabetPartyList_.begin(), alphabetPartyList_.end(),
                      [](OPLParty *a, OPLParty *b) { return a->getName() < b->getName(); });

            // AUDIT FILE: Add Election Overview information to audit file
            auditFile_ << "*** ELECTION OVERVIEW ***" << std::endl;
            auditFile_ << numParties_ << " Parties, "
                       << numCandidates_ << " Candidates" << std::endl;
            auditFile_ << numSeats_ << " seats to be filled" << std::endl;
            if (numBallots_ == 0)
            {
                auditFile_ << "There are " << numBallots_ << " ballots cast" << std::endl;
            }
            auditFile_ << std::endl;

            //AUDIT FILE: Add Parties and Candidates section
            auditFile_ << "*** PARTIES AND CANDIDATES ***" << std::endl;
            for (int i = 0; i < numParties_; i++)
            {
                OPLParty *p = alphabetPartyList_[i];
                auditFile_ << p->getName() << ":" << std::endl;
                for (int j = 0; j < p->getCandidates().size(); j++)
                {
                    //sort candidates by abbrevname
                    std::vector<Candidate *> pcands = p->getCandidates();
                    std::sort(pcands.begin(), pcands.end(),
                              [](Candidate *a, Candidate *b) {
                                  return a->getAbbrevName() < b->getAbbrevName();
                              });
                    auditFile_ << "\t" << pcands[j]->getName() << std::endl;
                }
            }
            auditFile_ << "\n"
                       << std::endl;
        }
        else
        {
            inputFile_.close();
            inputFile_.open(filenames_[fileno]); //opening whichever file
            std::string ln;                      //creates a buffer to store each line of the csv file
            getline(inputFile_, ln);
            getline(inputFile_, ln);
            getline(inputFile_, ln);
            getline(inputFile_, ln);
            getline(inputFile_, ln);
            numBallots_ += stoi(ln);
            recentFileBallots_ = stoi(ln);
        }
    }

    void OPLElection::verifyInfo()
    {
        //verifty info
        std::cout << "****** VerifyInfo ******" << std::endl;
        std::cout << numParties_ << " Parties, " << numCandidates_ << " Candidates" << std::endl;
        std::cout << totalSeats_ << " Seats to be filled" << std::endl;
        std::cout << "Total Votes - " << numBallots_ << " Votes" << std::endl;
        std::cout << std::endl;

        char c;
        std::cout << "This is information correct? Type Y/N. (Pressing N will exit program.)" << std::endl;
        if (!debugMode_)
        {
            std::cin >> c;
        }
        else
        {
            c = 'Y';
        }
        c = toupper(c);
        while (c != 'N' && c != 'Y')
        {
            std::cout << "Please Type Y/N. Y is for Yes, the information is correct. N is for no, it's not correct" << std::endl;
            std::cin >> c;
            c = toupper(c);
        }
        if (toupper(c) == 'N')
        {
            printf("Program terminated\n");
            auditFile_.close();

            // delete audit file if user types N
            removeAuditFile();
            exit(EXIT_FAILURE);
        }
    }

    void OPLElection::readBallots(int startID)
    {
        std::string ln;
        for (int i = 0; i < recentFileBallots_; i++) //loops through all ballots in csv file
        {
            getline(inputFile_, ln); //obtains ballot line
            for (int j = 0; j < numCandidates_; j++)
            {
                if (ln.substr(0, 1) == "1") //checks for if a particular candidate recieved the vote
                {
                    candidatesList_[j]->increaseNumVote(1); //gives a candidate their vote
                    Ballot *newBallot = new Ballot(startID + i + 1);
                    newBallot->addCandidate(candidatesList_[j]);
                    ballotsList_.push_back(newBallot);
                    break;
                }
                else
                {
                    ln.erase(0, 1);
                }
            }
        }
    }

    void OPLElection::writeBallotsToAudit()
    {
        //AUDIT FILE: Log Ballot Section
        auditFile_ << "*** BALLOTS ***" << std::endl;
        auditFile_ << numBallots_ << " ballots cast" << std::endl;
        if (numBallots_ > 0)
        {
            auditFile_ << "Ballots are given IDs b1 to b" << numBallots_ << std::endl;
            auditFile_ << "Ballot's chosen candidate and party listed\n"
                       << std::endl;
        }

        //Log candidates and ballots
        for (int i = 0; i < numBallots_; i++)
        {
            Ballot *b = ballotsList_[i];
            Candidate *c = b->getRankedCandidates()[0];
            auditFile_ << "b" << b->getId() << ": "
                       << c->getAbbrevName() << " ("
                       << c->getParty() << ")" << std::endl;
        }

        auditFile_ << "\n"
                   << std::endl;
    }

    void OPLElection::sumPartyVotes()
    {
        for (int i = 0; i < numParties_; i++) //loops through all parties and sums their candidates votes.
        {
            party_[i]->sumCandidateVotes();
        }
    }

    void OPLElection::rankCandidatesInParties()
    {
        for (int i = 0; i < numParties_; i++) //loops through all parties and orders their candidates by vote totals
        {
            if (debugMode_)
            {
                party_[i]->orderCandidates(1);
            }
            else
            {
                party_[i]->orderCandidates(0);
            }
        }
    }

    void OPLElection::allocateFirstSeats()
    {
        int totalSeatsFilled = 0;
        quota_ = std::ceil((float)numBallots_ / (float)numSeats_); //calculates quota

        //AUDIT FILE: Log first allocation
        auditFile_ << "*** FIRST ALLOCATION ***" << std::endl;
        auditFile_ << "QUOTA = number of ballots cast / number of seats" << std::endl;
        auditFile_ << "\tA party needs " << quota_ << " votes per seat awarded\n"
                   << std::endl;
        auditFile_ << "Number of allocated seats for party" << std::endl;
        auditFile_ << "\tfloor(number of votes party received / quota)\n"
                   << std::endl;

        for (int i = 0; i < numParties_; i++)
        {
            int firstSeats = alphabetPartyList_[i]->getVotes() / quota_;    //calculates a parties first seats
            int remainder = (alphabetPartyList_[i]->getVotes() % (quota_)); //calculates a parties remainder votes
            alphabetPartyList_[i]->addSeats(firstSeats);
            numSeats_ = numSeats_ - firstSeats;
            totalSeatsFilled += firstSeats;
            alphabetPartyList_[i]->updateRemainingVotes(remainder);

            //AUDIT FILE: Log party's first seats
            auditFile_ << alphabetPartyList_[i]->getName() << " wins "
                       << firstSeats << " seats" << std::endl;
        }

        //AUDIT FILE: log total number of seats filled
        auditFile_ << "\n"
                   << totalSeatsFilled << " seats filled\n\n"
                   << std::endl;
    }

    void OPLElection::orderPartiesByRemainder()
    {
        auto compare = [](OPLParty *a, OPLParty *b) {
            return a->getRemainingVotes() >= b->getRemainingVotes();
        };
        std::sort(party_.begin(), party_.end(), compare);

        size_t i = 0;
        size_t j = i + 1;
        std::vector<OPLParty *> ties;
        int usedCoinFlip = 0; // bool to check whether order was done through randomization
        // Go through candidates_ and randomly rearrange any candidates with
        // the same number of votes
        while (i < party_.size())
        {
            j = i + 1;
            while ((j < party_.size()) &&
                   (party_[j]->getRemainingVotes() == party_[i]->getRemainingVotes()))
            {
                j++; // j is first candidate after i with a different numVotes_ than i
            }
            while (j - i > 1)
            {
                // populate ties vector with all candidates in range [i,j)
                for (size_t k = i; k < j; k++)
                {
                    ties.push_back(party_[k]);
                }
                // randomly select one of the tied candidates
                OPLParty *p;
                if (debugMode_)
                {
                    p = nullptr;
                    for (int i = 0; i < ties.size(); i++)
                    {
                        if (p == nullptr || ties[i]->getID() < p->getID())
                        {
                            p = ties[i];
                        }
                    }
                }
                else
                {
                    p = coinFlip(ties);
                }
                usedCoinFlip = 1;
                // find selected candidate's index in candidates_
                int pIdx;
                for (int k = i; i < j; k++)
                {
                    if (party_[k]->getID() == p->getID())
                    {
                        pIdx = k;
                        break;
                    }
                }
                // clear ties vector
                ties.clear();
                // swap candidate at i with selected candidate
                OPLParty *pAtI = party_[i];
                party_.erase(party_.begin() + i);
                party_.insert(party_.begin() + i, p);
                party_.erase(party_.begin() + pIdx);
                party_.insert(party_.begin() + pIdx, pAtI);

                // increment i
                i++;
            }
            // i and j are next to each other -> increment i
            i++;
        }
        //AUDIT FILE: Write if coinFlip was used
        if (usedCoinFlip)
        {
            auditFile_ << "Randomization was used to order parties that have the same number"
                       << " of remaining votes" << std::endl;
        }
    }
    void OPLElection::allocateRemainingSeats()
    {
        //AUDIT FILE: log Remainder Allocation section
        auditFile_ << "*** REMAINDER ALLOCATION ***" << std::endl;
        auditFile_ << numSeats_ << " seats remaining\n"
                   << std::endl;
        if (numSeats_ != 0)
        {
            auditFile_ << "Remaining votes calculated by" << std::endl;
            auditFile_ << "\tnum votes party received - "
                       << "(quota * num seats allocated at first allocation)\n"
                       << std::endl;

            //AUDIT FILE: log each party's remaining votes
            for (int i = 0; i < numParties_; i++)
            {
                OPLParty *p = alphabetPartyList_[i];
                auditFile_ << p->getName() << " : "
                           << p->getRemainingVotes() << " remaining votes" << std::endl;
            }

            auditFile_ << "Remaining seats chosen in order of "
                       << "most remaining votes to least\n\t" << std::endl;

            // sort parties by remaining votes
            this->orderPartiesByRemainder();

            for (int i = 0; i < numParties_ - 1; i++)
            {
                auditFile_ << party_[i]->getName() << " -> ";
            }
            auditFile_ << party_[numParties_ - 1]->getName() << "\n"
                       << std::endl;

            int i = 0;
            while (this->numSeats_ > 0) //checks if there are remaining seats to be awarded.
            {
                party_[i]->addSeats(1);
                auditFile_ << party_[i]->getName() << " wins 1 additional seat" << std::endl;
                i++;
                if (i == numParties_) //resets index to avoid going out of bounds
                {
                    i == 0;
                }

                this->numSeats_--;
            }
        }
        auditFile_ << std::endl;

        auditFile_ << "*** FINAL SEAT ALLOCATION ***" << std::endl;
        auto compare = [](OPLParty *p1, OPLParty *p2) {
            if (p1->getSeats() != p2->getSeats())
            {
                // sort by number of seats won
                return p1->getSeats() > p2->getSeats();
            }
            else
            {
                // if multiple parties win same number of seats,
                // sort them by party name
                return p1->getName() < p2->getName();
            }
        };
        std::sort(party_.begin(), party_.end(), compare);

        for (int i = 0; i < numParties_; i++)
        {
            OPLParty *p = party_[i];
            auditFile_ << p->getName() << " wins " << p->getSeats() << " seats" << std::endl;
        }
    }

    void OPLElection::generateTermOutput()
    {

        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "************** Preliminary Output ***************" << std::endl;
        std::cout << "(See audit file and media file for details)" << std::endl;

        //Election info
        std::cout << "Election Name: " << electionName_ << std::endl;
        std::cout << "Election Type : Open Party List" << std::endl;
        std::cout << std::endl;

        //Election overview
        std::cout << "********* ELECTION OVERVIEW *********" << std::endl;
        std::cout << numParties_ << " Parties, " << numCandidates_ << " Candidates" << std::endl;
        std::cout << totalSeats_ << " Seats to be filled" << std::endl;
        std::cout << std::endl;

        //Result
        std::cout << "*************** Votes ***************" << std::endl;
        std::cout << "Total Votes - " << numBallots_ << " Votes" << std::endl;
        for (int i = 0; i < numCandidates_; i++)
        {
            Candidate *c = candidatesList_[i];
            std::string cName = c->getAbbrevName();
            std::string cParty = c->getParty();
            int cVotes = c->getNumVotes();
            int cVotePercentage = 0;
            if (numBallots_ != 0)
            {
                cVotePercentage = (cVotes * 100 / numBallots_);
            }
            //std::cout << std::setw(20) << cName << std::setw(25) << cParty << std::setw(20) << cVotePercentage << std::setw(15) << cVotes << std::endl;
            printf("%s (%s) :16 (%d%%) - %d Votes\n", cName.c_str(), cParty.c_str(), cVotePercentage, cVotes);
        }
        std::cout << std::endl;

        //Winners
        std::cout << "*************** Winners *************" << std::endl;
        for (int i = 0; i < numParties_; i++)
        {
            OPLParty *p = party_[i];
            //std::cout<< p->getName()<<"has winner candidate: "<<p->getWinnerCandidates().size()<< std::endl;
            if (p->getWinnerCandidates().size() != 0)
            {
                std::cout << p->getName() << ":" << std::endl;
                for (int j = 0; j < p->getWinnerCandidates().size(); j++)
                {
                    Candidate *c = p->getWinnerCandidates()[j];
                    std::cout << "  " << c->getAbbrevName() << std::endl;
                }
            }
        }
    }

    void OPLElection::generateMediaFile()
    {

        //create mediafile
        std::ofstream mediaFile;
        char date[100];
        strftime(date, 100, "_%m-%d-%Y_%I%M%S", localtime(&electionDate_));
        std::string time = date;
        std::string media_File_String = "election_media_" + electionName_ + time + ".txt";
        mediaFile.open(media_File_String);

        //Eleciton info
        mediaFile << "*********** OFFICIAL ELECTION MEDIA FILE ***********"
                  << std::endl;
        strftime(date, 100, "%B %d, %Y at %I:%M:%S %p", localtime(&electionDate_));
        mediaFile << "File generated on " << date << std::endl;
        mediaFile << "Eleciton Type: Open Party List (OPL)"
                  << std::endl;
        mediaFile << "Election Name: " << electionName_ << std::endl;
        mediaFile << std::endl;

        //Eleciton overview
        mediaFile << "**************** ELECTION OVERVIEW *****************" << std::endl;
        mediaFile << numParties_ << " Parties, " << numCandidates_ << " Candidates" << std::endl;
        mediaFile << totalSeats_ << " Seats to be filled" << std::endl;
        mediaFile << std::endl;

        //Party and Candidate info
        mediaFile << "************** PARTIES AND CANDIDATES **************" << std::endl;

        for (int i = 0; i < numParties_; i++)
        {
            OPLParty *p = party_[i];
            mediaFile << p->getName() << ":" << std::endl;
            for (int j = 0; j < p->getCandidates().size(); j++)
            {
                Candidate *c = p->getCandidates()[j];
                mediaFile << "  " << c->getAbbrevName() << std::endl;
            }
        }
        mediaFile << std::endl;

        //Result
        mediaFile << "**************** RESULTS ****************" << std::endl;
        mediaFile << "Total Votes - " << numBallots_ << " Votes" << std::endl;
        for (int i = 0; i < numCandidates_; i++)
        {
            Candidate *c = candidatesList_[i];
            std::string cName = c->getAbbrevName();
            std::string cParty = c->getParty();
            int cVotes = c->getNumVotes();
            int cVotePercentage = 0;
            if (numBallots_ != 0)
            {
                cVotePercentage = (cVotes * 100 / numBallots_);
            }
            mediaFile << cName << " (" << cParty << ") : (" << cVotePercentage << "%) - " << cVotes << " Votes" << std::endl;
            //printf("%s (%s) :16 (%d%%) - %d Votes\n", cName.c_str(), cParty.c_str(), cVotePercentage, cVotes);
        }
        mediaFile << std::endl;

        // Winners
        mediaFile << "*************** Winners ****************" << std::endl;
        for (int i = 0; i < numParties_; i++)
        {
            OPLParty *p = party_[i];
            //std::cout<< p->getName()<<"has winner candidate: "<<p->getWinnerCandidates().size()<< std::endl;
            if (p->getWinnerCandidates().size() != 0)
            {
                mediaFile << p->getName() << ":" << std::endl;
                for (int j = 0; j < p->getWinnerCandidates().size(); j++)
                {
                    Candidate *c = p->getWinnerCandidates()[j];
                    mediaFile << "  " << c->getAbbrevName() << std::endl;
                }
            }
        }
        mediaFile.close();
    }

    void OPLElection::assignCandidates()
    {
        //AUDIT FILE: log Candidate rankings by number of votes and
        // which candidates get seats
        auditFile_ << "\n\n*** CANDIDATE ALLOCATION ***" << std::endl;
        auditFile_ << "Candidates listed in order of votes received" << std::endl;
        auditFile_ << "Candidates at top of list for each party" << std::endl;
        auditFile_ << "\tselected first for seats" << std::endl;
        auditFile_ << "If multiple candidates in the same party have\n"
                   << "\tthe same number of votes, the order of those\n"
                   << "\tcandidates is randomized\n"
                   << std::endl;

        for (int i = 0; i < numParties_; i++)
        {
            OPLParty *p = alphabetPartyList_[i];
            auditFile_ << p->getName() << ":" << std::endl;
            for (int j = 0; j < p->getCandidates().size(); j++)
            {
                std::vector<Candidate *> pcands = p->getCandidates();
                auditFile_ << "\t" << pcands[j]->getName() << std::endl;
            }
        }
        auditFile_ << "\n"
                   << std::endl;

        for (int i = 0; i < numParties_; i++)
        {
            std::vector<Candidate *> winners = party_[i]->assignCandidatesToSeats(); //hands out each parties earned seats to their candidates
            for (int j = 0; j < winners.size(); j++)                                 //loops through winners adding them as winners and printing them out
            {

                winners_.push_back(winners[j]);
                //std::cout << winners[j]->getName() << "\n"<< std::endl;
            }
        }
    }

    void OPLElection::run()
    { //run drives the election along and calls all other methods

        if (check_header_consistency() == false)
        {
            auditFile_.close();
            removeAuditFile();
            return;
        }
        //AUDIT FILE: Add election date/time/type to audit file
        auditFile_ << "****** OFFICIAL ELECTION AUDIT FILE ******" << std::endl;
        if (debugMode_)
        {
            auditFile_ << "This audit file was generated from an election run in debug mode\n";
            auditFile_ << "Election results may not be fair" << std::endl;
        }
        char date[100];
        strftime(date, 100, "%B %d, %Y at %I:%M:%S %p", localtime(&electionDate_));
        auditFile_ << "File generated on " << date << std::endl;
        auditFile_ << "Voting System : Open Party List (OPL)\n\n"
                   << std::endl;
        int startID = 0;
        for (int i = 0; i < numFiles_; i++)
        {
            this->readHeader(i);
            this->readBallots(startID);
            startID = numBallots_;
        }
        
        this->writeBallotsToAudit();
        if (!debugMode_)
        {
            this->verifyInfo();
        }
        int totalNumSeats = numSeats_;

        //if either value is 0, there is no meaning to run the election
        if(numSeats_ == 0 || numCandidates_ == 0 || numBallots_ == 0){
            if(!debugMode_){
                std::cout << "Your input file has either empty candidates or empty ballots or empty seats. Election not run." << std::endl;
            }
            //remove auditFile
            auditFile_.close();
            removeAuditFile();
            return;
        }
        if (numSeats_ > 0 && numCandidates_ > 0 && numBallots_ > 0)
        {
            //this->readBallots();

            //AUDIT FILE: Log vote distribution
            auditFile_ << "*** VOTE DISTRIBUTION ***" << std::endl;
            for (int i = 0; i < numParties_; i++)
            {
                OPLParty *p = alphabetPartyList_[i];
                p->sumCandidateVotes();
                auditFile_ << p->getName() << " : " << p->getVotes() << " votes" << std::endl;
                for (int j = 0; j < p->getCandidates().size(); j++)
                {
                    Candidate *c = p->getCandidates()[j];
                    auditFile_ << "\t" << c->getAbbrevName() << " : "
                               << c->getNumVotes() << " votes" << std::endl;
                }
            }
            auditFile_ << "\n"
                       << std::endl;

            this->rankCandidatesInParties();
            this->allocateFirstSeats();
            this->allocateRemainingSeats();
            this->assignCandidates();

            //AUDIT FILE: Log results
            auditFile_ << "*** RESULTS ***" << std::endl;
            //sort winners by alphabetical order
            std::sort(winners_.begin(), winners_.end(),
                      [](Candidate *c1, Candidate *c2) {
                          return c1->getAbbrevName() < c2->getAbbrevName();
                      });
            for (int i = 0; i < winners_.size(); i++)
            {
                auditFile_ << winners_[i]->getAbbrevName() << " ("
                           << winners_[i]->getParty() << ") wins seat" << std::endl;
            }
        }
        auditFile_ << "\nThere are " << totalNumSeats - winners_.size() << " remaining seats to be filled by candidates" << std::endl;
        if (totalNumSeats - winners_.size() == 0)
        {
            auditFile_ << "No subsequent election needed" << std::endl;
        }
        else
        {
            auditFile_ << "Another election is needed to fill the remaining seats" << std::endl;
        }
        this->generateMediaFile();
        if (!debugMode_)
        {
            this->generateTermOutput();
        }
    }

}
