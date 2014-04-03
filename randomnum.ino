const byte NUMS[][8]={{LOW,LOW,LOW,HIGH,HIGH,LOW,LOW,LOW},{HIGH,HIGH,LOW,HIGH,HIGH,HIGH,HIGH,LOW},{HIGH,LOW,LOW,HIGH,LOW,HIGH,LOW,LOW}};  // 这个二位数组存储所有数字的显示方法
const byte PINS[]={1,2,3,4,5,6,7,8,9,13}; //这样设置就很好更改pin了
const byte REFRESHRATE=10; //每10毫秒增加一次 
const byte COUNT=1000/REFRESHRATE; //每1秒显示一个新数字 
int now=0; // 当前显示的数字
int time=0; //时间计数器
int paused=false; //当前状态
int pressed=false; //是否被按下

void setup() {
  for (int i=0;i<8;i++){
     pinMode(PINS[i], OUTPUT);
  }
  pinMode(PINS[8],INPUT);
}

void displayNum(int num){// 输入一个数，在数码管上显示之
    if(num<0||num>2) return; //输入错误，直接返回
    for(int i=0;i<8;i++){
          digitalWrite(PINS[i],NUMS[num][i]);
    }
}

void loop() {
  if(digitalRead(PINS[8]==HIGH)){
      pressed=true;
  }else if(pressed==true){
      paused=!paused;
      pressed=false;
  }
  if(time>=COUNT && !paused){ // 每秒更新一次，只有低电平才更新 
      displayNum(now++);
      if(now==3) now=0;
      time=0;
  }
  time++;
  delay(REFRESHRATE);
}
