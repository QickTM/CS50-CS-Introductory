You already know about plurality elections, which follow a very simple algorithm for determining the winner of an election: every voter gets one vote, and the candidate with the most votes wins.<br>
But the plurality vote does have some disadvantages. What happens, for instance, in an election with three candidates, and the ballots below are cast?<br>

![image](https://github.com/QickTM/CS50-CS-Introductory/assets/77444347/fe0aa0a0-7239-4e0c-927d-004707f87279)<br>

A plurality vote would here declare a tie between Alice and Bob, since each has two votes. But is that the right outcome?<br>

There’s another kind of voting system known as a ranked-choice voting system. In a ranked-choice system, voters can vote for more than one candidate.<br>
Instead of just voting for their top choice, they can rank the candidates in order of preference. The resulting ballots might therefore look like the below.<br>

![image](https://github.com/QickTM/CS50-CS-Introductory/assets/77444347/7872454a-1344-429a-9ef0-6927b367bbe3)<br>

Here, each voter, in addition to specifying their first preference candidate, has also indicated their second and third choices.<br>
And now, what was previously a tied election could now have a winner. The race was originally tied between Alice and Bob, so Charlie was out of the running.<br>
But the voter who chose Charlie preferred Alice over Bob, so Alice could here be declared the winner. <br>

Ranked choice voting can also solve yet another potential drawback of plurality voting. Take a look at the following ballots. <br>

![image](https://github.com/QickTM/CS50-CS-Introductory/assets/77444347/8c590558-51c8-481c-9a83-53913d006f19)<br>

Who should win this election?<br>
In a plurality vote where each voter chooses their first preference only, Charlie wins this election with four votes compared to only three for Bob and two for Alice.<br> 
But a majority of the voters (5 out of the 9) would be happier with either Alice or Bob instead of Charlie. <br>
By considering ranked preferences, a voting system may be able to choose a winner that better reflects the preferences of the voters.<br>

One such ranked choice voting system is the instant runoff system. <br>
In an instant runoff election, voters can rank as many candidates as they wish. <br>
If any candidate has a majority (more than 50%) of the first preference votes, that candidate is declared the winner of the election.<br>

If no candidate has more than 50% of the vote, then an “instant runoff” occurs. <br>
The candidate who received the fewest number of votes is eliminated from the election, and anyone who originally chose that candidate as their first preference now has their second preference considered. <br>
Why do it this way? Effectively, this simulates what would have happened if the least popular candidate had not been in the election to begin with.<br>

The process repeats: if no candidate has a majority of the votes, the last place candidate is eliminated, 
and anyone who voted for them will instead vote for their next preference (who hasn’t themselves already been eliminated). Once a candidate has a majority, that candidate is declared the winner.<br>

Let’s consider the nine ballots above and examine how a runoff election would take place.<br>

Alice has two votes, Bob has three votes, and Charlie has four votes. <br>
To win an election with nine people, a majority (five votes) is required. <br>
Since nobody has a majority, a runoff needs to be held. <br>
Alice has the fewest number of votes (with only two), so Alice is eliminated. <br>
The voters who originally voted for Alice listed Bob as second preference, so Bob gets the extra two vote. <br>
Bob now has five votes, and Charlie still has four votes. <br>
Bob now has a majority, and Bob is declared the winner.<br>

What corner cases do we need to consider here?<br>

One possibility is that there’s a tie for who should get eliminated. <br>
We can handle that scenario by saying all candidates who are tied for last place will be eliminated. <br>
If every remaining candidate has the exact same number of votes, though, eliminating the tied last place candidates means eliminating everyone! <br>
So in that case, we’ll have to be careful not to eliminate everyone, and just declare the election a tie between all remaining candidates.<br>

Some instant runoff elections don’t require voters to rank all of their preferences — so there might be five candidates in an election, but a voter might only choose two.<br> 
For this problem’s purposes, though, we’ll ignore that particular corner case, and assume that all voters will rank all of the candidates in their preferred order.<br>
