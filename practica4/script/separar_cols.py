import sys

entrada = open(sys.argv[1], "r")

for i in range(1,4):
	for j in range(1,4):
		fichero = sys.argv[1]
		if i == 1:
			fichero += "_I"
		elif i == 2:
			fichero += "_S"
		elif i == 3:
			fichero += "_R"

		if j == 1:
			fichero += "_I_data"
		elif j == 2:
			fichero += "_S_data"
		elif j == 3:
			fichero += "_R_data"

		salida = open(fichero, "w")


		with open(sys.argv[1]) as fp:
			line = fp.readline()
			while line:
				items = line.strip()
				items = items.split(',')
				linea = items[i] + ',' + items[j] + '\n'
				salida.write(linea)
				line = fp.readline()
