for (( i = 0; i < 10; i++ )); do
	../JR < ../../matrizes/matriz3000.txt > ../outs/3000/seq/3000_seqOp$i.txt
	../JRParalelo < ../../matrizes/matriz3000.txt > ../outs/3000/conc/3000_concOp$i.txt
done