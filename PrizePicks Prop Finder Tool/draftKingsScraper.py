import requests


class DraftKings:
	def get_pregame_odds(self) -> list:
		
		# Creates a list to store all player props
		player_props = []
		url = f"https://sportsbook.draftkings.com//sites/US-SB/api/v5/eventgroups/84240/categories/1031/subcategories/9885?format=json"

		response = requests.get(url).json()
		
		categoryNum = 0
		
		# Loops through the different prop categories on Draft Kings
		for category in response['eventGroup']['offerCategories']:
			# Checks to see when the pitching props are located
			if category['name'] == "Pitcher Props":
				url = f"https://sportsbook.draftkings.com//sites/US-SB/api/v5/eventgroups/84240/categories/1031/subcategories/9885?format=json"
				response2 = requests.get(url).json()
				statTypeNum = 0
				# Loops through all the different pitching statistics and stores the props with their odds to go over and under in the player_props list
				for statType in response2['eventGroup']['offerCategories'][categoryNum]['offerSubcategoryDescriptors']:
					if statType['name'] == "Strikeouts":
						url = f"https://sportsbook.draftkings.com//sites/US-SB/api/v5/eventgroups/84240/categories/1031/subcategories/9885?format=json"
						response2 = requests.get(url).json()
						for game in response2['eventGroup']['offerCategories'][categoryNum]['offerSubcategoryDescriptors'][statTypeNum]['offerSubcategory']['offers']: 
							for player in game:
								player_props.append({"player_statistic": player['label'], "stat": "Pitcher Strikeouts", "line": player['outcomes'][0]['line'], "odds_over": player['outcomes'][0]['oddsAmerican'], "odds_under": player['outcomes'][1]['oddsAmerican']})
					if statType['name'] == "Outs Recorded":
						url = f"https://sportsbook.draftkings.com//sites/US-SB/api/v5/eventgroups/84240/categories/1031/subcategories/9883?format=json"
						response2 = requests.get(url).json()
						for game in response2['eventGroup']['offerCategories'][categoryNum]['offerSubcategoryDescriptors'][statTypeNum]['offerSubcategory']['offers']: 
							for player in game:
								player_props.append({"player_statistic": player['label'], "stat": "Pitching Outs", "line": player['outcomes'][0]['line'], "odds_over": player['outcomes'][0]['oddsAmerican'], "odds_under": player['outcomes'][1]['oddsAmerican']})
					if statType['name'] == "Hits Allowed":
						url = f"https://sportsbook.draftkings.com//sites/US-SB/api/v5/eventgroups/84240/categories/1031/subcategories/9886?format=json"
						response2 = requests.get(url).json()
						for game in response2['eventGroup']['offerCategories'][categoryNum]['offerSubcategoryDescriptors'][statTypeNum]['offerSubcategory']['offers']: 
							for player in game:
								player_props.append({"player_statistic": player['label'], "stat": "Hits Allowed", "line": player['outcomes'][0]['line'], "odds_over": player['outcomes'][0]['oddsAmerican'], "odds_under": player['outcomes'][1]['oddsAmerican']})
					if statType['name'] == "Earned Runs":
						url = f"https://sportsbook.draftkings.com//sites/US-SB/api/v5/eventgroups/84240/categories/1031/subcategories/11064?format=json"
						response2 = requests.get(url).json()
						for game in response2['eventGroup']['offerCategories'][categoryNum]['offerSubcategoryDescriptors'][statTypeNum]['offerSubcategory']['offers']: 
							for player in game:
								player_props.append({"player_statistic": player['label'], "stat": "Earned Runs Allowed", "line": player['outcomes'][0]['line'], "odds_over": player['outcomes'][0]['oddsAmerican'], "odds_under": player['outcomes'][1]['oddsAmerican']})
					if statType['name'] == "Walks":
						url = f"https://sportsbook.draftkings.com//sites/US-SB/api/v5/eventgroups/84240/categories/1031/subcategories/11035?format=json"
						response2 = requests.get(url).json()
						for game in response2['eventGroup']['offerCategories'][categoryNum]['offerSubcategoryDescriptors'][statTypeNum]['offerSubcategory']['offers']: 
							for player in game:
								player_props.append({"player_statistic": player['label'], "stat": "Walks Allowed", "line": player['outcomes'][0]['line'], "odds_over": player['outcomes'][0]['oddsAmerican'], "odds_under": player['outcomes'][1]['oddsAmerican']})													
					statTypeNum = statTypeNum + 1
			# Checks to see when the batting props are located
			if category['name'] == "Batter Props":
				url = f"https://sportsbook.draftkings.com//sites/US-SB/api/v5/eventgroups/84240/categories/743/subcategories/6607?format=json"
				response2 = requests.get(url).json()
				statTypeNum = 0
				# Loops through all the different batting statistics and stores the props with their odds to go over or under in the player_props list
				for statType in response2['eventGroup']['offerCategories'][categoryNum]['offerSubcategoryDescriptors']:
					if statType['name'] == "Total Bases":
						url = f"https://sportsbook.draftkings.com//sites/US-SB/api/v5/eventgroups/84240/categories/743/subcategories/6607?format=json"
						response2 = requests.get(url).json()
						for game in response2['eventGroup']['offerCategories'][categoryNum]['offerSubcategoryDescriptors'][statTypeNum]['offerSubcategory']['offers']: 
							for player in game:
								player_props.append({"player_statistic": player['label'], "stat": "Total Bases", "line": player['outcomes'][0]['line'], "odds_over": player['outcomes'][0]['oddsAmerican'], "odds_under": player['outcomes'][1]['oddsAmerican']})
					if statType['name'] == "Runs Scored":
						url = f"https://sportsbook.draftkings.com//sites/US-SB/api/v5/eventgroups/84240/categories/743/subcategories/7979?format=json"
						response2 = requests.get(url).json()
						for game in response2['eventGroup']['offerCategories'][categoryNum]['offerSubcategoryDescriptors'][statTypeNum]['offerSubcategory']['offers']: 
							for player in game:
								player_props.append({"player_statistic": player['label'], "stat": "Runs", "line": player['outcomes'][0]['line'], "odds_over": player['outcomes'][0]['oddsAmerican'], "odds_under": player['outcomes'][1]['oddsAmerican']})
					if statType['name'] == "Hits + Runs + RBIs":
						url = f"https://sportsbook.draftkings.com//sites/US-SB/api/v5/eventgroups/84240/categories/743/subcategories/12149?format=json"
						response2 = requests.get(url).json()
						for game in response2['eventGroup']['offerCategories'][categoryNum]['offerSubcategoryDescriptors'][statTypeNum]['offerSubcategory']['offers']: 
							for player in game:
								player_props.append({"player_statistic": player['label'], "stat": "Hits+Runs+RBIS", "line": player['outcomes'][0]['line'], "odds_over": player['outcomes'][0]['oddsAmerican'], "odds_under": player['outcomes'][1]['oddsAmerican']})
					if statType['name'] == "Strikeouts":
						url = f"https://sportsbook.draftkings.com//sites/US-SB/api/v5/eventgroups/84240/categories/743/subcategories/6605?format=json"
						response2 = requests.get(url).json()
						for game in response2['eventGroup']['offerCategories'][categoryNum]['offerSubcategoryDescriptors'][statTypeNum]['offerSubcategory']['offers']: 
							for player in game:
								player_props.append({"player_statistic": player['label'], "stat": "Hitter Strikeouts", "line": player['outcomes'][0]['line'], "odds_over": player['outcomes'][0]['oddsAmerican'], "odds_under": player['outcomes'][1]['oddsAmerican']})											
					statTypeNum = statTypeNum + 1

			

			categoryNum = categoryNum + 1






		return player_props