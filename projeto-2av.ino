int numAtualSorteado = 0; //Número sorteado
int numSorteados[20]; //Array dos números sorteados

int numAtualEscolhido = 0; //Número escolhido pelo jogador
int numEscolhidos[20]; //Array dos números escolhidos

int nivel = 0; //Nível do jogo
int verifica = 0; //Verifica o número
bool sortear = true; //Variável de controle para sortear os números

void setup() {
  //Declara Serial
  Serial.begin(9600); //Definição da velocidade de transmissão

  //Declara os pinos dos botões
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  
  //Declara os pinos dos leds
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  //Função para sortear números
  randomSeed(analogRead(0)); //Ler os pinos analógicos
  delay(3000);
}

//Função para reiniciar o jogo
//Será usada caso o usuário errar a sequência
//Será usada caso o botão de reiniciar seja usado 
void reiniciar () {
  //Escrevendo na porta Digital
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);

  delay(1000);

  //Resetando o jogo
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);

  delay(1000);

  nivel = 0;
  verifica = 0;
  sortear = true;
}

//Função para verificar se a sequÊncia está errada
//Vai ativar o buzzer
//Vai piscar os leds
void EscolhaErrada() {
  for(int i = 0; i <= 3; i++) {
    noTone(12); //Fecha o som
    tone(12, 100); //Difine a frequência do som
    digitalWrite(8, HIGH);
    digitalWrite(10, HIGH);
    delay(100);

    noTone(12); //Fecha o som
    tone(12, 200); //Difine a frequência do som
    digitalWrite(8, LOW);
    digitalWrite(10, LOW);
    delay(100);

    noTone(12); //Fecha o som
    tone(12, 300); //Difine a frequência do som
    digitalWrite(9, HIGH);
    digitalWrite(11, HIGH);
    delay(100);

    noTone(12); //Fecha o som
    tone(12, 400); //Difine a frequência do som
    digitalWrite(9, LOW);
    digitalWrite(11, LOW);
    delay(100);
  }
  noTone(12);

  //Resetar o Array de sequência
  for(int i = 0; i <= 10; i++) {
    numSorteados[i] = 0;
  }

  reiniciar();
}

//Função para mostrar a sequência
void mostrarSequencia() {
  for(int i = 0; i <= nivel; i++) {
    switch(numSorteados[i]) {

      //Liga o led dependendo do número sorteado
      case 1:
      digitalWrite(8, HIGH);
      tone(12, 100);
      delay(500);
      digitalWrite(8, LOW);
      noTone(12);
      delay(500);
      break;

      case 2:
      digitalWrite(9, HIGH);
      tone(12, 200);
      delay(500);
      digitalWrite(9, LOW);
      noTone(12);
      delay(500);
      break;

      case 3:
      digitalWrite(10, HIGH);
      tone(12, 300);
      delay(500);
      digitalWrite(10, LOW);
      noTone(12);
      delay(500);
      break;

      case 4:
      digitalWrite(11, HIGH);
      tone(12, 400);
      delay(500);
      digitalWrite(11, LOW);
      noTone(12);
      delay(500);
      break;
    }
  }
}

//Função para verificar a saída
void verificar(int pinoSaida, int som) {
  //Verifica se o número escolhido é o certo
  if(numAtualEscolhido == numSorteados[verifica]) {
    digitalWrite(pinoSaida, HIGH);
    tone(12, som);
    delay(500);
    digitalWrite(pinoSaida, LOW);
    noTone(12);
    delay(500);
    
    //Verifica o nível
    if(verifica == nivel ) {
      nivel++;
      verifica = 0;
      sortear = true;
    } else {
      verifica++;
    }
  } else {
      EscolhaErrada();
  }
}


void loop() {
  //Verificao nível
  if(nivel != 21) {
    //Sorteia um número para começar o jogo
    if(sortear) {
      numAtualSorteado = random(1,5); //Escolhe um dos leds aleatoriamente
      numSorteados[nivel] = numAtualSorteado;
      mostrarSequencia();
    }

    sortear = false;
    //Verificar os botôes para receber o número e o nível
    if(digitalRead(2) == 0){
      numAtualEscolhido = 1;
      verificar(8,100);
    } else if (digitalRead(3) == 0){
      numAtualEscolhido = 2;
      verificar(9,200);
    } else if (digitalRead(4) == 0){
      numAtualEscolhido = 3;
      verificar(10,300);
    } else if (digitalRead(5) == 0){
      numAtualEscolhido = 4;
      verificar(11,400);
    } else if (digitalRead(6) == 0){
      reiniciar();
    }
  } else {
    reiniciar();
  }
}
