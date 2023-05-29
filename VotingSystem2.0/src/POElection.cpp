
#include "include/POElection.h"
#include <string>
#include <math.h>

namespace VotingSystem
{

  POElection::POElection(std::string elName, std::vector<std::string> filenames_vec, int debug)
      : Election(elName, filenames_vec, debug)
  {
    electionType_ = "PO";
  }

  bool POElection::check_header_consistency()
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

  void POElection::readHeader(int fileno)
  {
    if (fileno == 0)
    {
      inputFile_.open(filenames_[fileno]); // open PO file
      //std::cout<<"Reading header of " << filenames_[fileno] << " file"<<std::endl;
      std::string line;
      getline(inputFile_, line); //  Election Type
      electionType_ = line;
      getline(inputFile_, line); //  Number of candidates
      numCandidates_ = stoi(line);
      getline(inputFile_, line); //  candidates
      //std::cout << "Election Type: " << electionType_ << std::endl;
      //std::cout << "NumCandidates: " << numCandidates_ << std::endl;
      int stringindex;
      std::string candidateLine;
      std::string candname;
      std::string candparty;
      Candidate *newCandidate;
      int candid = 1;
      numBallots_ = 0;
      while ((stringindex = line.find("]")) != std::string::npos)
      {
        // get [Cand,Party] entry
        candidateLine = line.substr(0, stringindex + 1);
        // parse candidate name
        candname = candidateLine.substr(1, candidateLine.find(",") - 1);
        //std::cout << candidateLine << std::endl;
        // parse candidate party
	      int start = candidateLine.find(',') + 1;
        candparty = candidateLine.substr(start, candidateLine.find(']') - start);
        newCandidate = new Candidate(candname, candparty, candid);
        candidatesList_.push_back(newCandidate);
        candid++;
        // erase this entry from line
        line.erase(0, stringindex + 2);
        // if there is a whitespace at the first index of the string now, remove it
        if (line[0] == ' ')
        {
          line.erase(0, 1);
        }
      }
      getline(inputFile_, line); //  number of ballots
      numBallots_ = stoi(line);
      recentFileBallots_ = stoi(line);
    }
    else
    {
      inputFile_.close();
      inputFile_.open(filenames_[fileno]); //opening whichever file
      //std::cout<<"Reading header of " << filenames_[fileno] << " file"<<std::endl;
      std::string line;
      getline(inputFile_, line); // skip Election Type
      getline(inputFile_, line); // skip numCands line
      getline(inputFile_, line); // skip candidates line
      getline(inputFile_, line); // skip numBallots line
      recentFileBallots_ = stoi(line);
      numBallots_ += stoi(line);
      // numBallotsToWin_ = numBallots_ / 2.0 + 1;
    }
    //std::cout << "Header finished reading" << std::endl;
  }

  // Copied from IRElection, not implemented yet
  void POElection::verifyInfo()
  {
    //verifty info
    std::cout << "****** VerifyInfo ******" << std::endl;
    std::cout << numCandidates_ << " Candidates" << std::endl;
    for (int i = 0; i < numCandidates_; i++ ) {
      Candidate *c = candidatesList_[i];
      std::string cName = c->getAbbrevName();
      std::string cParty = c->getParty();
      printf("%s (%s)\n", cName.c_str(), cParty.c_str());
    }
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

      // delete audit file if user types N
      removeAuditFile();
      exit(EXIT_FAILURE);
    }
  }

  // Copied from OPLElection, not implemented yet
  void POElection::readBallots(int startID)
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

  void POElection::run()
  {
    //check_header_consistency
    if (check_header_consistency() == false)
    {
      return;
    }

    //parse input files
    int startID = 0;
    for (int i = 0; i < numFiles_; i++)
    {
      this->readHeader(i);
      // Read Ballots from input file
      this->readBallots(startID);
      // Update startID to first ID of next file
      startID = numBallots_;
    }

    removeAuditFile();
    
    if (!debugMode_)
    {
      this->verifyInfo();
    }

    std::cout << "TODO: Run PO Election" << std::endl;
  }
}
