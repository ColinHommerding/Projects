
#include "include/IRElection.h"
#include "include/Candidate.h"
#include "include/IRBallot.h"
#include "include/Election.h"
#include <algorithm>
#include <string>
#include <math.h>

namespace VotingSystem
{

  IRElection::IRElection(std::string elName, std::vector<std::string> filenames_vec, int debug)
      : Election(elName, filenames_vec, debug)
  {
    electionType_ = "IR";
    elimBallots_ = 0;
  }

  bool IRElection::check_header_consistency()
  {
    /**
   *open input files
   */
    std::ifstream fileC;
    std::string LineElectionType;
    std::string LineNumCandidates;
    std::string LineCandidate;

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
      std::getline(fileC, tempType);
      std::getline(fileC, tempNumCandidate);
      std::getline(fileC, tempCandidate);

      //compare header infos
      if (tempType != LineElectionType || tempNumCandidate != LineNumCandidates || tempCandidate != LineCandidate)
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

  void IRElection::readHeader(int fileno)
  {
    if (fileno == 0)
    {
      inputFile_.open(filenames_[fileno]); //opening whichever file
      //std::cout<<"Reading header of " << filenames_[fileno] << " file"<<std::endl;
      std::string line;
      getline(inputFile_, line); //  Election Type
      electionType_ = line;
      getline(inputFile_, line); //  Number of candidates
      numCandidates_ = stoi(line);
      candidatesLeft_ = numCandidates_;
      getline(inputFile_, line); //  candidates
      int stringindex;
      std::string candidateLine;
      std::string candname;
      std::string candparty;
      Candidate *newCandidate;
      int candid = 1;
      while ((stringindex = line.find(", ")) != std::string::npos)
      {
        candidateLine = line.substr(0, stringindex);
        candname = candidateLine.substr(0, candidateLine.find(" ("));
        //std::cout << candidateLine << std::endl;
        candparty = candidateLine.substr(candidateLine.find('(') + 1, candidateLine.find(')') - candidateLine.find('(') - 1);
        newCandidate = new Candidate(candname, candparty, candid);
        candidatesList_.push_back(newCandidate);
        candid++;
        line.erase(0, stringindex + 2);
      }
      candidateLine = line.substr(0, stringindex);
      candname = candidateLine.substr(0, candidateLine.find(" ("));
      candparty = candidateLine.substr(candidateLine.find('(') + 1, candidateLine.find(')') - candidateLine.find('(') - 1);
      //std::cout << "Creating new candidate " << candname << "with party " << candparty << std::endl;
      newCandidate = new Candidate(candname, candparty, candid);
      candidatesList_.push_back(newCandidate);

      // alphabetize candidates and place in alphabetCandidatesList_
      for (int i = 0; i < numCandidates_; i++)
      {
        alphabetCandidatesList_.push_back(candidatesList_[i]);
      }
      // sort by candidate's last name
      std::sort(alphabetCandidatesList_.begin(), alphabetCandidatesList_.end(),
                [](Candidate *a, Candidate *b) { return a->getAbbrevName() < b->getAbbrevName(); });
      // for (int i = 0; i < numCandidates_; i++)
      // {
      //   std::cout << alphabetCandidatesList_.at(i)->getName() << std::endl;
      // }

      // AUDIT FILE: Add Candidate information to audit file
      auditFile_ << "*** CANDIDATES ***" << std::endl;
      auditFile_ << numCandidates_ << " Candidates:" << std::endl;
      for (int i = 0; i < numCandidates_; i++)
      {
        Candidate *c = alphabetCandidatesList_[i];
        auditFile_ << c->getName() << " (" << c->getParty() << ")" << std::endl;
      }
      auditFile_ << "\n"
                 << std::endl;

      getline(inputFile_, line); //Number of ballots
      recentFileBallots_ = stoi(line);
      // numBallots_ = stoi(line);
      // numBallotsToWin_ = numBallots_ / 2.0 + 1;
    }
    else
    {
      inputFile_.close();
      inputFile_.open(filenames_[fileno]); //opening whichever file
      //std::cout<<"Reading header of " << filenames_[fileno] << " file"<<std::endl;
      std::string line;
      getline(inputFile_, line); //  Election Type
      getline(inputFile_, line);
      getline(inputFile_, line);
      getline(inputFile_, line);
      recentFileBallots_ = stoi(line);
      // numBallots_ += stoi(line);
      // numBallotsToWin_ = numBallots_ / 2.0 + 1;
    }
    //std::cout << "Header finished reading: "<< numBallots_<< " ballots total" << std::endl;
  }

  void IRElection::verifyInfo()
  {
    //verifty info
    std::cout << "******** VerifyInfo ********" << std::endl;
    std::cout << numCandidates_ << " Candidates:" << std::endl;
    for (int i = 0; i < numCandidates_; i++)
    {
      Candidate *c = alphabetCandidatesList_[i];
      std::string cName = c->getAbbrevName();
      std::string cParty = c->getParty();
      printf("%s (%s)\n", cName.c_str(), cParty.c_str());
    }
    std::cout << "Total Votes - " << numBallots_ << " Votes" << std::endl;
    std::cout << std::endl;

    //check edge case when
    char c;
    std::cout << "Is this information correct? Type Y/N. (Pressing N will exit program.)" << std::endl;
    // Edit: If debug mode is on, automatically accept information as correct
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

  void IRElection::readBallots(int startID)
  {
    std::string line;
    int index = 0;
    int numCorrectBallots_ = 0;
    for (int i = 0; i < recentFileBallots_; i++)
    { //  Iterates through each line (ballot)
      //std::cout << "Loop: " << i << std::endl;
      int numUnranked = 0;
      IRBallot *newBallot = new IRBallot(startID + i + 1);
      getline(inputFile_, line);
      int orderme[numCandidates_]; //  So this is the only way I really figured out how to add candidates to ballots in the correct order see addRankedCandidates
      for (int j = 0; j < numCandidates_; j++)
      { // Goes into each line and actually gets the rankings
        index = 0;
        int candrank;
        index = line.find(',');
        if (index == 0)
        {
          orderme[j] = 0;
          numUnranked++;
        }
        else if (index == -1)
        {
          try
          { //  If the last candidate is ranked
            candrank = stoi(line);
            orderme[j] = candrank;
          }
          catch (std::exception &err)
          { //  If the last candidate is not ranked
            orderme[j] = 0;
            numUnranked++;
          }
        }
        else
        {
          candrank = stoi(line.substr(0, index));
          orderme[j] = candrank;
        }
        line.erase(0, index + 1);
      }
      float halfRanked = float(numCandidates_) / 2;
      int ranked = numCandidates_ - numUnranked;
      addRankedCandidates(newBallot, orderme, numUnranked);
      if (ranked >= halfRanked)
      {
        ballotsList_.push_back(newBallot);
        distributeBallot(newBallot);
        numCorrectBallots_++;
      }
    }
    //recentFileBallots_ = numCorrectBallots_;
    numBallots_ += numCorrectBallots_;
    numBallotsToWin_ = numBallots_ / 2.0 + 1;
  }

  void IRElection::writeBallotsToAudit()
  {
    //Add "Ballots" section
    auditFile_ << "*** BALLOTS ***" << std::endl;
    auditFile_ << numBallots_ << " ballots cast" << std::endl;
    
    if (numBallots_ > 0)
    {
      auditFile_ << "Ballots are shuffled and given IDs b1 to b" << numBallots_ << std::endl;
      auditFile_ << "Ballot's candidates listed in order of rank, first choice listed first\n";
      auditFile_ << "Candidate needs " << numBallotsToWin_
                 << " or more votes to win" << std::endl;
    }

    for (int i = 0; i < numBallots_; i++)
    {
      // Write ballot information to audit file
      // write id
      Ballot *newBallot = ballotsList_[i];
      auditFile_ << "b" << newBallot->getId() << " : ";
      std::vector<Candidate *> cands = newBallot->getRankedCandidates();
      // write first n-1 candidates with trailing comma
      for (int i = 0; i < newBallot->getRankedCandidates().size() - 1; i++)
      {
        auditFile_ << cands[i]->getAbbrevName() << ",";
      }
      // write last candidate without trailing comma
      auditFile_ << cands[cands.size() - 1]->getAbbrevName() << std::endl;
    }
    auditFile_ << std::endl;
  }

  void IRElection::addRankedCandidates(IRBallot *ballot, int places[], int numUnranked)
  {
    int rank = 1;
    for (int i = 0; i < numCandidates_ - numUnranked; i++)
    {
      for (int j = 0; j < numCandidates_; j++)
      {
        if (places[j] == rank)
        {
          ballot->addCandidate(candidatesList_.at(j));
        }
      }
      rank++;
    }
  }

  void IRElection::distributeBallot(IRBallot *ballot)
  {
    Candidate *candidate;
    candidate = ballot->getCandidate();
    candidate->addBallot(ballot);
  }

  Candidate *IRElection::findWinner()
  {

    Candidate *winner = nullptr;
    //AUDIT FILE: Begin "Round" section
    auditFile_ << "*** ROUND " << roundNum_ << " ***" << std::endl;
    // std::cout << "\n"
    //           << std::endl;
    // std::cout << "Round number: " << roundNum_ << std::endl;
    // std::cout << "CHECKING FOR WINNER" << std::endl;
    Candidate *currCandidate;

    // Go through all candidates, checking number of votes and looking for a winner
    for (int i = 0; i < alphabetCandidatesList_.size(); i++)
    {
      currCandidate = alphabetCandidatesList_.at(i);
      //std::cout << currCandidate->getName() << " has " << currCandidate->getNumVotes() << " votes" << std::endl;

      //AUDIT FILE: Log candidate's votes for this round, if not eliminated
      if (!currCandidate->isEliminated())
      {
        auditFile_ << currCandidate->getAbbrevName() << ": "
                   << currCandidate->getNumVotes() << " votes" << std::endl;
        if (currCandidate->getNumVotes() != 0)
        {
          auditFile_ << "\t[";
          std::vector<Ballot *> bals = currCandidate->getBallots();
          // sort candidate's votes by ascending ID
          std::sort(bals.begin(), bals.end(),
                    [](Ballot *b1, Ballot *b2) { return b1->getId() < b2->getId(); });
          for (int i = 0; i < bals.size() - 1; i++)
          {
            auditFile_ << "b" << bals[i]->getId() << ",";
            if (i != 0 && i % 20 == 0)
            {
              auditFile_ << std::endl
                         << "\t";
            }
          }
          auditFile_ << "b" << bals[bals.size() - 1]->getId() << "]" << std::endl;
        }
      }

      // If a winner is found, set winner variable
      if (currCandidate->getNumVotes() >= numBallotsToWin_)
      {
        winner = currCandidate;
      }
    }

    //AUDIT FILE: Log number of valid ballots in this round
    auditFile_ << "\nTotal valid ballots : " << numBallots_ - elimBallots_ << "\n"
               << std::endl;

    // if there is a winner
    if (winner != nullptr)
    {
      //std::cout << "WINNER FOUND: " << winner->getName() << std::endl;
      winners_.push_back(winner);
      //AUDIT FILE: log winner
      auditFile_ << winner->getAbbrevName() << " wins by majority" << std::endl;
      return winner;
    }

    if (candidatesLeft_ == 2)
    { //  Case in which there is no majority and popularity is used
      //AUDIT FILE: log that there are two candidates left
      auditFile_ << "2 candidates left, popularity wins" << std::endl;
      //std::cout << "POPULARITY CONTEST: " << std::endl;
      Candidate *finalistA;
      bool aFilled = false;
      Candidate *finalistB;
      for (int i = 0; i < candidatesList_.size(); i++)
      {
        currCandidate = candidatesList_.at(i);
        if (!currCandidate->isEliminated() && aFilled == false)
        {
          aFilled = true;
          finalistA = currCandidate;
        }
        else if (!currCandidate->isEliminated())
        {
          finalistB = currCandidate;
        }
      }
      if (finalistA->getNumVotes() > finalistB->getNumVotes())
      {
        //std::cout << "WINNER FOUND: " << finalistA->getName() << std::endl;
        //AUDIT FILE: log winner
        auditFile_ << finalistA->getAbbrevName() << " wins by popularity" << std::endl;
        winners_.push_back(finalistA);
        return finalistA;
      }
      if (finalistA->getNumVotes() < finalistB->getNumVotes())
      {
        //std::cout << "WINNER FOUND: " << finalistB->getName() << std::endl;
        //AUDIT FILE: log winner
        auditFile_ << finalistB->getAbbrevName() << " wins by popularity" << std::endl;
        winners_.push_back(finalistB);
        return finalistB;
      }
      else
      {
        //std::cout << "ITS A TIE!" << std::endl;
        if (debugMode_)
        {
          // return candidate with lowest ID if debug mode is on
          if (finalistA->getId() < finalistB->getId())
          {
            winner = finalistA;
          }
          else
          {
            winner = finalistB;
          }
        }
        else
        {
          winner = coinFlip(std::vector<Candidate *>{finalistA, finalistB});
        }
        //AUDIT FILE: log winner by tie
        auditFile_ << winner->getAbbrevName() << " wins by popularity (Coin Flip)" << std::endl;
        winners_.push_back(winner);
        return winner;
      }
    }
    //AUDIT FILE: log no winner
    //std::cout << "No winner found\n";
    auditFile_ << "no winner" << std::endl;
    return NULL;
  }

  Candidate *IRElection::findLastPlace()
  {
    int minvotes = numBallots_;
    //std::cout<<"initial minvotes "<<minvotes<<std::endl;
    std::vector<Candidate *> lowestCandidates;
    Candidate *last;
    Candidate *currCandidate;
    // if there are no candidates
    if (numCandidates_ == 0)
    {
      return nullptr;
    }

    // find min number of votes a candidate has
    for (int i = 0; i < candidatesList_.size(); i++)
    {
      currCandidate = candidatesList_.at(i);
      if (currCandidate->getNumVotes() < minvotes && !currCandidate->isEliminated())
      {
        //std::cout<<"candidate: "<<currCandidate->getAbbrevName()<< " with " << currCandidate->getNumVotes()<< " votes" <<std::endl;
        minvotes = currCandidate->getNumVotes();
      }
    }
    // find all candidates who have minvotes votes
    for (int i = 0; i < numCandidates_; i++)
    {
      currCandidate = candidatesList_.at(i);
      if (currCandidate->getNumVotes() == minvotes && !currCandidate->isEliminated())
      {
        lowestCandidates.push_back(currCandidate);
      }
    }
    // if there is more than one candidate with the lowest amount of votes
    if (lowestCandidates.size() != 1)
    {
      //std::cout << "UH OH THERES A TIE" << std::endl;
      // if debug mode, select tied candidate with lowest ID
      if (debugMode_)
      {
        Candidate *minCand = nullptr;
        for (int i = 0; i < lowestCandidates.size(); i++)
        {
          if (minCand == nullptr || lowestCandidates[i]->getId() < minCand->getId())
          {
            minCand = lowestCandidates[i];
          }
        }
        last = minCand;
      }
      else
      {
        // else randomly select last
        last = coinFlip(lowestCandidates);
      }

      //AUDIT FILE: log eliminated candidate, note random selection
      auditFile_ << last->getAbbrevName() << " eliminated (Coin Flip)" << std::endl;
      return last;
    }

    else
    {
      // return only candidate in lowestCandidates
      //AUDIT FILE: log eliminated candidate
      auditFile_ << lowestCandidates[0]->getAbbrevName() << " eliminated" << std::endl;
      return lowestCandidates[0];
    }
    return nullptr;
  }

  void IRElection::runRunoff()
  {
    Candidate *lastPlace;
    lastPlace = this->findLastPlace();
    //std::cout << "Last Place: " << lastPlace->getName() << std::endl;
    lastPlace->setEliminate(roundNum_);
    candidatesLeft_--;
    redistribute(lastPlace);
  }

  void IRElection::redistribute(Candidate *biggestLoser)
  {
    std::vector<std::pair<Candidate *, Ballot *>> distBallots;
    std::vector<Ballot *> eliminatedBallots;
    Candidate *nextCand;
    //std::cout << "Redistributing last place: " << biggestLoser->getAbbrevName()<< std::endl;
    IRBallot *currballot;
    for (int i = 0; i < biggestLoser->getNumVotes(); i++)
    {
      bool notfound = false; //  This is switched if nextCandidate() returns a 0 indicating no more ranked candidates
      currballot = (IRBallot *)biggestLoser->getBallots().at(i);
      while (currballot->getCandidate()->isEliminated())
      {
        //std::cout << "Needing to redistribute this ballot to someone not eliminated" << std::endl;
        if (!currballot->nextCandidate())
        {
          //std::cout << "No more candidates ranked" << std::endl;
          notfound = true;
          break;
        }
      }
      if (!notfound)
      {
        // distribute if there is a candidate to distribute to
        distributeBallot(currballot);
        // add ballot,newCand pair to distBallots
        Candidate *newCand = currballot->getCandidate();
        std::pair<Candidate *, Ballot *> pair = std::make_pair(newCand, currballot);
        distBallots.push_back(pair);
      }
      else
      {
        // add ballot to eliminatedBallots
        eliminatedBallots.push_back(currballot);
      }
    }

    //AUDIT FILE: log ballot distribution
    //create compare function for sorting algorithm
    auto compare = [](std::pair<Candidate *, Ballot *> p1, std::pair<Candidate *, Ballot *> p2) {
      if (p1.first->getAbbrevName() != p2.first->getAbbrevName())
      {
        // return pair whose candidate name occurs first in the alphabet
        return p1.first->getAbbrevName() < p2.first->getAbbrevName();
      }
      else if (p1.first->getName() != p2.first->getName())
      {
        // if candidates have the same abbrev name, return pair whose candidate's full name
        // appears first
        return p1.first->getName() < p2.first->getName();
      }
      else
      {
        // if candidates have the same name, return pair whose ballot has smallest ID
        return p1.second->getId() < p2.second->getId();
      }
    };
    // sort distballots
    std::sort(distBallots.begin(), distBallots.end(), compare);

    Candidate *currCandidate;
    if (distBallots.size() > 0)
    {
      currCandidate = distBallots[0].first;
    }
    std::vector<Ballot *> distBallotsToCand;
    int i = 0;
    while (i < distBallots.size())
    {
      while (distBallots[i].first == currCandidate)
      {
        distBallotsToCand.push_back(distBallots[i].second);
        i++;
      }
      // write to audit file for this candidate
      auditFile_ << distBallotsToCand.size() << " votes transferred to "
                 << currCandidate->getAbbrevName() << std::endl;
      auditFile_ << "\t[";
      for (int j = 0; j < distBallotsToCand.size() - 1; j++)
      {
        auditFile_ << "b" << distBallotsToCand[j]->getId() << ",";
        if (j != 0 && j % 20 == 0)
        {
          auditFile_ << std::endl
                     << "\t";
        }
      }
      auditFile_ << "b" << distBallotsToCand[distBallotsToCand.size() - 1]->getId()
                 << "]" << std::endl;

      // redefine currCandidate and clear distBallotsToCand
      currCandidate = distBallots[i].first;
      distBallotsToCand.clear();
    }

    // sort eliminatedBallots by ascending ID
    std::sort(eliminatedBallots.begin(), eliminatedBallots.end(),
              [](Ballot *b1, Ballot *b2) { return b1->getId() < b2->getId(); });

    // log all eliminated ballots to the audit file
    if (eliminatedBallots.size() > 0)
    {
      elimBallots_ += eliminatedBallots.size();
      auditFile_ << eliminatedBallots.size() << " votes discarded" << std::endl;
      auditFile_ << "\t[";
      for (int i = 0; i < eliminatedBallots.size() - 1; i++)
      {
        auditFile_ << "b" << eliminatedBallots[i]->getId() << ",";
        if (i != 0 && i % 20 == 0)
        {
          auditFile_ << std::endl
                     << "\t";
        }
      }
      auditFile_ << "b" << eliminatedBallots[eliminatedBallots.size() - 1]->getId()
                 << "]" << std::endl;
    }

    auditFile_ << std::endl
               << std::endl;
  }

  void IRElection::run()
  {

    if (check_header_consistency() == false)
    {
      auditFile_.close();
      removeAuditFile();
      return;
    }
    roundNum_ = 1;

    // AUDIT FILE: Add election date/time/type to audit file
    auditFile_ << "****** OFFICIAL ELECTION AUDIT FILE ******" << std::endl;
    if (debugMode_)
    {
      auditFile_ << "This audit file was generated from an election run in debug mode\n";
      auditFile_ << "Election results may not be fair" << std::endl;
    }
    char date[100];
    strftime(date, 100, "%B %d, %Y at %I:%M:%S %p", localtime(&electionDate_));
    auditFile_ << "File generated on " << date << std::endl;
    auditFile_ << "Voting System : Instant Runoff (IR)\n\n"
               << std::endl;

    int startID = 0;
    for (int i = 0; i < numFiles_; i++)
    {
      this->readHeader(i);
      // Read Ballots from input file
      this->readBallots(startID);
      // Update startID to first ID of next file
      startID = ballotsList_.size();
    }
    this->writeBallotsToAudit();
    if (!debugMode_)
    {
      this->verifyInfo();
    }

    // if there are no valid ballots in the input file
    if (numBallots_ == 0 ||numCandidates_ == 0)
    {
      if(!debugMode_){
        std::cout << "Your input file has either empty candidates or empty ballots. Election not run." << std::endl;
      }
      auditFile_.close();
      removeAuditFile();
      return;
    }


    Candidate *winner;
    while ((winner = this->findWinner()) == nullptr)
    {
      this->runRunoff();
      roundNum_++;
    }
    //std::cout << "Running findWinner again just to set the winner" << std::endl;
    //winners_.push_back(this->findWinner());
    //std::cout << "The final WINNER is: " << winners_.front()->getName() << std::endl;
    auditFile_ << "\nElection ends\n\n\n"
               << std::endl;

    this->generateMediaFile();
    if (!debugMode_)
    {
      this->generateTermOutput();
    }
  }

  void IRElection::generateTermOutput()
  {
    std::cout << std::endl;

    //Eleciton info
    std::cout << "*********** Preliminary Output ************" << std::endl;
    std::cout << "(See audit file and media file for details)" << std::endl;
    std::cout << "Election Name: " << electionName_ << std::endl;
    std::cout << "Election Type : Instant Runoff" << std::endl;
    std::cout << std::endl;

    //Result
    std::cout << "************ RESULTS ****************" << std::endl;
    std::cout << "Total Valid Ballots: " << numBallots_ - elimBallots_ << std::endl;

    std::cout << "Candidate Status: " << std::endl;
    for (int i = 0; i < numCandidates_; i++)
    {
      Candidate *c = alphabetCandidatesList_[i];
      std::string cName = c->getAbbrevName();
      std::string cParty = c->getParty();
      int cVotes = c->getNumVotes();
      //if(cVotes==0){continue;}

      int cVotePercentage = (cVotes * 100 / (numBallots_ - elimBallots_));
      printf("%s (%s) : ", cName.c_str(), cParty.c_str());
      if (c->isEliminated())
      {
        printf("Eliminated at Round %d\n", c->getElimatedRound());
      }
      else if (winners_.size() != 0 && c == winners_.front())
      {
        printf("(%d%%) - %d Votes - ELECTED\n", cVotePercentage, cVotes);
      }
      else
      {
        printf("(%d%%) - %d Votes\n", cVotePercentage, cVotes);
      }
    }
  }

  void IRElection::generateMediaFile()
  {

    //create mediafile
    std::ofstream mediaFile;
    char date[100];
    strftime(date, 100, "_%m-%d-%Y_%I%M%S", localtime(&electionDate_));
    std::string time = date;
    std::string media_File_String = "election_media_" + electionName_ + time + ".txt";
    //std::cout <<"Note: " <<media_File_String <<"is generated."<< std::endl;
    mediaFile.open(media_File_String);

    //Eleciton info
    mediaFile << "****** OFFICIAL ELECTION MEDIA FILE ******"
              << std::endl;
    strftime(date, 100, "%B %d, %Y at %I:%M:%S %p", localtime(&electionDate_));
    mediaFile << "File generated on " << date << std::endl;
    mediaFile << "Election Type: Instant Runoff (IR)"
              << std::endl;
    mediaFile << "Election Name: " << electionName_ << std::endl;
    mediaFile << std::endl;

    //Candidate info
    mediaFile << "*********** CANDIDATES **************" << std::endl;
    mediaFile << numCandidates_ << " Candidates:" << std::endl;
    for (int i = 0; i < numCandidates_; i++)
    {
      Candidate *c = alphabetCandidatesList_[i];
      std::string cName = c->getAbbrevName();
      std::string cParty = c->getParty();
      mediaFile << cName << " (" << cParty << ")" << std::endl;
    }
    mediaFile << std::endl;

    //Result
    mediaFile << "************ RESULTS ****************" << std::endl;
    mediaFile << "Total Valid Votes: " << numBallots_ - elimBallots_ << std::endl;
    mediaFile << std::endl;

    mediaFile << "Candidate Status: " << std::endl;
    for (int i = 0; i < numCandidates_; i++)
    {
      Candidate *c = alphabetCandidatesList_[i];
      std::string cName = c->getAbbrevName();
      std::string cParty = c->getParty();
      int cVotes = c->getNumVotes();
      int cVotePercentage = (cVotes * 100 / (numBallots_ - elimBallots_));
      mediaFile << cName << " (" << cParty << ") : ";
      if (c->isEliminated())
      {
        mediaFile << "Eliminated at Round " << c->getElimatedRound() << std::endl;
      }
      else if (winners_.size() != 0 && c == winners_.front())
      {
        mediaFile << "(" << cVotePercentage << "%) - " << cVotes << " Votes - ELECTED" << std::endl;
      }
      else
      {
        mediaFile << "(" << cVotePercentage << "%) - " << cVotes << " Votes" << std::endl;
      }
    }
    mediaFile.close();
  }

}
