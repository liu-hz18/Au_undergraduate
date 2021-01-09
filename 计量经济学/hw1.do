cd "D:\大三上\计量\作业\"  //注意修改数据路径
use "EduIncome.dta", clear

summarize gender birthyear marriage empjob_twage schooling_yr

generate female = 1 if gender == 1
replace female = 0 if female==.
tab female

reg empjob_twage schooling_yr female

generate pred_twage = 1984.774*schooling_yr - 14048.56 * female + 46554.54

generate pred_u = empjob_twage - pred_twage

summarize empjob_twage pred_twage pred_u

drop pred_twage pred_u
