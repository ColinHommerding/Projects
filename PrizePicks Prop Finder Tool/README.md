Instructions to run the PrizePicks Prop Finder Tool

1. The PrizePicks Prop Finder Tool can be downloaded by downloading the code on this github. All the files for the tool are specifically located in the PrizePicks Prop Finder Tool folder and can be placed wherever the user wants. Navigate in terminal to the directory that contains the prizePicksScraper.py, draftKingsScraper.py, prizePicksPropFinderRunner.py, script.js, and style.css files.

2. Make sure that the neccesary modules are installed. Python requests, selenium, and undetected chromdriver are neccesary for this tool to run.

3. Make sure that the proper version of chrome is installed. This tool runs using version 113 of chrome.

4. This tool requires python3. Use python3 is the proper directory to run the tool. The file that is meant to be run to start the tool is the "prizePicksPropFinderRunner.py. This is done by typing "py prizePicksPropFinderRunner.py" into the command line. Then click enter. 

5. The tool will then procede to run and this could take up to a minute or so depending on how many player props are currently available.

6. Once the tool finishes running open the directory that contained all the files and there should now be an index.html file.

7. Make sure that the script.js and style.css files are in the same directory as the index.html in order for it to display correctly.

8. Open the index.html and the table displaying the Prize Picks player props with their odds will be shown. Read the information below in the "How to Read and Understand the Prize Pricks Prop Finder Table" section to learn how to understand the table and properly utilize the tool. There is also an example of the completed table located in the example folder.


How to Read and Understand the Prize Pricks Prop Finder Table

Prizepicks is a daily fantasy sports site/app. They offer fixed odds where users take the over or under on different player props. Fixed odds mean that for each entry type the payouts do not shift depending on which player props the user selects or depending on if the user selects the over or under on the props. The most optimal entry type with the best fixed odds is 5 or 6 player prop entries that contain 5 or 6 player props with an over or under selected. Users will place wagers on these 5/6 player prop entries and the goal is to correctly predict whether each player prop will go over or under its line to win a return on the wager. The odds on these types of entries for each player prop are -119. The PrizePicks prop finder tool will scrape PrizePicks for the props and then scrape odds data from Draft Kings sportsbook. Sportsbook odds are real time market data that give a very accurate picture of a players chances to go over or under a certain line. Sportsbooks like Draft Kings juice their odds to make money so on Draft Kings being favored at around -140 is roughly equal to actually being favored at -119 odds. To account for the juiced odds on Draft Kings, we want player props that are favored on Draft Kings at approximately -140 odds or better to go over or under a particular player prop line. This is in order to beat the -119 odds given for each player prop on PrizePicks in 5/6 prop entries. For example if the Minnesota Twins pitcher Sonny Gray was -140 or better to go over 4.5 strikeouts then his over 4.5 strikeouts would be a great play on Prizepicks. If only player props with approximately -140 odds or better are played in 5/6 player prop entries then a user will be profitable long term. So this tool will gather the props from Prizepicks and real time odds from DraftKings. It then compiles them into a table where it will highlight the mathematically long term profitable plays in green and the long term non-profitable plays in red.

Once you locate the green plays, which are profitable you must look at the odds beneath the over and under columns. The negative number is the favored side and the side that should be played on PrizePicks. For example lets say the line for Shohei Ohtani Strikeouts Thrown is set at 7.5 and highlighted in green. If a negative number is beneath the over column for that prop than you will want to play Ohtani over 7.5 strikeouts on PrizePicks. If a negative number is beneath the under column for that prop than you will want to play Ohtani under 7.5 strikeouts on PrizePicks.

Note that at night or times when Draft Kings and Prizepicks have not yet released all game Props/Lines the list will be very small or possibly empty after running the tool.  It is also important to note that Prize Picks will attempt to move the lines that player props are set at if one side is too heavily favored. So it is important to move quick to submit entries on PrizePicks once green player props have been identified before PrizePicks removes it or shifts the line so that no side is favored heavily. This also means that there may be times where there are no or few green props. So the tool can be ran whenever throughout the day to find the mathematically profitable player props when they appear as odds change and new player props are added.

