md ..\outs\250\conc-8t
for ($i=1; $i -le 10; $i++)
{
    echo "matriz 250 : $i"
    Get-Content ..\..\matrizes\matriz250.txt | start /REALTIME ..\JRParalelo > ..\outs\250\conc-8t\250_concOp$i.txt
}

md ..\outs\500\conc-8t
for ($i=1; $i -le 10; $i++)
{
    echo "matriz 500 : $i"
     Get-Content ..\..\matrizes\matriz500.txt | start /REALTIME ..\JRParalelo > ..\outs\500\conc-8t\500_concOp$i.txt
}

md ..\outs\1000\conc-8t
for ($i=1; $i -le 10; $i++)
{
    echo "matriz 1000 : $i"
	Get-Content ..\..\matrizes\matriz1000.txt | start /REALTIME ..\JRParalelo > ..\outs\1000\conc-8t\1000_concOp$i.txt
}

md ..\outs\1500\conc-8t
for ($i=1; $i -le 10; $i++)
{
    echo "matriz 1500 : $i"
	Get-Content ..\..\matrizes\matriz1500.txt | start /REALTIME ..\JRParalelo > ..\outs\1500\conc-8t\1500_concOp$i.txt
}

md ..\outs\2000\conc-8t
for ($i=1; $i -le 10; $i++)
{
    echo "matriz 2000 : $i"
	Get-Content ..\..\matrizes\matriz2000.txt | start /REALTIME ..\JRParalelo > ..\outs\2000\conc-8t\2000_concOp$i.txt
}

md ..\outs\3000\conc-8t
for ($i=1; $i -le 10; $i++)
{
    echo "matriz 3000 : $i"
	Get-Content ..\..\matrizes\matriz3000.txt | start /REALTIME ..\JRParalelo > ..\outs\3000\conc-8t\3000_concOp$i.txt
}

md ..\outs\4000\conc-8t
for ($i=1; $i -le 10; $i++)
{
    echo "matriz 4000 : $i"
	Get-Content ..\..\matrizes\matriz4000.txt | start /REALTIME ..\JRParalelo > ..\outs\4000\conc-8t\4000_concOp$i.txt
}
