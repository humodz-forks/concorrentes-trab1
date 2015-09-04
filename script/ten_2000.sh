for (( i = 0; i < 10; i++ )); do
	../JR < ../../matrizes/matriz2000.txt > ../outs/2000/seq/2000_seqOp$i.txt
	../JRParalelo < ../../matrizes/matriz2000.txt > ../outs/2000/conc/2000_concOp$i.txt
done