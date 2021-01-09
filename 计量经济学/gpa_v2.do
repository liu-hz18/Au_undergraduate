// Code: HW3, gpa
cd "" //put your folder path here
use gpa.dta, clear

* Estimate original model, get residuals
reg colGPA hsGPA ACT skipped PC
predict uhat, residual
predict yhat

* Residual plot
rvfplot, yline(0)

* BP test
estat hettest

* Estimate weights
g u2 = uhat ^ 2
g yhat2 = yhat ^ 2
reg u2 yhat yhat2
predict hhat

* Verify weights are positive
count if hhat <= 0 //you should get zero

* Reestimate the model using WLS
reg colGPA hsGPA ACT skipped PC [weight = 1/hhat]

* Report WLS with heteroskedasticity-robust standard errors
reg colGPA hsGPA ACT skipped PC [weight = 1/hhat], vce(robust)

