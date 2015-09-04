for (( i = 0; i < 10; i++ )); do
	../JR < ../../matrizes/matriz250.txt > ../outs/250/seq/250_seqOp$i.txt
	../JRParalelo < ../../matrizes/matriz250.txt > ../outs/250/conc/250_concOp$i.txt
done