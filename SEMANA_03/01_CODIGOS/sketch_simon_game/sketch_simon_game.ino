// declara as variaveis dos leds e botoes
int button_verde = 27;
int button_amarelo = 33;
int button_vermelho = 23;
int button_azul = 26;
int button_reset = 22;
int led_verde = 14;
int led_amarelo = 25;
int led_vermelho = 16;
int led_azul = 32;
int zero[4]; //cria um vetor vazio para reset
int sequencia_pc[4]; // cria um vetor para armazenar a sequencia aleatoria
int sequencia_jogador[4]; // cria um vetor para armazenar a sequencia do jogador
int nivel = 0; // declara a varivel para controlar o nivel do jogador

void setup() 
{  
  Serial.begin(9600);
  // define os LEDs como saídas
  pinMode(led_verde, OUTPUT); 
  pinMode(led_vermelho, OUTPUT); 
  pinMode(led_amarelo, OUTPUT); 
  pinMode(led_azul, OUTPUT); 
  // define os botões como entradas com resistores de pull-up internos ativados
  pinMode(button_verde, INPUT_PULLUP); 
  pinMode(button_vermelho, INPUT_PULLUP); 
  pinMode(button_amarelo, INPUT_PULLUP); 
  pinMode(button_azul, INPUT_PULLUP); 
  pinMode(button_reset, INPUT_PULLUP); 
}

void loop() 
{
  // se o nível do jogador é 0, chama a função que cria uma sequencia nova
  if(nivel == 0){
    criar_sequencia();
  }
  // se o nível do jogador for 1 ou maior, chama as funções que mostram a sequencia e lê o input do jogador
  if (nivel >= 1){
    ler_sequencia();
    ler_input_jogador();
  }   
}

void criar_sequencia()
{
  // define a o número aleatório para a função random()
  randomSeed(millis()); 
  // cria uma nova sequência de 4 números aleatórios de 1 a 4 para o vetor
  for (int i = 0; i < 4; i++){
    sequencia_pc[i]  = random(1, 5);
    // converte os números gerados para cada led específico
    if(sequencia_pc[i] == 1){
      sequencia_pc[i] = led_vermelho;
    }
    if(sequencia_pc[i] == 2){
      sequencia_pc[i] = led_verde;
    }
    if(sequencia_pc[i] == 3){
      sequencia_pc[i] = led_amarelo;
    }
    if(sequencia_pc[i] == 4){
      sequencia_pc[i] = led_azul;
    }
    nivel = 1; // define o nível do jogador com 1
  }
}

void ler_sequencia()
{
  // mostra a sequencia até o nível do jogador no momento
  for(int i = 0; i < nivel; i++){
    digitalWrite(sequencia_pc[i], 1);
    delay(1000);
    digitalWrite(sequencia_pc[i], 0);
    delay(400);
  }
}

void define_sequencia(int jogador_led, int i){
  // executa o led que o jogador clicou
  digitalWrite(jogador_led, 1);
  delay(500);
  digitalWrite(jogador_led, 0);
  // inclui na sequencia do jogador
  sequencia_jogador[i] = jogador_led;
}

void ler_input_jogador()
{
  int jogador_led; 
  int verify = 0; 
  // recebe os inputs do jogador até o nível que ele está
  for(int i = 0; i < nivel; i++){
    while(verify == 0){
      // se o botão reset for clicado, volta para o início
      if(digitalRead(button_reset)  == 1){
        errado(); // função que volta o jogo do início quando o jogador reseta ou erra a sequencia
        Serial.println("RESET");
        return; 
      }
      // verifica o led clicado e atribui para a sequencia do jogador
      else if(digitalRead(button_vermelho)  == 1){
        jogador_led = led_vermelho;
        define_sequencia(jogador_led, i);
        // verifica se a sequencia do jogador é igual a sequencia correta
        if(sequencia_jogador[i] != sequencia_pc[i]){
          errado(); 
          return;
        }
        break; // finaliza o loop para aguardar ó proximo input do jogador
      } 
      else if(digitalRead(button_verde) == 1){
        jogador_led = led_verde;
        define_sequencia(jogador_led, i);
        if(sequencia_jogador[i] != sequencia_pc[i]){
          errado();
          return;
        }
        break;
      }
      else if(digitalRead(button_amarelo) == 1){
        jogador_led = led_amarelo;
        define_sequencia(jogador_led, i);
        if(sequencia_jogador[i] != sequencia_pc[i]){
          errado();
          return;
        }
        break;
      }
      else if(digitalRead(button_azul) == 1){
        jogador_led = led_azul;
        define_sequencia(jogador_led, i);
        if(sequencia_jogador[i] != sequencia_pc[i])
        {
          errado();
          return;
        }
        break;
      }
    }
  }
  correto(); // função executada quando o jogador acerta a sequencia
}

void correto()
{
  int count = 1;
  // se o nível do jogador é menor que 5, aumenta o nível
  if(nivel < 5){
    nivel++;
  }
  // se o nível do jogador é igual a 5, mostra que ele venceu o jogo
  if(nivel == 5){
  // executa os leds piscando 2 vezes
    while(count <= 3){
      delay(120);
      digitalWrite(led_vermelho, 1);
      digitalWrite(led_verde, 0);
      digitalWrite(led_amarelo, 0);
      digitalWrite(led_azul, 0);
      delay(120);
      digitalWrite(led_vermelho, 0);
      digitalWrite(led_verde, 1);
      digitalWrite(led_amarelo, 0);
      digitalWrite(led_azul, 0);
      delay(120);
      digitalWrite(led_vermelho, 0);
      digitalWrite(led_verde, 0);
      digitalWrite(led_amarelo, 1);
      digitalWrite(led_azul, 0);
      delay(120);
      digitalWrite(led_vermelho, 0);
      digitalWrite(led_verde, 0);
      digitalWrite(led_amarelo, 0);
      digitalWrite(led_azul, 1);
      count++;
    }
    nivel = 0; // volta o nível para 0 para iniciar um jogo novo
  }
  delay(120);
  digitalWrite(led_vermelho, 0);
  digitalWrite(led_verde, 0);
  digitalWrite(led_amarelo, 0);
  digitalWrite(led_azul, 0);
  delay(700);
}

void errado(){
  int erro = 1; // variavel de controle
  // executa os leds piscando 2 vezes
  while(erro <= 2){
    digitalWrite(led_vermelho, 1);
    digitalWrite(led_verde, 1);
    digitalWrite(led_amarelo, 1);
    digitalWrite(led_azul, 1);
    delay(350);
    digitalWrite(led_vermelho, 0);
    digitalWrite(led_verde, 0);
    digitalWrite(led_amarelo, 0);
    digitalWrite(led_azul, 0);
    delay(350);
    erro++;
}
  nivel = 0; // define o nível do jogador para 0 para iniciar um novo jogo 
  // armazena um vetor vazio na sequencia do jogador
  for(int i = 0; i < 5; i++){
    sequencia_jogador[i] =  zero[i];
  }
}