## Voting System 2.0


This project was created by Colin Hommerding, Fan Ding, Alex Gude, and Chris Walaszek.
This voting system is able to completely run Open Party List and Instant Runoff Elections.
It will prompt the user for csv files that contains the selections of each individual that voted from all polling locations.
It will then process these files and print the proper outcome to the screen depending on which type of election it is. 
The system will also produce a comprehensive audit file showing how the entire election was conducted and a media
file that provides handy statistics about the election that media companies can use. 


## To see the Doxygen http
Navigate to  `/VotingSystem2.0/documentation/html/` folder, and double click `index.http`.

## To run the Voting System2.0
* Clone this repo to a directory of your choice
* Navigate to `repo_path/Projects/VotingSystem2.0` folder
* Type in `chmod u+x ./bin/*` to enable the bash scripts.
* Create a build folder in the `VotingSystem2.0/` directory with `mkdir build`
* Build the program by running `./bin/build.sh`
* Run the program from `VotingSystem2.0` directory by using the command `./bin/run.sh`.\
  Upon program completion the resulting audit file and media file will be present in the `/VotingSystem2.0`\
  directory.

## Testing and Debug mode  
* The executable files themselves can be found at `./build/src/VotingSystem` for the program and at\
  `./build/testing/VotingSystem_test` for the GoogleTest files.
* To run the program in debug mode, use `./bin/debug.sh` from the `/VotingSystem2.0` directory or directly by
  running the executable with a `-d` flag, i.e. `./VotingSystem -d`.

## Notes
This program comes with many test input files, found in `testing/{IR,OPL}_input_files`, which can be\
entered as input when prompted by the program. (UPDATE) Enter the full path from the `/VotingSystem2.0/` directory when\
entering these files, e.g. `/testing/IR_input_files/IR_stress_test.csv` to input the file `IR_stress_test.csv`

To run unit/system tests, ensure you are in the `Projects/VotingSystem2.0` directory and run `./bin/test.sh`

To run `make` and `make clean` commands, use `./bin/make.sh` and `./bin/clean.sh`, respectively
