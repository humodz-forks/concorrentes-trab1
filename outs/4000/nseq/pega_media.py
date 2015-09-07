import os

arquivos = os.listdir() # pega uma lista com todos os arquivos da pasta

medias = []
interacoes = 0
for nome_arq in arquivos:
	if 'txt' in nome_arq and "final" not in nome_arq:
		arq = open(nome_arq,'r')
		esquece_primeiro_tempo = True
		for line in arq:
			if line != '':
				if "tempo de leitura" in line :
					if esquece_primeiro_tempo :
						esquece_primeiro_tempo = False
					else :
						frase,tempo = line.split(": ")
						tempo = tempo.replace("\n",'')
						medias.append(float(tempo))
				if 'Numero de Interacoes' in line :
					interacoes = line			
		arq.close()

new_arq = open('final.txt','w')
new_arq.write("Tempos:\n")
media= 0.0
maior_tempo = 0.0 
menor_tempo = 99999.0
medias
for i in medias:
	new_arq.write(str(i)+"\n")
	media +=i
	if i > maior_tempo:
		maior_tempo = i
	if i < menor_tempo:
		menor_tempo = i
media/=3.0
new_arq.write(str(interacoes)+"\n")
new_arq.write("media: "+str(media)+"\n")
new_arq.write("maior tempo : "+str(maior_tempo)+"\n")
new_arq.write("menor tempo : "+str(menor_tempo)+"\n\n\n")
new_arq.write("array: "+str(maior_tempo-media)+"\n")
new_arq.write("arrayminus: "+str(media-menor_tempo)+"\n")
new_arq.close()
