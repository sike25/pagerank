import requests
import re
import threading
from bs4 import BeautifulSoup

"""
a set of all amherst links
the number of all amherst links
validate the set, by making sure following any of them does not lead to an error

omit:
archive
course-evaluations
2001 t0 2016

a map that indexes them by id, which will go on to be their matrix indexes
a 2d matrix representing their relationships

written to an output file


# is not under news or library (huge)
    if not href.startswith("https://www.amherst.edu/news/") and not href.startswith("https://www.amherst.edu/library") and not href.startswith("https://www.amherst.edu/taxonomy/"):
        # is not a course or user page, news release or a calendar entry (there are too many of these)
            if not href.startswith("https://www.amherst.edu/user") and not href.startswith("https://www.amherst.edu/academiclife/departments/courses/") and not href.startswith("https://www.amherst.edu/news/news_releases/") and not href.startswith("https://www.amherst.edu/news/events/calendar"):
"""

def is_valid_link(href, url, visitedLinks):
    # initialise return variable
    isValid = False
    # Define the file extensions to ignore
    ignored_extensions = ['.jpg', '.jpeg', '.png', '.gif', '.ics', '.pdf', '.mp4', '.mp3', '.docx', '.html']

    # Ensure the link is not null, does not lead to the same page it lives in.
    if href and href != url:
        # is an amherst.edu link
        if href.startswith("https://www.amherst.edu/"):
            # is not a duplicate page in php
            if not href.startswith("https://www.amherst.edu/index.php/"):
                # is not a shortcut, bookmark or a log in page
                if "/mm/" not in href and "/go/" not in href and "/node/" not in href and "#" not in href and "?" not in href and "-mm-" not in href and "/saml/" not in href and not re.match(r'^https://www.amherst.edu/\d', href):
                    # is a page and not a file
                    if not href.startswith("https://www.amherst.edu/system/files/") and not href.startswith("https://www.amherst.edu/securimage") and not href.startswith("https://www.amherst.edu/media/") and not any(href.endswith(ext) for ext in ignored_extensions):
                        # is not more than four pages deep
                        if href.count('/') <= 5:
                            # is not a user page (too plenty) 
                            if not href.startswith("https://www.amherst.edu/user"):
                                    # has not been visited
                                    if href not in visitedLinks:
                                        isValid = True
    return isValid

def find_links(url, toVisitLinks, visitedLinks):
    print()
    try:
        # Send a GET request to the URL
        response = requests.get(url)
        
        # Check if the request was successful (status code 200)
        if response.status_code == 200:
            # Parse the HTML content of the page
            soup = BeautifulSoup(response.text, 'html.parser')
            
            # Find all the links in the page
            links = soup.find_all('a')
            
            # Extract and print the href attribute of each link
            for link in links:
                href = link.get('href')

                if href and href.startswith("/"):
                    href = "https://www.amherst.edu" + href
                    isValidLink = is_valid_link(href, url, visitedLinks)
                else:
                    isValidLink = is_valid_link(href, url, visitedLinks)

                if isValidLink:
                    if href not in toVisitLinks:
                            print(href)
                    toVisitLinks.add(href)

        else:
            print(f"Error: {response.status_code}")
            
    except Exception as e:
        print(f"An error occurred: {e}")


def validateAndWriteLinks(links):
    print("validate collated links.")
    validatedLinks = set()
    for url in links:
        try:
            # Send a GET request to the URL
            response = requests.get(url)
            # If the request succeeds (status code 200)
            if response.status_code == 200:
                # add the link to our validated set
                validatedLinks.add(url)
                with open('C:\\Users\\ogiev\\OneDrive\\Desktop\\amherstwebpages.txt', 'a') as file:
                    # and write link into our output file
                    file.write('\n'+url)     
        except Exception as e: 
            print(f"An error occurred: {e}")
    links = validatedLinks

    

def collate_links():
    toVisitLinks = set()
    visitedLinks = set()
    visitedLinks.add('https://www.amherst.edu/')
    find_links('https://www.amherst.edu/', toVisitLinks, visitedLinks)

    count = 0
    while toVisitLinks and count < 10:
        count += 1
        presentLink = toVisitLinks.pop()
        visitedLinks.add(presentLink)
        find_links(presentLink, toVisitLinks, visitedLinks)

    print("studying ", len(visitedLinks), " links.")
    validateAndWriteLinks(visitedLinks)
    print("now studying ", len(visitedLinks), " links.")


    # Create two threads
    threadOne = threading.Thread(target=find_links)
    threadTwo = threading.Thread(target=find_links)

    # Start the threads
    threadOne.start()
    threadTwo.start()

    # Wait for both threads to finish
    threadOne.join()
    threadTwo.join()

  
collate_links()

"""
import threading
import time

def print_characters(start, end):
    for char in range(ord(start), ord(end) + 1):
        time.sleep(1)  # Simulate some work
        print(f"{threading.current_thread().name}: {chr(char)}")

# Create two threads targeting the same function with the same arguments
thread1 = threading.Thread(target=print_characters, args=('A', 'E'), name='Thread 1')
thread2 = threading.Thread(target=print_characters, args=('A', 'E'), name='Thread 2')

# Start the threads
thread1.start()
thread2.start()

# Wait for both threads to finish
thread1.join()
thread2.join()

print("Both threads have finished.")

"""
