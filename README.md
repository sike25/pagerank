## PageRank and The Amherst Website

---

> "PageRank can be thought of as a model of user behavior. We assume there is a "random surfer" who is given a web page at random and keeps clicking on links, never hitting "back" but eventually gets bored and starts on another random page. The probability that the random surfer visits a page is its PageRank."

**— Larry Page and Sergey Brin**

### Implementation

I map and visualize the net structure of the web pages in www.amherst.edu. 

#### Web scraping

I use the Python library:

I remove webpages that 

#### Rank Calculation

After collecting this data, we calculate the page ranks with a C++ program

#### Visualization

We finish by using a Javascript program and the D3 library
