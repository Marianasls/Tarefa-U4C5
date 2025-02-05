# Tarefa do EmbarcaTech U4C5

## Descrição
1. Atividade 1:
   Semáforo com temporização de 3 segundos para cada alteração de sinal.
2. Atividade 2:
   Sistema de temporização para o acionamento de LEDs, que atua a partir do clique em um
botão (pushbutton).

## Componentes

O projeto utiliza os seguintes componentes conectados à placa BitDogLab:

- **LED RGB**: com os pinos conectados às GPIOs 11, 12 e 13.
- **Botão A**: conectado à GPIO 5.

## Como Executar

1. Conecte a placa BitDogLab ao computador via cabo micro-usb
2. Compile e faça o upload do código para o microcontrolador.
3. Atividade 1:
   - Os LEDs RGB irão alternar entre os canais vermelho, amarelo e azul, a cada 3 segundos, repedidamente.
4. Atividade 2:
   - Ao pressionar o botão A o LED RGB irá ligar os três canais ao mesmo tempo.
   - Os canais azul, vermelho e verde serão apagados a cada 2 segundos, respectivamente.
   - Quando todos os canais estirem apagados, o botão poderá ser acionado novamente para acender o LED RGB. Se o botão for acionado antes dos três canais estarem desligados, o estado dos canais não será alterado.

## Simulação
É possível testar o projeto no ambiente de simulação wokwi, ao clicar no arquivo "diagram.json" e iniciar a simulação.