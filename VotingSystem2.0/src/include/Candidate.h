
#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <iostream>
#include <string>
#include <vector>

namespace VotingSystem
{

    class Ballot; // forward declaration of Ballot class

    /**
     * @brief A Candidate class which used to store candidate information, including name, belonged party, id number, eliminated status.
     **/
    class Candidate
    {

    private:
        int id_;                           //!< Unique ID that identify this candidate
        int numVotes_;                     //!< Number of votes that this candidate current having
        int eliminatedRound_;              //!< At which round, this candidate is eliminated
        bool eliminated_;                  //!< Elimination status
        std::string name_;                 //!< Candidate Name
        std::string abbrevName_;           //!< Candidate AbbrevName
        std::string party_;                //!< Party belongs to
        std::vector<Ballot *> ballotList_; //!< Ballotlist that contaisn all ballot votes to this candidate

    public:
        /**
         * @brief Constructor that initialize candidate.
         * @param Cname candidate name
         * @param PartyName party that this candidate belongs to 
         * @param Cid unique ID that identify this candidate
         * @return void
         **/
        Candidate(std::string Cname, std::string PartyName, int Cid); // Constructor

        /**
         * @brief Destructor that delete this object when it goes out of scope.
         * @return void
         **/
        ~Candidate() {}

        /**
         * @brief Returns the ID of the candidate stored in the id attribute.
         * @return candidate's unique ID
         **/
        int getId();

        /**
         * @brief Returns the current number of votes a candidate has in the numVotes attribute.
         * @return number of votes this candidate current has
         **/
        int getNumVotes();

        /**
         * @brief Returns the round number that candidate has been elimimated.
         * @return ElimatedRound
         **/
        int getElimatedRound();

        /**
         * @brief Returns the status of elimimation of this candidate.
         * @return True (this candidate has been eliminated.） False（ not eliminated.） 
         **/
        bool isEliminated();

        /**
         * @brief Returns the name of a candidate.
         * @return candidate name_
         **/
        std::string getName();

        /**
         * @brief Returns the abbreviation name of a candidate.
         * @return candidate Abbrevname_
         **/
        std::string getAbbrevName();

        /**
         * @brief Returns the party name of this candidate belongs to.
         * @return party name
         **/
        std::string getParty();

        /**
         * @brief Returns an array containing each ballot cast for that candidate contained in the ballotList_array.
         * @return ballotList_array
         **/
        std::vector<Ballot *> getBallots();

        /**
         * @brief set eliminated_ to true and update the eliminatedRound number as well.
         * @param roundNum the round number that this candidate been eleminated
         * @return void
         **/
        void setEliminate(int roundNum);

        /**
         * @brief Takes a pointer to a ballot and adds that ballot to the candidates ballot array.
         * @param b a ballot pointer that need to be attached to this candidate
         * @return void
         **/
        void addBallot(Ballot *b); //also need to update the numVote

        /**
         * @brief Increase this candidate's vote number 
         * @param i how many votes added
         * @return void
         **/
        void increaseNumVote(int i);
    };

} // namespace VotingSystem

#endif
