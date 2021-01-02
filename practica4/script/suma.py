import sys

entrada = open(sys.argv[1], "r")
fichero_s = sys.argv[1] + "_sum"
salida = open(fichero_s, "w")

with open(sys.argv[1]) as fp:
	line = fp.readline()
	while line:
		items = line.strip()
		items = items.split(',')
		suma = []
		suma.append(float(items[1]))
		suma.append(suma[0] + float(items[2]))
		suma.append(suma[1] + float(items[3]))
		suma_linea = items[0] + ',' + str(suma[0]) + ',' + str(suma[1]) + ',' + str(suma[2]) + '\n'
		salida.write(suma_linea)
		line = fp.readline()
