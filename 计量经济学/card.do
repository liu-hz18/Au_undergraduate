// Code: HW3, return on schooling
cd "D:\大三上\计量\作业\hw3" //put your folder path here
use card.dta, clear

* Estimate OLS
reg lwage educ smsa exper expersq motheduc

* Verify first stage
reg educ nearc4

* Estimate 2SLS
ivregress 2sls lwage smsa exper expersq motheduc (educ = nearc4)

* Endogenous test
estat endogenous
