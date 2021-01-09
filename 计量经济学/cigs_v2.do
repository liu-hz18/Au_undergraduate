* Code

* Put the name of the folder where you save the data. Note: dataset name should not be included
cd ""

* Import data from .csv files
clear
insheet using "cigs.csv"

* Create age groups = 0 (age <= 30); =1 (age <= 50 & age > 30); =2 (age <= 70 & age > 50); = 3 (age > 70)
g agegrp = (age > 30) + (age > 50) + (age > 70)
* Calculate the mean, standard deviation of cigs and the number of observations in each age group
tabstat cigs, by(agegrp) stat(mean n)

* Estimate: cigs ~ age, age^2, educ, restaurn. agesq: square of age
reg cigs age agesq educ restaurn

* Test whether the coefficient of age, agesq, educ are jointly zero at 1% significance level
test (age = 0) (agesq = 0) (educ = 0)

* At what estimated age level the expected number of cigs is the highest?
display -_b[age]/(_b[agesq]*2)

* Reestimate a model exploring whether the effects of no-smoking rule in the restaurant are the same for people with different education level
reg cigs age agesq restaurn educ i.restaurn#c.edu

clear
