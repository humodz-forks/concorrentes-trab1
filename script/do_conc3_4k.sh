for (( i = 0; i < 10; i++ )); do
	echo "matriz 4000 : $i"
	../JRParalelo3 <  ../../matrizes/matriz4000.txt > ../outs/4000/conc3/4000_conc3_Op$i.txt
done