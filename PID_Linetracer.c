int L = 5;
int L1 = 6;
int R = 9;
int R1 = 10;
long sensor_ave;
int sensor_sum;
long sensor[] = {0,0,0,0,0};
int position;
int prop;
int integral = 0;
int deriv = 0;
int last_prop = 0;
float error;
float prev_error;
int left1;
int left2;
int right1;
int right2;
float kp = 1.5;
float ki = 0.0;
float kd = 1;
int p=0;
int k=0;
unsigned long start, finished, elapsed;


void setup()
{
  
}
void loop()
{

sensors_read();
pid_calc();
calc_turn();
motor_drive(right1,right2,left1,left2);
}

void sensors_read()
{
sensor_ave = 0;
sensor_sum = 0;
for(int i=0;i<5;i++)
{
sensor[i] = analogRead(i);
if (sensor[i] < 500)
{
sensor[i] = 0;
}
else
{
sensor[i] = 1;
}

sensor_ave += sensor[i]*i*180;
sensor_sum += sensor[i];
}
if(sensor_sum == 0)
{
 sensor_ave = 360;
 sensor_sum = 1;
}

}
void pid_calc()
{
position = int(sensor_ave/sensor_sum);
prop = position - 360;
integral = integral + prop;
deriv = prop - last_prop;
last_prop = prop;
error = float(prop*kp - integral*ki + deriv*kd);
p=error;
}
void calc_turn()
{
  if(sensor[0]==1&& sensor[1]==1 && sensor[2]==1 && sensor[3]==1 && sensor[4]==1)
 {
   
  error=prev_error;
  
}
else
{
if(error < -255)
{
error = -255;
}
if(error > 255)
{
error = 255;
}
if (error < 0)
{
right1 = 225 + error;
right2 = 0 - error;
left1 = 225;
left2 = 0;
}
else
{
left1 = 225 - error;
left2 = error;
right1 = 225;
right2 = 0;
}
}
}
void motor_drive ( int right1,int right2,int left1,int left2)
{
  start=millis();
  if(((sensor[0])==1 && (sensor[1])==0 && (sensor[2])==0 && (sensor[3])==1 && (sensor[4])==1) || ((sensor[0])==1 && (sensor[1])==1 && (sensor[2])==0 && (sensor[3])==0 && (sensor[4])==1) || ((sensor[0])==1 && (sensor[1])==1 && (sensor[2])==0 && (sensor[3])==1 && (sensor[4])==1) || ((sensor[0])==1 && (sensor[1])==0 && (sensor[2])==0 && (sensor[3])==0 && (sensor[4])==1))
{
 analogWrite(R,225);
 analogWrite(R1,0);
 analogWrite(L,225);
 analogWrite(L1,0);
 
 p=0;

}
finished=millis();
elapsed=finished-start;
while ((sensor[0]==0 && sensor[1]==0 && sensor[2]==0 && sensor[3]==0 && sensor[4]==1) || (sensor[0]==0 && sensor[1]==0 && sensor[2]==0 && sensor[3]==1 && sensor[4]==1) || (sensor[0]==0 && sensor[1]==0 && sensor[2]==1 && sensor[3]==1 && sensor[4]==1) || (sensor[0]==0 && sensor[1]==1 && sensor[2]==1 && sensor[3]==1 && sensor[4]==1) || (sensor[0]==1 && sensor[1]==0 && sensor[2]==1 && sensor[3]==1 && sensor[4]==1) || (sensor[0]==1 && sensor[1]==0 && sensor[2]==0 && sensor[3]==0 && sensor[4]==0) || (sensor[0]==1 && sensor[1]==1 && sensor[2]==0 && sensor[3]==0 && sensor[4]==0) || (sensor[0]==1 && sensor[1]==1 && sensor[2]==1 && sensor[3]==0 && sensor[4]==0) || (sensor[0]==1 && sensor[1]==1 && sensor[2]==1 && sensor[3]==1 && sensor[4]==0) || (sensor[0]==1 && sensor[1]==1 && sensor[2]==1 && sensor[3]==0 && sensor[4]==1))   //00001 00011 00111 01111 10111 10000 11000 11100 11110 11101
{
  if(((sensor[0])==1 && (sensor[1])==0 && (sensor[2])==0 && (sensor[3])==1 && (sensor[4])==1) || ((sensor[0])==1 && (sensor[1])==1 && (sensor[2])==0 && (sensor[3])==0 && (sensor[4])==1) || ((sensor[0])==1 && (sensor[1])==1 && (sensor[2])==0 && (sensor[3])==1 && (sensor[4])==1) || ((sensor[0])==1 && (sensor[1])==0 && (sensor[2])==0 && (sensor[3])==0 && (sensor[4])==1))
            break;

  if(p==0 && elapsed > 2000)
  {
    analogWrite(R,0);
    analogWrite(R1,160);
    analogWrite(L,0);
    analogWrite(L1,160);
    delay(10);
    start=finished==millis();p=error;
  }
  else
  {
    analogWrite(R , right1);
    analogWrite(R1, right2);
    analogWrite(L, left1);
    analogWrite(L1, left2);
  }

}
}
