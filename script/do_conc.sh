for (( i = 0; i < 10; i++ )); do
	echo "matriz 250 : $i"
	../JRParalelo < ../../matrizes/matriz250.txt > ../outs/250/conc/250_concOp$i.txt
done

for (( i = 0; i < 10; i++ )); do
	echo "matriz 500 : $i"
	../JRParalelo < ../../matrizes/matriz500.txt > ../outs/500/conc/500_concOp$i.txt
done

for (( i = 0; i < 10; i++ )); do
	echo "matriz 1000 : $i"
	../JRParalelo < ../../matrizes/matriz1000.txt > ../outs/1000/conc/1000_concOp$i.txt
done

for (( i = 0; i < 10; i++ )); do
	echo "matriz 1500 : $i"
	../JRParalelo < ../../matrizes/matriz1500.txt > ../outs/1500/conc/1500_concOp$i.txt
done

for (( i = 0; i < 10; i++ )); do
	echo "matriz 2000 : $i"
	../JRParalelo < ../../matrizes/matriz2000.txt > ../outs/2000/conc/2000_concOp$i.txt
done

for (( i = 0; i < 10; i++ )); do
	echo "matriz 3000 : $i"
	../JRParalelo < ../../matrizes/matriz3000.txt > ../outs/3000/conc/3000_concOp$i.txt
done

for (( i = 0; i < 10; i++ )); do
	echo "matriz 4000 : $i"
	../JRParalelo <  ../../matrizes/matriz4000.txt > ../outs/4000/conc/4000_concOp$i.txt
done
