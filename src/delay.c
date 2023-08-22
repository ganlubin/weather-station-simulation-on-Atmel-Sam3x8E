void delay(int Value){
  for(int i = 0; i < Value; i++){
    asm("nop");
  }
}
