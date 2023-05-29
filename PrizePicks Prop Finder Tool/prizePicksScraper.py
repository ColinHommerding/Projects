from selenium import webdriver
from selenium.webdriver.common.keys import Keys
import time
from selenium.common.exceptions import NoSuchElementException
from selenium.common.exceptions import StaleElementReferenceException
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.proxy import *
import undetected_chromedriver as uc

class PrizePicks:

	def getProps(self) -> list: 
		options = uc.ChromeOptions()
		options.headless = True
		options.add_argument("--window-size=1920,1080")
		options.add_argument('--log-level=1')
		user_agent = 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/60.0.3112.50 Safari/537.36'
		options.add_argument(f'user-agent={user_agent}')
		options.add_argument("--no-sandbox")
		options.add_argument("--disable-gpu")
		driver = uc.Chrome(version_main = 113, options = options)
		# Has the driver navigate to Prize Picks
		driver.get("https://app.prizepicks.com/")
		wait = WebDriverWait(driver, 5)
		driver.find_element(By.CLASS_NAME, "close").click()
		time.sleep(2)
		driver.find_element(By.XPATH, "//div[@class='name'][normalize-space()='MLB']").click()
		time.sleep(2)

		# Makes sure the stat_container element is available before attempting to access it
		stat_container = WebDriverWait(driver, 10).until(EC.visibility_of_element_located((By.CLASS_NAME, "stat-container")))

		# Locates all the different types of of statistics
		categories = driver.find_element(By.CSS_SELECTOR, ".stat-container").text.split('\n')

		# Creates the list where the props will be stored
		playersList = []

		# Loops through each of the stat categories
		for category in categories:
			driver.find_element(By.XPATH, f"//div[text()='{category}']").click()
			projections = WebDriverWait(driver, 20).until(EC.presence_of_all_elements_located((By.CSS_SELECTOR, ".projection")))

			# Loops through all the props in each stat category to store the data of the prop in the playersList
			for projection in projections:

        			names = projection.find_element(By.XPATH, './/div[@class="name"]').text
        			points= projection.find_element(By.XPATH, './/div[@class="presale-score"]').get_attribute('innerHTML')
        			text = projection.find_element(By.XPATH, './/div[@class="text"]').text.replace('\n','')

        			players = {'Name': names, 'Prop':points, 'Line':text} 

        			playersList.append(players)


		return playersList
