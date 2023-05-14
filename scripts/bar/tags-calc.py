#!/usr/bin/env python
import sys, re
scan = None
ocpd = None
 
def extract(str):
	return int(re.findall(r'\d+', str)[0])
 
def addf(arr, num):
	if num in arr:
		return " ".join(str(x) for x in arr).replace(str(num), 'F' + str(num))
	else:
		return " ".join(str(x) for x in sorted(arr + [num])).replace(str(num), 'F' + str(num))
 
def tags(num, power = 16, arr = []):
  if power >= 0:
    if num >= pow(2, power):
      return tags(num - pow(2, power), power - 1, arr + [power + 1])
    else:
      return tags(num, power - 1, arr)
  return arr[::-1]
 
for line in sys.stdin:
	if 'old_state' in line:
		scan = False
	if 'new_state' in line:
		scan = True
	if 'occupied' in line and scan:
		print(addf(tags(extract(line)), ocpd))
	if 'selected' in line and scan:
		ocpd = tags(extract(line))[0]
