from draftKingsScraper import DraftKings
from prizePicksScraper import PrizePicks
import pandas as pd


print("Prop Finder Started")
dk = DraftKings()
pp = PrizePicks()
# Runs method to obtain prize picks props
propsPP = pp.getProps()
# Runs method to obtain props and lines from Draft Kings
propsDK = dk.get_pregame_odds()
# Creates the list that is for storing the Prize Picks props with their appropriate odds to go over or under from Draft Kings
finalProps = []

# Loops through Prize Picks props and Draft King odds to match the Prize Pick props with their appropriate odds to go over or under from Draft Kings. Then stores the data in the finalProps list.
for i in range(len(propsPP)):
	for j in range(len(propsDK)):
		if propsPP[i]['Name'] in propsDK[j]['player_statistic']:
			words = propsDK[j]['player_statistic'].split(' ')
			if propsDK[j]['stat'] == propsPP[i]['Line']:
				if propsDK[j]['line'] == float(propsPP[i]['Prop']):
					props = {'Prop': propsDK[j]['player_statistic'], 'Line': propsPP[i]['Prop'], 'Over': propsDK[j]['odds_over'], 'Under': propsDK[j]['odds_under']}
					finalProps.append(props)
					



doctype = "<!DOCTYPE html> \n"
script = "\n <script type='text/javascript' src='https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js'></script>\n <script type='text/javascript' src='script.js'></script> \n"
style = "\n <head> \n <link rel='stylesheet' href='style.css'> \n </head> \n"
end = " \n </html>"

df = pd.DataFrame(finalProps)
result = df.to_html()
# Create final layout for html page
result = doctype + style + result + script + end
text_file = open("index.html", "w", encoding="utf-8")
text_file.write(result)
text_file.close()
print("Prop Finder Completed")