for (( i = 0; i < 10; i++ )); do
	echo "matriz 250 : $i"
	../JR < ../../matrizes/matriz250.txt > ../outs/250/seq/250_seqOp$i.txt
done

for (( i = 0; i < 10; i++ )); do
	echo "matriz 500 : $i"
	../JR < ../../matrizes/matriz500.txt > ../outs/500/seq/500_seqOp$i.txt
done

for (( i = 0; i < 10; i++ )); do
	echo "matriz 1000 : $i"
	../JR < ../../matrizes/matriz1000.txt > ../outs/1000/seq/1000_seqOp$i.txt
done

for (( i = 0; i < 10; i++ )); do
	echo "matriz 1500 : $i"
	../JR < ../../matrizes/matriz1500.txt > ../outs/1500/seq/1500_seqOp$i.txt
done

for (( i = 0; i < 10; i++ )); do
	echo "matriz 2000 : $i"
	../JR < ../../matrizes/matriz2000.txt > ../outs/2000/seq/2000_seqOp$i.txt
done

for (( i = 0; i < 10; i++ )); do
	echo "matriz 3000 : $i"
	../JR < ../../matrizes/matriz3000.txt > ../outs/3000/seq/3000_seqOp$i.txt
done

for (( i = 0; i < 10; i++ )); do
	echo "matriz 4000 : $i"
	../JR < ../../matrizes/matriz4000.txt > ../outs/4000/seq/4000_seqOp$i.txt
done