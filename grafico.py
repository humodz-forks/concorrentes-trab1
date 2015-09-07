import plotly.plotly as py
from plotly.graph_objs import *


sequencial = Scatter(  
    x=[250,500,1000,1500,2000,3000,4000],
    y=[0.434,3.171,25.894,86.242,205.131,685.682,1254.931],
    name ="Sequencial",
    error_y=ErrorY(
        symmetric=False,
        type='data',
        color = 'rgb(255, 0, 0)',
        array=[0.006,0.009,0.097,0.187,3.128,2.221,17.451],
        arrayminus=[0.004,0.0122,0.052,0.162,1.861,1.690,13.034],
        visible=True
    ),
    visible=True,
    xaxis='x',
    yaxis='y'
)


otimizado = Scatter( #sequencial com -O3
    x=[250, 500, 1000,1500,2000,3000,4000],# cada um  eh a ordem de uma matriz
    y=[0.117,0.823,6.855,22.650,54.352,179.004,324.299], # cada um eh a media dos tempos de execucao da matriz;;;
    name='Otimizado',
    error_y=ErrorY(
        symmetric=False,
        type='data',
        color='rgb(255, 0, 0)',
        array=[0.033, 0.047, 0.04,0.106,4.06,0.615,0.46], # num do maior tempo de execucao menos a media
        arrayminus=[0.015,0.024,0.041,0.103,1.151,0.736,0.485], # media menos o menor tempo de execucao
        visible=True
    ),
    visible=True,
    marker=Marker(
        color='rgb(0, 0, 0)')
)

thread3 = Scatter(  #com 3 thread s
    x=[250,500,1000,1500,2000,3000,4000],
    y=[0.107,0.644,5.178,17.079,39.038,127.821,229.525],
    name ="3 threads",
    error_y=ErrorY(
        symmetric=False,
        type='data',
        color = 'rgb(255, 0, 0)',
        array=[0.021,0.002,0.06,0.157,0.409,1.103,3.058],
        arrayminus=[0.003,0.018,0.094,0.114,0.135,0.437,0.856],
        visible=True
    ),
    visible=True,
    xaxis='x',
    yaxis='y'
)

thread4 = Scatter( # com 4 threads
    x=[250,500,1000,1500,2000,3000,4000],
    y=[0.131,0.717,4.961,14.538,31.486,101.212,180.395],
    name="4 threads",
    error_y=ErrorY(
        symmetric=False,
        type='data',
        color = 'rgb(255,0,0)',
        array=[0.033,0.041,0.278,0.296,1.110,1.805,7.617],
        arrayminus=[0.006,0.028,0.133,0.239,0.293,1.205,2.445],
        visible=True
        ),
    visible=True,
    xaxis='x',
    yaxis='y'
)

layout = Layout(
    showlegend=True,
    autosize=True,
    width=500,
    height=500,
    xaxis=XAxis(
        title='Ordem',
       
        type='linear',
        autorange=True
    ),
    yaxis=YAxis(
        title='Tempo',
        
        type='linear',
        autorange=True
    ),
    margin=Margin(
        l=65,
        r=50,
        b=65,
        t=65
    ),
    hovermode='x',
    dragmode='zoom'
)

data = Data([sequencial,otimizado, thread3,thread4])
fig = Figure(data=data, layout=layout)
#py.image.save_as({'data':data,'layout':layout},'img\\a.png')
url = py.plot(fig)