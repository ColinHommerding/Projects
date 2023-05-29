
#ifndef ELECTION_H
#define ELECTION_H

#include "Candidate.h"
#include "OPLParty.h"
#include "Ballot.h"

#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <vector>

namespace VotingSystem
{

     /**
      * @brief An Election class which can be inherited for IRElection and OPLElection
      **/
     class Election
     {

     protected:
          std::vector<Candidate *> winners_;                //!< Vector of candidates that wins this election
          std::vector<OPLParty *> party_;                   //!< Vector of all parties in this election
          std::vector<OPLParty *> alphabetPartyList_;       //!< Vector of party in alphabet order
          std::ifstream inputFile_;                         //!< Input file ifstream
          std::ofstream auditFile_;                         //!< Audit file ofstream
          int numCandidates_;                               //!< Number of candidates in this election
          int numBallots_ = 0;                              //!< Total number of Ballots in this election
          std::string electionName_;                        //!< Name of this election
          time_t electionDate_;                             //!< Date of this election runs
          std::string electionType_;                        //!< Election type, either IR, OPL or PO for now
          std::vector<Candidate *> candidatesList_;         //!< Vector of candidate in this election
          std::vector<Candidate *> alphabetCandidatesList_; //!< Vector of candidate in alphabet order
          std::vector<Ballot *> ballotsList_;               //!< Vector of all ballots in this elction
          int debugMode_;                                   //!< Debug mode for testers
          static unsigned int seed_;                        //!< Attribute that used for coinFlip
          int numFiles_;                                    //!< Number of files read in
          std::vector<std::string> filenames_;
          int recentFileBallots_;

     public:
          /**
           * @brief Constructor that initialize Election. It will be overrided in both IRElection.cpp and OPLElection.cpp
           * @see IRElection.h
           * @see OPLElection.h
           * @param elName election name
           * @param filename_vec vector containing all input file names
           * @param debug debug mode
           * @return void
           **/
          Election(std::string elName, std::vector<std::string> filenames_vec, int debug);

          /**
           * @brief Destructor that delete this object when it goes out of scope.
           * @return void
           **/
          virtual ~Election();

          /**
           * @brief Get election name
           * @return election name
           **/
          std::string getName() { return electionName_; }

          /**
           * @brief Get election date
           * @return election date
           **/
          time_t getDate() { return electionDate_; }

          /**
           * @brief get the candidateList that contains all the candidates in this election.
           * @return candidateList
           **/
          std::vector<Candidate *> getCandidatesList() { return candidatesList_; }

          /**
           * @brief get the ballotsList that contains all the ballots in this election.
           * @return ballotsList_
           **/
          std::vector<Ballot *> getBallotsList() { return ballotsList_; }

          /**
           * @brief get the winners of this election
           * @return list of winners
           **/
          std::vector<Candidate *> getWinners() { return winners_; }

          /**
           * @brief Run the entire election.
           *        It will be the main driver of the actions within the election class.
           *        It will be overrided in both IRElection.cpp and OPLElection.cpp
           * @see IRElection.h
           * @see OPLElection.h
           * @return void
           **/
          virtual void run() = 0;

          /**
           * @brief It will take in an vector of multiple pointers as the parameter.
           *        Then will use random number generation to randomly select an index
           *        in the vector and return the object at that index.
           * @param tiedEntities an vector of multiple pointers
           * @return an randomly chosen object from input vector
           **/
          template <typename T>
          T *coinFlip(std::vector<T *> tiedEntities)
          {
               if (tiedEntities.size() == 0)
               {
                    return nullptr;
               }
               std::srand(seed_);
               // find random valid index
               int i = rand() % tiedEntities.size();

               // increment seed
               seed_++;
               return tiedEntities.at(i);
          }

          /**
           * @brief verifys the input files have the same header,otherwise the election will not be run.
           * @return bool
           **/
          virtual bool check_header_consistency()= 0;

          /**
           * @brief Read each input file's header and parse useful information.
           *        It will be overrided in both IRElection.cpp and OPLElection.cpp
           * @return void
           **/
          virtual void readHeader(int fileno) = 0;

          /**
           * @brief verifys the important information before proceed.
           * @return void
           **/
          virtual void verifyInfo() = 0;

          /**
           * @brief Creates the media file according to the results of the election.
           *        It will be overrided in both IRElection.cpp and OPLElection.cpp
           * @return void
           **/
          virtual void generateMediaFile() = 0;

          /**
           * @brief Prints the preliminary results of the election to the screen.
           *        It will be overrided in both IRElection.cpp and OPLElection.cpp
           * @return void
           **/
          virtual void generateTermOutput() = 0;


          /**
           * @brief get total ballot Number in election.
           * @return int
           **/
          virtual int getBallotNum() {
               return numBallots_;
          };

          /**
           * @brief get total candiate Number in election.
           * @return int
           **/
          virtual int getCandidateNum() {
               return numCandidates_;
          };

          /**
           * @brief removeAuditFile.
           * @return void
           **/
          virtual void removeAuditFile();

          
     };

} // namespace VotingSystem

#endif
