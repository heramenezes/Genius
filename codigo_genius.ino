//definindo o valor das leds com seus respectivos pinos
#define led_verde 3
#define led_vermelho 5
#define led_azul 7
#define led_amarelo 9

//definindo o valor dos botões das leds com seus respectivos pinos
#define botao_verde 2
#define botao_vermelho 4
#define botao_azul 6
#define botao_amarelo 8

//definindo variaveis
int buzzer = 13;

int sequencia[11];

bool vivo = false;

int nivel = 0;

int pressed = -1;

//definindo a frequência (tom) das notas musicais
const int notaDo = 262; // Dó
const int notaRe = 294; // Ré
const int notaMi = 330; // Mi
const int notaFa = 349; // Fá 
const int notaSol = 392;// Sol


//fazendo o setup das leds com seus respectivos botões de ação e do piezo
void setup(){
  pinMode(led_verde, OUTPUT);
  pinMode(botao_verde, INPUT_PULLUP);
  
  pinMode(led_vermelho, OUTPUT);
  pinMode(botao_vermelho, INPUT_PULLUP);
  
  pinMode(led_azul, OUTPUT);
  pinMode(botao_azul, INPUT_PULLUP);
  
  pinMode(led_amarelo, OUTPUT);
  pinMode(botao_amarelo, INPUT_PULLUP);
  
  pinMode(buzzer, OUTPUT);
  
  Serial.begin(9600);
}

void acender (int pos){
  
  if (pos == 0)digitalWrite(led_verde, HIGH);
  else if (pos == 1)digitalWrite(led_vermelho, HIGH);
  else if (pos == 2)digitalWrite(led_azul, HIGH);
  else if (pos == 3)digitalWrite(led_amarelo, HIGH);
    
  delay(980);
  
  digitalWrite(led_verde, LOW);
  digitalWrite(led_vermelho, LOW);
  digitalWrite(led_azul, LOW);
  digitalWrite(led_amarelo, LOW);
}

bool apertado (){
  
  Serial.print("G - ");
  Serial.print(digitalRead(botao_verde));
  Serial.print(" R - ");
  Serial.print(digitalRead(botao_vermelho));
  Serial.print(" B - ");
  Serial.print(digitalRead(botao_azul));
  Serial.print(" Y - ");
  Serial.print(digitalRead(botao_amarelo));
  Serial.print("\n");
  
  return !(digitalRead(botao_verde) == LOW || digitalRead(botao_vermelho) == LOW || digitalRead(botao_azul) == LOW || digitalRead(botao_amarelo) == LOW);
}

int convertendo_apertador (){
  
  if (digitalRead(botao_verde) == LOW){
    return 0;
  }
  else if (digitalRead(botao_vermelho) == LOW){
    return 1;
  }
  else if (digitalRead(botao_azul) == LOW){
    return 2;
  }
  else if (digitalRead(botao_amarelo) == LOW){
    return 3;
  }
  
}

void loop(){
  
  // ANIMACAO INICIAL
  if(!vivo || nivel>9){
    
    randomSeed(analogRead(1));
    
    nivel = 0;
    vivo = true;
    
    digitalWrite(led_verde, HIGH);
    digitalWrite(led_vermelho, HIGH);
    digitalWrite(led_azul, HIGH);
    digitalWrite(led_amarelo, HIGH);
    
    //Dó
    tone(buzzer, notaDo, 300);//Frequência e duração da nota Dó
    delay(300);//Intervalo de 300 milissegundos
    noTone(buzzer);

  
  
    //Ré
    tone(buzzer, notaRe, 300);//Frequência e duração da nota Ré
    delay(300);//Intervalo de 300 milissegundos
    noTone(buzzer);

    //Mi
    tone(buzzer, notaMi, 300);//Frequência e duração da nota Mi
    delay(300);//Intervalo de 300 milissegundos
    noTone(buzzer);

     //Fá
    tone(buzzer, notaFa, 300);//Frequência e duração da nota Fá
    delay(300);//Intervalo de 300 milissegundos
    noTone(buzzer);
    
    delay(1000);
        
    digitalWrite(led_verde, LOW);
    digitalWrite(led_vermelho, LOW);
    digitalWrite(led_azul, LOW);
    digitalWrite(led_amarelo, LOW);
  }
  
  if(nivel<12){
    sequencia [nivel] = random(0, 4);
  }
  
  nivel = nivel + 1;
    
  for(int i = 0; i < nivel; i++){
    delay(1000);
    acender(sequencia[i]);
  }
  
  for (int j = 0; j<nivel; j++){
    
    Serial.write("entrada1\n");
    while (apertado());
    Serial.write("entrada2\n");
    
    pressed = convertendo_apertador();
    acender(pressed);
    
    while(!apertado());
    
    if(pressed != sequencia[j]){
     vivo = false;
     j = nivel;
    }
  }
}


























