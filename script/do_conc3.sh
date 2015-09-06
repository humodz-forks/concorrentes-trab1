for (( i = 0; i < 10; i++ )); do
	echo "matriz 250 : $i"
	../JRParalelo3 < ../../matrizes/matriz250.txt > ../outs/250/conc3/250_conc3_Op$i.txt
done

for (( i = 0; i < 10; i++ )); do
	echo "matriz 500 : $i"
	../JRParalelo3 < ../../matrizes/matriz500.txt > ../outs/500/conc3/500_conc3_Op$i.txt
done

for (( i = 0; i < 10; i++ )); do
	echo "matriz 1000 : $i"
	../JRParalelo3 < ../../matrizes/matriz1000.txt > ../outs/1000/conc3/1000_conc3_Op$i.txt
done

for (( i = 0; i < 10; i++ )); do
	echo "matriz 1500 : $i"
	../JRParalelo3 < ../../matrizes/matriz1500.txt > ../outs/1500/conc3/1500_conc3_Op$i.txt
done

for (( i = 0; i < 10; i++ )); do
	echo "matriz 2000 : $i"
	../JRParalelo3 < ../../matrizes/matriz2000.txt > ../outs/2000/conc3/2000_conc3_Op$i.txt
done

for (( i = 0; i < 10; i++ )); do
	echo "matriz 3000 : $i"
	../JRParalelo3 < ../../matrizes/matriz3000.txt > ../outs/3000/conc3/3000_conc3_Op$i.txt
done

for (( i = 0; i < 10; i++ )); do
	echo "matriz 4000 : $i"
	../JRParalelo3 <  ../../matrizes/matriz4000.txt > ../outs/4000/conc3/4000_conc3_Op$i.txt
done
