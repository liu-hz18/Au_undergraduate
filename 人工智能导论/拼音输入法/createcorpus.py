
import json

inputfile = "answer_oral.txt"
output = "temp.txt"

with open(inputfile, 'r', encoding='gbk', errors='ignore') as f:
    lines = f.readlines()
with open(output, 'w+', encoding='gbk', errors='ignore') as f:
    for line in lines:
        temp = {"html": line.strip(), "time": "2019.03.12"}
        f.write(json.dumps(temp, ensure_ascii=False) + '\n')
