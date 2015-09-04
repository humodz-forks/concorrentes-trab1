for (( i = 0; i < 10; i++ )); do
	../JR < ../../matrizes/matriz1500.txt > ../outs/1500/seq/1500_seqOp$i.txt
	../JRParalelo < ../../matrizes/matriz1500.txt > ../outs/1500/conc/1500_concOp$i.txt
done