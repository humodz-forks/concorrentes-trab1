for (( i = 0; i < 3; i++ )); do
	echo "matriz 250 : $i"
	../JR < ../../matrizes/matriz250.txt > ../outs/250/nseq/250_seq$i.txt
done

for (( i = 0; i < 3; i++ )); do
	echo "matriz 500 : $i"
	../JR < ../../matrizes/matriz500.txt > ../outs/500/nseq/500_seq$i.txt
done

for (( i = 0; i < 3; i++ )); do
	echo "matriz 1000 : $i"
	../JR < ../../matrizes/matriz1000.txt > ../outs/1000/nseq/1000_seq$i.txt
done

for (( i = 0; i < 3; i++ )); do
	echo "matriz 1500 : $i"
	../JR < ../../matrizes/matriz1500.txt > ../outs/1500/nseq/1500_seq$i.txt
done

for (( i = 0; i < 3; i++ )); do
	echo "matriz 2000 : $i"
	../JR < ../../matrizes/matriz2000.txt > ../outs/2000/nseq/2000_seq$i.txt
done

for (( i = 0; i < 3; i++ )); do
	echo "matriz 3000 : $i"
	../JR < ../../matrizes/matriz3000.txt > ../outs/3000/nseq/3000_seq$i.txt
done

for (( i = 0; i < 3; i++ )); do
	echo "matriz 4000 : $i"
	../JR < ../../matrizes/matriz4000.txt > ../outs/4000/nseq/4000_seq$i.txt
done
