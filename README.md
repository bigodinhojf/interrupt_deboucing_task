<div align="center">
    <img src="https://moodle.embarcatech.cepedi.org.br/pluginfile.php/1/theme_moove/logo/1733422525/Group%20658.png" alt="Logo Embarcatech" height="100">
</div>

<br>

# Uso de Interrupções, Deboucing e controle de LEDs

## Sumário

- [Descrição](#descrição)
- [Funcionalidades Implementadas](#funcionalidades-implementadas)
- [Ferramentas utilizadas](#ferramentas-utilizadas)
- [Objetivos](#objetivos)
- [Instruções de uso](#instruções-de-uso)
- [Vídeo de apresentação](#vídeo-de-apresentação)
- [Aluno e desenvolvedor do projeto](#aluno-e-desenvolvedor-do-projeto)
- [Licensa](#licença)

## Descrição

Este projeto implementa um sistema interativo utilizando a placa de desenvolvimento BitDogLab e o microcontrolador Raspberry Pi Pico W. Ele também foi desenvolvido e testado no simulador de eletrônica Wokwi, integrando uma matriz de LEDs RGB 5x5 WS2812, um LED RGB e dois botões físicos para explorar o uso de interrupções e debouncing via software. O objetivo principal é exibir números de 0 a 9 na matriz de LEDs, permitindo a navegação entre eles através dos botões, enquanto um LED RGB pisca continuamente.

## Funcionalidades Implementadas

1. Exibição de números na matriz de LEDs RGB 5x5:

   - A matriz WS2812 exibe números de 0 a 9 em um formato fixo ou criativo.
   - Os números podem ser representados por segmentos iluminados ou efeitos visuais personalizados, desde que sejam claramente identificáveis.

2. Controle de números via botões físicos:

   - Botão A (GPIO 5): Incrementa o número exibido na matriz de LEDs.
   - Botão B (GPIO 6): Decrementa o número exibido na matriz de LEDs.

3. Debouncing via software:

   - Implementação de um algoritmo de debouncing para evitar leituras indesejadas devido ao bouncing mecânico dos botões.

4. Piscar contínuo do LED RGB:

   - O LED vermelho do LED RGB (GPIO 11) pisca 5 vezes por segundo continuamente.

## Ferramentas utilizadas

- **Simulador de eletrônica wokwi**: Ambiente utilizado para simular o hardware e validar o funcionamento do sistema.
- **Ferramenta educacional BitDogLab (versão 6.3)**: Placa de desenvolvimento utilizada para programar o microcontrolador.
- **Microcontrolador Raspberry Pi Pico W**: Responsável pelo controle da matriz de LEDs, teclado matricial e o buzzer.
- **Matriz de LEDs RGB 5x5**: Dispositivo principal para exibição de animações controladas pelo sistema.
- **LED RGB**: Dispositivo utilizado para piscar 5 vezes por segundo, servindo como indicador visual.
- **Botões físicos (2 unidades)**: Utilizados para incrementar e decrementar os números exibidos na matriz de LEDs.
- **Visual Studio Code (VS Code)**: IDE utilizada para o desenvolvimento do código com integração ao Pico SDK.
- **Pico SDK**: Kit de desenvolvimento de software utilizado para programar o Raspberry Pi Pico W em linguagem C.
- **Monitor serial do VS Code**: Ferramenta utilizada para monitorar o fenômeno de bouncing nos botões e validar o funcionamento do debouncing via software.

## Objetivos

1. Compreender o funcionamento e a aplicação de interrupções em microcontroladores.
2. Identificar e corrigir o fenômeno do bouncing em botões por meio de debouncing via software.
3. Manipular e controlar LEDs comuns e LEDs endereçáveis WS2812.
4. Fixar o estudo do uso de resistores de pull-up internos em botões de acionamento.
5. Desenvolver um projeto funcional que combine hardware e software.

## Instruções de uso

1. **Clonar o Repositório**:

```bash
git clone https://github.com/bigodinhojf/interrupt_deboucing_task.git
```

   

2. **Compilar e Carregar o Código**:
   No VS Code, configure o ambiente e compile o projeto com os comandos:

```bash	
cmake -G Ninja ..
ninja
```

3. **Interação com o Sistema**:
   - Conecte a placa ao computador.
   - Clique em run usando a extensão do raspberry pi pico.
   - Utilize os botões para incrementar e decrementar os números exibidos na matriz de LEDs.

## Vídeo de apresentação

O vídeo apresentando o projeto pode ser assistido [clicando aqui](https://youtu.be/vi-1jh6bHWo).

## Aluno e desenvolvedor do projeto

<a href="https://github.com/bigodinhojf">
        <img src="https://github.com/bigodinhojf.png" width="150px;" alt="João Felipe"/><br>
        <sub>
          <b>João Felipe</b>
        </sub>
</a>

## Licença

Este projeto está licenciado sob a licença MIT.
