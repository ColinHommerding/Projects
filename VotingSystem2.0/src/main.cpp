
#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include "include/IRElection.h"
#include "include/OPLElection.h"
#include "include/POElection.h"

using namespace std;
namespace VS = VotingSystem;

int debugMode = 0;

vector<string> filenames_vec;
string electionType;
string electionName;
ifstream fileC;

void prompt_input_files();
void parse_election_type();
void prompt_election_name();
void end_Program();
void check_debug_Mode(int argc, char **argv);

int main(int argc, char **argv)
{
  std::cout << "---------------Welcome to Voting System-------------------" << endl;
  std::cout << endl;
  //variables for input files

  check_debug_Mode(argc, argv);
  prompt_input_files();
  parse_election_type();
  prompt_election_name();

  /**
   *run election
   */
  if (electionType.compare("IR") == 0)
  {
    VS::IRElection *irelection = new VS::IRElection(electionName, filenames_vec, debugMode);
    irelection->run();
  }
  else if (electionType.compare("OPL") == 0)
  {
    VS::OPLElection *oplelection = new VS::OPLElection(electionName, filenames_vec, debugMode);
    oplelection->run();
  }
  else if (electionType.compare("PO") == 0)
  {
    VS::POElection *poelection = new VS::POElection(electionName, filenames_vec, debugMode);
    poelection->run();
  }
  else
  {
    printf("Something wrong with input file format. Check with tech team.\n");
    exit(EXIT_FAILURE);
  }
}

void parse_election_type(){
  if(filenames_vec.size()==0){
    std::cout<<"no file inputted"<<std::endl;
    end_Program();
  }
  fileC.open(filenames_vec[0].c_str());
  if (!fileC.is_open())
  {
    std::cout << "input file " << filenames_vec[0] << " can't be opened" << endl;
    end_Program();
  }
  std::getline(fileC, electionType);
  fileC.close();

}

void prompt_input_files()
{
  /**
   *Ask for input file
   */
  string tempFileName = "";
  std::cout << "Instruction: Type one input file and press enter, then type the second input file, and so on." << endl;
  std::cout << "             Type \"done\" when finished" << endl;
  std::cout << endl;
  while (1)
  {
    std::cout << "Please type one input file name: "; // Type a number and press enter
    std::cin >> tempFileName;
    if (tempFileName == "done")
    {
      break;
    }
    //check if the file has been input or not
    bool alreadyExsit = false;
    for (int i = 0; i < filenames_vec.size(); i++)
    {
      if (filenames_vec[i] == tempFileName)
      {
        std::cout << tempFileName << " is already exist" << endl;
        alreadyExsit = true;
      }
    }
    //add it to vector if it's not showed up before.
    if (!alreadyExsit)
    {
      filenames_vec.push_back(tempFileName);
    }
    std::cout << endl;
  }
}

void end_Program()
{
  std::cout << "Program terminated" << endl;
  exit(EXIT_FAILURE);
}

void check_debug_Mode(int argc, char **argv)
{
  // Check if -d debug flag is set
  if (argc == 2)
  {
    std::string d(argv[1]);
    if (d == "-d")
    {
      std::cout << "WARNING: Debug flag has been set.\n Election results may not be fair, "
                << "please rerun the program without the '-d' flag if you are running\n"
                << " an official election." << std::endl;
      debugMode = 1;
    }
  }
}

void prompt_election_name()
{
  //if all file can be opened, ask for elction name
  std::cout << endl;
  std::cout << "Give this Election a name: ";

  cin.ignore();
  getline(cin, electionName);

  //remove special characters
  std::string charList = "#!/@$%^&*()+=";
  for (char c : charList)
  {
    electionName.erase(std::remove(electionName.begin(), electionName.end(), c), electionName.end());
  }
  replace(electionName.begin(), electionName.end(), ' ', '_');
  std::cout << endl;
}
