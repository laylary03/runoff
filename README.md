# runoff.c

This is my implementation of the **Runoff voting system** from Harvard’s [CS50x](https://cs50.harvard.edu/x) course.

## 🔁 Problem Summary

In a runoff election, voters rank candidates by preference. If no one wins a majority in the first round, the candidate(s) with the fewest votes are eliminated, and votes are redistributed based on next preferences — repeating until a winner emerges.

### Key Features:
- Accepts ranked votes from all voters
- Uses a 2D array to track preferences
- Eliminates lowest-ranked candidates in rounds
- Detects ties and breaks loops when needed

## 💡 Personal Note

This problem really tested my ability to manage **multiple arrays**, **nested loops**, and complex control flow. It pushed me — but I stuck with it and solved it on my own. Learned a ton about how real elections and simulations work.

## 🛠 Concepts Practiced

- 2D arrays
- Structs
- Dynamic elimination logic
- Nested loops and conditionals
- Handling ties and majority detection

## ✅ Status

Passed all `check50` tests for Runoff.

---
