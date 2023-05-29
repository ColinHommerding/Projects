
#ifndef OPLELECTION_H
#define OPLELECTION_H

#include "Candidate.h"
#include "Election.h"
#include "OPLParty.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>

namespace VotingSystem
{
   /**
* @brief Class that handles Open Party List Elections. The run() method is the main driver function and will be called from main after the
* IRElection object is created.
  **/
   class OPLElection : public Election
   {
   public:
      /**
     * @brief Constructor. Sets the name of the election and passes in the vector of filenames containing the name of each OPL election input file.
     * @param electionName A string that is passed in to give the OPLElection its name/
     * @param filenames_vec a vector of strings containing the names of all the input files
     */
     OPLElection(std::string electionName, std::vector<std::string> filenames_vec, int debug);

      ~OPLElection();

      /**
     * @brief Run is the main driver function, and makes all the function calls inside this class itself.
     */
      void run();

    /**
       * @brief check consistency header
       * @return bool
       *
       * return true if input files has the same header, false otherwise
       */
      bool check_header_consistency();

      /**
     * @brief readHeader is specific to OPLElection files. It reads the header of every OPL election input file in the election and sets the number of candidates, number of parties, candidatesList_ vector, party_vector, number of seats, and number of votes.
     */
      void readHeader(int fileno);

      /**
    * @brief verifyInfo asks the user to verify information. It exits the program if the user says the information is not correct.
    */
      void verifyInfo();

      /**
     * @brief readBallots reads through the rest of all OPL election input files besides the header and increments each candidate's number of votes for each vote they recieve.
     * @param startID an integer from which to start the ID-ing of ballots from.
     */
      void readBallots(int startID = 0);

      /**
       * @brief writes the **BALLOTS** header, along with number of ballots cast, each ballot's
       * ID, and the contents of each ballot
       **/
      void writeBallotsToAudit();

      /**
     * @brief sumPartyVotes adds up all the votes of each candidate in each individual party
     */
      void sumPartyVotes();

      /**
     * @brief rankCandidatesInParties has each party in the election rank its candidates in order of amount of votes they recieved.
     */
      void rankCandidatesInParties();

      /**
     * @brief allocateFirstSeats uses the quota to give each party its initial amount of seats and calculates each party's vote remainder.
     */
      void allocateFirstSeats();

      /**
     * @brief orderPartiesByRemainder orders the parties in the OPL election by the vote remainder they had in the party_ vector from most to least.
     */
      void orderPartiesByRemainder();

      /**
     * @brief allocateRemainingSeats goes round robin assigning seats to parties in order of the remaining votes until their are no more available seats left.
     */
      void allocateRemainingSeats();

      /**
     * @brief assignCandidates hands out each party's won seats to the candidates in the party in order of the most votes until the party has no more won seats left.
     */
      void assignCandidates();

      /**
     * @brief getTotalSeats returns the total seats for this OPL election.
     * @return An integer which is the total amount of seats for an OPL election.
     */
      int getTotalSeats() { return totalSeats_; };

      /**
     * @brief generateTermOutput outputs text to the terminal with an overview of the OPL election.
     * @return void
     */
      void generateTermOutput();

      /**
     * @brief generateMediaFile creates a media file with an overview of the OPL election.
     * @return void
     */
      void generateMediaFile();

      /**
     * @brief addParty adds a party to the party_ vector.
     * @param party is an OPLParty object that gets added to the OPL election's party_ vector to store it.
     */
      void addParty(VotingSystem::OPLParty* party);

      /**
     * @brief addPartyAlphabetical adds a party to the alphabetPartList_ vector of an OPL election.
     */
      void addPartyAlphabetical(VotingSystem::OPLParty* party);

      /**
     * @brief getElectionName returns the name of the OPL election.
     * @return A string which is the OPL election's name.
     */
      std::string getElectionName() { return electionName_; }

      /**
     * @brief setSeats can be used to set the number of available seats for an OPL election.
     * @param seats An integer that is set as the numSeats for an OPL election.
     */
      void setSeats(int seats);

      /**
     * @brief setNumBallots can be used to set the number of ballots cast.
     * @param ballots An integer that is set as the numBallots for an OPL election.
     */
      void setNumBallots(int ballots);

      /**
     * @brief getParties returns the party_ vector of an OPL election.
     * @return Returns a vector of OPLParty objects .
     */
      std::vector<OPLParty *> getParties() {return party_;}

      /**
     * @brief getWinners returns the winners_ vector of an OPL election.
     * @return Returns a vector of Candidate objects.
     */
      std::vector<Candidate *> getWinners() {return winners_;}

   private:
   /**
     * @brief totalSeats_ is the number of seats up for grabs in an OPL election.
    */
      int totalSeats_;

    /**
    * @brief numParties_ is the number of parties participating in the OPL election.
    */
      int numParties_;

   /**
     * @brief numSeats_ is the amount of seats that need to be allocated for an OPL election currently.
    */
      int numSeats_;

    /**
    * @brief numAllocatedSeats_ is the number of seats that have already been allocated in an OPL election.
    */
      int numAllocatedSeats_;

   /**
     * @brief quota_ is the calculated value that determines how many votes a party needs to earn one seat during the first allocation. It is the ceiling of numBallots divided by numSeats.
    */
      int quota_;
   };

}

#endif
