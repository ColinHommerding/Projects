# UMN CSCI 5801
Team14 (Ding, Gude, Hommerding, Walaszek)

The Voting System is a tool that people can use to calculate and analyze results for voting. 

This system will be designed to maximize productivity by automating the counting of ballots and generating an accurate result.

Users can use it to give results to the media and produce a detailed audit file that allows the user to review the development of the election.

# repo-Team14
Team14 (Ding, Gude, Hommerding, Walaszek)

This repository contains Team 14's Voting System2.0, along with its Software Requirements Specification and Software Design Document.

## To see the Doxygen http
Navigate to  `repo-Team14/Project2/documentation/html/` folder, and double click `index.http`.

## To run the Voting System2.0
* Clone this repo to a directory of your choice
* Navigate to `repo_path/repo-Team14/Project2` folder
* Type in `chmod u+x ./bin/*` to enable the bash scripts.
* Create a build folder in the Project2/ directory with mkdir build
* Build the program by running `./bin/build.sh`
* Run the program from `Project2` directory by using the command `./bin/run.sh`.\
  Upon program completion the resulting audit file and media file will be present in the `/Project2`\
  directory.

## Testing and Debug mode  
* The executable files themselves can be found at `./build/src/VotingSystem` for the program and at\
  `./build/testing/VotingSystem_test` for the GoogleTest files.
* To run the program in debug mode, use `./bin/debug.sh` from the `/Project2` directory or directly by
  running the executable with a `-d` flag, i.e. `./VotingSystem -d`.

## Notes
This program comes with many test input files, found in `testing/{IR,OPL,PO}_input_files`, which can be\
entered as input when prompted by the program. (UPDATE) Enter the full path from the `/Project2/` directory when\
entering these files, e.g. `/testing/IR_input_files/IR_stress_test.csv` to input the file `IR_stress_test.csv`

To run unit/system tests, ensure you are in the `repo-Team14/Project2` directory and run `./bin/test.sh`

To run `make` and `make clean` commands, use `./bin/make.sh` and `./bin/clean.sh`, respectively

