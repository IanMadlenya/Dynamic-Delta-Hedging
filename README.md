# Dynamic-Delta-Hedging

- The following code monitors the pre-market trading prices of a single ticker AAPL
starting at 9am and after 9.30am EST (NYC time). Also,

  a. It records the pre-market trading price every 60 seconds between 9am and
9.30am EDT

  b. It continues to record the regular trading prices every 60 seconds from
9:30am to 16:00

  c. The code records the after-hours trading prices every 60 seconds from
16:00 to 16:30.

- It is possible to get N=10 queries for N=10 stocks by calling, for example:
 
 NASDAQ:AAPL,NYSE:JNJ,… in line #7 of the code. Program can
 
 fetch pre-market time-series, xi(t) (i=1,…,N), for N-asset portfolio.
 
 Given that, I compute a fractional root-mean-square volatility, σxi(t)/⟨xi(t)⟩,
 
 i.e. standard deviation divided by the mean, between 6am and 9.30am EDT
 
 for each asset and check if it can be used as an indicator for stock price movement
 
 after 9.30am. 

Tip: the higher market capitalization the firms the more trading are
 expected in first 15 min of a new session at Wall Street.
