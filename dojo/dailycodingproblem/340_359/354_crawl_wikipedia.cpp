#include "catch2/catch.hpp" // for AssertionHandler, Sou...

namespace {
/*
Problem
This problem was asked by Google.

Design a system to crawl and copy all of Wikipedia using a distributed network
of machines.

More specifically, suppose your server has access to a set of client machines.
Your client machines can execute code you have written to access Wikipedia
pages, download and parse their data, and write the results to a database.

Some questions you may want to consider as part of your solution are:

How will you reach as many pages as possible?
How can you keep track of pages that have already been visited?
How will you deal with your client machines being blacklisted?
How can you update your database when Wikipedia pages are added or updated?

Solution
For any design problem, the first step should be to clarify the requirements.
What is the goal of this project? Do we have limited resources? How much error
can we tolerate?

To answer these questions, an interviewer will often recommend making reasonable
assumptions that help you solve the problem. This will be necessary in our case
as well.

We will assume, then, that the number of client machines is sufficiently large
that we do not need to worry about a few of them failing, and that each machine
has access to a separate database to which it can write webpage data. In
addition, let us say that the machines can communicate with the server but not
with each other.

It is also necessary to know a little about the structure of Wikipedia. A quick
Google search will tell us that English-language Wikipedia has around 50 million
pages, of which around 6 million are articles. Each article has links to related
articles embedded within the text, which must be extracted as we parse the page.

Outline

Now we are ready to dive into the general approach of our solution. Each client
machine, or bot, can be seeded with some initial URLs to crawl, designed to
explore different topics. The table of contents page has various categories that
we can use for this purpose.

For each article, the bot will download the HTML page data, extract new links,
and write the text of the article to its database. The links found will provide
us with new pages to crawl, and ideally through this process we will be able to
traverse all of Wikipedia.

There are several options for how each database might be structured, but the
simplest way would probably be a key value store mapping the URL to a JSON blob.
Databases will be separate, and we will assume we can combine all the results
together once our scraping phase is complete.

Here is how this would look:

               --------
              |        |
              | server |
              |        |
               --------
             /    |     \
           /      |       \
         /        |         \
 --------      --------       --------
|        |    |        |     |        |
| client |    | client |     | client |
|        |    |        |     |        |
 --------      --------       --------
    |              |              |
    |              |              |
   (DB)           (DB)           (DB)
Deduplication

The question now arises of how to prevent our bots from crawling the same page
multiple times. For example, it has been calculated that around 97% of the time,
starting from a random page and repeatedly following the first link will
eventually lead to philosophy.

One solution might be to store a local cache on each client of links already
traversed, and only follow links that have not been added to this cache. This
essentially amounts to executing N independent breadth-first searches, where N
is the number of client machines. However, this does nothing to solve the issue
of two clients independently scraping the same page.

Suppose that instead, the server maintains some data structure that keeps track
of unique URLs. Before visiting any page, a client will make a call to the
server to ensure the page has not been seen yet. After scraping this page, the
client will send a second request to the server marking the page as visited.

This is more effective, but at a significant cost of efficiency. A third and
improved approach is as follows. Each bot visits and parses its full list of
URLs, and populates a set of outward links discovered along the way. This entire
list is then batched up and sent to the server. Upon receiving such a batch, the
server combines and deduplicates these pages, and sends back the unvisited ones
to be crawled.

Our slightly modified diagram is as follows. We only show two client machines
for the sake of clarity, but there may be arbitrarily many.

 --------    (deduped URLs)    --------    (deduped URLs)    --------
|        |       <-----       |        |       <-----       |        |
| client |                    | server |                    | client |
|        |       ----->       |        |       ----->       |        |
 --------     (found links)    --------     (found links)    --------
    |                             |                              |
    |                             |                              |
    |                             |                              |
   (DB)                         deduper                         (DB)
How exactly should our deduper work, though, given that storing every URL in
memory may be infeasible? One useful tool we can employ here is a Bloom filter.

As discussed in a previous problem, a Bloom filter is a space-efficient data
structure that tests set membership. At the cost of some potential false
positives, we can guarantee a fixed, reasonable upper bound on the cost of
checking whether a page has already been visited.

Blacklisting

The advantage of having multiple bots performing our web crawling is that even
if a few IPs are blacklisted, the remaining ones can still continue scraping.
Nevertheless we would like to avoid this scenario if possible.

First, it helps to follow the rules. Many websites maintain a page called
robots.txt, which gives instructions to any bots crawling the site on what pages
should be accessed and by whom. We can see Wikipedia's version here. The
structure of this page is a series of assignments of the form:

User-agent: *
Disallow: /wiki/forbidden_page.html

User-agent: bad_actor
Disallow: /
The User-agent field defines which bots are being issued an instruction, and the
Disallow field specifies which domains are off-limits. In the first example
above, all bots are told not to visit a particularly forbidden page. In the
second, the bot bad_actor is told not to crawl at all.

A common reason that bots are disallowed is due to scraping too fast. To prevent
this from happening, we can first test the number of requests per second
Wikipedia can handle, and throttle our calls to stay within this limit.

It is also a good idea to map client machines to separate kinds of domains. This
way, we will not have every bot bombarding the same servers with traffic. In our
case, if we wanted to crawl articles in all different language domains, (for
example, en.wikipedia.org, es.wikipedia.org, and so on), we could assign pages
to each client accordingly.

Updates

Most articles on Wikipedia do not frequently have major updates. However, there
are indeed new pages created all the time, and with each news story, scientific
discovery, or piece of celebrity gossip, an article probably will be updated.

One simple implementation would be to store each URL and the date it was scraped
in a database accessible by the server. Each day we can run a query to find
articles older than N days, instruct our client machines to re-crawl them, and
update the date column. The downside of this approach is that unless N can be
dynamically determined to suit different kinds of articles, we will end up
scraping far more (or less) than necessary.

A more sensible approach for keeping track of updates to a site is with an RSS
feed, which allows subscribers to receive a stream of changes. In the case of
Wikipedia, there are both "New Page" and "Recent Changes" RSS feeds. As a
result, after our initial scrape is finished, we can direct our server to listen
to this feed and send instructions to the client machines to re-crawl the
updated pages.

As is often the case in design problems, we have only touched on a few areas in
detail, and there are many more questions we could answer. Feel free to explore
this in greater depth and implement your own version!

*/
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    REQUIRE(true);
}