import sys

entrada = open(sys.argv[1], "r")

fichero = sys.argv[1] + "_I_S_data"

salida = open(fichero, "w")


with open(sys.argv[1]) as fp:
	line = fp.readline()
	while line:
		items = line.strip()
		items = items.split(',')
		linea = items[1] + ',' + items[2] + '\n'
		salida.write(linea)
		line = fp.readline()
