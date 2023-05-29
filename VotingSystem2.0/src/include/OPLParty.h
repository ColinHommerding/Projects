
#ifndef OPLPARTY_H_
#define OPLPARTY_H_

#include "Candidate.h"
#include <ctime>
#include <vector>

namespace VotingSystem {

/**
 * @brief An OPLParty class which represents parties in Open Party List voting
 **/
class OPLParty {
 public:
  /// OPLParty constructor, requires a string as the party's name
  /// Initializes all attributes to 0, name_ to passed in name
  /**
   * @brief OPLParty constructor
   * @param name a string which contains the name of the party
   * @param partyID an integer which contains OPLParty's ID. Intended to be a unique identifier.
   * @return void
   *
   * Sets id_ to partyID, name_ to party name, and initializes all other attributes to 0 or
   * an empty vector. Also initializes seed_, used for random selection in the case of ties
   */
  OPLParty(std::string name, int partyID);

  /**
   * @brief OPLParty destructor
   *
   * Does not delete any of the candidates inside the candidates_ or winnerCandidates_ vectors
   */
  ~OPLParty() {}
  /**
   * @brief numSeats_ getter
   * @return the party's currently assigned number of seats
   */
  int getSeats() { return numSeats_; }
  
  /**
   * @brief numVotes_ getter
   * @return the number of votes the Party has
   */
  int getVotes() { return numVotes_; }

  /**
   * @brief name_ getter
   * @return the party's name
   */
  std::string getName() { return name_; }

  /**
   * @brief candidates_ getter
   * @return a vector of all OPLParty's candidates
   */
  std::vector<Candidate*> getCandidates() { return candidates_; }

  /**
   * @brief winnerCandidates_ getter
   * @return a vector of all the party's winning candidates
   */
  std::vector<Candidate*> getWinnerCandidates() { return winnerCandidates_; }

  /**
   * @brief id_ getter
   * @return the party's ID
   */
  int getID(){return id;}
  
  /**
   * @brief adds Candidate pointer to candidates_ vector
   * @param c a pointer to the candidate to be added
   * @return void
   *
   * Does not add in the given candidate if the pointer is null, or there already
   * exists a candidate in candidates_ with the same ID as the given candidate.
   */
  void addCandidate(Candidate *c);

  /**
   * @brief remainderVotes_ getter
   * @return the party's number of remaining votes after the first allocation of seats.
   */
  int getRemainingVotes() { return remainderVotes_; }

  /**
   * @brief randomly selects an object from a vector
   * @param tiedEntities a vector of pointers to an object
   * @return one of the elements in tiedEntities, nullptr if tiedEntities is empty vector
   *
   * Generates a random index and returns the element at that index. Returns nullptr
   * if the inputted vector has a size of 0. Does not work with vectors of non-pointer
   * types.
   */
  template <typename T>
  T *coinFlip(std::vector<T*> tiedEntities) {
    if (tiedEntities.size() == 0) {
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
   * @brief Sums together each candidate's votes and stores value in numVotes_
   * @return void
   *
   * If no candidates exist in candidate_ vector, sets numVotes_ to -1
   */
  void sumCandidateVotes();

  /**
   * @brief Adds seats to numSeats_
   * @param n an int of the number of seats to add
   * @return void
   *
   * If n is 0, adds zero seats. If n is negative, subtracts |n| seats from numSeats_
   */
  void addSeats(int n);

  /**
   * @brief Updates remainderVotes_
   * @param n an int of the number of remaining votes
   * @return void
   *
   * Function updates the remainderVotes_ attribute to the value passed in. If n is 
   * zero or negative, resets remainderVotes_ to 0, so remainderVotes_ is never negative
   */
  void updateRemainingVotes(int n);

  /**
   * @brief Rearranges candidates from those with most votes to least votes
   * @param debug an int which toggles randomization of tied candidates
   * @return void
   *
   * Orders candidates in candidates_ vector in decreasing order by each
   * candidate's numVotes_ attribute. Breaks ties randomly if debug is false.
   * If debug is true, then breaks ties by ordering all tied candidates by
   * order of appearance in the input file, which is equivalent to ordering
   * by ascending ID values.
   */
  void orderCandidates(bool debug);

  /**
   * @brief returns first numSeats_ candidates in candidates_ vector
   * @return a vector of the qualifying candidates
   *
   * Returns as a Candidate* vector the first numSeats_ candidates from the
   * candidates_ vector, if possible. If numSeats_ is greater than or equal
   * to the number of candidates, returns all candidates. For proper usage in
   * OPL, candidates should be already ordered by orderCandidates().
   */
  std::vector<Candidate *> assignCandidatesToSeats();

 private:
  /// a seed for the randomization used in coinFlip()
  static unsigned int seed_;
  /// name of the party
  std::string name_;
  /// the total number of votes the party received
  int numVotes_;
  /// the number of remaining votes after first allocation
  int remainderVotes_;
  /// the number of seats the party has
  int numSeats_;
  /// all the party's candidates
  std::vector<Candidate *> candidates_;
  /// all candidates who won a seat in the OPL election
  std::vector<Candidate *> winnerCandidates_;
  /// a unique identifier
  int id;
};

} // namespace VotingSystem

#endif  // OPLPARTY_H_
