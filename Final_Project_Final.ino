#include <Adafruit_CircuitPlayground.h>

//global variables//////////////////////////////////////////                                      GLOBALVARIABLES
///////////INPUTS
    //button global variables
      int leftButton = 4;/// pin for left button
      int rightButton = 5;// pin for right button
      volatile bool leftFlag = 0;//left interrupt is off
      volatile bool rightFlag = 0;//tight interrupt is off

    //slide switch global variables
      int switchPin = 7;//pin for switch
      volatile bool switchFlag = 0;//switch interrupt is of
      volatile bool switchState = 0;//switch state is off
///////OUTPUTS
    //functions
        //midi song things
          float midi[127];//for calculating the frequency of the play tone
          int A_four = 440; // a is 440 hz...

          // notes defined
            int D=86;
            int F=89;
            int E=88;
            int G=91;
            int B=94;
            int A=93;
            int G2 =79;
          // Arrays to store Scale MIDI pitch sequence
            int thunderstruck[]={D,F,D,F,D,F,D,F,D,F,D,F,E,G,E,G,E,G,E,G,E,G,E,G,D,F,D,F,D,F,D,F,D,F,D,F,E,G,E,G,E,G,E,G,E,G,E,G,B,A,G,A,G,F,E,D,E,D,E,D,B,A,G,A,G,F,E,D,E,D,E,D};
            int miss[1]={G2};

        //return value for level functions
          int r = 0;

////////////////////////SETUP///////////////////////////////                                              SETUP
void setup() {
//starts the board
  CircuitPlayground.begin();

  //button setup
    pinMode(leftButton,INPUT_PULLDOWN);
    pinMode(rightButton,INPUT_PULLDOWN);
    attachInterrupt(digitalPinToInterrupt(leftButton), leftInterrupt , RISING);
    attachInterrupt(digitalPinToInterrupt(rightButton), rightInterrupt , RISING);

  //slide switch setup
    pinMode(switchPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(switchPin), onOff, CHANGE);
  //for song
    generateMIDI();

  //random
    randomSeed(analogRead(0));
}
///////////////LOOP///////////////////////////////////////////////////////////                        START OF LOOP
void loop() {
//is the slide switch on?
if(switchFlag){
  countDown();
  if(r==0){
    //play level 1 function
    levelOne();
  }
if(r ==1){
//play level 2 function
    levelTwo();
}
if(r ==2){
//play level 3 function
    levelThree();
}
if(r ==3){
//play grand victory sequence
    grandVictory();
}
if(r==4){
  CircuitPlayground.clearPixels();
  delay(5);
  switchFlag = 0;
}
}
}/////////////////////////////////                                                                   END OF LOOP           



/////////////////////////////////////////////////////////////////////////             FUNCTIONS!!!!
                                                                                        //Interrupts
                                                                                        //Light Sequences
                                                                                        //Levels

  //Interrupts
    //Generate MIDI
    //Slide Switch
    //Button Interrupts
    //Button Check

      // Generate MIDI
        //This function calculates frequency values for MIDI pitch numbers 0 - 127.
        // These values are stored in an array where the index at the MIDI pitch value will retrieve the corresponding frequency to set a speaker
        // MIDI 60 is C4 on the piano, and corresponds to 261.62 Hz
        // Each digit up or down corresponds to playing the key that many steps above or below on the piano
        // adapted from https://subsynth.sourceforge.net/midinote2freq.html
          void generateMIDI()
          {
            for (int x = 0; x < 127; ++x)
            {
              midi[x] = (A_four / 32.0) * pow(2.0, ((x - 9.0) / 12.0));
              Serial.println(midi[x]);
            }
          }

      //Slide Switch
        //is it on? slide switch interrupt
          void onOff(){
            switchFlag =1;
          }

      //Button Interrupts
        //turns interrupt flag on when interrupts are triggered
          void leftInterrupt(){
            leftFlag = 1;
            }

          void rightInterrupt(){
            rightFlag = 1;
            }
      //BUTTON CHECK
          //if true functions for left and right sides
            void leftYes(){
              if(leftFlag){CircuitPlayground.setPixelColor(2,0,255,0); }
              delay(500);
              CircuitPlayground.setPixelColor(2,0,0,0);
              if(!leftFlag){CircuitPlayground.setPixelColor(2,0,0,0);;}
              delay(5);
            }

            void rightYes(){
              if(rightFlag){CircuitPlayground.setPixelColor(7,0,255,0); }
              delay(500);
              CircuitPlayground.setPixelColor(7,0,0,0);
              if(!rightFlag){CircuitPlayground.setPixelColor(7,0,0,0);;}
              delay(5);
            }



  //Light Sequences
    //Main Light Sequence
    //Countdown
    //Game over
    //Victory
    //Grand Victory

      //Main Light Sequence
        //Left and Right Approaching Lights                                               LEFT APPROACHING
          //Blinks closer and closer on the side towards the goal LED till you have to press the button 
            void leftApproaching(int delayTime){
              for(int j=0;j<2;j++){

                for(int i=0; i<255;i++){
                  CircuitPlayground.setPixelColor(j,0,0,i);
                  delay(delayTime/1000);
                }
                for(int i=0; i<255;i++){
                  CircuitPlayground.setPixelColor(j,0,i,255);
                  delay(delayTime/1000);
                }
                for(int i=255; i>0;i--){
                  CircuitPlayground.setPixelColor(j,0,i,255);
                  delay(delayTime/1000);
                }
                for(int i=255; i>0;i--){
                  CircuitPlayground.setPixelColor(j,0,0,i);
                  delay(delayTime/1000);
                }
                CircuitPlayground.setPixelColor(j,0,0,0);
                delay(delayTime);
              }
            }

            void rightApproaching(int delayTime){
              for(int j=10;j>=8;j--){
                for(int i=0; i<255;i++){
                  CircuitPlayground.setPixelColor(j,0,0,i);
                  delay(delayTime/1000);
                }
                for(int i=0; i<255;i++){
                  CircuitPlayground.setPixelColor(j,0,i,255);
                  delay(delayTime/1000);
                }
                for(int i=255; i>0;i--){
                  CircuitPlayground.setPixelColor(j,0,i,255);
                  delay(delayTime/1000);
                }
                for(int i=255; i>0;i--){
                  CircuitPlayground.setPixelColor(j,0,0,i);
                  delay(delayTime/1000);
                }
                CircuitPlayground.setPixelColor(j,0,0,0);
                delay(delayTime);
              }
            }


      //Countdown
        // a ready, set, go light sequence
          void countDown(){
            CircuitPlayground.setPixelColor(0,255,0,0);
            CircuitPlayground.setPixelColor(9,255,0,0);
            delay(1000);
            CircuitPlayground.setPixelColor(0,255,255,0);
            CircuitPlayground.setPixelColor(9,255,255,0);
            delay(1000);
            CircuitPlayground.setPixelColor(0,0,255,0);
            CircuitPlayground.setPixelColor(9,0,255,0);
            delay(1000); 
            CircuitPlayground.setPixelColor(0,0,0,0);
            CircuitPlayground.setPixelColor(9,0,0,0);
            delay(1000);     
          }
      //Game Over
        void gameOver(){
          CircuitPlayground.clearPixels();
        }
      //Victory
        //blinks pretty purple lights for use when you pass a level
          void victory(){
            for(int j=0;j<4;j++){
              for(int i=0; i<10;i++){
                CircuitPlayground.setPixelColor(i,127,0,255);
              }
              delay(50);
              for(int i=0; i<10;i++){
                CircuitPlayground.setPixelColor(i,0,0,0);
              }
              delay(50);
              for(int i=0; i<10;i++){
                CircuitPlayground.setPixelColor(i,255,0,127);
              }
              delay(50);
              for(int i=0; i<10;i++){
                CircuitPlayground.setPixelColor(i,0,0,0);
              }
              delay(50);
            }
          }

      //Grand Victory
        //blinks pretty blue lights for use when you win the game
          int grandVictory(){
            for(int j=0;j<4;j++){
              for(int i=0; i<10;i++){
                CircuitPlayground.setPixelColor(i,0,178,255);
              }
              delay(50);
              for(int i=0; i<10;i++){
                CircuitPlayground.setPixelColor(i,0,0,0);
              }
              delay(50);
              for(int i=0; i<10;i++){
                CircuitPlayground.setPixelColor(i,0,178,255);
              }
              delay(50);
              for(int i=0; i<10;i++){
                CircuitPlayground.setPixelColor(i,0,0,0);
              }
              delay(50);
              Serial.println("YAY!!!!!!");
              }
              return r=0;
            }

  //LEVELS
    //Level One
    //Level Two
    //Level Three

      //Level One
        //randomly choses a side for an led to indicate how soon you need to press the LED, then if you press it on time you get a point,
        //if you don't you get a strike, three strikes and you have to start over, if you get 10 points you get to move to the next level,
        //each correct LED is worth one point and will light up and make the corresponding sound from the array
          int levelOne(){
            int v=0;
            int j=0;//number of strikes set to zero
            int p=0;//points
            int levelUpNum = 10;
            Serial.println("Level One (10 points to win level)");
            if(p<levelUpNum){
            for(int i=0; i<levelUpNum;i++){

              //for the strikes you have accumulated
              if(j<3){
                //picks which side the LED will go on
                int randomSide =random(0,2);

                int delayTime = 100;//sets up delay time for playing song notes

                //left side LEDs
                if(randomSide == 0){
                  leftApproaching(100);
                  delay(100);
                  //buttonCheck();
                    if(leftFlag){
                      leftYes();
                      CircuitPlayground.playTone(midi[thunderstruck[i]], delayTime);
                      delay(.1); 
                      p++;
                      Serial.println("points:");
                      Serial.print(p); 
                      Serial.print('\n');       
                    }
                    //buttonCheck();
                    if(!leftFlag){
                    j++;
                      CircuitPlayground.setPixelColor(2,255,0,0);
                      CircuitPlayground.playTone(midi[miss[0]], 1000);
                      //delay(100);
                      CircuitPlayground.setPixelColor(2,0,0,0);
                      i=0;
                    }
                }
                //right side LEDs
                if(randomSide == 1){
                  rightApproaching(100);
                  delay(100);
                  //buttonCheck();
                    if(rightFlag){
                      rightYes();
                      CircuitPlayground.playTone(midi[thunderstruck[i]], delayTime);
                      delay(.1);
                      p++;
                      Serial.println("points:");
                      Serial.print(p); 
                      Serial.print('\n');         
                    }
                    //buttonCheck();
                    if(!rightFlag){
                      j++;
                      CircuitPlayground.setPixelColor(7,255,0,0);
                      CircuitPlayground.playTone(midi[miss[0]], 1000);
                      //delay(100);
                      CircuitPlayground.setPixelColor(7,0,0,0);
                      i=0;
                    }
                }
                rightFlag = 0;
                leftFlag = 0;

                if(j>0){
                  Serial.print('\n');
                  Serial.print("strike: ");
                  Serial.println(j);
                  Serial.print('\n');
                }
              }
              if(j>=3){
                i=levelUpNum;
                Serial.println("game over");
              }
            }
            }
            if(p>=levelUpNum){
            v=1;
            Serial.println("you win!!!");
            victory();
            }
            if(p>=levelUpNum){
              return r=1;}

            else{
              return r=0;
            }
          }

      //Level Two
        //same as level one except you need to get 20 points to move to the next level and it is a little faster
          int levelTwo(){
            int v=0;
            int j=0;//number of strikes set to zero
            int p=0;//points
            int levelUpNum = 20;
            Serial.println("Level Two (20 points to win level)");
            if(p<levelUpNum){
            for(int i=0; i<levelUpNum;i++){

              //for the strikes you have accumulated
              if(j<3){
                //picks which side the LED will go on
                int randomSide =random(0,2);

                int delayTime = 100;//sets up delay time for playing song notes

                //left side LEDs
                if(randomSide == 0){
                  leftApproaching(10);
                  delay(10);
                  //buttonCheck();
                    if(leftFlag){
                      leftYes();
                      CircuitPlayground.playTone(midi[thunderstruck[i]], delayTime);
                      delay(.1); 
                      p++;
                      Serial.println("points:");
                      Serial.print(p); 
                      Serial.print('\n');       
                    }
                    //buttonCheck();
                    if(!leftFlag){
                    j++;
                      CircuitPlayground.setPixelColor(2,255,0,0);
                      CircuitPlayground.playTone(midi[miss[0]], 1000);
                      //delay(100);
                      CircuitPlayground.setPixelColor(2,0,0,0);
                      i=0;
                    }
                }
                //right side LEDs
                if(randomSide == 1){
                  rightApproaching(10);
                  delay(10);
                  //buttonCheck();
                    if(rightFlag){
                      rightYes();
                      CircuitPlayground.playTone(midi[thunderstruck[i]], delayTime);
                      delay(.1);
                      p++;
                      Serial.println("points:");
                      Serial.print(p); 
                      Serial.print('\n');         
                    }
                    //buttonCheck();
                    if(!rightFlag){
                      j++;
                      CircuitPlayground.setPixelColor(7,255,0,0);
                      CircuitPlayground.playTone(midi[miss[0]], 1000);
                      //delay(100);
                      CircuitPlayground.setPixelColor(7,0,0,0);
                      i=0;
                    }
                }
                rightFlag = 0;
                leftFlag = 0;

                if(j>0){
                  Serial.print('\n');
                  Serial.print("strike: ");
                  Serial.println(j);
                  Serial.print('\n');
                }
              }
              if(j>=3){
                i=levelUpNum;
                Serial.println("game over");
              }
            }
            }
            if(p>=levelUpNum){
            v=1;
            Serial.println("you win!!!");
            victory();
            }
            if(p>=levelUpNum){
              return r=2;}

            else{
              return r=1;
            }
          }

      //Level Three
        //same as level two except you need to get 30 points to move to the next level and it is a little faster
          int levelThree(){
            int v=0;
            int j=0;//number of strikes set to zero
            int p=0;//points
            int levelUpNum = 30;
            Serial.println("Level Three (30 points to win level)");
            if(p<levelUpNum){
            for(int i=0; i<levelUpNum;i++){

              //for the strikes you have accumulated
              if(j<3){
                //picks which side the LED will go on
                int randomSide =random(0,2);

                int delayTime = 100;//sets up delay time for playing song notes

                //left side LEDs
                if(randomSide == 0){
                  leftApproaching(1);
                  delay(1);
                  //buttonCheck();
                    if(leftFlag){
                      leftYes();
                      CircuitPlayground.playTone(midi[thunderstruck[i]], delayTime);
                      delay(.1); 
                      p++;
                      Serial.println("points:");
                      Serial.print(p); 
                      Serial.print('\n');       
                    }
                    //buttonCheck();
                    if(!leftFlag){
                    j++;
                      CircuitPlayground.setPixelColor(2,255,0,0);
                      CircuitPlayground.playTone(midi[miss[0]], 1000);
                      //delay(100);
                      CircuitPlayground.setPixelColor(2,0,0,0);
                      i=0;
                    }
                }
                //right side LEDs
                if(randomSide == 1){
                  rightApproaching(1);
                  delay(1);
                  //buttonCheck();
                    if(rightFlag){
                      rightYes();
                      CircuitPlayground.playTone(midi[thunderstruck[i]], delayTime);
                      delay(.1);
                      p++;
                      Serial.println("points:");
                      Serial.print(p); 
                      Serial.print('\n');         
                    }
                    //buttonCheck();
                    if(!rightFlag){
                      j++;
                      CircuitPlayground.setPixelColor(7,255,0,0);
                      CircuitPlayground.playTone(midi[miss[0]], 1000);
                      //delay(100);
                      CircuitPlayground.setPixelColor(7,0,0,0);
                      i=0;
                    }
                }
                rightFlag = 0;
                leftFlag = 0;

                if(j>0){
                  Serial.print('\n');
                  Serial.print("strike: ");
                  Serial.println(j);
                  Serial.print('\n');
                }
              }
              if(j>=3){
                i=levelUpNum;
                Serial.println("game over");
              }
            }
            }
            if(p>=levelUpNum){
            v=1;
            Serial.println("you win!!!");
            victory();
            }
            if(p>=levelUpNum){
              return r=3;}

            else{
              return r=4;
            }
          }


