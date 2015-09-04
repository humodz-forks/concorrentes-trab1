for (( i = 0; i < 10; i++ )); do
	../JR < ../../matrizes/matriz4000.txt > ../outs/4000/seq/4000_seqOp$i.txt
	../JRParalelo <  ../../matrizes/matriz4000.txt > ../outs/4000/conc/4000_concOp$i.txt
done