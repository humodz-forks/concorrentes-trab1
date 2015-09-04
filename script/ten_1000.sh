for (( i = 0; i < 10; i++ )); do
	../JR < ../../matrizes/matriz1000.txt > ../outs/1000/seq/1000_seqOp$i.txt
	../JRParalelo < ../../matrizes/matriz1000.txt > ../outs/1000/conc/1000_concOp$i.txt
done