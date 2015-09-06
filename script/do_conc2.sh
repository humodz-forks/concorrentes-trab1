for (( i = 0; i < 10; i++ )); do
	echo "matriz 250 : $i"
	../JRParalelo2 < ../../matrizes/matriz250.txt > ../outs/250/conc2/250_conc2_Op$i.txt
done

for (( i = 0; i < 10; i++ )); do
	echo "matriz 500 : $i"
	../JRParalelo2 < ../../matrizes/matriz500.txt > ../outs/500/conc2/500_conc2_Op$i.txt
done

for (( i = 0; i < 10; i++ )); do
	echo "matriz 1000 : $i"
	../JRParalelo2 < ../../matrizes/matriz1000.txt > ../outs/1000/conc2/1000_conc2_Op$i.txt
done

for (( i = 0; i < 10; i++ )); do
	echo "matriz 1500 : $i"
	../JRParalelo2 < ../../matrizes/matriz1500.txt > ../outs/1500/conc2/1500_conc2_Op$i.txt
done

for (( i = 0; i < 10; i++ )); do
	echo "matriz 2000 : $i"
	../JRParalelo2 < ../../matrizes/matriz2000.txt > ../outs/2000/conc2/2000_conc2_Op$i.txt
done

for (( i = 0; i < 10; i++ )); do
	echo "matriz 3000 : $i"
	../JRParalelo2 < ../../matrizes/matriz3000.txt > ../outs/3000/conc2/3000_conc2_Op$i.txt
done

for (( i = 0; i < 10; i++ )); do
	echo "matriz 4000 : $i"
	../JRParalelo2 <  ../../matrizes/matriz4000.txt > ../outs/4000/conc2/4000_conc2_Op$i.txt
done
