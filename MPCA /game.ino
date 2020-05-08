#include <MaxMatrix.h>
MaxMatrix lm(7, 5, 6, 4);      //creating an instance of the matrix 7, 5,6 are the pins that correspond to CIN, CLK and DIN, 4 is the maximum number of odules in use
void setup()
{
	lm.init();					//initializing the matrix
	lm.setIntensity(1);			//setting the brightness to 1 (can be anywhere between 0 and 15)
	pinMode(2,INPUT_PULLUP);	//setting pin 2 as the input pin
}

int main()
{
	setup();
	setRow(0,0,7,true);												//lighting up the bottom two rows as the base of the stack
	setRow(1,0,7,true);	
	byte len=5;														//setting the initial length of the block
	byte row=2;														//setting the initial row
	byte s=move(len,row,15);										//handles each move, it returns the starting edge of the block when the user hits the button
	byte prev_s=s;													//storing the start edge of the base of the stack
	for(byte i=0;i<40;++i)											//delay loop (had to use a delay loop cuz delay(int) doesn't work outside void loop() for some weird reason it just causes the code to crash)
		delayMicroseconds(32767);
	++row;
	while(len>0 && row <31)											//loop runs until the user loses or reaches the top
	{
		s=move(len,row,15);											//calling the move function
		if(prev_s != s)												//checking if the start edge is the same as the edge of the stack
		{
			byte diff= prev_s>s? prev_s - s : s - prev_s;			//if they aren't the same, calculating the amount to drop off
			len = len - diff;										//changing the length of the block appropriately
		}
		for(byte i=0;i<40;++i)										//delay loop
			delayMicroseconds(32767);
		prev_s = s < prev_s ? prev_s : s;							//changing the edge of the stack appropriately
		setRow(row,0,7,false);										//switching off all the LEDs in the row
		if(len>0 && len < 8)										//this check is necessary. code crashes without it, cuz the setRow code isn't perfect
			setRow(row,prev_s,prev_s + len - 1,true);
		else
			len=0;													//the while loop doesn't seem to terminate without this. it just crashes even though the conditions are correct
		++row;														//incrementing the row
	}
	lm.clear();														//switching off all LEDs
	if(row==31)
		you_win();													//displaying the appropriate message
	else
		you_lose();
	return 1;
}

byte move(byte len, byte row, byte d)
{
	bool flag = false;
	bool side = true;												//decides the side the oscillation starts on true -> left to right & false -> right to left;
	byte s = 0;														//start point of the block is column 0
	byte e = len-1;													//edge of the block is the length -1
	int pushButton;
	while(flag == false)											//loop runs until the user hits the button
	{
		pushButton = digitalRead(2);								//checking if the user has hit the button, this check happens 4 times every time the loop runs to ensure that a button press isn't missed
		if(pushButton == LOW)										//if the button is pressed
		{
			flag = true;
			break;
		}
		setRow(row,s,e,true);										//switching on the LEDs from s to e
		pushButton = digitalRead(2);								//button press check
		if(pushButton == LOW)
		{
			flag = true;
			break;
		}
		if(side==true && e<7)										//if the block hasn't reached the right edge while moving towards the right, the position of the block is incremented
		{
			++s;
			++e;
		}
		else if(side==false && s>0)									//if the block is moving towards the left and hasn't reached the left edge, the position is decrememnted
		{
			--s;
			--e;
		}
		else if(e==7)												//if it is at the right edge, the direction is reversed and position decremented
		{
			side=false;
			--s;
			--e;
		}
		else if(s==0)												//if it is at the left edge, the direction is reversed and the position incremented
		{
			side=true;
			++s;
			++e;
		}
		pushButton = digitalRead(2);								//button press check
		if(pushButton==LOW)
		{
			flag = true;
		}
		for(byte i=0;i<d;++i)										//delay loop
			delayMicroseconds(32767);
		pushButton = digitalRead(2);								//button press check
		if(pushButton==LOW)
		{
			flag = true;
		}
		setRow(row,0,7,false);										//switching off the row
	}
	setRow(row,s,e,true);											//displaying the spot where the user stops the block
	return s;														//returning the staarting edge
}

void mapping(byte mr, byte mc, byte* r, byte* c)					//code is pretty straightforward. refer disp.pdf
{
	switch(mr)
	{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		{
			*r = 7 - mr;
			*c = mc;
			break;
		}
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		{
			*r = 15 - mr;
			*c = mc + 8;
			break;
		}
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
		case 22:
		case 23:
		{
			*r = 23 - mr;
			*c = mc + 16;
			break;
		}
		case 24:
		case 25:
		case 26:
		case 27:
		case 28:
		case 29:
		case 30:
		case 31:
		{
			*r = 31 - mr;
			*c = mc + 24;
			break;
		}
		default:
		{
			*r = -1;
			*c = -1;
			break;
		}
	}
}

void setRow(byte mr,byte s, byte e, bool value)								///function that switches on/off all the LEDs between s and e on row mr if value is true, it switches them on and off if it's false
{
	if(s>=0 && s<=e && e<8)													//checking if s and e are possible values
	{
		for(byte j=s;j<=e;++j)												//iterating throught the respective LEDs
		{
			byte r,c;
			mapping(mr,j,&r,&c);											//calculating the actual row and column values
			lm.setDot(c,r,value);											//switching on/off the LED
		}
	}
}

void you_win()																//calls all the letter display functions sequentially with appropriate delays
{
	for(byte ij=0;ij<8;++ij)
	{
		lm.clear();
		y(ij);
		for(byte ik=0;ik<2;++ik)
			delayMicroseconds(32767);
	}
	for(byte ij=8;ij<16;++ij)
	{
		lm.clear();
		y(ij);
		o(ij-8);
		for(byte ik=0;ik<2;++ik)
			delayMicroseconds(32767);
	}
	for(byte ij=16;ij<24;++ij)
	{
		lm.clear();
		y(ij);
		o(ij-8);
		u(ij-16);
		for(byte ik=0;ik<2;++ik)
			delayMicroseconds(32767);
	}
	for(byte ij=24;ij<32;++ij)
	{
		lm.clear();
		y(ij);
		o(ij-8);
		u(ij-16);
		for(byte ik=0;ik<2;++ik)
			delayMicroseconds(32767);
	}
	for(byte ij=32;ij<40;++ij)
	{
		lm.clear();
		y(ij);
		o(ij-8);
		u(ij-16);
		w(ij-32);
		for(byte ik=0;ik<2;++ik)
			delayMicroseconds(32767);
	}
	for(byte ij=32;ij<40;++ij)
	{
		lm.clear();
		o(ij);
		u(ij-8);
		w(ij-24);
		i(ij-32);
		for(byte ik=0;ik<4;++ik)
			delayMicroseconds(32767);
	}
	for(byte ij=32;ij<40;++ij)
	{
		lm.clear();
		u(ij);
		w(ij-16);
		i(ij-24);
		n(ij-32);
		for(byte ik=0;ik<2;++ik)
			delayMicroseconds(32767);
	}
	for(byte ij=32;ij<40;++ij)
	{
		lm.clear();
		w(ij-8);
		i(ij-16);
		n(ij-24);
		for(byte ik=0;ik<4;++ik)
			delayMicroseconds(32767);
	}
	for(byte ij=32;ij<40;++ij)
	{
		lm.clear();
		w(ij);
		i(ij-8);
		n(ij-16);
		for(byte ik=0;ik<2;++ik)
			delayMicroseconds(32767);
	}
	for(byte ij=32;ij<48;++ij)
	{
		lm.clear();
		i(ij);
		n(ij-8);
		for(byte ik=0;ik<2;++ik)
			delayMicroseconds(32767);
	}
}

void you_lose()
{
	for(byte ij=0;ij<8;++ij)
	{
		lm.clear();
		y(ij);
		for(byte ik=0;ik<2;++ik)
			delayMicroseconds(32767);
	}
	for(byte ij=8;ij<16;++ij)
	{
		lm.clear();
		y(ij);
		o(ij-8);
		for(byte ik=0;ik<2;++ik)
			delayMicroseconds(32767);
	}
	for(byte ij=16;ij<24;++ij)
	{
		lm.clear();
		y(ij);
		o(ij-8);
		u(ij-16);
		for(byte ik=0;ik<2;++ik)
			delayMicroseconds(32767);
	}
	for(byte ij=24;ij<32;++ij)
	{
		lm.clear();
		y(ij);
		o(ij-8);
		u(ij-16);
		for(byte ik=0;ik<2;++ik)
			delayMicroseconds(32767);
	}
	for(byte ij=32;ij<40;++ij)
	{
		lm.clear();
		y(ij);
		o(ij-8);
		u(ij-16);
		l(ij-32);
		for(byte ik=0;ik<2;++ik)
			delayMicroseconds(32767);
	}
	for(byte ij=32;ij<40;++ij)
	{
		lm.clear();
		o(ij);
		u(ij-8);
		l(ij-24);
		o(ij-32);
		for(byte ik=0;ik<2;++ik)
			delayMicroseconds(32767);
	}
	for(byte ij=32;ij<40;++ij)
	{
		lm.clear();
		u(ij);
		l(ij-16);
		o(ij-24);
		s(ij-32);
		for(byte ik=0;ik<2;++ik)
			delayMicroseconds(32767);
	}
	for(byte ij=32;ij<40;++ij)
	{
		lm.clear();
		l(ij-8);
		o(ij-16);
		s(ij-24);
		e(ij-32);
		for(byte ik=0;ik<2;++ik)
			delayMicroseconds(32767);
	}
	for(byte ij=32;ij<40;++ij)
	{
		lm.clear();
		l(ij);
		o(ij-8);
		s(ij-16);
		e(ij-24);
		for(byte ik=0;ik<2;++ik)
			delayMicroseconds(32767);
	}
	for(byte ij=32;ij<40;++ij)
	{
		lm.clear();
		o(ij);
		s(ij-8);
		e(ij-16);
		for(byte ik=0;ik<2;++ik)
			delayMicroseconds(32767);
	}
	for(byte ij=32;ij<40;++ij)
	{
		lm.clear();
		s(ij);
		e(ij-8);
		for(byte ik=0;ik<2;++ik)
			delayMicroseconds(32767);
	}
		for(byte ij=32;ij<48;++ij)
	{
		lm.clear();
		e(ij);
		for(byte ik=0;ik<2;++ik)
			delayMicroseconds(32767);
	}
}

void e(byte row)
{
	byte nr;
	byte nc;
	mapping(row,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row,2,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row,3,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row,4,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-1,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-2,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-3,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-3,2,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-3,3,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-3,4,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-4,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-5,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,2,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,3,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,4,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,5,&nr,&nc);
	lm.setDot(nc,nr,true);
}

void i(byte row)
{
	byte nr;
	byte nc;
	mapping(row,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row,2,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row,3,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row,4,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-1,3,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-2,3,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-3,3,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-4,3,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-5,3,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,2,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,3,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,4,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,5,&nr,&nc);
	lm.setDot(nc,nr,true);
}

void l(byte row)
{
	byte nr;
	byte nc;
	mapping(row,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-1,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-2,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-3,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	lm.setDot(nc,nr,true);
	mapping(row-4,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-5,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,2,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,3,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,4,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,5,&nr,&nc);
	lm.setDot(nc,nr,true);
}

void n(byte row)
{
	byte nr;
	byte nc;
	mapping(row,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-1,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-1,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-2,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-2,2,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-2,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-3,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-3,3,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-3,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-4,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-4,4,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-4,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-5,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-5,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,5,&nr,&nc);
	lm.setDot(nc,nr,true);
}

void o(byte row)
{
	byte nr;
	byte nc;
	mapping(row,2,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row,3,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row,4,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-1,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-1,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-2,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-2,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-3,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-3,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-4,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-4,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-5,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-5,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,2,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,3,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,4,&nr,&nc);
	lm.setDot(nc,nr,true);
}

void s(byte row)
{
	byte nr;
	byte nc;
	mapping(row,2,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row,3,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row,4,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-1,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-2,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-3,2,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-3,3,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-3,4,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-4,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-5,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,2,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,3,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,4,&nr,&nc);
	lm.setDot(nc,nr,true);
}

void u(byte row)
{
	byte nr;
	byte nc;
	mapping(row,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-1,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-1,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-2,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-2,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-3,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-3,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-4,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-4,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-5,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-5,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,2,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,3,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,4,&nr,&nc);
	lm.setDot(nc,nr,true);
}

void w(byte row)
{
	byte nr;
	byte nc;
	mapping(row,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-1,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-1,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-2,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-2,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-3,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-3,3,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-3,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-4,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-4,3,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-4,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-5,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-5,2,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-5,4,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-5,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,5,&nr,&nc);
	lm.setDot(nc,nr,true);
}

void y(byte row)
{
	byte nr;
	byte nc;
	mapping(row,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-1,1,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-1,5,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-2,2,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-2,4,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-3,3,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-4,3,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-5,3,&nr,&nc);
	lm.setDot(nc,nr,true);
	mapping(row-6,3,&nr,&nc);
	lm.setDot(nc,nr,true);
}