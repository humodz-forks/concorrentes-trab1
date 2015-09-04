for (( i = 0; i < 10; i++ )); do
	../JR < ../../matrizes/matriz500.txt > ../outs/500/seq/500_seqOp$i.txt
	../JRParalelo < ../../matrizes/matriz500.txt > ../outs/500/conc/500_concOp$i.txt
done