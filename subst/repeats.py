file = open('./repeats', 'w')
string = "GATTACA"
for i in range(1,50):
    file.write(string)

file.close()
